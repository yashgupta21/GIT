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
	list<u_int32_t*> lst1, lst2;
	int i;	
	for (i = 0; i < 12; i++)
	{
		lst1.push_back((u_int32_t*)malloc(sizeof(u_int32_t)));
		lst2.push_back((u_int32_t*)malloc(sizeof(u_int32_t)));
	}
	cout<<"Opening Driver"<<endl;
        obj.fd=open("/dev/my_device",O_RDWR);
        if(obj.fd<0)
	{
        	cout<<"Cannot open device file..."<<endl;
               	return 0;
       	}
	list<uint32_t*>::iterator it1 = lst1.begin();
	list<uint32_t*>::iterator it2 = lst2.begin();
	for (; it1 != lst1.end(); it1++)
	{
		cout << *it1 << endl;
	}
	cout<<endl<<"\n";
	/*for (; it2 != lst2.end(); it2++)
	{
		cout << *it2 << endl;
	}
	cout<<endl<<"\n";
	*/
	obj.endpoint_driver_init(lst1,lst2);
	cout<<"Closing Driver File"<<endl;
	close(obj.fd);
}
