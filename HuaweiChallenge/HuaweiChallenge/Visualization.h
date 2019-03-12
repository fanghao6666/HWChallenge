// This visualization program is used to DEBUG
// The official submission code does not include this file
// @Date : 2019/3/12
// @Author: 第一名是我小号

#pragma once
#include <iostream>
#include <glut.h>

#include "Model.h"

using namespace std;

class Scene
{
public:
	Scene() {};
	~Scene() {};

public:
	// initialize the scene
	static void Init(Graph graph, map<int, Car> _car_map);

	// rendering the graph
	static void OnRender();

	// mouse click function
	static void OnMouseClick(int button, int state, int x, int y);
	
	// mouse click&move function
	static void OnMouseMove(int x, int y);

	// keyboard function
	static void OnKey(unsigned char key, int, int);

	// render mainloop
	void Render();

public:
	// graph
	static Graph graph;

	// car
	static map<int, Car> car_map;
};