#ifndef __MAX6675_H_
#define __MAX6675_H_

#include <stm32g0xx_hal.h>

#define MAX6675_SPI hspi1

#define MAX6675_CS_Port GPIOA
#define MAX6675_CS_Pin GPIO_PIN_2

typedef struct {
  float temperature;
  int8_t error;
} K_Value;
 

K_Value read_k(void);    
void max6675_cs(uint8_t choice);
#endif
