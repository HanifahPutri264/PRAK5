#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

// === Transformasi Kamera dan Objek ===
float angle = 0.0f;
float posX = 0.0f, rotX = 0.0f;
float posY = 0.0f, rotY = 0.0f;
float posZ = 5.0f, rotZ = -1.0f;
float objectAngleX = 0.0f;
float objectAngleY = 0.0f;
float objectAngleZ = 0.0f;

// === Struktur Titik 3D ===
struct Vec3 {
    float X, Y, Z;
    Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
    Vec3() { X = Y = Z = 0.0f; }
    ~Vec3() {}
};

// === Control Point untuk Permukaan NURBS ===
Vec3 controlPoint[4][4];
bool showPoints = false;

GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 100.0 };

GLUnurbsObj *theNurb;

// === Fungsi Menggambar Permukaan ===
void drawObject() {
    glPushMatrix();
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.7f, 0.7f, 0.7f); // abu-abu

    // Knot vector
    GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };

    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 8, knots, 8, knots,
                    4 * 3, 3, &controlPoint[0][0].X,
                    4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);

    // Tampilkan titik kontrol jika showPoints true
    if (showPoints) {
        glPointSize(5.0);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 0.0);  // kuning
        glBegin(GL_POINTS);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                glVertex3f(controlPoint[i][j].X,
                           controlPoint[i][j].Y,
                           controlPoint[i][j].Z);
            }
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
}

// === Fungsi Tampilan ===
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ,
              posX + rotX, posY + rotY, posZ + rotZ,
              0.0f, 1.0f, 0.0f);
    drawObject();
    glutSwapBuffers();
}

// === Inisialisasi ===
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Inisialisasi control point untuk permukaan cekung
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) {
            controlPoint[u][v].X = 2.0f * (u - 1.5f);
            controlPoint[u][v].Y = 2.0f * (v - 1.5f);

            // Tengah lebih dalam, pinggir lebih tinggi
            if ((u == 1 || u == 2) && (v == 1 || v == 2))
                controlPoint[u][v].Z = -10.0f;  // cekungan
            else
                controlPoint[u][v].Z = 5.0f;    // pinggiran
        }
    }

    // Pengaturan material dan pencahayaan
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    // Buat NURBS renderer
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}

// === Resize ===
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// === Keyboard (Panah dan Fungsi Khusus) ===
void keyboard(int key, int x, int y) {
    float fraction = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT:
            objectAngleY -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            objectAngleY += 5.0f;
            break;
        case GLUT_KEY_UP:
            objectAngleX -= 5.0f;
            break;
        case GLUT_KEY_DOWN:
            objectAngleX += 5.0f;
            break;
        case GLUT_KEY_PAGE_UP:
            posZ -= fraction * 5;
            break;
        case GLUT_KEY_PAGE_DOWN:
            posZ += fraction * 5;
            break;
        case GLUT_KEY_F1:
            showPoints = !showPoints;
            break;
        case GLUT_KEY_F2:
            // Perbesar cekungan di tengah saat runtime
            for (int u = 1; u <= 2; u++) {
                for (int v = 1; v <= 2; v++) {
                    controlPoint[u][v].Z -= 1.0f;
                }
            }
            break;
    }
    glutPostRedisplay();
}

// === Main Program ===
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2200018217 - Permukaan NURBS Cekung");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutMainLoop();

    return 0;
}
