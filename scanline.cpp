#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
int LE[500], RE[500];
void init() {
    glLoadIdentity();
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
void intersection(GLint x1, GLint y1, GLint x2, GLint y2) {
    float x, M;
    int t, y;
    if (y1 > y2)
    {
        t = x1;
        x1 = x2;
        x2 = t;
        t = y1;
        y1 = y2;
        y2 = t;
    }
    if ((y2 - y1) == 0) M = (x2 - x1);
    else M = (x2 - x1) / (y2 - y1);

    x = x1;
    for (y = y1; y <= y2; y++)
    {
        if (x < LE[y])LE[y] = x;
        if (x > RE[y])RE[y] = x;
        x = x + M;
    }
}
void display()
{
    GLint P1[2] = { 125, 250 }, P2[2] = { 250, 125 }, P3[2] = { 375, 250 }, P4[2] = { 250, 375 };
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < 500; i++)
    {
        LE[i] = 500;
        RE[i] = 0;
    }
    intersection(P1[0], P1[1], P2[0], P2[1]);
    intersection(P2[0], P2[1], P3[0], P3[1]);
    intersection(P3[0], P3[1], P4[0], P4[1]);
    intersection(P4[0], P4[1], P1[0], P1[1]);
    for (int y = 0; y < 500; y++)
    {
        for (int x = LE[y]; x < RE[y]; x++)
        {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Scan Line");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}