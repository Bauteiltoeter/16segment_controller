#ifndef __SLAVECOMMUNICATOR
#define __SLAVECOMMUNICATOR

#define UART_BAUD_RATE 115200

#include "stdint.h"

typedef enum {
    id_assign = 0x00,
    data_transmit = 0x01
} commandwords;

typedef enum {
    character_update = 0x01,
    brightness_update = 0x02
} datatypes;

typedef struct {
    int id;
    uint8_t* data;
    uint8_t length;
    datatypes mode;
    uint32_t sendTime;
    int retrycounter;
} package_t;

void sc_init(void);
void sc_initID(void);
void sc_run(void);
void sc_sendpackage(package_t* package);
#endif
