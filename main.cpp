

#include <iostream>

#include "windows.h"
#include <time.h>
#include <math.h>
#include <gl\gl.h>

#include <GL/glut.h>

#define PI 3.14159265

// Devrim Mert Yöyen 151805004

int screenWidth = 800;
int screenHeight = 800;
int delay = 10;
double A[3] = { 0,0,0 };
double B[3] = { 0,0,0 };
double alfa = 0;
int    fx = 0, fy = 0, fz = 0;
float  sphi = 0.0, stheta = 0.0;
float  sside = 0, sdepth = -5;
float  sx = 0, sy = 0;
bool  mouse_left_click, mouse_middle_click, mouse_right_click;
int   mouseX, mouseY;


//______________________ <myIdle()> ____________________________
void myIdle(int frame)
{
	alfa += 10;
	if (alfa > 360) alfa -= 360;
	A[1] = sin(alfa*PI / 180);
	A[2] = cos(alfa*PI / 180);
	B[1] = sin((alfa + 180)*PI / 180);
	B[2] = cos((alfa + 180)*PI / 180);

	glutTimerFunc(delay, myIdle, 0);
	glutPostRedisplay();
}

//______________________ </myIdle()> ____________________________

//----------------------------------------------------------------------------

//______________________<myInit()> ____________________________
// COLOR 
void myInit()
{
	glColor3f(0.1f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 1.0, 1.0, 100.0);
	gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	myIdle(0);
}
//______________________</myInit()> ____________________________

//--------------------------------------------------------------------------

//______________________ <myReshape()> ___________________________
void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glOrtho(-2, 2, -2, 2, -2, 2);
}

//______________________ </myReshape()> ___________________________


//--------------------------------------------------------------------------


//_______________________ <myKeyboard()> ___________________________
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(-1);
	}
	glutPostRedisplay();
}

//_______________________ </myKeyboard()> ___________________________


//--------------------------------------------------------------------------


//________________________ <myDisplay()> ______________________________
void myDisplay(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(sside, 0, -sdepth);
	glRotatef(-stheta, 1, 0, 0);
	glRotatef(sphi, 0, 1, 0);
	glTranslatef(sx, 0, -sy);

	glColor3f(0, 1, 1);
	glutSolidTeapot(2);
	glutSwapBuffers();
}

int Theta_x = 0;
int Theta_y = 0;
int Theta_z = 0;

void menu(int value) {
	switch (value) {
	case 1:
		Theta_x += 90;
		glutPostRedisplay();
		break;
	case 2:
		Theta_y += 90;
		glutPostRedisplay();
		break;
	case 3:
		Theta_z += 90;
		glutPostRedisplay();
		break;
	case 4: exit(0);
	}
	glutPostRedisplay();
}

// WIEW WINDOW DISPLAY
void myDisplayWin2(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(Theta_x, 1, 0, 0);
	glRotatef(Theta_y, 0, 1, 0);
	glRotatef(Theta_z, 0, 0, 1);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.07, 0.37, 0.0);
	glColor3f(1, 0, 0);

	glutWireTeapot(2);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void myInitWin2()
{
	glColor3f(0.1f, 0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 1.0, 1.0, 100.0);
	gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
	myIdle(0);
}

void myReshapeWin2(int width, int height)
{
	glViewport(0, 0, width, height);
	glOrtho(-1, 1, -1, 1, -1, 1);

}


// MOUSE EVENTS
void myMouse(int button, int state, int x, int y)
{
	mouseX = x; mouseY = y;
	mouse_left_click = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	mouse_middle_click = ((button == GLUT_MIDDLE_BUTTON) &&
		(state == GLUT_DOWN));
	mouse_right_click = ((button == GLUT_RIGHT_BUTTON) &&
		(state == GLUT_DOWN));
	glutPostRedisplay();
}

//MOUSE MOVE EVENTS
void myMouseMove(int x, int y) {
	// rotate
	if (mouse_left_click)
	{
		sphi += (float)(x - mouseX) / 4.0;
		stheta += (float)(mouseY - y) / 4.0;

	}

	// scale
	if (mouse_middle_click)
	{
		sx += (float)(x - mouseX) * 50;
		sy += (float)(y - mouseY) * 50;
	}

	// scale
	if (mouse_right_click)
	{
		sside += (float)(x - mouseX) * 50;
		sdepth += (float)(y - mouseY) * 50;
	}
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
}
//________________________ </myDisplay()> ______________________________

//----------------------------------------------------------------------

//________________________ <main function> _______________________________
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("View Agle");
	glutReshapeFunc(myReshapeWin2);
	glutDisplayFunc(myDisplayWin2);
	glutCreateMenu(menu);
	glutAddMenuEntry("Top", 1);
	glutAddMenuEntry("Side", 2);
	glutAddMenuEntry("Bottom", 3);
	glutAddMenuEntry("Close", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	myInitWin2();


	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Drag Rotate");
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMouseMove);
	myInit();

	glutMainLoop();
}
//________________________ </main function> _______________________________

