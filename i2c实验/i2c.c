#include "i2c.h"
/*******************************************
*函数名：       delay10us()
*函数功能；     延时10us
*输入：         null
*输出：         null
*******************************************/


void delay10us()
{
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);

}
/*
void delay10us()
{
	unsigned char a, b;
	for (a = 1; a > 0; a--)
	    for (b = 2; b > 0; b--);
}
*/

/*******************************************
*函数名：       i2cstart()
*函数功能：     起始信号，SCL时钟信号为高电平期间SDA信号产生一个下降沿
*输入：         null
*输出：         null
*备注：         起始之后，SDA和SCL都为0
*******************************************/

void i2cstart()
{
	SDA = 1;
	delay10us();
	SCL = 1;
	delay10us();
	SDA = 0;
	delay10us();
	SCL = 0;
	delay10us();
}

/*******************************************
*函数名：       i2cstop()
*函数功能：     终止信号，SCL时钟信号为高电平期间SDA信号产生一个上升沿
*输入：         null
*输出：         null
*备注：         终止之后，SDA和SCL都为1，表示总线空闲
*******************************************/

void i2cstop()
{
	SDA = 0;
	delay10us();
//	SCL = 0;
//	delay10us();
	SCL = 1;
	delay10us();
	SDA = 1;
	delay10us();
}

/*******************************************
*函数名：       i2csendbyte(unsigned char dat)
*函数功能：     通过I2C发送一个字节。在SCL时钟信号高电平期间，保持发送信号SDA保持稳定
*输入：			null
*输出：         0或1，发送成功返回1，发送失败返回0
*备注：         发送完一个字节，SDA = 1,SCL = 0
********************************************/

unsigned char i2csendbyte(unsigned char dat)
{
	unsigned char a = 0, b = 0;
	for (a = 0; a < 8; a++)
	{
		SDA=dat>>7;	 //起始信号之后SCL=0，所以可以直接改变SDA信号
		dat=dat<<1;
		delay10us();
		SCL=1;
		delay10us();//建立时间>4.7us
		SCL=0;
		delay10us();
	}
	SDA = 1;
	delay10us();
	SCL = 1;
//	delay10us();
	while(SDA)//等待应答，也就是等待从设备把SDA拉低
	{
		b++;
		if(b>200)	 //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
		{
			SCL=0;
			delay10us();
			return 0;
		}
	}
	SCL = 0;
	delay10us();
	return 1;
}


/*************************************************************
*函数名：     i2creadbyte()
*函数功能：   使用i2c读取一个字节的数据
*输入：       null
*输出：       dat
*备注：       接收完数据 SDA = 1  SCL = 0
*************************************************************/

unsigned char i2creadbyte()
{
	unsigned char a = 0, dat = 0;
	SDA = 1;
	delay10us();
	for (a = 0; a < 8; a++)
	{
		SCL = 1;
		delay10us();
		dat = dat << 1;
		delay10us();
		dat |= SDA;
		delay10us();
		SCL = 0;
		delay10us();
	}
	return dat;
}

/**************************************************************
*函数名：     at24c02write(unsigned char date, unsignet char addr)
*函数功能：   往at24c02写入一个数据
*输入：       null
*输出：       null     
**************************************************************/

void at24c02write(unsigned char addr, unsigned char dat)
{
    i2cstart();			 
	i2csendbyte(0xa0);	 //发送写器件地址
	i2csendbyte(addr);	 //发送要写入的内存地址
	i2csendbyte(dat);	 //发送数据
	i2cstop();
}

/***************************************************************
*函数名：     at24c02read(unsigned char addr)
*函数功能：   从at24c02读取一个数据
*输入：       null
*输出：       num
***************************************************************/

unsigned char at24c02read(unsigned char addr)
{
    unsigned char num;
    i2cstart();
	i2csendbyte(0xa0);
	i2csendbyte(addr);
    i2cstart();
	i2csendbyte(0xa1);
	num = i2creadbyte();
	i2cstop();
	return num;
}







