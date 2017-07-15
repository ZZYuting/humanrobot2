#include "uart5.h"

void jiance(void);

/*
xiao_leftturn_mai();
xiao_leftturn_luo();
xiao_leftturn_right_tai0();
xiao_leftturn_right_tai0_tiaozheng();
xiao_leftturn_right_tai1();

*/



void xiao_leftturn_mai()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,485,150);
Action_write(02,451,150);
Action_write(03,318,150);
Action_write(04,420,150);
Action_write(05,553,150);
Action_write(11,509,150);
Action_write(12,545,150);
Action_write(13,727,150);
Action_write(14,588,150);
Action_write(15,580,150);
Action();
	}
}
void xiao_leftturn_luo()
{
	unsigned char i;
	for(i=0;i<25;i++)
	{
Action_write(01,486,050);
Action_write(02,449,050);
Action_write(03,320,050);
Action_write(04,421,050);
Action_write(05,510,050);
Action_write(11,503,050);
Action_write(12,545,050);
Action_write(13,727,050);
Action_write(14,594,050);
Action_write(15,517,050);
Action();
	}
}
void xiao_leftturn_right_tai0()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,484,150);
Action_write(02,448,150);
Action_write(03,320,150);
Action_write(04,422,150);
Action_write(05,485,150);
Action_write(11,503,150);
Action_write(12,545,150);
Action_write(13,727,150);
Action_write(14,593,150);
Action_write(15,402,150);
Action();
	}
}
void xiao_leftturn_right_tai0_tiaozheng()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,486,150);
Action_write(02,480,150);
Action_write(03,294,150);
Action_write(04,417,150);
Action_write(05,484,150);
Action_write(11,503,150);
Action_write(12,529,150);
Action_write(13,716,150);
Action_write(14,619,150);
Action_write(15,402,150);
Action();
	}
}
void xiao_leftturn_right_tai1()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,486,150);
Action_write(02,484,150);
Action_write(03,296,150);
Action_write(04,410,150);
Action_write(05,450,150);
Action_write(11,503,150);
Action_write(12,529,150);
Action_write(13,716,150);
Action_write(14,619,150);
Action_write(15,402,150);
Action();
	}
}