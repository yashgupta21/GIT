obj-m += Driver.o

KDIR = /lib/modules/$(shell uname -r)/build


all:
	make -C $(KDIR)  M=$(shell pwd) modules
	g++ -c libballuff.cpp baluff_main.cpp
	ar rcs lib_mylib.a libballuff.o	
	g++ -o run baluff_main.o -L.  -l_mylib       
	sudo insmod Driver.ko
	sudo dmesg -C
	sudo ./run
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	sudo rm -rf run my_device *.so *.o
	sudo rmmod Driver
	sudo clear
