
#ifndef MUDUO_BASE_SIGNALSLOT_H
#define MUDUO_BASE_SIGNALSLOT_H

#include "Mutex.h"

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <vector>

namespace muduo
{

namespace detail
{

template<typename Callback>
struct SlotImpl;

template<typename Callback>
struct SignalImpl : boost::noncopyable
{
  typedef std::vector<boost::weak_ptr<SlotImpl<Callback> > > SlotList;

  MutexLock mutex_;
  boost::shared_ptr<SlotList> slots_;

  SignalImpl()
    : slots_(new SlotList)
  {
  }

  void copyOnWrite()
  {
    mutex_.assertLocked();
    if (!slots_.unique())
    {
      slots_.reset(new SlotList(*slots_));
    }
    assert(slots_.unique());
  }

  void clean()
  {
    MutexLockGuard lock(mutex_);
    copyOnWrite(); //不是一个对象独占的话进行拷贝
    SlotList& list(*slots_);
    typename SlotList::iterator it(list.begin());
    while (it != list.end())
    {
      if (it->expired())
      {
        it = list.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }

};

template<typename Callback>
struct SlotImpl : boost::noncopyable
{
  typedef SignalImpl<Callback> Data;
  SlotImpl(const boost::shared_ptr<Data>& data, Callback&& cb)
    : data_(data), cb_(cb), tie_(), tied_(false)
  {
  }

  SlotImpl(const boost::shared_ptr<Data>& data, Callback&& cb,
           const boost::shared_ptr<void>& tie)
    : data_(data), cb_(cb), tie_(tie), tied_(true)
  {
  }

  ~SlotImpl()
  {
    boost::shared_ptr<Data> data(data_.lock());
    if (data)
    {
      data->clean();
    }
  }

  boost::weak_ptr<Data> data_; //使用weak_ptr的原因是为了防止在SignalImpl死亡后使用SlotImpl 这两者之间应该是绑定的
  Callback cb_;
  boost::weak_ptr<void> tie_;
  bool tied_;
};

}

/// This is the handle for a slot
///
/// The slot will remain connected to the signal fot in the life time of the
/// returned Slot object (and its copies).
typedef boost::shared_ptr<void> Slot; //接收任意对象

template<typename Signature>
class Signal;

template <typename RET, typename... ARGS>
class Signal<RET(ARGS...)> : boost::noncopyable
{
 private:

  void add(const boost::shared_ptr<SlotImpl>& slot)
  {
    SignalImpl& impl(*impl_);
    {
      MutexLockGuard lock(impl.mutex_);
      impl.copyOnWrite();
      impl.slots_->push_back(slot);
    }
  }

  const boost::shared_ptr<SignalImpl> impl_;

 public:
  typedef std::function<void (ARGS...)> Callback;
  typedef detail::SignalImpl<Callback> SignalImpl;
  typedef detail::SlotImpl<Callback> SlotImpl;

  Signal()
    : impl_(new SignalImpl)
  {
  }

  ~Signal()
  {
  }

  //Slot存在的时间里一直可被call
  Slot connect(Callback&& func)
  {
    boost::shared_ptr<SlotImpl> slotImpl(
        new SlotImpl(impl_, std::forward<Callback>(func)));
    add(slotImpl);
    return slotImpl;
  }
                                                            //这个参数有种自行管理生命周期的感觉
  Slot connect(Callback&& func, const boost::shared_ptr<void>& tie)
  {
    boost::shared_ptr<SlotImpl> slotImpl(new SlotImpl(impl_, func, tie));
    add(slotImpl);
    return slotImpl;
  }

  void call(ARGS&&... args)
  {
    SignalImpl& impl(*impl_);
    boost::shared_ptr<typename SignalImpl::SlotList> slots;
    {
      MutexLockGuard lock(impl.mutex_);
      slots = impl.slots_; ////意味着进行call的时候智能指针计数大于1 即不允许此时插入(防止迭代器失效)
    }
    typename SignalImpl::SlotList& s(*slots);
    for (typename SignalImpl::SlotList::const_iterator it = s.begin(); it != s.end(); ++it)
    {
      boost::shared_ptr<SlotImpl> slotImpl = it->lock();
      if (slotImpl)
      {
        boost::shared_ptr<void> guard;
        if (slotImpl->tied_)
        {
          guard = slotImpl->tie_.lock();
          if (guard)
          {
            slotImpl->cb_(args...);
          }
        }
        else
        {
          slotImpl->cb_(args...);
        }
      }
    }
  }
};

}

#endif // MUDUO_BASE_SIGNALSLOT_H