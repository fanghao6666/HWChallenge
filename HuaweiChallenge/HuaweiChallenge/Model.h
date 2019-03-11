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

	// channel
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
};


//************** GRAPH *************//

class Graph
{
public:
	Graph() {};

	~Graph() {};

	// parse cross file to get row & col
	void getRowAndCol();



public:
	// Cross list
	map<int, Cross> cross_map;

	// Road list
	map<int, Road> road_map;

	// cross matrix
	vector<vector<Cross>> graph;

	// row & col
	int row;
	int col;
};