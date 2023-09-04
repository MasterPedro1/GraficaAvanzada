#include <windows.h>
#include <GL/glut.h>
#include <cmath>

char title[] = "Icosahedron Rubik 3D";
float cameraRadius = 12.0f;
float cameraAngle = 0.0f;
float cameraHeight = 1.0f;
float centerPosition[3] = { 0.0f, 0.0f, 0.0f };
GLfloat drawBaseModelMatrix[16];

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, drawBaseModelMatrix);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void drawEquilateralTriangle() {
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 1.0f);

    // Triángulo superior
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.25f, 0.0f, 0.0f);
    glVertex3f(0.25f, 0.0f, 0.0f);

    // Triángulo izquierdo superior
    glVertex3f(-0.25f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);

    // Triángulo Medio Superior
    glVertex3f(-0.25f, 0.0f, 0.0f);
    glVertex3f(0.25f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);

    // Triángulo derecho superior
    glVertex3f(0.25f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);

    // Triángulo izquierdo medio
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(-0.75f, -1.0f, 0.0f);
    glVertex3f(-0.25f, -1.0f, 0.0f);

    // Triángulo central medio
    glVertex3f(0.0f, -0.5f, 0.0f);
    glVertex3f(-0.25f, -1.0f, 0.0f);
    glVertex3f(0.25f, -1.0f, 0.0f);

    // Triángulo derecho medio
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.25f, -1.0f, 0.0f);
    glVertex3f(0.75f, -1.0f, 0.0f);

    glEnd();
}

void drawIcosahedronRubik() {
    // Coordenadas de los vértices para un icosaedro regular
    GLfloat phi = (1.0f + sqrt(5.0f)) / 2.0f;

    GLfloat icosahedronVertices[12][3] = {
        {-1, phi, 0}, {1, phi, 0}, {-1, -phi, 0}, {1, -phi, 0},
        {0, -1, phi}, {0, 1, phi}, {0, -1, -phi}, {0, 1, -phi},
        {phi, 0, -1}, {phi, 0, 1}, {-phi, 0, -1}, {-phi, 0, 1}
    };

    int icosahedronFaces[20][3] = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 20; i++) {
        if (i % 3 == 0)
            glColor3f(1.0f, 0.0f, 0.0f);  // Rojo
        else if (i % 3 == 1)
            glColor3f(0.0f, 1.0f, 0.0f);  // Verde
        else
            glColor3f(0.0f, 0.0f, 1.0f);  // Azul

        for (int j = 0; j < 3; j++) {
            int vertexIndex = icosahedronFaces[i][j];
            glVertex3fv(icosahedronVertices[vertexIndex]);
        }
    }
    glEnd();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float cameraX = centerPosition[0] + cameraRadius * sin(cameraAngle);
    float cameraZ = centerPosition[2] + cameraRadius * cos(cameraAngle);

    gluLookAt(cameraX, cameraHeight, cameraZ, centerPosition[0], centerPosition[1], centerPosition[2], 0.0f, 1.0f, 0.0f);

    drawIcosahedronRubik();

    glutSwapBuffers();
}

// Función de actualización de la cámara
void updateCamera(int value) {
    cameraAngle += 0.005f; // Ajusta la velocidad de rotación
    if (cameraAngle > 2 * 3.14) {
        cameraAngle -= 2 * 3.14;
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateCamera, 0); // 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, updateCamera, 0);
    glutMainLoop();
    return 0;
}