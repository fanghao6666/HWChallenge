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
void selectFont(int size, int rotate_angle)
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
void Scene::Init(Graph _graph, map<int, Car> _car_map)
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

// GL Draw point
void glDrawPoint(float x, float y)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
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
void glDrawString(float x, float y, int font_size, int rotate_angle, const char* str)
{
	glColor3f(1.0f, 1.0f, 0.0f);
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

	// each cross graph coordinate map
	map<int, pair<float, float>> graph_coord_map;

	//draw cross
	float rate = 180.0f;
	float cross_x_offset = 30.0f;
	float cross_y_offset = 15.0f;
	float string_x_offset = cross_x_offset - 6.0f;
	float string_y_offset = cross_y_offset + 3.0f;
	for (map<int, Cross>::iterator iter = graph.cross_map.begin(); iter != graph.cross_map.end(); ++iter)
	{
		// draw cross
		glDrawCross(rate * iter->second.rel_coordinate.x + cross_x_offset, rate * iter->second.rel_coordinate.y + cross_y_offset, 10.0f);
		graph_coord_map[iter->first] = pair<float, float>(rate * iter->second.rel_coordinate.x + cross_x_offset, rate * iter->second.rel_coordinate.y + cross_y_offset);

		// draw string
		string cross_id_str = to_string(iter->second.id);
		const char* cross_id = cross_id_str.c_str();
		glDrawString(rate * iter->second.rel_coordinate.x + string_x_offset, rate * iter->second.rel_coordinate.y + string_y_offset, 15, 0, cross_id);
	}

	// draw road
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
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
void Scene::OnKey(unsigned char key, int, int)
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

