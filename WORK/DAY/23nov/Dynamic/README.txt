Instruction To Execute 

List of files associated with you
	main.c(User code)
	Driver.c (Chracter Code)
	header.h (Header file for code)
	lib_mylib.c (Library code)
	Makefile

step 1:
	Write "make "on terminal then following files created
 
	{ Driver.c,Driver.ko,Driver.mod,Driver.mod.c,Driver.mod.o,Driver.o,header.h,
	  lib_dynamic.so,lib_mylib.c,lib_mylib.o,main.c,main.o,modules.order,
	  Module.symvers,run(executable) }
	
	Driver.ko moduke uploaded automatically no need to do it manually 

	NOTE:**IF you want to clear all (.so .o and run(executable)file) then use "make clean"**

step 2:
	Use this command on terminal (export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD) to give path of dynamic.so file 

step 3:
	Use "sudo ./run" to run your application.


Result:

Opening Driver

Enter :
1 for 1 Byte Data
2 for 2 Byte Data
3 for 4 Byte Data
4 for 16 Byte Data

(Choose the data bytes )

Enter 1 for Write and 2 for Read

(Choose Write or Read Operation) 
(**For Write Operaration Use "dmesg" to view output **)




