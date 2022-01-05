#include<stdio.h>
int main()
{  	
	int x;
 	printf("Enter Your choice:\n1.To print Hello\n2.To print Bye\n");
	scanf("%d",&x);
	switch(x){
			case 1:
				printf("Hello Ternimal");
				break;
			case 2:
				printf("Bye Terminal");
				break;
			default:
				printf("Wrong Choice ");
				break;
		}
}

