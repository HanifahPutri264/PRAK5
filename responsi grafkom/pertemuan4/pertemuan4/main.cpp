#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

// Variabel transformasi
float objectAngleZ = 0.0f;                // rotasi obyek di sumbu Z
float objectScaleX = 1.0f, objectScaleY = 1.0f, objectScaleZ = 1.0f; // skala obyek
float objectPositionX = 0.0f, objectPositionY = 0.0f, objectPositionZ = -5.0f; // posisi obyek

// Fungsi menggambar persegi berwarna cyan
void drawObject()
{
    glPushMatrix();

    glTranslatef(objectPositionX, objectPositionY, objectPositionZ); // Translasi
    glScalef(objectScaleX, objectScaleY, objectScaleZ);              // Skala
    glRotatef(objectAngleZ, 0.0f, 0.0f, 1.0f);                        // Rotasi Z

    glColor3f(0.0f, 1.0f, 1.0f); // Cyan

    glBegin(GL_QUADS); // Persegi bidang XY
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f,  0.5f, 0.0f);
        glVertex3f(-0.5f,  0.5f, 0.0f);
    glEnd();

    glPopMatrix();
}

// Fungsi display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawObject();
    glutSwapBuffers();
}

// Inisialisasi tampilan
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // background putih
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Reshape saat jendela diubah
void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard biasa (translasi dan scaling)
void keyboard1(unsigned char key, int x, int y)
{
    float moveStep = 0.2f;
    float scaleStep = 0.1f;

    switch (key)
    {
    case 'w': objectPositionY += moveStep; break;
    case 's': objectPositionY -= moveStep; break;
    case 'a': objectPositionX -= moveStep; break;
    case 'd': objectPositionX += moveStep; break;
    case 'q': objectPositionZ += moveStep; break;
    case 'e': objectPositionZ -= moveStep; break;

    case 't': objectScaleY += scaleStep; break;
    case 'g': objectScaleY -= scaleStep; break;
    case 'f': objectScaleX += scaleStep; break;
    case 'h': objectScaleX -= scaleStep; break;
    case 'r': objectScaleZ += scaleStep; break;
    case 'y': objectScaleZ -= scaleStep; break;

    case 27: exit(0);
            break; // esc
    }

    glutPostRedisplay();
}

// Keyboard khusus (rotasi Z)
void keyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F1:
        objectAngleZ += 5.0f;
        break;
    case GLUT_KEY_F2:
        objectAngleZ -= 5.0f;
        break;
    }
    glutPostRedisplay();
}

// Main Program
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Persegi Cyan - Translasi, Rotasi, Scaling");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard1);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}
