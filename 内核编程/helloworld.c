#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int __init lkm_init(void){//编译修饰符 在模块执行完以后把内存空间回收回来
    printk("hello world\n");
    return 0;
}

static void __exit lkm_exit(void){
    printk("Goodbye\n");
}

module_init(lkm_init); //引导函数 用来引导内核
module_exit(lkm_exit);

MODULE_LICENSE("GPL"); //许可证 

//感觉用make是为了跨平台
///usr/src/linux-headers-4.15.0-29deepin/include/linux
//cp linux /usr/include 