#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14

static int move=1,year = 0, day = 0;
static float x_off=0,y_off=0,dist=4,theta=0,a[9];
class celestialSphere
{
public:
	virtual float radius()=0;
	virtual float day()=0;
	virtual float orbit()=0;

};
class star : public celestialSphere
{
	float rd,angle;
public:
	star(float r,float ang)
	{
		rd=r;
		angle=ang;
	}
	float radius()
	{
		return rd;
	}
	float day()
	{
		return angle;
	}
	float orbit()
	{
		return 0;
	}
} sun(0.771,1);

class planet : public celestialSphere{
	float rd,dy,orbt;
public:
	planet(float r,float d, float o)
	{
		rd=r;
		dy=d;
		orbt=o;
	}
	float radius()
	{
		return rd;
	}
	float day()
	{
		return dy;
	}
	float orbit()
	{
		return orbt;
	}
}       mercury(0.02,1.67,1.05),
	venus(0.042,1.5,1.19),
	earth(0.044,1,1.36),
	mars(0.022,0.9,1.58),
	jupiter(0.3,0.76,2.022),
	saturn(0.21,0.64,2.75),
	uranus(0.095,0.43,3.473),
	neptune(0.08,0.341,4.3);
	//pluto(0.01,0.21,3.7461);


void drawBody(celestialSphere& p,float r,float g,float b)
{
	float orb,ang;
	GLUquadric * optr= gluNewQuadric();
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);


		glColor3f (1,1,1);

		if(p.orbit()!=0)
		{
			orb = p.orbit()*0.499;
			glutWireTorus((GLdouble)orb,(GLdouble)(orb + 0.001),(GLint)1,(GLint)100);

		}

		glRotatef ((GLfloat) (year*p.day()), 0.0, 0.0, 1.0);
		glTranslatef (p.orbit(), 0.0, 0.0);

		if (p.radius()>0.2&&p.radius()<0.22)
		{
			ang=(float)((int)(p.day()*year)%360)/360;
			ang*=2*PI;
            glRotatef ((GLfloat)25,sin(ang), cos(ang), 0.0);
			GLUquadric* quad = gluNewQuadric();
			glColor3f (0.4,0.3,0.3);
			gluDisk(quad,0.23,0.35,100,100);

		}
		glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
		glColor3f (r,g,b);
		gluSphere(optr,p.radius(),30 , 40);

	glPopMatrix();
}
void print(int x, int y, float r, float g, float b, void * font, char *string)
{
  	glColor3f( r, g, b );
  	glRasterPos2f(x, y);
  	int len, i;
  	len = (int)strlen(string);
  	for (i = 0; i < len; i++)
	{
  		  glutBitmapCharacter(font, string[i]);
  	}
}

void init(void)
{


	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position0[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position1[] = { 0, 1.0, .0, 0.0 };
	GLfloat light_position2[] = { 0, 0, 1.0, 0.0 };
	GLfloat light_position3[] = { 0, 0, -1.0, 0.0 };
	glClearColor (0.0, 0.0, 0.062, 0.0);
	glShadeModel (GL_SMOOTH);

	GLfloat light_diffuse[] = { 0.75, 0.75, 0.75, 1.0};
	GLfloat light_ambient[] = { 0.12, 0.12, 0.12, 1.0};
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_EMISSION);
}

void camera()
{

	glTranslatef (x_off, 0, 0.0);
	gluLookAt (0,dist*cos(theta)+y_off,dist*sin(theta),0,y_off,0,0,-sin(theta),cos(theta));

}
void light_on()
{
 		GLfloat light_pos0[] = { 100, 100, 100, 0.0 };
		GLfloat mat_emission[] = {0.45,0,0, 1.0};
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);

}
void light_off()
{
		GLfloat light_pos0[] = { 0, 0, 0, 1 };
		GLfloat mat_emission[] = {0,0,0, 1.0};
		GLfloat light_radiant[] = { 1,1,1,0.8};
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_radiant);

}
void display(void)
{


	glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


	glPushMatrix();

		camera();

	/*
		print(-2,-5,5,5,5,GLUT_BITMAP_HELVETICA_18,"Solar System Simulation");
		print(-6,-8,5,5,5,GLUT_BITMAP_HELVETICA_12,"Controls: Space-Rotation and revolution, m-Rotation only, c-Change camera view, o-Zoom out, p-Zoom in");
		print(3,-6,5,5,5,GLUT_BITMAP_HELVETICA_12,"By: Raveendra P Soori");
		*/
		light_on();
		drawBody(sun,0.966,0.466,0.066);
		light_off();


		drawBody(mercury,0.5054,0.5054,0.5054);
		drawBody(venus,0.5764,0,0);
		drawBody(earth,0,0.247, 0.549);
		drawBody(mars,0.6764,0,0);
		drawBody(jupiter,0.701,0.2505,0.2505);
		drawBody(saturn,0.6,0.4,0.4);
		drawBody(uranus,0.541, 0.749, 1);
		drawBody(neptune,0.23039,0.6156,0.6177);
		//drawBody(pluto,0.9, 0.4, 0);
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
}
