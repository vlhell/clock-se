#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>
#define PI 3.1415926536
#define RAD 165

int h_angle, m_angle, s_angle, gdr = DETECT, gm, err, max_x, max_y;
unsigned long long time_h = 0, time_m = 0, time_s = 0;

int AngleX(int angle, int radius = RAD)
{
	return -1 * sin(angle * PI / 180) * radius;
}

int AngleY(int angle, int radius = RAD)
{
	return cos(angle * PI / 180) * radius;
}

void lines(int cX, int cY)
{
	line(cX + AngleX(s_angle, 10), cY + AngleY(s_angle, 10), cX + AngleX(s_angle, RAD - 15), cY + AngleY(s_angle, RAD - 15));
	line(cX + AngleX(m_angle, 10), cY + AngleY(m_angle, 10), cX + AngleX(m_angle, RAD / 1.4), cY + AngleY(m_angle, RAD / 1.4));
	line(cX + AngleX(h_angle, 10), cY + AngleY(h_angle, 10), cX + AngleX(h_angle, RAD / 2.1), cY + AngleY(h_angle, RAD / 2.1));
}

void numbs(int cX, int cY)
{
	outtextxy(cX + AngleX(180) - 8, cY + AngleY(180) - 25, "12");
	outtextxy(cX + AngleX(180 + 30 * 1) + 10, cY + AngleY(180 + 30 * 1) - 20, "1");
	outtextxy(cX + AngleX(180 + 30 * 2) + 15, cY + AngleY(180 + 30 * 2) - 15, "2");
	outtextxy(cX + AngleX(180 + 30 * 3) + 20, cY + AngleY(180 + 30 * 3) - 5, "3");
	outtextxy(cX + AngleX(180 + 30 * 4) + 13, cY + AngleY(180 + 30 * 4) + 10, "4");
	outtextxy(cX + AngleX(180 + 30 * 5) + 5, cY + AngleY(180 + 30 * 5) + 15, "5");
	outtextxy(cX + AngleX(180 + 30 * 6) - 3, cY + AngleY(180 + 30 * 6) + 18, "6");
	outtextxy(cX + AngleX(180 + 30 * 7) - 20, cY + AngleY(180 + 30 * 7) + 15, "7");
	outtextxy(cX + AngleX(180 + 30 * 8) - 22, cY + AngleY(180 + 30 * 8) + 10, "8");
	outtextxy(cX + AngleX(180 + 30 * 9) - 25, cY + AngleY(180 + 30 * 9) - 5, "9");
	outtextxy(cX + AngleX(180 + 30 * 10) - 30, cY + AngleY(180 + 30 * 10) - 15, "10");
	outtextxy(cX + AngleX(180 + 30 * 11) - 25, cY + AngleY(180 + 30 * 11) - 20, "11");
}

void draw_w(int max_x, int max_y)
{
	int cX = max_x / 2, cY = max_y / 2, i, j;
	setcolor(0);

	setfillstyle(SOLID_FILL, 0);
	floodfill(20, 20, 0);

	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(8);

	circle(cX, cY, 7);
	setfillstyle(SOLID_FILL, 8);
	floodfill(cX, cY, 8);

	circle(cX, cY, RAD);
	setfillstyle(SOLID_FILL, 15);
	floodfill(cX + 15, cY + 15, 8);

	rectangle(cX - RAD - 40, cY - RAD - 40, cX + RAD + 40, cY + RAD + 40);
	setfillstyle(SOLID_FILL, 6);
	floodfill(cX - 10, cY - RAD - 10, 8);

	setcolor(15);
	settextstyle(GOTHIC_FONT, 0, 1);
	numbs(cX, cY);

	setcolor(8);

	for (i = 0; i < 12; i++)
	{
		int t = 180 + 30 * i;
		line(cX + AngleX(t, RAD - 10), cY + AngleY(t, RAD - 10), cX + AngleX(t, RAD + 10), cY + AngleY(t, RAD + 10));
		for (j = 1; j < 5; j++)
		{
			t += 6;
			line(cX + AngleX(t, RAD - 5), cY + AngleY(t, RAD - 5), cX + AngleX(t, RAD + 5), cY + AngleY(t, RAD + 5));
		}
	}
}

void main()
{
	printf("Enter time in format h:m:s\n");
	scanf("%u:%u:%u", &time_h, &time_m, &time_s);
	h_angle = 180 + 30 * time_h + 6 * (time_m / 12);
	m_angle = 180 + 6 * time_m;
	s_angle = 180 + 6 * time_s;
	initgraph(&gdr, &gm, "C:\\TURBOC3\\BGI");
	max_x = getmaxx();
	max_y = getmaxy();
	int cX = max_x / 2;
	int cY = max_y / 2;
	setviewport(10, 10, max_x - 10, max_y - 10, 1);
	draw_w(max_x, max_y);
	while (!kbhit())
	{
		//clear
		setcolor(15);
		lines(cX, cY);
		s_angle += 6;
		if (s_angle == 540)
		{
			s_angle = 180;
			m_angle += 6;
			if ((m_angle - 180) % 12 == 0)
				h_angle += 6;
		}
		//draw
		setcolor(0);
		lines(cX, cY);
		sound(200);
		delay(100);
		nosound();
		delay(900);
	}
	closegraph();
	return;
}
