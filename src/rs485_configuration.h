#ifndef __RS485_CONFIGURATION_H
#define __RS485_CONFIGURATION_H

#define HW_TYPE 2

#define RS485_getc uart1_getc
#define RS485_init uart1_init
#define RS485_putc uart1_putc

#define RS485_CTL_DDR DDRC
#define RS485_CTL_PORT PORTC
#define RS485_RX 5
#define RS485_TX 4

#endif
