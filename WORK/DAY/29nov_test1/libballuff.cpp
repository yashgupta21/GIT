#include <iostream>
#include <sys/ioctl.h>
#include <list>
#include <signal.h>
#include "libballuff.h"
using namespace std;
// TODO: remove list_size parameter?
uint8_t Balluff::endpoint_driver_init(list<uint32_t*> data_cube_addr,list<uint32_t*> meta_data_cube_addr)
{
    uint8_t index_n = 0;
    uint32_t ret=0;
    list<uint32_t*>::iterator data_cube_itr = data_cube_addr.begin();
    list<uint32_t*>::iterator meta_data_cube_itr = meta_data_cube_addr.begin();
    
    // TODO: open_character_device
    if (data_cube_addr.size() != meta_data_cube_addr.size())
    {
        cout << "List size of data cube and meta data cube is not same." << endl;
        return -1;
    }
    for (; data_cube_itr != data_cube_addr.end() && 
            meta_data_cube_itr != meta_data_cube_addr.end();
            data_cube_itr++, meta_data_cube_itr++)
    {
        uint32_t error;
        data_addresses data;
        data.data_cube_address =*data_cube_itr;
        data.meta_data_cube_address =*meta_data_cube_itr;
        data.index = index_n++;
        error = ioctl(fd, IOCTL_SET_DMA_ADDRESS, &data);
        if (error < 0)
        {
            // TODO: close character driver
            return error;
        }    
    }

    return 1;
}
/*
uint8_t Balluff::endpoint_driver_deinit()
{
    uint32_t error;
    error = ioctl(fd, IOCTL_FREE_DMA_ADDRESS, NULL);
    if (error < 0)
    {
        return error;
    }
    
    /* error = close_character_driver();
    if (error)
    {
        return error;
    } /

    return 1;
}*/
