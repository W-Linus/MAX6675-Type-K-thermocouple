#include <max6675.h>

extern SPI_HandleTypeDef hspi1;
extern K_Value k;

#include "max6675.h"

K_Value read_k(void)
{
  uint8_t data_temp[2];  // [0] 高位 [1]低位

  
  // 拉低
  max6675_cs(0);
  // 读取
  HAL_SPI_Receive(&hspi1, &data_temp[0], 2, 1);
  
  // D2 low: 正常 high: 开路  
  if (data_temp[1] & 0x4) {
    // printf("No Probe\r\n");
    k.temperature = 0;
    k.error = 1;
  }
  else  {  
    k.temperature = /*(int16_t)*/(( (data_temp[0] << 5) | (data_temp[1] >> 3) ) * 0.25);
    k.error = 0;
  }
  
  // 拉高
  max6675_cs(1);
  
  return k;
}

/*
 *@name max6675_cs
 *@brief select CS pin level
 *@param 0-selected 1-unselected
 *@return none
 */
void max6675_cs(uint8_t choice){
	if(choice==0){
		HAL_GPIO_WritePin(MAX6675_CS_Port,MAX6675_CS_Pin,GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(MAX6675_CS_Port,MAX6675_CS_Pin,GPIO_PIN_SET);
	}
}