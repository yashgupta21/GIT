#include <iostream>
#include <sys/types.h>
#include <list>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include "libballuff.h"

using namespace std;

int main()
{
	Balluff obj;
	u_int32_t *lst1,*lst2;
	int i;	
	lst1=(u_int32_t*)calloc(12,sizeof(u_int32_t));
	lst2=(u_int32_t*)calloc(12,sizeof(u_int32_t));
	cout<<"Opening Driver"<<endl;
        obj.fd=open("/dev/my_device",O_RDWR);
        if(obj.fd<0)
	{
        	cout<<"Cannot open device file..."<<endl;
               	return 0;
       	}

	cout << "From Test application" << endl;
	for (i=0;i<12;i++)
	{
		cout <<lst1 << endl;
		lst1++;
	}
	cout<<"\n\n";
	obj.endpoint_driver_init(lst1,lst2);

	/*for (i=0;i<12;i++)
	{
		cout << lst2 << endl;
		lst2++;
	}
	cout<<endl<<"\n";*/
	//obj.endpoint_driver_init(lst1,lst2);
	cout<<"Closing Driver File"<<endl;
	close(obj.fd);
}
