#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>


// Titik kontrol untuk spline rangka sepeda
GLfloat controlPoints[4][3] = {
    {-0.5, 0.0, 0.0},   // roda belakang
    {-0.2, 0.4, 0.0},   // melengkung ke atas
    {0.4, 0.4, 0.0},    // lengkung ke depan
    {0.6, 0.2, 0.0}     // roda depan
};

// Gambar spline rangka sepeda
void drawSplineFrame() {
    glColor3f(1.0, 0.0, 0.0); // Merah
    glLineWidth(5.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &controlPoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 30; i++) {
        glEvalCoord1f((GLfloat)i / 30.0);
    }
    glEnd();
}

// Gambar ban (mesh torus tipis)
void drawWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 1, 0, 0);
    GLUquadric *quad = gluNewQuadric();
    glColor3f(0.1f, 0.1f, 0.1f); // Hitam
    gluDisk(quad, 0.25, 0.4, 32, 1);  // Ban
    gluDeleteQuadric(quad);
    glPopMatrix();
}

// Gambar sadel pakai mesh sphere yang dipipihkan
void drawSaddle() {
    glPushMatrix();
    glColor3f(0.5, 0.2, 0.8); // Ungu
    glTranslatef(0.0, 0.45, 0.0);
    glScalef(1.5, 0.5, 1.0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(1.5, 1.5, 3.0,   // posisi kamera
              0.0, 0.0, 0.0,   // arah lihat
              0.0, 1.0, 0.0);  // atas

    drawSplineFrame();             // Rangka spline
    drawWheel(-0.5, 0.0, 0.0);     // Roda belakang
    drawWheel(0.6, 0.2, 0.0);      // Roda depan
    drawSaddle();                 // Sadel

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1); // background putih

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sepeda Anak 3D - Spline & Mesh");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
