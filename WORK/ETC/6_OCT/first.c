#include <stdio.h>
#include "header.h"
#include<string.h>
int first_func()
        {   	  FILE *fp;
                 int max=0,len,temp;
                 char buff[500];
                 fp = fopen("test.txt", "r");
                 for (int i=0;i<10;i++)
                        {
                                fgets(buff, 500, fp);
                                len=strlen(buff);
                                if(len<=255)
                                        {
                                                if(max<len)
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

                 printf("The length of longest line is %d\n",max-1);
                 printf("The number of longest line is %d\n",temp+1);
                 fclose(fp);
        }
