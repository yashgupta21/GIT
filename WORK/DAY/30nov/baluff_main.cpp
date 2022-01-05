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
	list<u_int32_t*> data_cube_addr,meta_data_cube_addr;
	int i;	
	for (i = 0; i < 12; i++)
	{
		data_cube_addr.push_back((u_int32_t*)malloc(sizeof(u_int32_t)));
		meta_data_cube_addr.push_back((u_int32_t*)malloc(sizeof(u_int32_t)));
	}
	cout<<"Opening Driver"<<endl;
        obj.fd=open("/dev/my_device",O_RDWR);
        if(obj.fd<0)
	{
        	cout<<"Cannot open device file..."<<endl;
               	return 0;
       	}
	list<uint32_t*>::iterator it1 = data_cube_addr.begin();
        list<uint32_t*>::iterator it2 = meta_data_cube_addr.begin();
	obj.endpoint_driver_init(data_cube_addr,meta_data_cube_addr);
	obj.endpoint_driver_deinit();
	for(i =0 ;i<12;i++)
	{
		free(*it1);
		free(*it2);
		it1++,it2++;
	}
	cout<<"Memory Released "<<endl<<"Closing Driver File"<<endl;
	close(obj.fd);
}
