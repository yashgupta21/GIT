#include <stdio.h>
#include <string.h>        
FILE *fp;				//File descriptor
char buff[500];				//Buffer For data
int  temp,func1(),func2();		//Functions Declared    
int  main()				//main
{
        func1();
	func2();
}
int func1()				//Function1 starts here
{
		 int max=0,len;                      
		 fp = fopen("test.txt", "r");		//test.txt file open here
        	 for (int i=0;i<10;i++)
        		{
                		fgets(buff, 500, fp);	//Reading line by line from test.txt to Buffer 
                		len=strlen(buff);
                		if(len<=255)
                        		{
                                		if(max<len)		//Finding largest line of a file 
                                        		{
                                                		max=len;
                                                		temp=i;
                                        		}
                        		}
                		else
                        		{
                                		continue;
                        		}

        		}

       		 printf("The length of longest line is %d\n",max-1);	//Printing longest line length
        	 printf("The number of longest line is %d\n",temp+1);	//Printing longets line number
        	 fclose(fp);						//test.txt file closed
}
int func2()					//Fuction2 starts here
{
		printf("The line is-->\n");						
        	fp = fopen("test.txt", "r"); 	//test.txt opens here
        	for(int i=0;i<=temp;i++)	
       			 {
                		fgets(buff,255,fp);
                		if(i<temp)	
                			{
                        			continue;
                			}

                		else if(i==temp)
                			{
                        			printf("%s",buff);	//Printing largest line
               			        }
      			  }
		fclose(fp);			//test.txt File closed

}

	



