#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>

float posX = 0.0f, posY = 0.0f, posZ = 5.0f;
float rotX = 0.0f, rotY = 0.0f, rotZ = -1.0f;

#define PHI 3.141592654
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480

struct Vec3 {
    float X, Y, Z;
    Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    Vec3() {}
};

// Enumerasi tipe interpolasi
enum INTERP_TYPE {
    INTERP_POINTS = 0,
    INTERP_LINES = 1,
    INTERP_LINEAR = 2,
    INTERP_COSINE = 3,
    INTERP_CUBIC = 4
};

// Fungsi interpolasi cubic
float cubicInterpolate(float y0, float y1, float y2, float y3, float u) {
    float a = y3 - y2 - y0 + y1;
    float b = 2 * y0 - 2 * y1 - y3 + y2;
    float c = y2 - y0;
    float d = y1;
    return a * u * u * u + b * u * u + c * u + d;
}

// Fungsi untuk menggambar hasil interpolasi
void drawInterpolation(Vec3 point0, Vec3 point1, Vec3 point2, Vec3 point3, int n,
                       INTERP_TYPE type1, INTERP_TYPE type2) {
    float u = 0;
    float stepU = 1.0f / n;
    float stepX = fabs(point2.X - point1.X) / n;
    float pX = point1.X, pY = point1.Y, pZ = point1.Z;

    glPointSize(5);
    if (type1 == INTERP_POINTS) glBegin(GL_POINTS);
    else if (type1 == INTERP_LINES) glBegin(GL_LINES);

    for (int i = 0; i < n; i++) {
        glVertex3f(pX, pY, pZ);
        pX += stepX;
        u += stepU;
        if (type2 == INTERP_CUBIC)
            pY = cubicInterpolate(point0.Y, point1.Y, point2.Y, point3.Y, u);
        glVertex3f(pX, pY, pZ);
    }

    glEnd();
}

// Fungsi menggambar objek lembah
void drawObject()
{
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);  // warna hijau
    glPointSize(5);

    // 10 titik menyerupai bentuk lembah 
    Vec3 points[10] = {
        Vec3(-300, -100, 0), // Titik 1
        Vec3(-250, -100, 0), // Titik 2
        Vec3(-200,  0,   0), // Titik 3
        Vec3(-150,  100, 0), // Titik 4
        Vec3(-100,  100, 0), // Titik 5
        Vec3(-50,   100, 0), // Titik 6
        Vec3(0,     0,   0), // Titik 7
        Vec3(50,   -100, 0), // Titik 8
        Vec3(100,  -100, 0), // Titik 9
        Vec3(150,  -100, 0)  // Titik 10
    };

    // Gambar titik
    glBegin(GL_POINTS);
    for (int i = 0; i < 10; i++)
        glVertex3f(points[i].X, points[i].Y, points[i].Z);
    glEnd();

    // Gambar garis antar titik
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 10; i++)
        glVertex3f(points[i].X, points[i].Y, points[i].Z);
    glEnd();

    glPopMatrix();
}



// Tampilan utama
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);
    drawObject();
    glutSwapBuffers();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((GLfloat)-SCREEN_WIDTH / 2, (GLfloat)SCREEN_WIDTH / 2,
            (GLfloat)-SCREEN_HEIGHT / 2, (GLfloat)SCREEN_HEIGHT / 2,
            1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((GLfloat)-w / 2, (GLfloat)w / 2,
            (GLfloat)-h / 2, (GLfloat)h / 2,
            1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("LEMBAH - INTERPOLASI CUBIC - NAMA / NIM");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
