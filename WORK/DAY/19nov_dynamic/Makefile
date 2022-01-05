obj-m += Driver.o

KDIR = /lib/modules/$(shell uname -r)/build


all:
	make -C $(KDIR)  M=$(shell pwd) modules
	gcc -c lib_mylib.c main.c
	gcc lib_mylib.o -shared -o lib_dynamic.so
	gcc -o main main.o -L. -l_dynamic
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD)
	sudo insmod Driver.ko
	sudo dmesg -C
	sudo ./main
	dmesg 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	sudo rm -rf main my_device *.so *.o
	sudo rmmod Driver
	sudo clear


