#include <iostream>
#include <cmath>
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

// === Kamera ===
float posX = 0.0f, posY = 0.0f, posZ = 5.0f;
float rotX = 0.0f, rotY = 0.0f, rotZ = -1.0f;
float objectAngleX = 0.0f, objectAngleY = 0.0f;

// === Torus ===
int torusRings = 20;      // default ring
int torusSides = 20;      // sisi torus
float torusAngle = 0.0f;  // rotasi animasi torus

// === Material & Lighting ===
GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.8, 0.6, 0.4, 1.0 };   // Coklat
GLfloat mat_ambient[] = { 0.8, 0.6, 0.4, 1.0 };
GLfloat mat_shininess = 50.0;

GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat light_position1[] = { 1.5, 1.0, -2.0, 0.0 };
GLfloat light_position2[] = { -1.5, 1.0, 2.0, 0.0 };

// === Gambar Torus ===
void drawTorus() {
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.0f);        // posisi torus
    glRotatef(torusAngle, 0.0f, 1.0f, 0.0f);  // rotasi otomatis

    // Terapkan pencahayaan
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    // Gambar torus dengan subdivisi variabel
    glutSolidTorus(0.3, 1.0, torusRings, torusSides);

    glPopMatrix();
}

// === Display ===
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(posX, posY, posZ,
              posX + rotX, posY + rotY, posZ + rotZ,
              0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);

    drawTorus();

    glPopMatrix();

    // Animasi rotasi
    torusAngle += 0.5f;
    if (torusAngle > 360.0f) torusAngle -= 360.0f;

    glutSwapBuffers();
}

// === Resize Window ===
void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// === Keyboard (Special Keys) ===
void keyboard(int key, int x, int y) {
    float step = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT:  objectAngleY -= 5.0f; break;
        case GLUT_KEY_RIGHT: objectAngleY += 5.0f; break;
        case GLUT_KEY_UP:    objectAngleX -= 5.0f; break;
        case GLUT_KEY_DOWN:  objectAngleX += 5.0f; break;
        case GLUT_KEY_PAGE_UP:   posZ -= step * 5; break;
        case GLUT_KEY_PAGE_DOWN: posZ += step * 5; break;

        case GLUT_KEY_F5: torusRings = 5;  break;
        case GLUT_KEY_F6: torusRings = 10; break;
        case GLUT_KEY_F7: torusRings = 20; break;
        case GLUT_KEY_F8: torusRings = 50; break;
    }

    glutPostRedisplay();
}

// === Inisialisasi ===
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
}

// === Main ===
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Torus Coklat dengan Subdivisi Interaktif");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);  // untuk animasi torus
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);

    glutMainLoop();
    return 0;
}
