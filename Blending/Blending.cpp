// Blending.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <Windows.h>


static bool first = GLU_TRUE;
static double Y = 0;
int Time = 60 , distance = 1;

void init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glClearColor(0,0,0,0);

}

void drawCircle()
{

	glColor4f(1, 1, 1.0,.3);
	glutSolidSphere(1.0 * distance, 100, 50);

	/*GLfloat angle, raioX = 1.0f, raioY = 1.0f;
	GLfloat circle_points = 360.0f;


	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1, 1, 1.0, .3);
	glVertex2f(0.0f, 0.0f);

	for (int i = 0; i <= 360; i++)
	{
		angle = 2 * 3.1415 * i / circle_points;
		glVertex2f(0.0 + cos(angle) * raioX, 0.0 + sin(angle) * raioY);
	}

	glEnd();*/

}

void drawRightTriangle()
{
	glColor3f(1, 0, 0);
	glutSolidSphere(1.0 * distance, 100, 50);

}

void drawSquare()
{
	const GLfloat x1 = -1.02, x2 = 1.02, y1 = -1.02, y2 = 1.02;
	glPushMatrix();
	
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
	glPopMatrix();
}

void GL_idle()
{
	Sleep(100);
    Y+= 2 *distance * .1/Time;
	
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 't':
		//first = !first;
		
		glutIdleFunc(GL_idle);
		//glutPostRedisplay();
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
	
       drawRightTriangle();

	   glPushMatrix();
	   glTranslatef(0, Y, 0);
	   drawSquare();
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

	glOrtho(1.02, -1.02, 1.02, -1.02, 0, 0);

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
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);


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

