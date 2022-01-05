obj-m += Driver.o

KDIR = /lib/modules/$(shell uname -r)/build
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
	gcc -o run main.c -Wall
	sudo insmod Driver.ko
	sudo dmesg -C
	sudo ./run 
	dmesg 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	sudo rm -rf run my_device
	sudo rmmod Driver
	sudo clear

