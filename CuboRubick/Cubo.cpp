#include <windows.h>
#include <GL/glut.h>
#include <cmath>

char title[] = "3D Shapes";
GLfloat rotationAngle = 0.0f;

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void timer(int value) {
    rotationAngle += 1.0f;
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.0f);
    glScalef(0.5f, 0.5f, 0.5f);

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    GLfloat X = 0.525731112119133606f;
    GLfloat Z = 0.850650808352039932f;
    GLfloat N = 0.0f;

    GLfloat icosahedronVertices[12][3] = {
        {-X, N, Z}, {X, N, Z}, {-X, N, -Z}, {X, N, -Z},
        {N, Z, X}, {N, Z, -X}, {N, -Z, X}, {N, -Z, -X},
        {Z, X, N}, {-Z, X, N}, {Z, -X, N}, {-Z, -X, N}
    };

    int icosahedronFaces[20][3] = {
        {0, 4, 1}, {0, 9, 4}, {9, 5, 4}, {4, 5, 8}, {4, 8, 1},
        {8, 10, 1}, {8, 3, 10}, {5, 3, 8}, {5, 2, 3}, {2, 7, 3},
        {7, 10, 3}, {7, 6, 10}, {7, 11, 6}, {11, 0, 6}, {0, 1, 6},
        {6, 1, 10}, {9, 0, 11}, {9, 11, 2}, {9, 2, 5}, {7, 2, 11}
    };

    glTranslatef(0.0f, 0.0f, 1.0f);  // Separación en el eje Z

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 3; j++) {
            int vertexIndex = icosahedronFaces[i][j];
            if (i % 3 == 0) glColor3f(1.0f, 0.0f, 0.0f);  // Rojo
            else if (i % 3 == 1) glColor3f(0.0f, 1.0f, 0.0f);  // Verde
            else glColor3f(0.0f, 0.0f, 1.0f);  // Azul
            glVertex3f(icosahedronVertices[vertexIndex][0],
                icosahedronVertices[vertexIndex][1],
                icosahedronVertices[vertexIndex][2] + i * 0.1f); // Añadir separación
        }
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
