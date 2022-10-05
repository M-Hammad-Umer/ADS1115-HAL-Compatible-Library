/*
 * ADS1115.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Muhammad Hammad Umer
 */

#ifndef INC_ADS1115_H_
#define INC_ADS1115_H_

#include "main.h"

//7-Bit Device Address options
#define DEVICE_ADDR_GND		0b1001000
#define DEVICE_ADDR_VDD		0b1001001
#define DEVICE_ADDR_SDA		0b1001010
#define DEVICE_ADDR_SCL		0b1001011


//Register Addresses
#define ADS1115_CONVERSION_REG_ADDR		0b00000000
#define ADS1115_CONFIG_REG_ADDR			0b00000001
#define ADS1115_LOW_TRESH_REG_ADDR		0b00000010
#define ADS1115_HIGH_TRESH_REG_ADDR		0b00000011



//Defaults register values
#define ADS1115_CONVERSION_REG_DEF		0x0000
#define ADS1115_CONFIG_REG_DEF			0x8583
#define ADS1115_LOW_TRESH_REG_DEF		0x8000
#define ADS1115_HIGH_TRESH_REG_DEF		0x7FFF

//ADS1115 Analog Channel Single Ended Macros
#define A0 0
#define A1 1
#define A2 2
#define A3 3



void ADS1115_reset(I2C_HandleTypeDef I2CHandle);
uint16_t ADS1115_Pin(I2C_HandleTypeDef I2CHandle, uint16_t pinNo);



void ADS1115_write_register(I2C_HandleTypeDef I2CHandle, uint8_t regAddr, uint16_t data);
uint16_t ADS1115_read_register(I2C_HandleTypeDef I2CHandle, uint8_t regAddr);


#endif /* INC_ADS1115_H_ */
