#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14

static int move=1,year = 0, day = 0;
static float x_off=0,y_off=0,dist=4,theta=0,a[9],b[4]={0,0,0,1},ab[4]={0.78,0.33,0.058},lab[4]={0.7,0.7,0.7};

void drawBody(float r,float g,float b)
{
	GLUquadric* quad = gluNewQuadric();
	glPushMatrix();
		glColor3f (r,g,b);
		glutSolidSphere(0.771,30 , 40);
	gluDisk(quad,1.7,1.74,100,100);

	glPopMatrix();
}

void init(void)
{

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position0[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position1[] = { -1.0, -1.0, -1.0, 0.0 };
	GLfloat light_position2[] = { 0, 0, 1.0, 0.0 };
	GLfloat light_position3[] = { 0, 0, -1.0, 0.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	GLfloat light_ambient[] = { 1.0, 1, 1.0, 1.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void camera()
{

	glTranslatef (x_off, 0, 0.0);
	gluLookAt (0,dist*cos(theta)+y_off,dist*sin(theta),0,y_off,0,0,-sin(theta),cos(theta));

}

void display(void)
{


	glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


	glPushMatrix();

		camera();

		drawBody(0.966,0.466,0.066);

		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, b);


		for(int k=0;k<640000;k++);
		for(int k=0;k<640000;k++);
		for(int k=0;k<640000;k++);
		if(move==0)
		{
			day = (day+1) % 360;
		}
		else if(move==1)
		{
			day = (day+1) % 360;
			year++;
		}
		glutSwapBuffers();

	glPopMatrix();
	glFlush();

}
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0,0,3.18,0,0,0,0,1,0);
}

void keyboard (unsigned char key, int x, int y)
{
	int i;
	switch (key) {
	case 'y':
	case 'Y':
		theta+=0.01;
		if(theta>2*PI)
			theta=0;
		break;

	case 'h':
	case 'H':
		theta-=0.01;
		if(theta<0)
			theta=2*PI;
		break;

	case 'A':
	case 'a':
		x_off+=0.1;
		glutPostRedisplay();
		break;

	case 'D':
	case 'd':
		x_off-=0.1;
		glutPostRedisplay();
		break;

	case 's':
	case 'S':
		y_off+=0.1;
		glutPostRedisplay();
		break;

	case 'W':
	case 'w':
		y_off-=0.1;
		glutPostRedisplay();
		break;

	case 't':
	case 'T':
		move=(move+1)%3;
		glutPostRedisplay();
		break;

	case 'P':
	case 'p':
		dist-=0.1;
		if(dist<0)
			dist=0;
		break;

	case 'O':
	case 'o':
		dist+=0.1;
		break;

	case 'r':
	case 'R':
		x_off=0;
		y_off=0;
		dist=4;
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize ( 1000,700);

	glutInitWindowPosition (100, 0);
	glutCreateWindow ("Solar System");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
void init(void)
{
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel (GL_SMOOTH);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);

}
void display(void)
{
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glColor3f (1,0.5,0.5);
glutSolidSphere (0.77, 20, 16);
glColor3f (1,0,0);
glutWireTorus((GLdouble)1,(GLdouble)( 1.001),(GLint)1,(GLint)100);
gluLookAt (0,5,0.2,0,0,0,0,0,1);
glFlush ();
}
void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
if (w <= h)
glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
else
glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100, 100);
glutCreateWindow (argv[0]);
init ();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}*/
