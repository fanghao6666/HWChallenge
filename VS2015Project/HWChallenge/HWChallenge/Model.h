#pragma once
// This file include the classes of car cross and road
// @Date : 2019/3/10
// @Author: 第一名是我小号

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Road;
class Car;
class Cross;
class Graph;
class Scheme;

//************** CAR *************//

class Car
{
public:
	Car() {};
	Car(int &_id, int &_from, int &_to, int &_max_speed, int &_start_time) :
		id(_id), from(_from), to(_to), max_speed(_max_speed), cur_speed(_max_speed), start_time(_start_time) {};
	~Car() {};

	// car position struct
	struct Position
	{
		// road id
		int roadId;
		// channel id
		int channel;
		// position in channel
		int pos;
	};

	// get real speed of current road;
	int getRealSpeedOfRoad(Road& road);

	// get runtime of current road;
	int getRunTimeOfRoad(Road& road);

public:
	int id;
	int from;
	int to;
	int max_speed;
	int cur_speed;
	int start_time;
	Position position;
	vector<int> route;
	int route_idx;
	bool is_started;
	bool is_arrived;
	bool is_moved;
	//0: null, 1:hold, 2:stop
	int label;
};

//************** ROAD *************//

class Road
{
public:
	Road() {};
	Road(int &_id, int &_length, int &_max_speed, int &_channel, int &_from, int &_to) :
		id(_id), length(_length), max_speed(_max_speed), channel(_channel), from(_from), to(_to) {};
	~Road() {};

	// put a new car on road 
	void putNewCar(Car& car);

public:
	int id;
	int length;
	int from;
	int to;
	int max_speed;
	int channel;
	//channel_nums*length
	vector<vector<int>> roadCondition;

};

//************** CROSS *************//

class Cross
{
public:
	Cross() {};
	Cross(int _id) :id(_id) {};
	Cross(int _id, int *_next_road) :id(_id){};
	~Cross() {};

	// cross coordinate struct
	struct Coordinate
	{
		int x;
		int y;
	};

public:
	int id;

	//up->right->down->left, -1 means null
	vector<int> next_cross;
	vector<int> next_road;

	//relative location of this cross
	Coordinate pos;
	bool ispass;

	//for get shortest route
	int time;
	int prev;

};


//************** GRAPH *************//

class Graph
{
public:
	Graph() {};
	~Graph() {};


	// init gragh
	void initGraph();


	// init shortest routes of every cars
	void initPath();
	// init shortest route of this car in submap
	void getShortestRouteInSubmap(Car& car, vector<int>& submap);
	// get submap of rect from startid to endid, return Cross vector
	vector<int> getSubMap(int start_id, int end_id);


	// modify the some paths 
	vector<vector<int>> getModiCars(int modinum);
	void setNewPathWithoutRoads(vector<int> midicars);
	void modifyPath(int modinum);


	// simulate the process and return totaltime
	int Simulation();
	// return true if all cars are finished
	bool areAllCarsFinished();
	// drive cars that are not started
	void driveCarsInGarage(int curtime);
	// return true if all cars are marked
	bool areAllCarsMarked();
	// get cars numbers of a cross
	int getCarsNumsOfRoads(vector<Road> roads);
	// return true if all cars run
	bool areAllCarsMoved(vector<Road> roads);
	// simulate by three steps
	void updateStepOne(Road& road);
	void updateStepTwo(vector<Road> roads, int idx, int* handleflag, int handlecount, int roadnums);
	void updateStepThree(Road& road);

public:
	// car cross road map
	map<int, Cross> cross_map;
	map<int, Road> road_map;
	map<int, Car> car_map;

	// car cross road list
	vector<int> cross_list;
	vector<int> road_list;
	vector<int> car_list;

	// connection with cross & road 
	map<pair<int, int>, int> road_direction;

	// Coordinate map
	map<pair<int, int>, Cross> rel_coordinate_map;
	map<pair<int, int>, Cross> abs_coordinate_map;
};


//************** Scheme *************//

class Scheme {

public:
	Scheme() {};
	Scheme(Graph& graph) {
		for (int i = 0; i < graph.car_list.size(); i++) {
			Car& car = graph.car_map[graph.car_list[i]];
			cross_routes.push_back(car.route);

			vector<int> roads;
			for (int i = 0; i < car.route.size() - 1; i++) {				
				roads.push_back(graph.road_direction[pair<int, int>(car.route[i], car.route[i + 1])]);
			}
			road_routes.push_back(roads);

			vector<int> answer;
			answer.push_back(car.id);
			answer.push_back(car.start_time);
			answer.insert(answer.end(), roads.begin(), roads.end());
			answers.push_back(answer);
			
		}
	}
	~Scheme() {};

	vector<vector<int>> answers;
	vector<vector<int>> cross_routes;
	vector<vector<int>> road_routes;
	vector<vector<int>> car_runtimes;
	vector<vector<int>> car_taffcounts;
	vector<vector<int>> car_taffroads;
	int	total_whole_time;
	int toatal_run_time;
	int	total_taff_flow;
	int	total_car_taff_count;
	int	total_road_taff_count;

public:
	//vector<int>	GetAmendCars();
};