// Blending.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

static bool first = GLU_TRUE;
static float Y = 0;
void init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glClearColor(0,0,0,0);

}

void drawCircle()
{

	glColor4f(1, 1, 1.0,.5);
	glutSolidSphere(1.0, 100, 50);

}

void drawRightTriangle()
{
	
	glBegin(GL_TRIANGLES);
	glColor4f(0, 1, 1, 0.75);
	glVertex3f(0.0, 0, 0);
	glVertex3f(.3, .5, 0);
	glVertex3f(.9, .1, 0);
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 't':
		//first = !first;
		Y+=.1;
		glutPostRedisplay();
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (first)
	{
		glPushMatrix();
		glTranslatef(0, Y, 0);
		drawRightTriangle();
		glPopMatrix();

		drawCircle();
	}

	else
	{
		drawCircle();
		drawRightTriangle();
	}
	

	glFlush();
}

void reshape(int w, int h)
{

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("start");
	init();

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
