#include <windows.h>
#include <GL/glut.h>

float angle = 0.0f;                     // sudut transformasi kamera
float posX = 0.0f, rotX =  0.0f;        // posisi kamera di sumbu X
float posY = 0.0f, rotY =  0.0f;        // posisi kamera di sumbu Y
float posZ = 5.0f, rotZ = -1.0f;        // posisi kamera di sumbu Z


float objectAngleX = 0.0f;                        // sudut tranformasi obyek di sumbu X
float objectAngleY = 0.0f;                        // sudut tranformasi obyek di sumbu Y
float objectAngleZ = 0.0f;                        // sudut tranformasi obyek di sumbu Z


float objectScaleX = 1.0f;        // skala perbesaran obyek ke arah X
float objectScaleY = 1.0f;        // skala perbesaran obyek ke arah Y
float objectScaleZ = 1.0f;        // skala perbesaran obyek ke arah Z


float objectPositionX = 0.0f;        // posisi obyek di sumbu X
float objectPositionY = 0.0f;        // posisi obyek di sumbu Y
float objectPositionZ = 0.0f;        // posisi obyek di sumbu Z


void drawObject()
{
        glPushMatrix();
        glTranslatef(objectPositionX, objectPositionY, objectPositionZ);
        glScalef(objectScaleX, objectScaleY, objectScaleZ);
        glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
        glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 1.0f);
        glutSolidCube(1.0f); // menggambar obyek kubus
        glPopMatrix();
        glPopMatrix();
}


void display()
{
        // bersihkan dan reset layar dan buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);
        drawObject();
        glutSwapBuffers();
}

void init(void)
{
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glEnable(GL_DEPTH_TEST);                                // mengaktifkan depth buffer
        glMatrixMode(GL_PROJECTION);                
        glLoadIdentity();
        gluPerspective(45.0, 1.0, 1.0, 100.0);        // set proyeksi ke perspektif
        glMatrixMode(GL_MODELVIEW);                                
        glLoadIdentity();                     
        gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h)
{
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
}
void keyboard(int key, int x, int y)
{

        float fraction = 0.1f;


        switch (key) 
        {
        case GLUT_KEY_LEFT:
                objectAngleY -= 1.0f;
                glutPostRedisplay();        // update obyek
                break;
        case GLUT_KEY_RIGHT:                
                objectAngleY += 1.0f;
                glutPostRedisplay();        // update obyek
                break;
        case GLUT_KEY_UP:                
                objectAngleX -= 1.0f;
                glutPostRedisplay();        // update obyek
                break;
        case GLUT_KEY_DOWN:                
                objectAngleX += 1.0f;
                glutPostRedisplay();        // update obyek
                break;
        case GLUT_KEY_PAGE_UP:
                posX += rotX * fraction;                
                posZ += rotZ * fraction;
                glutPostRedisplay();        // update obyek
                break;
        case GLUT_KEY_PAGE_DOWN:
                posX -= rotX * fraction;
                posZ -= rotZ * fraction;
                glutPostRedisplay();        // update obyek
                break;
        }
}

void keyboard1(unsigned char key, int x, int y)
{
        float fraction = 0.5f;


        switch (key)
        {
        case 'w':        // bila tombol 'w' pada keyboard ditekan
                                // translasi ke atas
                        objectPositionY += fraction;
                        glutPostRedisplay();
                        break;
        case 's':         // bila tombol 's' pada keyboard ditekan
                                // translasi ke bawah
                        objectPositionY -= fraction;
                        glutPostRedisplay();
                break;
        case 'a':        // bila tombol 'a' pada keyboard ditekan
                                // translasi ke kiri
                        objectPositionX -= fraction;
                        glutPostRedisplay();
                break;
        case 'd':        // bila tombol 'd' pada keyboard ditekan
                                // translasi ke kanan
                        objectPositionX += fraction;
                        glutPostRedisplay();
                break;        
        case 'q':        // bila tombol 'q' pada keyboard ditekan
                                // translasi ke depan
                        objectPositionZ += fraction;
                        glutPostRedisplay();
                break;
        case 'e':        // bila tombol 'e' pada keyboard ditekan
                                // translasi ke belakang
                        objectPositionZ -= fraction;
                        glutPostRedisplay();
                break;
        case 't':        // bila tombol 't' pada keyboard ditekan
                                // perbesar ke arah sumbu Y
                        objectScaleY += 0.1f;
                        glutPostRedisplay();
                break;
        case 'g':        // bila tombol 'g' pada keyboard ditekan
                                // perkecil ke arah sumbu Y
                        objectScaleY = (objectScaleY - 0.1f, 1.0f);
                        glutPostRedisplay();
                break;
        case 'f':        // bila tombol 'f' pada keyboard ditekan
                                // perbesar ke arah sumbu X
                        objectScaleX += 0.1f;
                        glutPostRedisplay();
                break;
        case 'h':        // bila tombol 'h' pada keyboard ditekan
                                // perkecil ke arah sumbu X
                        objectScaleX = (objectScaleX - 0.1f, 1.0f);
                        glutPostRedisplay();
                break;
        case 'r':        // bila tombol 'r' pada keyboard ditekan
                                // perbesar ke arah sumbu Z
                        objectScaleZ += 0.1f;
                        glutPostRedisplay();
                break;
        case 'y':        // bila tombol 'y' pada keyboard ditekan
                                // perkecil ke arah sumbu Z
                        objectScaleZ = (objectScaleZ - 0.1f, 1.0f);
                        glutPostRedisplay();
                break;
        case 27:        // bila tombol 'esc' pada keyboard ditekan
                                // keluar program
                        exit(0);
                break;
        }
}

void timer(int value)
{
        glutPostRedisplay();
        glutTimerFunc(55, timer, 0);
}


// program utama
int main(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(480, 480);                // besarnya jendela dalam piksel dalam hal ini 300x300
        glutInitWindowPosition(100, 100);        // posisi jendela dilayar komputer dalam piksel
        glutCreateWindow("Augustav Fahrul Alzaiya / 2200018048 - PRAKTIKUM 4 GRAFIKA KOMPUTER");
    
        init();
        glutDisplayFunc(display);   // display
        glutReshapeFunc(reshape);   // reshape
        glutSpecialFunc(keyboard);  // keyboard
        glutKeyboardFunc(keyboard1);  // keyboard
        glutMainLoop();
        return 0;
}