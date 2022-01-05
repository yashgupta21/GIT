#ifndef LIBBALLUFF_H
#define LIBBALLUFF_H

#include <iostream>
#include <list>

// TODO
//#define IOCTL_WR_FPGA_REGISTER			NULL
//#define IOCTL_RD_FPGA_REGISTER			NULL
//#define IOCTL_SET_DMA_ADDRESS			NULL
#define IOCTL_FREE_DMA_ADDRESS			NULL
#define IOCTL_SET_SIGNAL_INTERRUPT		NULL
#define IOCTL_FREE_SIGNAL_INTERRUPT		NULL
#define LOW_POWER_MODE                  	NULL

using namespace std;
//#define IOCTL_WR_FPGA_REGISTER _IOW('a','a',u_int32_t*)
//#define IOCTL_RD_FPGA_REGISTER _IOR('a','b',u_int32_t*)
#define IOCTL_SET_DMA_ADDRESS _IOW('a','a',data_addresses*)
#if 0
enum cmd
{
    SEND_COMMAND,
    COMMAND_RESPONSE,
    CURRENT_DATA_CUBE_INDEX,
    CARD_POWER,
    TRIGGER_PERIOD,
    MEASUREMENT_DATA_LENGTH,
    TRIGGER_ENABLE,
    SELECT_CARD_NUMBERS,
    RADAR_READY_STATUS,
    FPGA_RESET
} commands;
-
enum fpga_off_cmd
{
    E_SEND_COMMAND = 1,
    E_COMMAND_RESPONSE,
    E_CURRENT_DATA_CUBE_INDEX,
    E_CARD_POWER,
    E_TRIGGER_PERIOD,
    E_MEASUREMENT_DATA_LENGTH,
    E_TRIGGER_ENABLE,
    E_SELECT_CARD_NUMBERS,
    E_RADAR_READY_STATUS,
    E_FPGA_RESET,

    // Add enums above this, not below
    E_OFFSET_MAX,
} fpga_offset_cmd;

enum
{
    E_ERROR_MEM,
    E_IOCTL,
    E_DATA,
    E_SUCCESS
} error_codes;
#endif
class Balluff
{
    public:
        Balluff()
        {

        }

        typedef struct _data_addr
        {
            // TODO: does the following two variables needs to be a pointer?
            uint32_t*   data_cube_address;             /* Data cube address */
            uint32_t*	meta_data_cube_address;        /* Meta data cube address */
            uint8_t	index;                          /* Index of the data cube in list */
            // TODO: add data_cube and meta_data_cube offset
        } data_addresses;
//	#define IOCTL_SET_DMA_ADDRESS _IOW('a','a',data_addresses*)
#if 0
        typedef struct _ioctl_addr
        {
            uint32_t offset;     /* FPGA BAR memory offset */
            uint8_t  *value;     /* address of data bytes to write/read in FPGA */
            uint16_t size;       /* Size of data bytes to write/read in FPGA */
        } ioctl_data;

        uint8_t     fd;
        uint8_t     send_command(uint8_t channel_index, uint8_t command_data[16]);
        uint8_t     send_command_and_get_response(uint8_t channel_index, uint8_t command_data[16], 
                    uint8_t *response_data, uint16_t timeout);*/
#endif
	uint8_t     fd;
	uint8_t     endpoint_driver_init(uint32_t* data_cube_addr, uint32_t* meta_data_cube_addr);
                    // uint8_t list_size);
        /*uint8_t     endpoint_driver_deinit();
        uint8_t     get_current_data_cube_index(uint8_t *index);
        uint8_t     set_card_power(uint8_t state);
        uint8_t     set_trigger_period(uint8_t trigger_period[2]);
        uint8_t     set_measurement_data_length(uint8_t measuremet_length[2]);
        uint8_t     set_low_power_mode(void);
        uint8_t     set_trigger(uint8_t state);
        uint8_t     set_card_numbers(uint8_t card_index_bit[2]);
        uint8_t     get_radar_board_ready_status(uint8_t card_index_bit[2]);
        uint8_t     soft_reset_fpga(void);
        uint8_t     register_callback_function(void (*func)(void), int id);
        uint32_t    get_fpga_register_offset(uint32_t cmd, uint8_t index);
        void        wait_for_response(uint16_t timeout);
        void        enter_low_power_mode(void);*/
};

#endif
