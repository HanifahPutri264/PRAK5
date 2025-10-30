#include <windows.h>
#include <GL/glut.h>

#include <stdio.h>
#include <iostream>

int SCREEN_WIDTH = 400; 
int SCREEN_HEIGHT = 400;

float angle = 0.0f;					// sudut transformasi kamera
float posX = 0.0f, rotX =  0.0f;	// posisi kamera di sumbu X
float posY = 0.0f, rotY =  0.0f;	// posisi kamera di sumbu Y
float posZ = 5.0f, rotZ = -1.0f;	// posisi kamera di sumbu Z

float objectAngleX = 0.0f;			// sudut tranformasi obyek di sumbu X
float objectAngleY = 0.0f;			// sudut tranformasi obyek di sumbu Y
float objectAngleZ = 0.0f;			// sudut tranformasi obyek di sumbu Z

struct Vec3{ 
	float X; float Y; float Z;
	Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vec3() { }
	~Vec3() { }
}; 

void lineDDAX(Vec3 point1, Vec3 point2){
	int dY = point2.Y - point1.Y;
	int dX = point2.X - point1.X;
	float m = (float)dY / dX;
	float im = 1.0f/m;
	glBegin(GL_POINTS);
	glVertex3f(point1.X, point1.Y, point1.Z);
	float pX = point1.X, pY = point1.Y, pZ = point1.Z;
	
	for (int i = point1.X; i < point2.X; i++){
		pX = pX + 1; // Xn+1 = Xn + 1
		pY = pY + m; // Yn+1 = Yn + m
		glVertex3f(pX, pY, pZ);
	}
	glVertex3f(point2.X, point2.Y, point2.Z);
	glEnd();
}

void lineDDAY(Vec3 point1, Vec3 point2){
	int dY = point2.Y - point1.Y;
	int dX = point2.X - point1.X;
	float m = (float)dY / dX;
	float im = 1.0f/m;
	
	glBegin(GL_POINTS);
	glVertex3f(point1.X, point1.Y, point1.Z);
	float pX = point1.X, pY = point1.Y, pZ = point1.Z;
	
	for (int i = point1.Y; i < point2.Y; i++){
		pX = pX + im; // Xn+1 = Xn + 1/m
		pY = pY + 1; // Yn+1 = Yn + 1
		glVertex3f(pX, pY, pZ);
	}
	glVertex3f(point2.X, point2.Y, point2.Z);
	glEnd();
}

void lineDDA(Vec3 point1, Vec3 point2){// fungsi untuk menggambar garis dengan algoritma DDA
	int dY = point2.Y - point1.Y;
	int dX = point2.X - point1.X;
	if (abs(dY) < abs(dX)) 
	{
		if (point1.X < point2.X) // bila X1 < X2
			lineDDAX(point1, point2);
		else // bila X1 > X2 maka dibalik
			lineDDAX(point2, point1);
	}
	else // bila deltaY lebih panjang dari deltaX
	{
		if (point1.Y < point2.Y) // bila Y1 < Y2
			lineDDAY(point1, point2);
		else // bila Y1 > Y2 maka dibalik
			lineDDAY(point2, point1);
	}
}

void drawObject(){
	glPushMatrix();
	glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
	
	glColor3f(0.0f, 1.0f, 0.0f);
	Vec3 sbY1 = Vec3( 0.0f,-300.0f, 0.0f);
	Vec3 sbY2 = Vec3( 0.0f, 300.0f, 0.0f);
	Vec3 sbX1 = Vec3(-300.0f, 0.0f, 0.0f);
	Vec3 sbX2 = Vec3( 300.0f, 0.0f, 0.0f);
	lineDDA(sbX1, sbX2);
	lineDDA(sbY1, sbY2);
	
	Vec3 point1 = Vec3( 100.0f, 100.0f, 0.0f);
	Vec3 point2 = Vec3( 100.0f, 10.0f, 0.0f);
	lineDDA(point1, point2);
	lineDDA(point1, point2);

	point1 = Vec3( 10.0f, 100.0f, 0.0f);
	point2 = Vec3( 100.0f, 100.0f, 0.0f);
	lineDDA(point1, point2);
	
	point1 = Vec3( 100.0f, -100.0f, 0.0f);
	point2 = Vec3( 100.0f, -10.0f, 0.0f);
	lineDDA(point1, point2);
	lineDDA(point1, point2);

	point1 = Vec3( 10.0f, -100.0f, 0.0f);
	point2 = Vec3( 100.0f, -100.0f, 0.0f);
	lineDDA(point1, point2);
	
	point1 = Vec3(-10.0f, 100.0f, 0.0f);
	point2 = Vec3(-100.0f, 100.0f, 0.0f);
	lineDDA(point1, point2);
	
	point1 = Vec3( -100.0f, 100.0f, 0.0f);
	point2 = Vec3( -100.0f, 10.0f, 0.0f);
	lineDDA(point1, point2);
	
	point1 = Vec3(-10.0f, -100.0f, 0.0f);
	point2 = Vec3(-100.0f, -100.0f, 0.0f);
	lineDDA(point1, point2);
	
	point1 = Vec3( -100.0f, -100.0f, 0.0f);
	point2 = Vec3( -100.0f, -10.0f, 0.0f);
	lineDDA(point1, point2);
	
	glPopMatrix();
	glPopMatrix();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);
	drawObject();
	glutSwapBuffers();
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);		
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();	
	glOrtho((GLfloat)-SCREEN_WIDTH/2, (GLfloat)SCREEN_WIDTH/2, (GLfloat)-SCREEN_HEIGHT/2, (GLfloat)SCREEN_HEIGHT/2, 1.0, 100.0); // set proyeksi ke perspektif
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();				
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho((GLfloat)-w/2, (GLfloat)w/2, (GLfloat)-h/2, (GLfloat)h/2, 1.0, 100.0);
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
		glutPostRedisplay();	// update obyek
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
	glutCreateWindow("Algoritma DDA");
	
	init();

	glutDisplayFunc(display);   // display
	glutReshapeFunc(reshape);   // reshape
	glutSpecialFunc(keyboard);  // keyboard
	glutMainLoop();

	return 0;
}