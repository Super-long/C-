#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

#include <unistd.h> // posix_memalign




int main()

{
    char *buf;
    size_t buf_size = 1024;
    off_t offset = 4096;
    posix_memalign((void **)&buf, getpagesize(), buf_size);

    printf("%d\n", getpagesize());
    //buf = (char*)malloc(buf_size);
    scanf("%s", buf);
    int writefd =open("test.txt",O_RDWR|O_DIRECT);
    if(writefd<0){
        printf("can't  open the file!\n");
        exit(1);
    }

    if(lseek(writefd,offset,SEEK_SET)<0){
        printf("lseekthe disk is error!\n");
        exit(1);
    }

    printf("%d %d\n", buf_size, write(writefd,buf,buf_size));
    perror("");

    if(buf_size != read(writefd,buf,buf_size)){
        perror("readdata from the disk is error!");
        printf("the tem_size is %d\n",buf_size);
        exit(1);
    }
}