obj-m += Driver.o

KDIR = /lib/modules/$(shell uname -r)/build


all:
	make -C $(KDIR)  M=$(shell pwd) modules
	gcc -c lib_mylib.c -o lib_mylib.o 
	ar rcs lib_mylib.a lib_mylib.o
	gcc -c main.c -o main.o -Wall
	gcc -o main main.o -L. -l_mylib
	sudo insmod Driver.ko
	sudo dmesg -C
	sudo ./main
	dmesg 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	sudo rm -rf main my_device *.so *.o
	sudo rmmod Driver
	sudo clear


