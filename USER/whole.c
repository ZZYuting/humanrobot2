#include "uart5.h"
#include "action.h"
void jiance(void);
extern u8 go_flag;  //left=0  right=1
extern u8 zhangai_flag;

void go_ahead_left()
{
		go_flag=1;
	l_mai();
	l_luo0();
	l_luo1();
	jiance();
	r_tai0();
	r_tai1();

}
void go_ahead_right()
{
	go_flag=0;
	r_mai();
	r_luo0();
	r_luo1();
	jiance();
	l_second_tai0();
	l_second_tai1();
	
}
void xiao_go_ahead_left()
{
	go_flag=1;
	xiaol_mai();
	xiaol_luo0();
	xiaol_luo1();
	jiance();
	xiaor_tai0();
	xiaor_tai1();
	

}
void xiao_go_ahead_right()
{
	go_flag=0;
	xiaor_mai();
	xiaor_luo0();
	xiaor_luo1();
	jiance();
	xiaol_tai0();
	xiaol_tai1();
	
}


void xiao_leftturn()
{
	go_flag=0;
	xiao_leftturn_mai(); //×ó½Å×ª
	xiao_leftturn_luo();
	xiao_leftturn_right_tai0();
	xiao_leftturn_right_tai0_tiaozheng();
	xiao_leftturn_right_tai1();
	r_mai();
	r_luo0();
	r_luo1();
	jiance();
	
	l_second_tai0();
	l_second_tai1();
	
	
}

void xiao_rightturn()
{
		go_flag=1;

	xiao_rightturn_mai();
	xiao_rightturn_luo();
	xiao_rightturn_left_tai0();
	xiao_rightturn_left_tai0_tiaozheng();
	xiao_rightturn_left_tai1();
	l_mai();
	l_luo0();
	l_luo1();
	jiance();
	r_tai0();
	r_tai1();
}
void big_leftturn()
{
//	xiao_leftturn_mai(); //×ó½Å×ª
//	xiao_leftturn_luo();
//	xiao_leftturn_right_tai0();
//	xiao_leftturn_right_tai0_tiaozheng();
//	xiao_leftturn_right_tai1();
//	r_mai();
//	r_luo0();
//	r_luo1();
//		l_second_tai0();
//	l_second_tai1();
	go_flag=0;
	/* 
	×ó¹ÕÒ»´Î*/
	xiao_leftturn_mai(); //×ó½Å×ª
	xiao_leftturn_luo();
	xiao_leftturn_right_tai0();
	xiao_leftturn_right_tai0_tiaozheng();
	xiao_leftturn_right_tai1();
	r_mai();
	r_luo0();
	r_luo1();
		jiance();
	l_second_tai0();
	l_second_tai1();



			/* 
	×ó¹ÕÈ2--´Î²¢¼ì²â*/
}
void big_rightturn()
{
		go_flag=1;
	xiao_rightturn_mai();
	xiao_rightturn_luo();
	xiao_rightturn_left_tai0();
	xiao_rightturn_left_tai0_tiaozheng();
	xiao_rightturn_left_tai1();
	l_mai();
	l_luo0();
	l_luo1();
	r_tai0();
	r_tai1();
	/*
ÓÒ×ªÒ»´Î	
	*/
	
	
//	xiao_rightturn_mai();
//	xiao_rightturn_luo();
//	xiao_rightturn_left_tai0();
//	xiao_rightturn_left_tai0_tiaozheng();
//	xiao_rightturn_left_tai1();
//	l_mai();
//	l_luo0();
//	l_luo1();
//	r_tai0();
//	r_tai1();
			//2
	xiao_rightturn_mai();
	xiao_rightturn_luo();
	xiao_rightturn_left_tai0();
	xiao_rightturn_left_tai0_tiaozheng();
	xiao_rightturn_left_tai1();
	l_mai();
	l_luo0();
	l_luo1();
	jiance();
	r_tai0();
	r_tai1();		
			/*
ÓÒ×ªÈý-´Î²¢¼ì²â	
	*/
}
void x_left()
{
	go_flag=1;
	x_l_mai();
	x_l_luo0();
	x_l_luo1();
	jiance();
	x_r_tai0();
	x_r_tai1();


}

void x_right()
{
	go_flag=0;
	x_r_mai();
	x_r_luo0();
	x_r_luo1();
	jiance();
	x_l_second_tai0();
	x_l_second_tai1();

}


void kuazhang(void)
{
	u8 i=0;
	if(go_flag==1) 
	{
		xiaor_tai0();
		xiaor_tai1();
		xiaor_mai();
		xiaor_luo0();
		xiaor_luo1();	
	}   
	xiaol_tai0();
	xiaol_tai1();

//tiaozheng	
	for(i=0;i<100;i++)
	{
Action_write(01,512,050);
Action_write(02,492,050);
Action_write(03,320,050);
Action_write(04,363,050);
Action_write(05,560,050);
Action_write(11,512,050);
Action_write(12,544,050);
Action_write(13,729,050);
Action_write(14,595,050);
Action_write(15,582,050);
Action();
	}	
			
//×óÆðÂõ
	for(i=0;i<100;i++)
	{
Action_write(01,490,050);
Action_write(02,320,050);
Action_write(03,325,050);
Action_write(04,504,050);
Action_write(05,550,050);
Action_write(11,512,050);
Action_write(12,482,050);
Action_write(13,743,050);
Action_write(14,590,050);
Action_write(15,579,050);
Action();
	}
//	¿çÕÏ´íÎ»Âä	
		for(i=0;i<100;i++)
	{
//Action_write(01,450,200);
//Action_write(02,399,150);
//Action_write(03,263,200);
//Action_write(04,570,200);
//Action_write(05,505,150);
//Action_write(11,450,200);
//Action_write(12,379,200);
//Action_write(13,711,150);
//Action_write(14,734,250);
//Action_write(15,508,150);
Action_write(01,490,200);
Action_write(02,399,150);
Action_write(03,263,200);
Action_write(04,570,150);
Action_write(05,505,150);
Action_write(11,512,200);
Action_write(12,379,200);
Action_write(13,711,150);
Action_write(14,734,250);
Action_write(15,508,150);
		
		
		//zheng luo
Action();
	}
	//xuan  zhuan
			for(i=0;i<100;i++)
	{
//Action_write(01,509,200);
//Action_write(02,410,200);
//Action_write(03,357,200);
//Action_write(04,426,200);
//Action_write(05,498,200);
//Action_write(11,378,200);
//Action_write(12,364,200);
//Action_write(13,845,200);
//Action_write(14,739,200);
//Action_write(15,549,200);
Action_write(01,509,200);
Action_write(02,410,200);
Action_write(03,357,200);
Action_write(04,426,200);
Action_write(05,498,200);
Action_write(11,358,200);
Action_write(12,364,200);
Action_write(13,845,200);
Action_write(14,739,200);
Action_write(15,549,200);
Action();
	}
	
	//ÓÒÌ§
				for(i=0;i<100;i++)
	{
Action_write(01,512,300);
Action_write(02,459,300);
Action_write(03,318,300);
Action_write(04,414,300);
Action_write(05,450,300);
Action_write(11,512,150);
Action_write(12,495,150);
Action_write(13,736,150);
Action_write(14,615,150);
Action_write(15,480,150);
Action();
	}
	//ÓÒÆðÂõ
					for(i=0;i<100;i++)
	{
Action_write(01,512,050);
Action_write(02,542,050);
Action_write(03,281,050);
Action_write(04,434,050);
Action_write(05,445,050);
Action_write(11,534,050);
Action_write(12,704,050);
Action_write(13,699,050);
Action_write(14,520,050);
Action_write(15,474,050);
Action();
	}
	//ÓÒºóÌß
						for(i=0;i<100;i++)
	{
Action_write(01,512,80);
Action_write(02,542,80);
Action_write(03,281,80);
Action_write(04,434,80);
Action_write(05,453,80);
Action_write(11,512,80);
Action_write(12,565,80);
Action_write(13,709,80);
Action_write(14,570,80);
Action_write(15,407,80);
Action();
	}
	
r_luo0();
r_luo1();
//jiance();
xiaol_tai0();
xiaol_tai1();
for(i=0;i>=2;i++){
xiao_leftturn_mai(); //×ó½Å×ª
xiao_leftturn_luo();
xiao_leftturn_right_tai0();
xiao_leftturn_right_tai0_tiaozheng();
xiao_leftturn_right_tai1();
r_mai();
r_luo0();
r_luo1();
l_second_tai0();
l_second_tai1();
}

	go_flag = 0;
	zhangai_flag=0;
}
void g_xiao_rightturn(void)
{
	xiao_rightturn_mai();
	xiao_rightturn_luo();
	xiao_rightturn_left_tai0();
	xiao_rightturn_left_tai0_tiaozheng();
	xiao_rightturn_left_tai1();
	xiaol_mai();
	xiaol_luo0();
	xiaol_luo1();
	xiaol_luo2();
	jiance();
	xiaor_tai0();
	xiaor_tai1();
	go_flag=1;
}
void g_xiao_leftturn(void)
{
	xiao_leftturn_mai(); //×ó½Å×ª
	xiao_leftturn_luo();
	xiao_leftturn_right_tai0();
	xiao_leftturn_right_tai0_tiaozheng();
	xiao_leftturn_right_tai1();
	xiaor_mai();
	xiaor_luo0();
	xiaor_luo1();
	jiance();	
	xiaol_tai0();
	xiaol_tai1();
	go_flag=0;
}