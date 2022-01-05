#include <iostream>
#include <sys/ioctl.h>
#include <list>
#include <signal.h>
#include "libballuff.h"
#if 0
uint8_t Balluff::send_command(uint8_t channel_index, uint8_t command_data[16])
{
    uint32_t error;
    ioctl_data io_data;

    /* Get FPGA register offset and fill data structure */
    io_data.offset = get_fpga_register_offset(SEND_COMMAND, channel_index);
    io_data.value = command_data;
    io_data.size = 16;
    
    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_WR_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
       return error;
    }
}

uint8_t Balluff::send_command_and_get_response(uint8_t channel_index, uint8_t command_data[16],
        uint8_t *response_data, uint16_t timeout)
{
    ioctl_data io_data;
    uint32_t error;

    /* Send command data bytes to specific SPI_C channel */
    error = send_command(channel_index, command_data);

    if (error < 0)
    {
        return error;
    }

    /* Wait for response receive notification. Library get the response 
       receive signals and get the status of response */
    wait_for_response(timeout);

    /* Get FPGA register offset and fill data structure */
    io_data.offset = get_fpga_register_offset(COMMAND_RESPONSE, channel_index);
    io_data.value = response_data;
    io_data.size = 16;

    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_RD_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }
}
#endif 
// TODO: remove list_size parameter?
uint8_t Balluff::endpoint_driver_init(list<uint32_t*> data_cube_addr,list<uint32_t*> meta_data_cube_addr) //, uint8_t list_size)
{
    //uint16_t list_size = data_cube_addr.size();
    //uint8_t index_n = 0;
    u_int8_t ret=0;
    list<uint32_t*>::iterator data_cube_itr = data_cube_addr.begin();
    list<uint32_t*>::iterator meta_data_cube_itr = meta_data_cube_addr.begin();
    
    // TODO: open_character_device
    // TODO: Validate hugepage memory allocation
    /*if (data_cube_addr.size() != meta_data_cube_addr.size())
    {
        cout << "List size of data cube and meta data cube is not same." << endl;
        return -1;
    }*/
    for (; data_cube_itr != data_cube_addr.end(); data_cube_itr++)
    {
	    cout << *data_cube_itr << endl;
    }
    cout<<endl<<"\n";
    for (; meta_data_cube_itr != meta_data_cube_addr.end(); meta_data_cube_itr++)
    {
	    cout << *meta_data_cube_itr << endl;
    }
    cout<<endl<<"\n";
    ret=ioctl(fd,IOCTL_WR_FPGA_REGISTER,&data_cube_addr);
    return 0;
}
#if 0

    for (; data_cube_itr != data_cube_addr.end() && 
            meta_data_cube_itr != meta_data_cube_addr.end();
            data_cube_itr++, meta_data_cube_itr++)
    {
        uint32_t error;
        data_addresses data;
        data.data_cube_address = *data_cube_itr;
        data.meta_data_cube_address = *meta_data_cube_itr;
        data.index = index_n++;
        
        if (data.data_cube_address == NULL || data.meta_data_cube_address == NULL)
        {
            continue;
            // cout << "Couldn't allocate memory" << endl;
            // TODO: close character driver
            // return error;
        }

        error = ioctl(fd, IOCTL_SET_DMA_ADDRESS, &data);
        
        if (error < 0)
        {
            // TODO: close character driver
            return error;
        }    
    }

    return 1;
}

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
    } */

    return 1;
}

uint8_t Balluff::get_current_data_cube_index(uint8_t *index)
{
    ioctl_data io_data;
    uint32_t error;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(CURRENT_DATA_CUBE_INDEX, 0);

    /* Set the address to get updated value. Updated value will be received in io_data.value
       parameter after IOCTL call */
    io_data.value = index;
    io_data.size = 2;
    error = ioctl(fd, IOCTL_RD_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }
}

uint8_t Balluff::set_card_power(uint8_t state)
{
    ioctl_data io_data;
    uint32_t error;
    uint8_t* const card_pow_state = &state;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(CARD_POWER, 0);
    io_data.value = card_pow_state;
    io_data.size = 1;

    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_WR_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }	
}

uint8_t Balluff::set_trigger_period(uint8_t trigger_period[2])
{
    ioctl_data io_data;
    uint32_t error;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(TRIGGER_PERIOD, 0);
    io_data.value = &trigger_period[0];
    io_data.size = 2;

    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_WR_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }
}

uint8_t Balluff::set_measurement_data_length(uint8_t measuremet_length[2])
{
    ioctl_data io_data;
    uint32_t error;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(MEASUREMENT_DATA_LENGTH, 0);
    io_data.value = &measuremet_length[0];
    io_data.size = 2;

    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_WR_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }	
}

uint8_t Balluff::set_low_power_mode(void)
{
    ioctl_data io_data;
    uint32_t error;

    /* Disable all 16-card power */
    error = set_card_power(LOW_POWER_MODE);

    if (error < 0)
    {
        return error;
    }

    /* Jetson will go into sleep mode. It will wake up from 
       external wake up source */
    enter_low_power_mode();

    if (error < 0)
    {
        return error;
    }	
}

uint8_t Balluff::set_trigger(uint8_t state)
{
    ioctl_data io_data;
    uint32_t error;
    uint8_t* const trigger_state = &state;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(TRIGGER_ENABLE, 0);
    io_data.value = trigger_state;
    io_data.size = 1;

    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_WR_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }	
}

uint8_t Balluff::set_card_numbers(uint8_t card_index_bit[2])
{
    ioctl_data io_data;
    uint32_t error;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(SELECT_CARD_NUMBERS, 0);
    io_data.value = &card_index_bit[0];
    io_data.size = 2;

    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_WR_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }
}

uint8_t Balluff::get_radar_board_ready_status(uint8_t card_index_bit[2])
{
    ioctl_data io_data;
    uint32_t error;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(RADAR_READY_STATUS, 0);
    io_data.value = &card_index_bit[0];
    io_data.size = 2;

    /* Call ioctl to pass the data pointer to endpoint driver which will update the data */
    error = ioctl(fd, IOCTL_RD_FPGA_REGISTER, io_data);

    if (error < 0)
    {
        return error;
    }	
}

uint8_t Balluff::soft_reset_fpga(void)
{
    ioctl_data io_data;
    uint32_t error;

    /* Get the FPGA register offset and fill the data structure */
    io_data.offset = get_fpga_register_offset(E_FPGA_RESET, 0);
    io_data.value = NULL; //E_FPGA_RESET; // TODO
    io_data.size = 1;

    /* Call ioctl to pass the data to endpoint driver */
    error = ioctl(fd, IOCTL_WR_FPGA_REGISTER, &io_data);

    if (error < 0)
    {
        return error;
    }	
}

uint8_t Balluff::register_callback_function(void (*func)(void), int id)
{
    // TODO
	// signal(id, func);
}

uint32_t Balluff::get_fpga_register_offset(uint32_t cmd, uint8_t index)
{
    uint32_t fpga_register_offset;
    uint32_t base_address = 0x400;
    uint32_t reg_bank = 0x400;

    if (cmd < SEND_COMMAND || cmd > FPGA_RESET)
    {
        // TODO: error
    }

    fpga_register_offset = base_address + (cmd * 4);

    switch (cmd)
    {
        case SEND_COMMAND:
            break;

        case COMMAND_RESPONSE:
            break;

        case CURRENT_DATA_CUBE_INDEX:
            break;

        case CARD_POWER:
            break;

        case TRIGGER_PERIOD:
            break;

        case MEASUREMENT_DATA_LENGTH:
            break;

        case TRIGGER_ENABLE:
            break;

        case SELECT_CARD_NUMBERS:
            break;

        case RADAR_READY_STATUS:
            break;

        case FPGA_RESET:
            break;

        default:
            break;
    }

    return fpga_register_offset;
}

void Balluff::wait_for_response(uint16_t timeout)
{

}

void Balluff::enter_low_power_mode(void)
{

}
#endif
