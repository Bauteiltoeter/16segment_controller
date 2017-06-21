#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "slavecommunicator.h"

#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "rs485_slave.h"
void init(void);

int main(void)
{
    init();
    PORTB|=(1<<0);

    _delay_ms(500);
    _delay_ms(500);


    sc_initID();

    PORTB|=(1<<1);


    while(1)
    {
       // sc_run();
        rs485_run();
        _delay_ms(1);

       // uart_puts("Hallo welt\r\n");
    }
}



void init(void)
{

    sc_init();
    rs485_init();
    sei();

}
