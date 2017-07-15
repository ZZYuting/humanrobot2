#include "uart5.h"
/*
xiao_rightturn_mai();
xiao_rightturn_luo();
 xiao_rightturn_left_tai0();
 xiao_rightturn_left_tai0_tiaozheng();
  xiao_rightturn_left_tai1();
	
	*/
void xiao_rightturn_mai()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,515,150);
Action_write(02,479,150);
Action_write(03,297,150);
Action_write(04,436,150);
Action_write(05,444,150);
Action_write(11,539,150);
Action_write(12,573,150);
Action_write(13,706,150);
Action_write(14,604,150);
Action_write(15,471,150);
Action();
	}
}
void xiao_rightturn_luo()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,521,50);
Action_write(02,479,50);
Action_write(03,297,50);
Action_write(04,430,50);
Action_write(05,507,50);
Action_write(11,538,50);
Action_write(12,575,50);
Action_write(13,704,50);
Action_write(14,603,50);
Action_write(15,514,50);
Action();
	}
}
void xiao_rightturn_left_tai0()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,521,150);
Action_write(02,479,150);
Action_write(03,297,150);
Action_write(04,431,150);
Action_write(05,622,150);
Action_write(11,540,150);
Action_write(12,576,150);
Action_write(13,704,150);
Action_write(14,602,150);
Action_write(15,539,150);
Action();
	}
}
void xiao_rightturn_left_tai0_tiaozheng()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(02,495,150);
Action_write(03,308,150);
Action_write(04,405,150);
Action_write(05,622,150);
Action_write(11,538,150);
Action_write(12,544,150);
Action_write(13,730,150);
Action_write(14,607,150);
Action_write(15,540,150);
Action();
	}
}
void xiao_rightturn_left_tai1()
{
	unsigned char i;
	for(i=0;i<80;i++)
	{
Action_write(01,521,150);
Action_write(02,495,150);
Action_write(03,308,150);
Action_write(04,405,150);
Action_write(05,622,150);
Action_write(11,538,150);
Action_write(12,540,150);
Action_write(13,728,150);
Action_write(14,614,150);
Action_write(15,574,150);
Action();
	}
}