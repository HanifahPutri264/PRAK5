#include <windows.h>
#include "gl/glut.h"
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
	//
	Vec3() { }
	~Vec3() { }
};

// kurva
Vec3 controlPoint[4][4];
bool showPoints = false;

GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 100.0 };

GLUnurbsObj *theNurb;
void drawObject()
{
glPushMatrix();
glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
glPushMatrix();
glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
glScalef(0.5, 0.5, 0.5);
glColor3f(0.0f, 1.0f, 0.0f);
//
GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
gluBeginSurface(theNurb);
gluNurbsSurface(theNurb, 8, knots, 8, knots,
 4 * 3, 3, &controlPoint[0][0].X, 4, 4, GL_MAP2_VERTEX_3);
gluEndSurface(theNurb);
if (showPoints)
{
 glPointSize(5.0);
 glDisable(GL_LIGHTING);
 glColor3f(1.0, 1.0, 0.0);
 glBegin(GL_POINTS);
 for (int i = 0; i < 4; i++)
 {
for (int j = 0; j < 4; j++)
{
 glVertex3f(controlPoint[i][j].X, controlPoint[i][j].Y,
 controlPoint[i][j].Z);
}
 }
 glEnd();
 glEnable(GL_LIGHTING);
}
	glPopMatrix();

	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);
	drawObject();
	glutSwapBuffers();
}

void init(void)
{
glClearColor(1.0, 1.0, 1.0, 0.0);
glEnable(GL_DEPTH_TEST); // mengaktifkan depth buffer
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0, 1.0, 1.0, 100.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
int u, v;
for (u = 0; u < 4; u++)
{
 for (v = 0; v < 4; v++)
 {
controlPoint[u][v].X = 2.0*((GLfloat)u - 1.5);
controlPoint[u][v].Y = 2.0*((GLfloat)v - 1.5);
if ((u == 1 || u == 2) && (v == 1 || v == 2))
 controlPoint[u][v].Z = -3.0;
else
 controlPoint[u][v].Z = 3.0;
 }
}
glClearColor(0.0, 0.0, 0.0, 0.0);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_AUTO_NORMAL);
glEnable(GL_NORMALIZE);
theNurb = gluNewNurbsRenderer();
gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
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
	// zoom in
	case GLUT_KEY_PAGE_UP:
		posX += rotX * fraction;		
		posZ += rotZ * fraction;
		glutPostRedisplay();	// update obyek
		break;
	// zoom out
	case GLUT_KEY_PAGE_DOWN:
		posX -= rotX * fraction;
		posZ -= rotZ * fraction;
		glutPostRedisplay();	// update obyek
		break;
	// tampilkan point
	case GLUT_KEY_F1:
		showPoints = !showPoints;
		break;
	}
}
void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(55, timer, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(480, 480);		
	glutInitWindowPosition(100, 100);	
	glutCreateWindow("Augustav Fahrul Alzaiya / 2200018048 - PRAKTIKUM 09 GRAFIKA KOMPUTER");
	init();
	glutDisplayFunc(display);   
	glutReshapeFunc(reshape);  
	glutSpecialFunc(keyboard);  
	glutMainLoop();

	return 0;
}