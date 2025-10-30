#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

// Variabel transformasi kamera
float posX = 0.0f, rotX = 0.0f;
float posY = 0.0f, rotY = 0.0f;
float posZ = 5.0f, rotZ = -1.0f;

// Fungsi untuk menggambar piramid menggunakan gluCylinder
void drawPyramid(float radius, float height, int slices, int stacks)
{
    glPushMatrix();

    GLUquadric* pyr = gluNewQuadric();
    gluQuadricDrawStyle(pyr, GLU_FILL);
    gluQuadricNormals(pyr, GLU_SMOOTH);

    glTranslatef(0.0f, -height / 2.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  // orientasi ke atas

    // Warna merah
    glColor3f(1.0f, 0.0f, 0.0f);

    // Gambar kerucut dengan alas ber-radius dan puncak di titik
    gluCylinder(pyr, radius, 0.0f, height, slices, stacks);

    // Tutup alas piramid
    gluDisk(pyr, 0.0f, radius, slices, stacks);

    glPopMatrix();
}

// Fungsi untuk menggambar seluruh obyek
void drawObject()
{
    glPushMatrix();
    drawPyramid(1.0f, 2.0f, 4, 1);  // radius, tinggi, sisi alas, tumpukan
    glPopMatrix();
}

// Fungsi tampilan utama
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(posX, posY, posZ,
              posX + rotX, posY + rotY, posZ + rotZ,
              0.0f, 1.0f, 0.0f);

    drawObject();

    glutSwapBuffers();
}

// Inisialisasi
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // latar belakang putih
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Aktifkan pencahayaan jika ingin (opsional)
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

// Fungsi resize jendela
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi utama
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("PIRAMID MERAH - GRAFIKA KOMPUTER");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
