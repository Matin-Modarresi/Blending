// Blending.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <gl/glut.h>
#include <Windows.h>



static double Y = -2.0;
int Time_s = 60;
int digit1 = 0  , digit2 = 0;
int binary1[4] , binary2[4];

void init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0,0,0,0);

}

void drawSquare(int r , int g , int b ,bool a)
{
	const GLfloat x1 = -1.0, x2 = 1.0, y1 = -1.0, y2 = 1.0;
	
	glBegin(GL_POLYGON);
	if (a)
		glColor4f(r, g, b, .75);
	 else
	   glColor3f(r, g, b);

	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();

}

void decToBinary(int n,int binaryNum[])
{
		 
	int i = 0;

	if (n == 0)
		for (int i = 0; i < 4; i++)
			binaryNum[i] = 0;

	while (n > 0) {

		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}

}

void GL_idle()
{

	if (digit2*10 + digit1 != Time_s)
	{
		Y += 2.0 / Time_s;


		if (digit1 == 9)
		{
			digit1 = 0;
			digit2++;
		}
		else
			digit1++;

		decToBinary(digit1, binary1);
		decToBinary(digit2, binary2);

		Sleep(1000);

		glutPostRedisplay();
	}
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
	case 'S':
		glutIdleFunc(GL_idle);
		
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}
}

void sevenSEG(bool A, bool B, bool C, bool D)
{
	

	bool a = A | C | B & D | !B & !D;
	bool b = !B | !C & !D | C & D;
	bool c = B | !C  |  D;
	bool d = !B & !D | C & !D | B & !C & D | !B & C | A;
	bool e = !B & !D | C & !D;
	bool f = A | !C & !D | B & !C | B & !D;
	bool g = A | B & !C | !B & C | C & !D;

	glLineWidth(5);
	glColor3f(0, 0, 1);

	glBegin(GL_LINES);
	//f
	if (f)
	{
		glVertex2f(-0.7f, .25f);
		glVertex2f(-0.7f, 0.02f);
	}


	//e
	 if (e)
	{
		glVertex2f(-0.7f, -0.01f);
		glVertex2f(-0.7f, -.25f);
	}

	//a
	 if (a)
	{
		glVertex2f(-0.68, .27);
		glVertex2f(-0.49, .27);
	}

	//g
	 if (g)
	{
		glVertex2f(-0.68, 0);
		glVertex2f(-0.49, 0);
	}

	//d
	 if (d)
	{
		glVertex2f(-0.68, -.27);
		glVertex2f(-0.49, -.27);
	}

	//b
	 if (b)
	{
		glVertex2f(-0.47, 0.25);
		glVertex2f(-0.47, 0.02);
	}

	//c
	if (c)
	{
		glVertex2f(-0.47, -0.01);
		glVertex2f(-0.47, -0.25);
	}
	glEnd();

}




void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

       glPushMatrix();
	   drawSquare(1,1,1,false);
	   glPopMatrix();
	 
	   glPushMatrix();
	   glTranslatef(.85, 0, 0);
	   sevenSEG(binary1[3], binary1[2], binary1[1], binary1[0]);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(.4, 0, 0);
	   sevenSEG(binary2[3], binary2[2], binary2[1], binary2[0]);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0, Y, 0);
	   drawSquare(1, 0, 0, true);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0, 2.0, 0);
	   drawSquare(0, 1, 0,false);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0, -2.0, 0);
	   drawSquare(0, 1, 0,false);
	   glPopMatrix();

	  

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
	glutInitWindowSize(600, 600);
	glutCreateWindow("Timer");
	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);


	glutMainLoop();
	return 0;
}



