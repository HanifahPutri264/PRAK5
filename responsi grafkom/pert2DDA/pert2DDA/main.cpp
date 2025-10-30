#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <iostream>

int SCREEN_WIDTH = 400;
int SCREEN_HEIGHT = 400;

// Transformasi
float angle = 0.0f;
float posX = 0.0f, rotX = 0.0f;
float posY = 0.0f, rotY = 0.0f;
float posZ = 5.0f, rotZ = -1.0f;
float objectAngleX = 0.0f;
float objectAngleY = 0.0f;
float objectAngleZ = 0.0f;

// Struktur titik 3D
struct Vec3 {
    float X, Y, Z;
    Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
    Vec3() {}
    ~Vec3() {}
};

// Deklarasi fungsi
void lineBresenham(Vec3 point1, Vec3 point2);

// Algoritma Bresenham terhadap X
void lineBresenhamX(Vec3 point1, Vec3 point2)
{
    int dY = point2.Y - point1.Y;
    int dX = point2.X - point1.X;

    int yi = 1;
    if (dY < 0) {
        yi = -1;
        dY = -dY;
    }

    glBegin(GL_POINTS);
    glVertex3f(point1.X, point1.Y, point1.Z);

    int pX = point1.X, pY = point1.Y, pZ = point1.Z;
    int dY2 = 2 * dY;
    int dX2 = 2 * dX;
    int pk = dY2 - dX;

    for (int i = point1.X; i < point2.X; i++) {
        if (pk < 0) {
            pk += dY2;
        } else {
            pk += dY2 - dX2;
            pY += yi;
        }
        pX++;
        glVertex3f(pX, pY, pZ);
    }
    glVertex3f(point2.X, point2.Y, point2.Z);
    glEnd();
}

// Algoritma Bresenham terhadap Y
void lineBresenhamY(Vec3 point1, Vec3 point2)
{
    int dY = point2.Y - point1.Y;
    int dX = point2.X - point1.X;

    int xi = 1;
    if (dX < 0) {
        xi = -1;
        dX = -dX;
    }

    glBegin(GL_POINTS);
    glVertex3f(point1.X, point1.Y, point1.Z);

    int pX = point1.X, pY = point1.Y, pZ = point1.Z;
    int dY2 = 2 * dY;
    int dX2 = 2 * dX;
    int pk = dX2 - dY;

    for (int i = point1.Y; i < point2.Y; i++) {
        if (pk < 0) {
            pk += dX2;
        } else {
            pk += dX2 - dY2;
            pX += xi;
        }
        pY++;
        glVertex3f(pX, pY, pZ);
    }
    glVertex3f(point2.X, point2.Y, point2.Z);
    glEnd();
}

// Fungsi utama Bresenham
void lineBresenham(Vec3 point1, Vec3 point2)
{
    int dY = point2.Y - point1.Y;
    int dX = point2.X - point1.X;

    if (abs(dY) < abs(dX)) {
        if (point1.X < point2.X)
            lineBresenhamX(point1, point2);
        else
            lineBresenhamX(point2, point1);
    } else {
        if (point1.Y < point2.Y)
            lineBresenhamY(point1, point2);
        else
            lineBresenhamY(point2, point1);
    }
}

// Gambar segitiga dengan Bresenham
void drawObject()
{
    glPushMatrix();
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);

    // Warna biru
    glColor3f(0.0f, 0.0f, 1.0f);

    // Titik-titik segitiga
    Vec3 A = Vec3(0.0f, 100.0f, 0.0f);     // titik atas
    Vec3 B = Vec3(-100.0f, -50.0f, 0.0f);  // kiri bawah
    Vec3 C = Vec3(100.0f, -50.0f, 0.0f);   // kanan bawah

    // Gambar sisi-sisi segitiga
    lineBresenham(A, B); // kiri
    lineBresenham(A, C); // kanan
    lineBresenham(B, C); // alas

    glPopMatrix();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);
    drawObject();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((GLfloat)-SCREEN_WIDTH/2, (GLfloat)SCREEN_WIDTH/2,
            (GLfloat)-SCREEN_HEIGHT/2, (GLfloat)SCREEN_HEIGHT/2, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((GLfloat)-w/2, (GLfloat)w/2, (GLfloat)-h/2, (GLfloat)h/2, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(int key, int x, int y)
{
    float fraction = 0.1f;
    switch (key)
    {
        case GLUT_KEY_LEFT:
            objectAngleY -= 1.0f;
            break;
        case GLUT_KEY_RIGHT:
            objectAngleY += 1.0f;
            break;
        case GLUT_KEY_UP:
            objectAngleX -= 1.0f;
            break;
        case GLUT_KEY_DOWN:
            objectAngleX += 1.0f;
            break;
        case GLUT_KEY_PAGE_UP:
            posX += rotX * fraction;
            posZ += rotZ * fraction;
            break;
        case GLUT_KEY_PAGE_DOWN:
            posX -= rotX * fraction;
            posZ -= rotZ * fraction;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Segitiga Biru - Algoritma Bresenham");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}
