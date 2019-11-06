obj-m:=helloworld.o

CURRENT_PATH:=$(shell pwd) 
LINUX_KERNRL:=$(shell uname -r)
LINUX_KERNRL_PATH:=/usr/src/linux-headers-4.15.0-29deepin;

all:
	make -C $(LINUX_KERNRL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNRL_PATH) M=$(CURRENT_PATH) clean