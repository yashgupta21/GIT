obj-m += Driver.o

KDIR = /lib/modules/$(shell uname -r)/build


all:
	make -C $(KDIR)  M=$(shell pwd) modules
	g++ -c libballuff.cpp baluff_main.cpp
	ar rcs lib_balluf.a libballuf.o
	gcc -o run baluff_main.o -L./ -l_balluf       
	sudo insmod Driver.ko
	sudo dmesg -C   
	dmesg 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	sudo rm -rf run my_device *.so *.o *.a
	sudo rmmod Driver
	sudo clear
