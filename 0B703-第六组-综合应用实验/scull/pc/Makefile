ifneq ($(KERNELRELEASE),) 
obj-m:= scull.o 

else
	KERNELDIR:=/home/xpt/raspberrypi/linux
PWD:=$(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers  modul*
endif
