#include "matrix.h"

/* Function Definitions */
void writeByte(uint8_t byte)
{
    for(int i=0;i<8;i++)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);            // Pull the clock pin low
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, byte&0x80);    // Write one BIT data MSB first
        byte = byte << 1;                                   // shift the data to the left
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);            // Pull the CLK HIGH
    }
}

void writeMax (uint8_t address, uint8_t data)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);   // Pull the CS pin LOW
    writeByte(address);   //  write address
    writeByte(data);  //  write data
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);  // pull the CS HIGH
}

void maxInit(void)
{
    writeMax(0x09, 0x00);       //  no decoding
    writeMax(0x0a, 0x01);       //  brightness intensity
    writeMax(0x0b, 0x07);       //  scan limit = 8 LEDs
    writeMax(0x0c, 0x01);       //  power down =0,normal mode = 1
    writeMax(0x0f, 0x00);       //  no test display
}
