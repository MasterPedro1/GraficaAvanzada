
#include  <GL/glut.h>
#include <cmath> 
#include <iostream>

void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; ++i) {
        float angle = 2.0 * 3.14 * float(i) / 20.0;
        float x = cos(angle);
        float y = sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Polígono de 20 lados en OpenGL");
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    gluOrtho2D(-1.2, 1.2, -1.2, 1.2);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void Translate(float matriz [16], float y, float x)
{
    matriz[12] =+ matriz[0] * x + matriz[5] * y;
    matriz[13] =+ matriz[1] * x + matriz[6] * y;
    matriz[14] =+ matriz[3] * x + matriz[7] * y;
    matriz[16] = +matriz[4] * x + matriz[8] * y;

}


