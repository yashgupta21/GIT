#include <stdio.h>
#include "header.h"
int second_func()
        {      
		FILE *fp;
		int temp;
		temp-=1;
		char buff[500];
		printf("The line is-->\n");
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

