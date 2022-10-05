/*
 * ADS111.c
 *
 *  Created on: Oct 5, 2022
 *      Author: Muhammad Hammad Umer
 *
 *
 *      Change the Device address MACRO
 */
#include "ADS1115.h"
#include <stdint.h>
#include <stdio.h>




void ADS1115_reset(I2C_HandleTypeDef I2CHandle)
{
	ADS1115_write_register(I2CHandle , ADS1115_CONFIG_REG_ADDR , ADS1115_CONFIG_REG_DEF);
	ADS1115_write_register(I2CHandle , ADS1115_LOW_TRESH_REG_ADDR , ADS1115_LOW_TRESH_REG_DEF);
	ADS1115_write_register(I2CHandle , ADS1115_HIGH_TRESH_REG_ADDR , ADS1115_HIGH_TRESH_REG_DEF);
}





////////////////////////////////////////Private Functions////////////////////////////////////////////
void ADS1115_write_register(I2C_HandleTypeDef I2CHandle, uint8_t regAddr , uint16_t data)
{
	uint8_t devAddr = (DEVICE_ADDR_GND << 1);                       //Dev Address with HIGH Read/Write Bit

	uint8_t data_to_transmit[3];
	data_to_transmit[0] = regAddr;                  // Register address
 	data_to_transmit[1] = ((data >>8) & 0x00ff);	// MSB of data
	data_to_transmit[2] = (data & 0x00ff);			// LSB of data

	HAL_I2C_Master_Transmit(&I2CHandle, devAddr, data_to_transmit, sizeof(data_to_transmit), 50);
}



uint16_t ADS1115_read_register(I2C_HandleTypeDef I2CHandle, uint8_t regAddr)
{
	uint8_t devAddr = (DEVICE_ADDR_GND << 1);                       //Dev Address with LOW Read/Write Bit

	uint8_t data[2];
	HAL_I2C_Master_Transmit(&I2CHandle, devAddr, &regAddr, sizeof(regAddr), 30);

	devAddr = ((DEVICE_ADDR_GND << 1) | (1 << 0));          //Dev Address with HIGH Read/Write Bit
	HAL_I2C_Master_Receive(&I2CHandle, devAddr, data, sizeof(data), 30);

	uint16_t buffer = (data[0] | (data[1] << 8));
	return buffer;
}



uint16_t ADS1115_Pin(I2C_HandleTypeDef I2CHandle, uint16_t pinNo)
{
	ADS1115_reset(I2CHandle);
	if(pinNo == A0)
		{
			ADS1115_write_register(I2CHandle, ADS1115_CONFIG_REG_ADDR , 0x4483);
		}
	else if(pinNo == A1)
		{
			ADS1115_write_register(I2CHandle, ADS1115_CONFIG_REG_ADDR , 0x5483);
		}
	else if(pinNo == A2)
		{
			ADS1115_write_register(I2CHandle, ADS1115_CONFIG_REG_ADDR , 0x6483);
		}
	else if(pinNo == A3)
		{
			ADS1115_write_register(I2CHandle, ADS1115_CONFIG_REG_ADDR , 0x7483);
		}

	return(ADS1115_read_register(I2CHandle, ADS1115_CONVERSION_REG_ADDR));
}


