#include<GL/glut.h>
#include<math.h>

void line(int x1, int y1, int x2, int y2) {
    glColor3f(0.0, 0.4, 0.53);
    glPointSize(2.0);
 
    int steps;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    float xInc = (float)dx / (float)steps;
    float yInc = (float)dy / (float)steps;
    float x = x1, y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i < steps; i++) {
        glVertex2i(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
    glFlush();
}

void draw1(int x, int y, int xc, int yc)
{
    glVertex2f(xc + x, yc + y);
    glVertex2f(xc + x, yc - y);
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc - x, yc + y);
}
void ellipse(int rx, int ry, int xc, int yc)
{
    glBegin(GL_POLYGON);
    int x = 0, y = ry;
    int ry_sq = ry * ry;
    int rx_sq = rx * rx;
    int P = ry_sq - rx_sq * ry + 0.25 * rx_sq;
    while (ry_sq * x < rx_sq * y)
    {
        draw1(x, y, xc, yc);
        if (P < 0)
        {
            P += ry_sq * (2 * x + 3);
        }
        else {
            P += ry_sq * (2 * x + 3) + rx_sq * (-2 * y + 2);
            y--;
        }
        x++;
    }
    P = ry_sq * (x + float(1) / 2) * (x + float(1) / 2) + double(rx_sq) * (y - 1) * (y - 1) - double(rx_sq) * ry_sq;
    while (y >= 0)
    {
        draw1(x, y, xc, yc);
        if (P >= 0)
        {
            P += rx_sq * (-2 * y + 3);
        }
        else {
            P += ry_sq * (2 * x + 2) + rx_sq * (-2 * y + 3);
            x++;
        }
        y--;
    }
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.53); 
    line(210,130,190,310);
    line(370, 130, 390, 310);
    ellipse(80, 50, 290, 120);   //upper
    ellipse(100, 50, 290, 320);   //lower
    glFlush();
}
void myinit()
{
    glClearColor(0.3, 0.7, 0.6, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 699.0, 0.0, 499.0);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("GLASS");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
