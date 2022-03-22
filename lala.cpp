#include <GL/glut.h>  
#include<iostream>  
using namespace std;
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 800.0);
}
void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void DDA(int x0, int y0, int x1, int y1) {
	int dx, dy, step;
	float X, Y, Xinc, Yinc;
	dx = x1 - x0;
	dy = y1 - y0;
	step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	Xinc = dx / (float)step;
	Yinc = dy / (float)step;
	X = x0;
	Y = y0;
	for (int i = 0;i <= step; i++) {
		glBegin(GL_POINTS);
		//glColor3f(0.0, 1.0, 0.0); 
		glVertex2f(round(X), round(Y));
		glEnd();
		X += Xinc;
		Y += Yinc;
	}
}



void ellipseMidPoint(int xCenter , int yCenter , int rx , int ry )
{
	  
	float x = 0;
	float y = ry;
	float p1 = ry * ry - (rx * rx) * ry + (rx * rx) * (0.25);
	float dx = 2 * (ry * ry) * x;
	float dy = 2 * (rx * rx) * y;
	while (dx < dy)
	{ 
		setPixel(xCenter + x, yCenter + y);
		setPixel(xCenter - x, yCenter + y);
		setPixel(xCenter + x, yCenter - y);
		setPixel(xCenter - x, yCenter - y);
		if (p1 < 0)
		{
			x = x + 1;
			dx = 2 * (ry * ry) * x;
			p1 = p1 + dx + (ry * ry);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			dx = 2 * (ry * ry) * x;
			dy = 2 * (rx * rx) * y;
			p1 = p1 + dx - dy + (ry * ry);
		}
	}
	
	float p2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y - 1) * (y - 1) - (rx * rx) * (ry * ry);
	while (y > 0)
	{ 
		setPixel(xCenter + x, yCenter + y);
		setPixel(xCenter - x, yCenter + y);
		setPixel(xCenter + x, yCenter - y);
		setPixel(xCenter - x, yCenter - y); 
		if (p2 > 0)
		{
			x = x;
			y = y - 1;
			dy = 2 * (rx * rx) * y; 
			p2 = p2 - dy + (rx * rx);
		}
		else {
			x = x + 1;
			y = y - 1;
			dy = dy - 2 * (rx * rx);
			dx = dx + 2 * (ry * ry);
			p2 = p2 + dx -dy + (rx * rx);
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);  
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0); 
	ellipseMidPoint(400,600,200,100);
	ellipseMidPoint(400,200,100,50);
	DDA(300, 200, 200, 600);
	DDA(500, 200, 600, 600);
	glFlush(); 
}


int main(int argc , char ** argv)
{
	
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Glass");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}