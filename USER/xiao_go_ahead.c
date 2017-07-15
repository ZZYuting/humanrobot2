#include "uart5.h"
/*
xiaol_tai0();
xiaol_tai1();
xiaol_mai();
xiaol_luo0();
xiaol_luo1();
xiaol_luo2();
xiaor_tai0();
xiaor_tai1();
xiaor_mai();
xiaor_luo0();
xiaor_luo1();
*/
void xiaol_tai0()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,512,150);
Action_write(02,468,150);
Action_write(03,266,150);
Action_write(04,453,150);
Action_write(05,616,150);
Action_write(11,512,150);
Action_write(12,545,150);
Action_write(13,731,150);
Action_write(14,588,150);
Action_write(15,539,200);
Action();
	}
}
void xiaol_tai1()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,512,150);
Action_write(02,472,150);
Action_write(03,269,150);
Action_write(04,453,150);
Action_write(05,503,150);
Action_write(11,512,150);
Action_write(12,544,150);
Action_write(13,729,150);
Action_write(14,590,150);
Action_write(15,582,150);
Action();
	}
}
void xiaol_mai()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,512,100);
Action_write(02,450,100);
Action_write(03,320,100);
Action_write(04,422,100);
Action_write(05,570,100);
Action_write(11,512,100);
Action_write(12,544,100);
Action_write(13,729,100);
Action_write(14,590,100);
Action_write(15,582,100);
Action();
	}
}
void xiaol_luo0()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,510,150);
Action_write(02,447,150);
Action_write(03,320,150);
Action_write(04,422,150);
Action_write(05,602,150);
Action_write(11,507,150);
Action_write(12,544,150);
Action_write(13,729,150);
Action_write(14,589,150);
Action_write(15,536,050);

Action();
	}
}
void xiaol_luo1()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,512,150);
Action_write(02,449,150);
Action_write(03,320,150);
Action_write(04,427,150);
Action_write(05,505,150);
Action_write(11,507,150);
Action_write(12,548,150);
Action_write(13,727,150);
Action_write(14,584,150);
Action_write(15,516,150);
Action();
	}
}
void xiaol_luo2()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,511,150);
Action_write(02,478,150);
Action_write(03,295,150);
Action_write(04,432,150);
Action_write(05,506,150);
Action_write(11,506,150);
Action_write(12,530,150);
Action_write(13,726,150);
Action_write(14,594,150);
Action_write(15,514,150);
Action();
	}
}
void xiaor_tai0()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,510,150);
Action_write(02,478,150);
Action_write(03,295,150);
Action_write(04,432,150);
Action_write(05,474,150);
Action_write(11,504,150);
Action_write(12,529,150);
Action_write(13,716,150);
Action_write(14,609,150);
Action_write(15,388,150);
Action();
	}
	}

void xiaor_tai1()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,517,150);
Action_write(02,474,150);
Action_write(03,297,150);
Action_write(04,424,150);
Action_write(05,442,150);
Action_write(11,516,150);
Action_write(12,533,150);
Action_write(13,716,150);
Action_write(14,609,150);
Action_write(15,418,150);
Action();
	}
}
void xiaor_mai()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,512,150);
Action_write(02,480,150);
Action_write(03,295,150);
Action_write(04,434,150);
Action_write(05,442,150);
Action_write(11,512,150);
Action_write(12,574,150);
Action_write(13,690,150);
Action_write(14,602,150);
Action_write(15,454,150);
Action();
	}
}
void xiaor_luo0()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,511,150);
Action_write(02,475,150);
Action_write(03,291,150);
Action_write(04,432,150);
Action_write(05,484,050);
Action_write(11,511,150);
Action_write(12,573,150);
Action_write(13,688,150);
Action_write(14,600,150);
Action_write(15,409,150);
Action();
	}
}
void xiaor_luo1()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,511,150);
Action_write(02,473,150);
Action_write(03,289,150);
Action_write(04,430,150);
Action_write(05,508,150);
Action_write(11,510,150);
Action_write(12,574,150);
Action_write(13,689,150);
Action_write(14,600,150);
Action_write(15,513,100);
Action();
	}
}
