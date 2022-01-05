#include <stdio.h>
#include <string.h>
void main() {

   FILE *fp;
   char buff[255];
   char inp[255];
   int len,max=0,temp;
   fp = fopen("IO.txt", "a+");
   for(int i=0;i<10;i++)
   {    
   	printf("Enter your line : ");
   	scanf("%s",inp);
   	fputs(inp, fp);
   	printf("\n");
   	
   }
   fclose(fp);	

   fp = fopen("IO.txt", "r");
   for (int i=0;i<10;i++)
   {
   	fgets(buff, 255, fp);
   	len=strlen(buff);
	if(max<len)
	{
           max=len;
	   temp=i;
	}
       
   }
   
   printf("The length of longest line is %d\n",max-1);
   printf("The number of longest line is %d\n",temp+1);
   printf("The line is-->\n");
   
   fclose(fp);
   fp = fopen("test.txt", "r");
   for(int i=0;i<=temp;i++)
   {
     fgets(buff,255,fp);

     if(i<temp)
     {
       continue;
     }     

     else if(i==temp)
     {
       printf("%s",buff);
     }

   }	   


   fclose(fp);

}
