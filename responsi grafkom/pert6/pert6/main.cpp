// deklarasikan semua header disini
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>


float angleX = 0.0f;
float angleY = 0.0f;
float zoom = -7.0f;

void drawCylinder() {
    GLUquadric *quad = gluNewQuadric();

    // Warna sisi samping
    glColor3f(0.6f, 0.1f, 0.1f);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluCylinder(quad, 1.0, 1.0, 2.0, 32, 32);

    // Tutup bawah
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.2f);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quad, 0.0, 1.0, 32, 1);
    glPopMatrix();

    // Tutup atas
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.2f);
    glTranslatef(0.0f, 0.0f, 2.0f);
    gluDisk(quad, 0.0, 1.0, 32, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}


void drawSphere() {
    glColor3f(0.2, 0.8, 0.3); // hijau muda
    glutSolidSphere(1.0, 30, 30);
}

void drawObject() {
    // Teapot Merah
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0); // merah
        glTranslatef(-2.0, 0.0, 0.0); // geser ke kiri
        glutWireTeapot(1.0); // ukuran 1
    glPopMatrix();

    // Teapot Hijau
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0); // hijau
        glTranslatef(0.0, 0.0, 0.0); // tengah
        glutWireTeapot(0.7); // ukuran lebih kecil
    glPopMatrix();

    // Teapot Biru
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0); // biru
        glTranslatef(2.0, 0.0, 0.0); // geser ke kanan
        glutWireTeapot(1.0); // ukuran 1
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 8.0,   // posisi kamera
              0.0, 0.0, 0.0,   // lihat ke tengah
              0.0, 1.0, 0.0);  // arah atas

    drawObject(); // menggambar 3 teapot

    glutSwapBuffers();
}


void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: angleX -= 5.0f; break;
        case GLUT_KEY_DOWN: angleX += 5.0f; break;
        case GLUT_KEY_LEFT: angleY -= 5.0f; break;
        case GLUT_KEY_RIGHT: angleY += 5.0f; break;
        case GLUT_KEY_PAGE_UP: zoom += 0.5f; break;
        case GLUT_KEY_PAGE_DOWN: zoom -= 0.5f; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Teapot");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}
