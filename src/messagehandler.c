#include "messagehandler.h"


msg_complete_update_t msgstore_complete_update;


void process_message(uint16_t msg_id, uint8_t length, uint8_t* data)
{
    char t[100];
    uart_puts("Processing Message ");

    sprintf(t,"No %u, length: %u\r\n",msg_id, length);
    uart_puts(t);

    if(msg_id == 2)
    {
        msgstore_complete_update.seq++;
        memcpy(msgstore_complete_update.characters,data,80);

        uart_puts(msgstore_complete_update.characters);
        for(uint8_t i=0; i < 4; i++)
        {
            msgstore_complete_update.dots[i] = ((uint32_t)data[80   +i*4])<<24;
            msgstore_complete_update.dots[i] |= ((uint32_t)data[81  +i*4])<<16;
            msgstore_complete_update.dots[i] |= ((uint32_t)data[82  +i*4])<<8;
            msgstore_complete_update.dots[i] |= ((uint32_t)data[83  +i*4])<<0;
        }
    }
}

void answer_message(uint16_t msg_id, uint8_t* buffer)
{
    if(msg_id==2)
    {
        buffer[0] = 20;
        buffer[1] = 4;
    }
}
