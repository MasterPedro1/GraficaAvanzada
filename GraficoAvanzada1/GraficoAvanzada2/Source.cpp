
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <Windows.h> // Para la función Sleep

float translationX = 0.0f;
float translationY = 0.0f;

void applyTranslationMatrix(float matrix[16], float tx, float ty) {
    matrix[12] += matrix[0] * tx + matrix[4] * ty;
    matrix[13] += matrix[1] * tx + matrix[5] * ty;
    matrix[14] += matrix[2] * tx + matrix[6] * ty;
    matrix[15] += matrix[3] * tx + matrix[7] * ty;
}

void drawPolygon() {
    float translationMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        translationX, translationY, 0.0f, 1.0f
    };

    applyTranslationMatrix(translationMatrix, translationX, translationY);

    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(translationMatrix);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; ++i) {
        float angle = 2.0 * 3.14159265358979323846 * float(i) / 20.0;
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
    glutCreateWindow("Polígono de 20 lados con traslación en OpenGL");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-1.2, 1.2, -1.2, 1.2);
    glutDisplayFunc(display);

    while (true) {
        if (GetAsyncKeyState(VK_LEFT)) {
            translationX -= 0.01f;
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            translationX += 0.01f;
        }
        if (GetAsyncKeyState(VK_UP)) {
            translationY += 0.01f;
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            translationY -= 0.01f;
        }

        glutPostRedisplay();
        Sleep(10);
    }

    glutMainLoop();
    return 0;
}