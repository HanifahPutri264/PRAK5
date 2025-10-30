#include <windows.h>
#include <GL/glut.h>

float angle = 0.0f;					
float posX = 0.0f, rotX =  0.0f;	
float posY = 0.0f, rotY =  0.0f;	
float posZ = 5.0f, rotZ = -1.0f;	

float objectAngleX = 0.0f;		
float objectAngleY = 0.0f;		
float objectAngleZ = 0.0f;		

void drawObject(){
	glPushMatrix();
	glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(1.0, 20, 20);
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
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);			
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();				
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:		
		objectAngleY += 1.0f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:		
		objectAngleX -= 1.0f;
		glutPostRedisplay();	
		break;
	case GLUT_KEY_DOWN:		
		objectAngleX += 1.0f;
		glutPostRedisplay();	
		break;
	case GLUT_KEY_PAGE_UP:
		posX += rotX * fraction;		
		posZ += rotZ * fraction;
		glutPostRedisplay();	
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
	glutCreateWindow("AUGUSTAV FAHRUL ALZAIYA / 2200018048 - KODE DASAR PRAKTIKUM GRAFIKA KOMPUTER");
	init();
	glutDisplayFunc(display);   
	glutReshapeFunc(reshape);   
	glutSpecialFunc(keyboard); 
	glutMainLoop();

	return 0;
}