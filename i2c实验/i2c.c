#include "i2c.h"
/*******************************************
*��������       delay10us()
*�������ܣ�     ��ʱ10us
*���룺         null
*�����         null
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
*��������       i2cstart()
*�������ܣ�     ��ʼ�źţ�SCLʱ���ź�Ϊ�ߵ�ƽ�ڼ�SDA�źŲ���һ���½���
*���룺         null
*�����         null
*��ע��         ��ʼ֮��SDA��SCL��Ϊ0
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
*��������       i2cstop()
*�������ܣ�     ��ֹ�źţ�SCLʱ���ź�Ϊ�ߵ�ƽ�ڼ�SDA�źŲ���һ��������
*���룺         null
*�����         null
*��ע��         ��ֹ֮��SDA��SCL��Ϊ1����ʾ���߿���
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
*��������       i2csendbyte(unsigned char dat)
*�������ܣ�     ͨ��I2C����һ���ֽڡ���SCLʱ���źŸߵ�ƽ�ڼ䣬���ַ����ź�SDA�����ȶ�
*���룺			null
*�����         0��1�����ͳɹ�����1������ʧ�ܷ���0
*��ע��         ������һ���ֽڣ�SDA = 1,SCL = 0
********************************************/

unsigned char i2csendbyte(unsigned char dat)
{
	unsigned char a = 0, b = 0;
	for (a = 0; a < 8; a++)
	{
		SDA=dat>>7;	 //��ʼ�ź�֮��SCL=0�����Կ���ֱ�Ӹı�SDA�ź�
		dat=dat<<1;
		delay10us();
		SCL=1;
		delay10us();//����ʱ��>4.7us
		SCL=0;
		delay10us();
	}
	SDA = 1;
	delay10us();
	SCL = 1;
//	delay10us();
	while(SDA)//�ȴ�Ӧ��Ҳ���ǵȴ����豸��SDA����
	{
		b++;
		if(b>200)	 //�������2000usû��Ӧ����ʧ�ܣ�����Ϊ��Ӧ�𣬱�ʾ���ս���
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
*��������     i2creadbyte()
*�������ܣ�   ʹ��i2c��ȡһ���ֽڵ�����
*���룺       null
*�����       dat
*��ע��       ���������� SDA = 1  SCL = 0
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
*��������     at24c02write(unsigned char date, unsignet char addr)
*�������ܣ�   ��at24c02д��һ������
*���룺       null
*�����       null     
**************************************************************/

void at24c02write(unsigned char addr, unsigned char dat)
{
    i2cstart();			 
	i2csendbyte(0xa0);	 //����д������ַ
	i2csendbyte(addr);	 //����Ҫд����ڴ��ַ
	i2csendbyte(dat);	 //��������
	i2cstop();
}

/***************************************************************
*��������     at24c02read(unsigned char addr)
*�������ܣ�   ��at24c02��ȡһ������
*���룺       null
*�����       num
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







