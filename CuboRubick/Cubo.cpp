#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#define M_PI 3.14159265358979323846
#include <vector>


char title[] = "Icosahedron Rubik 3D";
float cameraRadius = 12.0f;
float cameraAngle = 0.0f;
float cameraHeight = 1.0f;
float centerPosition[3] = { 0.0f, 0.0f, 0.0f };
GLfloat drawBaseModelMatrix[16];
int lastMouseX, lastMouseY;
bool mouseRotating = false;


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

// Índices de los vértices de las caras a rotar
int faceVerticesIndices[5][3] = {
    {0, 1, 2},  // Cara 1
    {3, 4, 5},  // Cara 2
    {6, 7, 8},  // Cara 3
    {9, 10, 11},  // Cara 4
    {12, 13, 14}  // Cara 5
};

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

void subdivideTriangle(float* v1, float* v2, float* v3) {
    // Implementa la subdivisión de triángulos aquí
    // Debes dividir los triángulos y definir colores para cada vértice
    // Aquí se muestra una subdivisión simple como ejemplo:
    float mid1[3], mid2[3], mid3[3];

    for (int i = 0; i < 3; i++) {
        mid1[i] = (v1[i] + v2[i]) / 2.0f;
        mid2[i] = (v2[i] + v3[i]) / 2.0f;
        mid3[i] = (v1[i] + v3[i]) / 2.0f;
    }

    glBegin(GL_TRIANGLES);
    // Triángulo 1
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3fv(v1);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3fv(mid1);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3fv(mid3);

    // Triángulo 2
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3fv(mid3);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3fv(mid2);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3fv(v3);
    glEnd();
}



void drawIcosahedronRubik() {
    // Lista de colores únicos para cada cara
    GLfloat colors[20][3] = {
        {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.0f}, {0.0f, 0.5f, 0.5f}, {0.5f, 0.0f, 0.5f}, {0.5f, 0.5f, 0.5f},
        {0.0f, 0.25f, 0.25f}, {0.25f, 0.0f, 0.25f}, {0.25f, 0.25f, 0.0f}, {0.75f, 0.75f, 0.75f}, {0.0f, 0.75f, 0.75f},
        {0.75f, 0.0f, 0.75f}, {0.75f, 0.75f, 0.0f}, {0.25f, 0.5f, 0.75f}, {0.75f, 0.25f, 0.5f}, {0.5f, 0.75f, 0.25f}
    };

    for (int i = 0; i < 20; i++) {
        glBegin(GL_TRIANGLES);

        glColor3fv(colors[i]);

        int v1Index = icosahedronFaces[i][0];
        int v2Index = icosahedronFaces[i][1];
        int v3Index = icosahedronFaces[i][2];

        float v1[3] = { icosahedronVertices[v1Index][0], icosahedronVertices[v1Index][1], icosahedronVertices[v1Index][2] };
        float v2[3] = { icosahedronVertices[v2Index][0], icosahedronVertices[v2Index][1], icosahedronVertices[v2Index][2] };
        float v3[3] = { icosahedronVertices[v3Index][0], icosahedronVertices[v3Index][1], icosahedronVertices[v3Index][2] };

        glVertex3fv(v1);
        glVertex3fv(v2);
        glVertex3fv(v3);

        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float cameraX = centerPosition[0] + cameraRadius * sin(cameraAngle);
    float cameraZ = centerPosition[2] + cameraRadius * cos(cameraAngle);

    gluLookAt(cameraX, cameraHeight, cameraZ, centerPosition[0], centerPosition[1], centerPosition[2], 0.0f, 1.0f, 0.0f);

    drawIcosahedronRubik();  // Dibuja las caras de los triángulos con colores únicos

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastMouseX = x;
            lastMouseY = y;
            mouseRotating = true;
        }
        else if (state == GLUT_UP) {
            mouseRotating = false;
        }
    }
}

void motion(int x, int y) {
    if (mouseRotating) {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;
        cameraAngle += deltaX * 0.01f;
        cameraHeight += deltaY * 0.01f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}


void rotateVertex(int vertexIndex, float angle) {
    // Obtener el vértice a rotar
    float* vertex = icosahedronVertices[vertexIndex];

    // Verificar si el vértice es el vértice central (el del centro del icosaedro)
    bool isCentralVertex = (vertexIndex == 0);

    // Crear una lista de vértices conectados al vértice que se va a girar
    int connectedVertices[5];
    for (int i = 0; i < 5; i++) {
        connectedVertices[i] = icosahedronFaces[faceVerticesIndices[vertexIndex][i]][0];
        if (connectedVertices[i] == vertexIndex) {
            connectedVertices[i] = icosahedronFaces[faceVerticesIndices[vertexIndex][i]][1];
        }
    }

    // Calcular el centro del Icosaedro
    float center[3] = { 0.0f, 0.0f, 0.0f };
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 3; j++) {
            center[j] += icosahedronVertices[i][j];
        }
    }
    for (int j = 0; j < 3; j++) {
        center[j] /= 12.0f;
    }

    // Calcular el eje de rotación
    float axis[3];
    axis[0] = vertex[0] - center[0];
    axis[1] = vertex[1] - center[1];
    axis[2] = vertex[2] - center[2];

    // Normalizar el eje de rotación
    float length = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
    axis[0] /= length;
    axis[1] /= length;
    axis[2] /= length;

    // Aplicar la rotación alrededor del eje solo si no es el vértice central
    if (!isCentralVertex) {
        float cosTheta = cos(angle);
        float sinTheta = sin(angle);

        float tempX = vertex[0] - center[0];
        float tempY = vertex[1] - center[1];
        float tempZ = vertex[2] - center[2];

        // Fórmula para rotación alrededor de un eje arbitrario
        vertex[0] = tempX * (cosTheta + (1 - cosTheta) * axis[0] * axis[0]) +
            tempY * ((1 - cosTheta) * axis[0] * axis[1] - sinTheta * axis[2]) +
            tempZ * ((1 - cosTheta) * axis[0] * axis[2] + sinTheta * axis[1]) + center[0];
        vertex[1] = tempX * ((1 - cosTheta) * axis[1] * axis[0] + sinTheta * axis[2]) +
            tempY * (cosTheta + (1 - cosTheta) * axis[1] * axis[1]) +
            tempZ * ((1 - cosTheta) * axis[1] * axis[2] - sinTheta * axis[0]) + center[1];
        vertex[2] = tempX * ((1 - cosTheta) * axis[2] * axis[0] - sinTheta * axis[1]) +
            tempY * ((1 - cosTheta) * axis[2] * axis[1] + sinTheta * axis[0]) +
            tempZ * (cosTheta + (1 - cosTheta) * axis[2] * axis[2]) + center[2];
    }

    // Aplicar la misma rotación a los vértices conectados
    for (int i = 0; i < 5; i++) {
        float* connectedVertex = icosahedronVertices[connectedVertices[i]];
        float tempX = connectedVertex[0] - center[0];
        float tempY = connectedVertex[1] - center[1];
        float tempZ = connectedVertex[2] - center[2];

        // Fórmula para rotación alrededor de un eje arbitrario
        connectedVertex[0] = tempX * (cos(angle) + (1 - cos(angle)) * axis[0] * axis[0]) +
            tempY * ((1 - cos(angle)) * axis[0] * axis[1] - sin(angle) * axis[2]) +
            tempZ * ((1 - cos(angle)) * axis[0] * axis[2] + sin(angle) * axis[1]) + center[0];
        connectedVertex[1] = tempX * ((1 - cos(angle)) * axis[1] * axis[0] + sin(angle) * axis[2]) +
            tempY * (cos(angle) + (1 - cos(angle)) * axis[1] * axis[1]) +
            tempZ * ((1 - cos(angle)) * axis[1] * axis[2] - sin(angle) * axis[0]) + center[1];
        connectedVertex[2] = tempX * ((1 - cos(angle)) * axis[2] * axis[0] - sin(angle) * axis[1]) +
            tempY * ((1 - cos(angle)) * axis[2] * axis[1] + sin(angle) * axis[0]) +
            tempZ * (cos(angle) + (1 - cos(angle)) * axis[2] * axis[2]) + center[2];
    }
}


void keyboard(unsigned char key, int x, int y) {
    // Llama a la función rotateVertex para rotar el vértice correspondiente
    float rotationAngle = 0.1f;
    switch (key) {
    case '1': // Rotar vértice 1 (arriba)
        rotateVertex(0, rotationAngle);
        break;
    case '2': // Rotar vértice 2 (abajo)
        rotateVertex(1, rotationAngle);
        break;
    case '3': // Rotar vértice 3 (frente)
        rotateVertex(2, rotationAngle);
        break;
    case '4': // Rotar vértice 4 (atrás)
        rotateVertex(3, rotationAngle);
        break;
    case '5': // Rotar vértice 5 (izquierda)
        rotateVertex(4, rotationAngle);
        break;
    case '6': // Rotar vértice 6 (derecha)
        rotateVertex(5, rotationAngle);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
