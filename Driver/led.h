#ifndef __LED_H
#define __LED_H
#include <stdint.h>






void LedDrvInit(void);
void TurnOnLed(uint8_t ledNo);
void TurnOffLed(uint8_t ledNo);
void ToggleLed(uint8_t ledNo);


#endif
