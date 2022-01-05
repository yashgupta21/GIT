all:
	g++ -c libballuff.cpp -o lib_mylib.o 
	ar rcs lib_mylib.a lib_mylib.o
	g++ -c baluff_main.cpp -o main.o 
	g++ -o main main.o -L. -l_mylib
	./main
 
clean:
	sudo rm -rf main *.so *.o *.a
	clear
	

