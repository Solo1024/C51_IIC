#ifndef __I2C_H_
#define __I2C_H_

#include <reg52.h>

sbit SCL=P2^1;
sbit SDA=P2^0;

//void delay10us();
void i2cstart();
void i2cstop();
unsigned char i2csendbyte(unsigned char dat);
unsigned char i2creadbyte();
void at24c02write(unsigned char addr, unsigned char dat);
unsigned char at24c02read(unsigned char addr);

#endif
