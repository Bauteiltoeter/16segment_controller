#ifndef __MESSAGEHANDLER_H
#define __MESSAGEHANDLER_H

#include <stdint.h>

//MSG 2
typedef struct {
    uint8_t seq;
    char characters[4*20];
    uint32_t dots[4];
}msg_complete_update_t;

#endif //__MESSAGEHANDLER_H
