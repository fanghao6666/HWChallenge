#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "Txtparser.h"
#include "Model.h"


using namespace std;

int main()
{
	// read car cross and road
	map<int, Car> car = readCar("C:/Users/ai/Desktop/car.txt");
	map<int, Cross> cross = readCross("C:/Users/ai/Desktop/cross.txt");
	map<int, Road> road = readRoad("C:/Users/ai/Desktop/road.txt");

	// graph
	Graph graph;
	graph.cross_map = cross;
	graph.road_map = road;

	return 0;
}
