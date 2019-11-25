#include"fileproxy.h"
#include<memory>

#include<unistd.h>
#include<fcntl.h>

namespace ws{

    void FileProxy::Statget(){ //这个设计理念没有大懂 
        if(!stat_){
            stat_ = std::make_unique<struct stat>();
            fstat(File_Description, stat_.get());
        }
    }
    
    __off_t FileProxy::FileSize(){
        Statget();
        return stat_->st_size;
    }

    //Refuse directory, character device, block device.
    bool FileProxy::IsTextFile(){
        Statget();
        return (stat_->st_mode & S_IFDIR || stat_->st_mode & S_IFCHR || stat_->st_mode & S_IFBLK);
    }

    FileProxy::~FileProxy(){
        ::close(File_Description); //非异常安全
    }

    //在path1 中搜寻path2
    FileProxy::FileProxy(const FileProxy& path1, const char* path2) : 
        File_Description(openat(path1.fd(), path2, O_RDONLY)){}

}