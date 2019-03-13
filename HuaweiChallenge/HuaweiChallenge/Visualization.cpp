#include <iostream>
#include <windows.h>

#include "Visualization.h"


using namespace std;

Graph Scene::graph;
map<int, Car> Scene::car_map;


/** \func Select Font
*
* @param 
*
*/
void selectFont(int size,int rotate_angle)
{
	HFONT hFont = CreateFont(size, 0, 0, rotate_angle, FW_MEDIUM, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, NULL);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}


/** \func Scene Initialize
*
* @param _graph to be visualized 
*
*/
void Scene::Init(Graph _graph,map<int,Car> _car_map)
{
	// add graph to scene
	graph = _graph;
	car_map = _car_map;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1440, 1080);
	glutInitWindowPosition(240, 0);
	glutCreateWindow("Traffic Condition");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.5f, 0.4f, 0.9f);
	glPointSize(5.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 1280, 960, 0.0);
}

// GL draw road 
void glDrawRoad(float x1, float y1, float x2, float y2)
{
	// green
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x1, y1, x2, y2);
}

// GL draw cross

void glDrawCross(float x, float y, float radius)
{
	int sections = 200;
	GLfloat TWOPI = 2.0f * 3.14159f;
	
	// purple
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= sections; ++i)
	{
		glVertex2f(x + radius*cos(i*TWOPI / sections), y + radius*sin(i*TWOPI / sections));
	}
	glEnd();
}
// GL draw string
void glDrawString(float x,float y,int font_size,int rotate_angle,const char* str)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	selectFont(font_size, rotate_angle);

	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall)
	{
		isFirstCall = 0;
		lists = glGenLists(128);

		wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
	}

	for (; *str != '\0'; ++str)
		glCallList(lists + *str);

	glutSwapBuffers();
}

/** \func Scene Display Function
*
* @param
*
*/
void Scene::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// draw map
	glDrawRoad(10.0f, 10.0f, 50.0f, 50.0f);

	glDrawCross(100.0f, 100.0f,30.0f);

	glDrawString(100.0f, 100.0f, 10, 0, "101");

	for (int i = 0; i <= graph.max_x; ++i)
	{
		for (int j = 0; j <= graph.max_y; ++j)
		{

		}
	}



	glFlush();
}

/** \func Scene MouseClick Function
*
* @param
*
*/
void Scene::OnMouseClick(int button, int state, int x, int y)
{

}

/** \func Scene MouseMove Function
*
* @param
*
*/
void Scene::OnMouseMove(int x, int y)
{

}

/** \func Scene Display Function
*
* @param
*
*/
void Scene::OnKey(unsigned char key,int,int)
{

}

/** \func Scene MainLoop
*
* @param
*
*/
void Scene::Render()
{

	glutDisplayFunc(OnRender);

	glutMouseFunc(OnMouseClick);
	glutMotionFunc(OnMouseMove);
	glutKeyboardFunc(OnKey);

	glutMainLoop();
}

