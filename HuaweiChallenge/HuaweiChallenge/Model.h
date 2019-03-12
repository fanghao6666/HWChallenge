// This file include the classes of car cross and road
// @Date : 2019/3/10
// @Author: 第一名是我小号

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


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
		int pos_in_channel;
	};

public:
	// car id
	int id;

	// start position
	int from;

	// destination
	int to;

	// max speed
	int max_speed;

	// current speed
	int cur_speed;

	// start time
	int start_time;

	// car position
	Position position;

};

//************** ROAD *************//

class Road
{
public:
	Road() {};
	Road(int &_id, int &_length, int &_max_speed, int &_channel, int &_from, int &_to, int &_idDuplex) :
		id(_id), length(_length), max_speed(_max_speed), channel(_channel), from(_from), to(_to), isDuplex(_idDuplex) {};
	~Road() {};

public:
	// road id
	int id;

	// road length
	int length;

	// max_speed
	int max_speed;

	// channel num
	int channel;

	// start id
	int from;

	// end id
	int to;

	// isDuplex
	int isDuplex;
};

//************** CROSS *************//

class Cross
{
public:
	Cross() {};
	Cross(int &_id, int &_up_id, int &_right_id, int &_down_id, int &_left_id) :
		id(_id), up_id(_up_id), right_id(_right_id), down_id(_down_id), left_id(_left_id) {};
	~Cross() {};

	// cross coordinate struct
	struct Coordinate
	{
		int x;
		int y;
	};

public:
	// cross id
	int id;

	// up road id
	int up_id;

	// right road id
	int right_id;

	// dowm road id
	int down_id;

	// left road id
	int left_id;

	// cross coordinate
	Coordinate coordinate;
};


//************** GRAPH *************//

class Graph
{
public:
	Graph() {};

	~Graph() {};

	// Coordinated each cross
	void coordinatedCross();

	// BFS
	void BFS(int start_cross_id);

	// get id of cross which meet the conditions
	int idOfCross(int road1, int road2, int road3, int road4);


public:
	// Cross list
	map<int, Cross> cross_map;

	// Road list
	map<int, Road> road_map;

	// cross matrix
	//vector<vector<Cross>> graph;

	// row & col
	//int row;
	//int col;
};