obj-m += Driver.o

KDIR = /lib/modules/$(shell uname -r)/build


all:
	make -C $(KDIR)  M=$(shell pwd) modules
	gcc -c lib_mylib.c main.c
	gcc lib_mylib.o -shared -o lib_dynamic.so
	gcc -o run main.o -L./ -l_dynamic	
	sudo insmod Driver.ko
	sudo dmesg -C	
	dmesg 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	sudo rm -rf run my_device *.so *.o
	sudo rmmod Driver
	sudo clear


