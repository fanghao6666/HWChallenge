#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "Txtparser.h"
#include "Model.h"
#include "Visualization.h"


using namespace std;

string path = "config_8";

int main()
{
	// read car cross and road
	map<int, Car> car = readCar("../config/" + path + "/car.txt");
	map<int, Cross> cross = readCross("../config/" + path + "/cross.txt");
	map<int, Road> road = readRoad("../config/" + path + "/road.txt");

	// graph
	Graph graph(cross, road);

	graph.coordinatedCross();

	//for (map<int, Cross>::iterator iter = graph.cross_map.begin(); iter != graph.cross_map.end(); ++iter)
	//{
	//	cout << "Cross id : " << iter->first << " Cross coordinate : X : " << iter->second.coordinate.x << " Y : " << iter->second.coordinate.y << endl;
	//}

	// visulization
	Scene scene;
	scene.Init(graph, car);
	scene.Render();

	return 0;
}
