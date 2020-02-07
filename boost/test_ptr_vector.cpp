#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <boost/ptr_container/ptr_vector.hpp>
#include <chrono>

class Animal
{
public:
    Animal() = default;
    //Animal(const Animal&) = delete;
    //Animal& operator=(const Animal&) = delete;
    virtual ~Animal() = default;

    virtual void speak() const = 0;
};

class Cat
    : public Animal
{
public:
    virtual void speak() const {std::cout << "Meow\n";}
    virtual ~Cat() {std::cout << "destruct Cat\n";}
};

class Dog
    : public Animal
{
public:
    virtual void speak() const {std::cout << "Bark\n";}
    virtual ~Dog() {std::cout << "destruct Dog\n";}
};

class Sheep
    : public Animal
{
public:
    virtual void speak() const {std::cout << "Baa\n";}
    virtual ~Sheep() {std::cout << "destruct Sheep\n";}
};

/*int main()
{
    typedef std::unique_ptr<Animal> Ptr;
    std::vector<Ptr> v;
    v.push_back(Ptr(new Cat));
    v.push_back(Ptr(new Sheep));
    v.push_back(Ptr(new Dog));
    v.push_back(Ptr(new Sheep));
    v.push_back(Ptr(new Cat));
    v.push_back(Ptr(new Dog));
    for (auto const& p : v)
        p->speak();
    std::cout << "Remove all sheep\n";
    v.erase(
        std::remove_if(v.begin(), v.end(),
                       [](Ptr& p)
                           {return dynamic_cast<Sheep*>(p.get());}),
        v.end());
    for (auto const& p : v)
        p->speak();

 boost::ptr_vector<Animal> v;
v.push_back(new Cat);
v.push_back(new Sheep);
v.push_back(new Dog);
v.push_back(new Sheep);
v.push_back(new Cat);
v.push_back(new Dog);
v.push_back(new Sheep);
v.push_back(new Sheep);
for (auto const& p : v)
    p.speak();
std::cout << "Remove all sheep\n";
v.erase(
    std::remove_if(v.begin(), v.end(),
                   [](Animal& p)
                       {return dynamic_cast<Sheep*>(&p);}),
    v.end());
for (auto const& p : v)
    p.speak(); 
}*/

class item{
private:
    int value;
public:
    explicit item(int para) : value(para){}
};

boost::ptr_vector<item> pointerContainer;
std::vector<std::unique_ptr<item>> container;
std::vector<std::shared_ptr<item>> container_;

int main(){
    
    const int count = 10000000;
    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < count; i++)
    {
        //pointerContainer.push_back(new item(i));
        //container.push_back(std::make_unique<item>(i));
        container_.push_back(std::make_shared<item>(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
                                            //ratio参数a,b a秒为b个周期
    std::chrono::duration<double, std::ratio<1,100000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,100000>>>(end - start);
   std::cout << time_span.count() << std::endl;

}