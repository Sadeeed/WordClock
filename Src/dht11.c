#include "dht11.h"

void delayUs(uint16_t time)
{
	/* change your code here for the delay in microseconds */
	__HAL_TIM_SET_COUNTER(&htim9, 0);
	while ((uint16_t)__HAL_TIM_GET_COUNTER(&htim9) < time);
}

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP; // change to no pull in case of error
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT11_Start(void)
{
	Set_Pin_Output(DHT11_GPIO_Port, DHT11_Pin);		  // set the pin as output
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 0); // pull the pin low
	delayUs(18000);									  // wait for 18ms
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 1); // pull the pin high
	delayUs(20);									  // wait for 20us
	Set_Pin_Input(DHT11_GPIO_Port, DHT11_Pin);		  // set as input
}

uint8_t DHT11_Check_Response(void)
{
	uint8_t Response = 0;
	delayUs(40);
	if (!(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)))
	{
		delayUs(80);
		if ((HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)))
		{
			Response = 1;
		}
		else
		{
			Response = -1; // 255
		}
	}
	while ((HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin))); // wait for the pin to go low

	return Response;
}

uint8_t DHT11_Read(void)
{
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		while (!(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)))
			;												 // wait for the pin to go high
		delayUs(40);										 // wait for 40 us
		if (!(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin))) // if the pin is low
		{
			i &= ~(1 << (7 - j)); // write 0
		}
		else
		{
			i |= (1 << (7 - j)); // if the pin is high, write 1
		}
		while ((HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin))); // wait for the pin to go low
	}
	return i;
}