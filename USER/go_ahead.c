#include "uart5.h"
void jiance(void);
/*
zhili();
l_first_tai0();
l_first_tai1();
l_mai();
l_luo0();
l_luo1();
r_tai0();
r_tai1();
r_mai();
r_luo0();
r_luo1();
l_second_tai0();
l_second_tai1();
*/


void zhili()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,512,150);
Action_write(02,470,150);
Action_write(03,267,150);
Action_write(04,452,150);
Action_write(05,503,150);
Action_write(11,512,150);
Action_write(12,548,150);
Action_write(13,731,150);
Action_write(14,586,150);
Action_write(15,516,150);
Action();
	}
}
void l_first_tai0()
{
	unsigned char i;
	for(i=0;i<20;i++)
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
void l_first_tai1()
{
	unsigned char i;
	for(i=0;i<20;i++)
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
void l_mai()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,512,50);
Action_write(02,459,50);
Action_write(03,315,50);
Action_write(04,454,50);
Action_write(05,594,50);
Action_write(11,512,50);
Action_write(12,482,50);
Action_write(13,743,50);
Action_write(14,590,50);
Action_write(15,579,50);
		Action();
	}
}
void l_luo0()
{
	unsigned char i;
	for(i=0;i<55;i++)
	{
Action_write(01,512,100);
Action_write(02,458,050);
Action_write(03,317,050);
Action_write(04,458,050);
Action_write(05,570,050);
Action_write(11,512,050);
Action_write(12,480,050);
Action_write(13,741,050);
Action_write(14,600,050);
Action_write(15,527,050);
Action();
	}
}
void l_luo1()
{
	unsigned char i;
	for(i=0;i<55;i++)
	{
Action_write(01,512,80);
Action_write(02,464,80);
Action_write(03,319,80);
Action_write(04,421,80);
Action_write(05,506,80);
Action_write(11,512,80);
Action_write(12,479,80);
Action_write(13,737,80);
Action_write(14,637,80);
Action_write(15,512,80);
Action();
	}
}
void r_tai0()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,512,150);
Action_write(02,459,150);
Action_write(03,318,150);
Action_write(04,414,150);
Action_write(05,489,150);
Action_write(11,512,150);
Action_write(12,495,150);
Action_write(13,736,150);
Action_write(14,635,150);
Action_write(15,419,150);
Action();
	}
}
void r_tai1()
{
	unsigned char i;
	for(i=0;i<20;i++)
	{
Action_write(01,512,150);
Action_write(02,459,150);
Action_write(03,318,150);
Action_write(04,414,150);
Action_write(05,450,150);
Action_write(11,512,150);
Action_write(12,495,150);
Action_write(13,736,150);
Action_write(14,635,150);
Action_write(15,419,150);
Action();
	}
}
void r_mai()
{
	unsigned char i;
	for(i=0;i<55;i++)
	{
Action_write(01,512,80);
Action_write(02,542,80);
Action_write(03,281,80);
Action_write(04,434,80);
Action_write(05,448,80);
Action_write(11,512,80);
Action_write(12,565,80);
Action_write(13,709,80);
Action_write(14,570,80);
Action_write(15,467,80);
Action();
	}
}
void r_luo0()
{
	unsigned char i;
	for(i=0;i<55;i++)
	{
Action_write(01,512,50);
Action_write(02,544,50);
Action_write(03,283,50);
Action_write(04,424,50);
Action_write(05,497,50);
Action_write(11,512,50);
Action_write(12,566,50);
Action_write(13,707,50);
Action_write(14,569,50);
Action_write(15,454,50);
Action();
	}
}
void r_luo1()
{
	unsigned char i;
	for(i=0;i<35;i++)
	{
Action_write(01,512,150);
Action_write(02,562,150);
Action_write(03,281,150);
Action_write(04,375,150);
Action_write(05,502,150);
Action_write(11,512,150);
Action_write(12,544,150);
Action_write(13,691,150);
Action_write(14,605,150);
Action_write(15,506,150);
Action();
	}
}
void l_second_tai0()
{
	unsigned char i;
	for(i=0;i<25;i++)
	{
Action_write(01,512,150);
Action_write(02,562,150);
Action_write(03,282,150);
Action_write(04,378,150);
Action_write(05,616,150);
Action_write(11,511,150);
Action_write(12,544,150);
Action_write(13,688,150);
Action_write(14,603,150);
Action_write(15,534,150);
Action();
	}
}
void l_second_tai1()
{
	unsigned char i;
	for(i=0;i<25;i++)
	{
Action_write(01,512,50);
Action_write(02,472,50);
Action_write(03,269,50);
Action_write(04,453,50);
Action_write(05,503,50);
Action_write(11,512,50);
Action_write(12,544,50);
Action_write(13,729,50);
Action_write(14,595,50);
Action_write(15,582,50);
Action();
	}
}