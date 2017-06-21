#include "slavecommunicator.h"
#include "uart.h"

uint8_t calc_checksum(uint8_t* data, uint8_t length);
void sendDatatransfer(int id, datatypes mode, uint8_t* buffer, size_t length);
void tickStatemachine(uint8_t byte);
void tickSendStatemachine(void);


void sc_init(void)
{
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
}

void sc_initID(void)
{
    uart_putc(0);
    uart_putc(0);
}

void sc_run(void)
{
    unsigned int c = uart_getc();
    if (! ( c & UART_NO_DATA) )
    {
        tickStatemachine(c);
    }
    //tickStatemachine() with new byte

    uint8_t tmp[20];
    tmp[0]='A';
    tmp[1]='A';
    tmp[2]='A';
    tmp[3]='A';
    tmp[4]='A';
    tmp[5]='A';

    sendDatatransfer(0,character_update,tmp,20);
}


void sc_sendpackage(package_t *package)
{

}


//########################
//Private functions
//########################

void tickSendStatemachine(void)
{

}

void tickStatemachine(uint8_t byte)
{
    static int state = 0; // 0: waiting
    static uint8_t mode;
    static int datacounter=0;
    static uint8_t data[4];

    switch(state)
    {
    case 0:
        mode=byte;
        datacounter=0;
        state=1;
        break;
    case 1:
        if(mode==0)
        {
           // qDebug() << "Detecting answer to init, " << byte << " displays found";
            state=0;
        }
        else if(mode==1)
        {
            data[datacounter]=byte;
            datacounter++;
            if(datacounter>=3)
            {
                state=0;
                if(data[2] == 0)
                {
                    //qDebug() << "received ack for id" << data[0];
                    //delete sendPackages[data[0]];
                    //sendPackages[data[0]] = NULL;
                }
                else
                {
                    //qDebug() << "Received Nack for id" << data[0];

                }

                //qDebug() << "Receiving answer: " << (int)data[0]<< (int)data[1]<< (int)data[2]<< (int)data[3];
            }
        }
        break;
    }
}

uint8_t calc_checksum(uint8_t* data, uint8_t length)
{
    uint8_t temp=0;
    for(uint16_t i=0; i < length; i++)
    {
        temp^=data[i];
    }
    return temp;
}

void sendDatatransfer(int id, datatypes mode, uint8_t *buffer, size_t length)
{
    uint8_t data[256];
    data[0] = data_transmit;
    data[1] = id; //message id
    data[2] = length+2; //length+modeword+checksum
    data[3] = mode;
    memcpy(data+4,buffer,length);
    data[length+4]= calc_checksum(data+3,length+1); //checksum

    for(int i=0; i < length+5; i++)
        uart_putc(data[i]);


}

