obj-m += driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o user app.c
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf user



