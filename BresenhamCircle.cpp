#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include<iostream>

using namespace std;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}

void plotPoints(int x0, int x, int y0, int y)
{
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);

    glVertex2d(x0 + x, y0 + y);
    glVertex2d(x0 - x, y0 + y);
    glVertex2d(x0 + x, y0 - y);
    glVertex2d(x0 - x, y0 - y);
    glVertex2d(x0 + y, y0 + x);
    glVertex2d(x0 - y, y0 + x);
    glVertex2d(x0 + y, y0 - x);
    glVertex2d(x0 - y, y0 - x);

    glEnd();
    glFlush();
}

void drawCircleBres(int x0, int y0, int radius)
{
    int x = 0;
    int y = radius;

    int d = 3 - 2 * radius;

    plotPoints(x0, x, y0, y);

    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        plotPoints(x0, x, y0, y);
    }

}

void fucntionToDraw()
{
    int r, x, y;
    cout << "Enter radius of circle: ";
    cin >> r;

    cout << "Enter co-ordinates of center(x and y): ";
    cin >> x >> y;
    drawCircleBres(x, y, r);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    fucntionToDraw();
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bresenham Circle Drawing Algorithm: ");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}