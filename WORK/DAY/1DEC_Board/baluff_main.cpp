#include <iostream>
#include <sys/types.h>
#include <list>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libballuff.h"

using namespace std;
int main()
{
	Balluff obj;
	list<u_int8_t*> data_cube_addr,meta_data_cube_addr;
	u_int8_t i, *data_cube,*meta_cube,j;	
	for (i = 0; i < 12; i++)
	{
		if(posix_memalign((void **)&data_cube, HUGE_PAGE_SIZE, DATACUBE_BUFSIZE))
		{
			cout << "Memory Allocation Error!" <<endl;
		}
		data_cube_addr.push_back(data_cube);

		if(posix_memalign((void **)&meta_cube, 2048, METACUBE_BUFSIZE * sizeof(uint8_t)))
                {
                        cout << "Memory Allocation Error!" <<endl;
                }
                meta_data_cube_addr.push_back(meta_cube);
	}
	cout<<"Opening Driver"<<endl;
        obj.fd=open("/dev/my_device",O_RDWR);
        if(obj.fd<0)
	{
        	cout<<"Cannot open device file..."<<endl;
               	return 0;
       	}
	list<uint8_t*>::iterator it1 = data_cube_addr.begin();
        list<uint8_t*>::iterator it2 = meta_data_cube_addr.begin();
	obj.endpoint_driver_init(data_cube_addr,meta_data_cube_addr);
	
	while(1)
	{
		sleep(1);
	}

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
