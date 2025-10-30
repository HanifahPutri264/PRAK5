#include <windows.h>
#include <gl/glut.h>
float angle = 0.0f;					
float posX = 0.0f, rotX =  0.0f;	
float posY = 0.0f, rotY =  0.0f;
float posZ = 5.0f, rotZ = -1.0f;

float objectAngleX = 0.0f;			
float objectAngleY = 0.0f;		
float objectAngleZ = 0.0f;		

struct Vec3
{
	float X; float Y; float Z;
	Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vec3() { }
	~Vec3() { }
};

void drawCube()
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f,-1.0f);
	glVertex3f( 1.0f, -1.0f,-1.0f);
	glVertex3f( 1.0f, 1.0f,-1.0f);
	glVertex3f(-1.0f, 1.0f,-1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f,-1.0f);
	glVertex3f(-1.0f, 1.0f,-1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f,-1.0f);
	glVertex3f( 1.0f, 1.0f,-1.0f);
	glVertex3f( 1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f( 1.0f, 1.0f, 1.0f);
	glVertex3f( 1.0f, 1.0f,-1.0f);
	glVertex3f(-1.0f, 1.0f,-1.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f,-1.0f);
	glVertex3f(-1.0f, -1.0f,-1.0f);
	glEnd();
}

void drawCylinder(float radius, float height, int slices, int stacks)
{
	glPushMatrix();
	GLUquadricObj* cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
	gluQuadricNormals(cyl, GLU_SMOOTH);
	gluQuadricOrientation(cyl, GLU_INSIDE);
	glTranslatef(0.0f, -height/2, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f); // warna kuning
	gluDisk(cyl, 0.0f, radius, slices, stacks);
	glColor3f(1.0f, 0.0f, 0.0f); // warna merah
	gluCylinder(cyl, radius, radius, height, slices, stacks);
	glColor3f(1.0f, 1.0f, 0.0f); // warna kuning
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(cyl, 0.0f, radius, slices, stacks);
	glPopMatrix();
}

void drawPyramid(float baseRadius, float height, int slices, int stacks)
{
    glPushMatrix();
    GLUquadricObj* pyramid = gluNewQuadric();
    gluQuadricDrawStyle(pyramid, GLU_FILL);
    gluQuadricNormals(pyramid, GLU_SMOOTH);
    gluQuadricOrientation(pyramid, GLU_OUTSIDE);

    // Translasi dan rotasi agar puncak limas menghadap ke atas
    glTranslatef(0.0f, -height / 2, 0.0f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);

    // Menggambar dasar limas
    glColor3f(1.0f, 0.0f, 0.0f); // warna merah
    gluDisk(pyramid, 0.0f, baseRadius, slices, stacks);

    // Menggambar sisi-sisi limas
    glColor3f(1.0f, 0.0f, 0.0f); // warna merah
    gluCylinder(pyramid, baseRadius, 0.0f, height, slices, stacks);

    glPopMatrix();
}

void drawSphere(float radius, int slices, int stacks)
{
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f); // warna merah
	GLUquadric *sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, radius, slices, stacks);
	glPopMatrix();
}

void drawObject(){
	glPushMatrix();
	glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	//glutSolidCube(1.0f); // menggambar obyek kubus
	//glutWireTeapot(1.0f);
//	drawCube(); //panggil fungsi untuk membuat obyek kubus
//	drawCylinder(1.0f, 2.0f, 20, 20); // fungsi untuk membuat obyek silinder
	drawPyramid(1.0f, 2.0f, 4, 1); 
	//drawSphere(1.0f, 50, 50); // fungsi untuk membuat obyek bola

	glPopMatrix();
	glPopMatrix();
	
	// membuat obyek polyhedron
	//glutSolidTetrahedron();
	//glutSolidOctahedron();
	//glutSolidDodecahedron();
	//glutSolidIcosahedron();
	//glutSolidCube(1.0f);
	//glutSolidCone(1.0f, 1.0f, 50, 50);
	//glutSolidSphere(1.0f, 50, 50);
	//glutSolidTeapot(1.0f);
	//glutSolidTorus(0.5f, 1.0f, 20, 20);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);
	drawObject();
	glutSwapBuffers();
}

void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);				
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);	
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();					
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
void keyboard(int key, int x, int y){
	float fraction = 0.1f;

	switch (key) 
{
	case GLUT_KEY_LEFT:
		objectAngleY -= 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	case GLUT_KEY_RIGHT:		
		objectAngleY += 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	case GLUT_KEY_UP:		
		objectAngleX -= 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	case GLUT_KEY_DOWN:		
		objectAngleX += 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	case GLUT_KEY_PAGE_UP:
		posX += rotX * fraction;		
		posZ += rotZ * fraction;
		glutPostRedisplay();	// update obyek
		break;
	case GLUT_KEY_PAGE_DOWN:
		posX -= rotX * fraction;
		posZ -= rotZ * fraction;
		glutPostRedisplay();	
		break;
	}
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(55, timer, 0);
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(480, 480);	
	glutInitWindowPosition(100, 100);	
	glutCreateWindow("Augustav Fahrul Alzaiya / 2200018048 - KODE DASAR PRAKTIKUM GRAFIKA KOMPUTER");
	init();
	glutDisplayFunc(display);   // display
	glutReshapeFunc(reshape);   // reshape
	glutSpecialFunc(keyboard);  // keyboard
	glutMainLoop();

	return 0;
}