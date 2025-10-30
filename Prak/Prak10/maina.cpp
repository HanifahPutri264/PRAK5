#include <iostream>
#include <math.h>
#include "GL/glut.h" // Menggunakan header standar GLUT

// --- Deklarasi Variabel Global ---
// Transformasi Kamera
float posX = 0.0f, rotX =  0.0f;
float posY = 0.0f, rotY =  0.0f;
float posZ = 5.0f, rotZ = -1.0f;

// Transformasi Objek
float objectAngleX = 0.0f;
float objectAngleY = 0.0f;

// --- Data Icosahedron (Basis untuk Bola) ---
#define vX 0.525731112119133696
#define vZ 0.850650808352039932

// Array data vertex
static GLfloat vdata[12][3] =
{
    {-vX, 0.0, vZ }, { vX, 0.0, vZ }, {-vX, 0.0,-vZ }, { vX, 0.0,-vZ },
    { 0.0, vZ, vX }, { 0.0, vZ,-vX }, { 0.0,-vZ, vX }, { 0.0,-vZ,-vX },
    { vZ, vX, 0.0 }, {-vZ, vX, 0.0 }, { vZ,-vX, 0.0 }, {-vZ,-vX, 0.0 }
};

// Indeks untuk membentuk 20 segitiga dari 12 vertex
static int tindices[20][3] = {
    {1,4,0},  {4,9,0},  {4,5,9},  {8,5,4},  {1,8,4},
    {1,10,8}, {10,3,8}, {8,3,5},  {3,2,5},  {3,7,2},
    {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
    {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9},  {11,2,7}
};

// --- Properti Material dan Cahaya ---
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_diffuse[] = { .0, 1.6, 1.4, 1.0 };
GLfloat mat_ambient[] = { 0.8, 0.6, 0.4, 1.0 };
GLfloat mat_shininess = 50.0;

GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat light_position1[] = { 1.5, 1.0, -2.0, 0.0 }; // Cahaya dari satu arah
GLfloat light_position2[] = { 1.5, 1.0, 2.0, 0.0 };  // Cahaya dari arah lain

int flat = 1;       // 1 = flat shading, 0 = smooth shading
int subdiv = 0;     // Level subdivisi (detail bola)

// --- Definisi Struktur dan Fungsi Utilitas ---
// Container untuk membuat tipe data 3D (X, Y, Z)
struct Vec3 {
    float X, Y, Z;
    Vec3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {}
};

// Fungsi untuk melakukan normalisasi vektor (membuat panjangnya menjadi 1)
Vec3 normalize(Vec3 value) {
    Vec3 result;
    float length = sqrt((value.X * value.X) + (value.Y * value.Y) + (value.Z * value.Z));
    if (length == 0.0f) return Vec3(0, 0, 0); // Mencegah pembagian dengan nol
    result.X = value.X / length;
    result.Y = value.Y / length;
    result.Z = value.Z / length;
    return result;
}

// Fungsi untuk operasi perkalian silang (cross product)
Vec3 cross(Vec3 value1, Vec3 value2) {
    Vec3 result;
    result.X = value1.Y * value2.Z - value2.Y * value1.Z;
    result.Y = value1.Z * value2.X - value2.Z * value1.X;
    result.Z = value1.X * value2.Y - value2.X * value1.Y;
    return result;
}

// --- Fungsi Penggambaran ---

// Menghitung normal untuk satu permukaan segitiga (untuk flat shading)
void normface(Vec3 v1, Vec3 v2, Vec3 v3) {
    Vec3 d1, d2;
    d1.X = v1.X - v2.X; d1.Y = v1.Y - v2.Y; d1.Z = v1.Z - v2.Z;
    d2.X = v2.X - v3.X; d2.Y = v2.Y - v3.Y; d2.Z = v2.Z - v3.Z;
    Vec3 tn = cross(d1, d2);
    tn = normalize(tn);
    glNormal3f(tn.X, tn.Y, tn.Z);
}

// Menggambar segitiga dengan flat shading
void drawTriangleFlat(Vec3 v1, Vec3 v2, Vec3 v3) {
    glBegin(GL_TRIANGLES);
    normface(v1, v2, v3);
    glVertex3f(v1.X, v1.Y, v1.Z);
    glVertex3f(v2.X, v2.Y, v2.Z);
    glVertex3f(v3.X, v3.Y, v3.Z);
    glEnd();
}

// Menggambar segitiga dengan smooth shading
void drawTriangleSmooth(Vec3 v1, Vec3 v2, Vec3 v3) {
    glBegin(GL_TRIANGLES);
    glNormal3f(v1.X, v1.Y, v1.Z);
    glVertex3f(v1.X, v1.Y, v1.Z);
    glNormal3f(v2.X, v2.Y, v2.Z);
    glVertex3f(v2.X, v2.Y, v2.Z);
    glNormal3f(v3.X, v3.Y, v3.Z);
    glVertex3f(v3.X, v3.Y, v3.Z);
    glEnd();
}

// Fungsi rekursif untuk membagi segitiga menjadi 4 segitiga yang lebih kecil
void subdivide(Vec3 v1, Vec3 v2, Vec3 v3, int depth) {
    Vec3 v12, v23, v31;
    if (depth == 0) {
        if (flat == 1)
            drawTriangleFlat(v1, v2, v3);
        else
            drawTriangleSmooth(v1, v2, v3);
        return;
    }
    // Hitung titik tengah setiap sisi segitiga
    v12.X = (v1.X + v2.X) / 2.0f; v12.Y = (v1.Y + v2.Y) / 2.0f; v12.Z = (v1.Z + v2.Z) / 2.0f;
    v23.X = (v2.X + v3.X) / 2.0f; v23.Y = (v2.Y + v3.Y) / 2.0f; v23.Z = (v2.Z + v3.Z) / 2.0f;
    v31.X = (v3.X + v1.X) / 2.0f; v31.Y = (v3.Y + v1.Y) / 2.0f; v31.Z = (v3.Z + v1.Z) / 2.0f;
    
    // Normalisasi titik tengah agar berada di permukaan bola satuan
    v12 = normalize(v12);
    v23 = normalize(v23);
    v31 = normalize(v31);
    
    // Panggil subdivide lagi untuk 4 segitiga baru
    subdivide(v1, v12, v31, depth - 1);
    subdivide(v2, v23, v12, depth - 1);
    subdivide(v3, v31, v23, depth - 1);
    subdivide(v12, v23, v31, depth - 1);
}

// Fungsi untuk menggambar objek utama
void drawObject() {
    glPushMatrix();
    
    // Atur posisi cahaya
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    
    // Rotasi objek berdasarkan input keyboard
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f); // Kanan-kiri
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f); // Atas-bawah
    
    // Gambar 20 segitiga dasar dari icosahedron
    for (int i = 0; i < 20; i++) {
        Vec3 v1(vdata[tindices[i][0]][0], vdata[tindices[i][0]][1], vdata[tindices[i][0]][2]);
        Vec3 v2(vdata[tindices[i][1]][0], vdata[tindices[i][1]][1], vdata[tindices[i][1]][2]);
        Vec3 v3(vdata[tindices[i][2]][0], vdata[tindices[i][2]][1], vdata[tindices[i][2]][2]);
        subdivide(v1, v2, v3, subdiv);
        // Baris-baris yang memodifikasi 'vdata' global telah dihapus karena menyebabkan error logika.
    }
    
    glPopMatrix();
}

// --- Fungsi Callback GLUT ---

// Fungsi display utama, dipanggil setiap kali layar perlu digambar ulang
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);
    drawObject();
    glutSwapBuffers();
}

// Fungsi inisialisasi OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Latar belakang putih
    glEnable(GL_DEPTH_TEST);
    
    // Pengaturan Proyeksi
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Inisialisasi Pencahayaan dan Material
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // FIX: Shininess adalah properti material (GL_FRONT), bukan cahaya (GL_LIGHT0)
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

// Fungsi yang dipanggil saat ukuran jendela diubah
void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk menangani input keyboard (tombol khusus)
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
            break; // FIX: Menambahkan 'break' yang hilang
        case GLUT_KEY_F1: // Menambah detail
            subdiv++;
            break;
        case GLUT_KEY_F2: // Mengurangi detail
            if (subdiv > 0) subdiv--;
            break;
    }
    glutPostRedisplay(); // Minta layar digambar ulang setelah ada input
}

// --- Fungsi Utama Program ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Praktikum Grafika Komputer - Bola Subdivisi");
    
    init(); // Panggil fungsi inisialisasi
    
    // Daftarkan fungsi callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    
    glutMainLoop(); // Mulai event loop GLUT
    return 0;
}
