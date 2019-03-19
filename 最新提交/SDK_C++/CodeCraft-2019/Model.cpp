#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <stack>

#include "Model.h"

using namespace std;



//***************** CAR ******************//
// get real speed of current road;
int Car::getRealSpeedOfRoad(Road& road) {
	return min(this->max_speed, road.max_speed);
}

// get runtime of current road;
int Car::getRunTimeOfRoad(Road& road) {
	return road.length / this->getRealSpeedOfRoad(road);
}

//***************** CROSS ******************//


//***************** ROAD ******************//


//***************** GRAPH ******************//
// init gragh
void Graph::initGraph() {

	//Coordinated each cross with relative location

	int direction[4][2] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };

	// BFS
	queue<Cross*> queue;
	queue.push(&cross_map[cross_list[0]]);
	cross_map[cross_list[0]].pos.x = 0;
	cross_map[cross_list[0]].pos.y = 0;
	cross_map[cross_list[0]].ispass = true;


	while (!queue.empty()) {
		Cross* cross = queue.front();
		queue.pop();
		int x = (cross->pos).x;
		int y = (cross->pos).y;
		for (int i = 0; i < 4; i++) {
			if ((cross->next_road)[i] != -1) {
				//find nextcross through nextroad
				Road& newroad = road_map[(cross->next_road)[i]];
				int newcrossid = newroad.from == (cross->id) ? newroad.to : newroad.from;
				Cross* newcross = &cross_map[newcrossid];

				if (!(newcross->ispass)) {
					(newcross->pos).x = x + direction[i][0];
					(newcross->pos).y = y + direction[i][1];
					(newcross->ispass) = true;
					queue.push(newcross);
				}
			}
		}
	}

	//put every cross with next cross
	for (int i = 0; i < cross_list.size(); i++) {
		Cross& cross = cross_map[cross_list[i]];
		cross.next_cross = vector<int>(4, -1);
		for (int j = 0; j < 4; j++) {
			if (cross.next_road[j] != -1) {
				Road& nextroad = road_map[cross.next_road[j]];
				if (road_direction.count(pair<int, int>(cross.id, nextroad.to)) != 0) {
					cross.next_cross[j] = nextroad.to;
				}
				if (road_direction.count(pair<int, int>(cross.id, nextroad.from)) != 0) {
					cross.next_cross[j] = nextroad.from;
				}
			}
		}
	}
}

// init shortest routes of every cars
void Graph::initPath() {
	//init shortest route of this car in submap
	for (int i = 0; i < car_list.size(); i++) {
		Car& car = car_map[car_list[i]];
		getShortestRouteInSubmap(car, getSubMap(car.from, car.to));
	}

	//if any cars have no route, rehandle in wholemap
	for (int i = 0; i < car_list.size(); i++) {
		Car& car = car_map[car_list[i]];
		if (car.route.size() < 2) {
			car.route.clear();
			getShortestRouteInSubmap(car, cross_list);
		}
	}
}

// init shortest route of this car in submap
void Graph::getShortestRouteInSubmap(Car& car, vector<int> submap) {

	map<int, bool> is_in_submap;
	map<int, bool> isVisited;

	stack<int> reverseRoute;	// save the route reversely
	for (int c : submap)
	{
		cross_map[c].time = 100000;			// set the initial metric to integer max value
		cross_map[c].prev = -1;				// set the prev to NULL
		cross_map[c].ispass = false;
		is_in_submap[c] = true;
		isVisited[c] = false;
	}
	cross_map[car.from].time = 0;	// the metric of start set to 0 

	Cross& from_cross = cross_map[car.from];
	Cross& to_cross = cross_map[car.to];

	for (int c : submap)
	{
		int minTime = 9999;
		int minCross;
		for (int c : submap)
		{
			Cross & cur = cross_map[c];
			if (!isVisited[c] && cur.time < minTime)
			{
				minTime = cur.time;
				minCross = c;
			}
		}
		Cross& curMinCross = cross_map[minCross];
		isVisited[minCross] = true;

		vector<int> nextcross = vector<int>(4);
		vector<int> nextroad = vector<int>(4);
		for (int i = 0; i < 4; i++) {
			nextcross[i] = (curMinCross.next_cross)[i];
			nextroad[i] = (curMinCross.next_road)[i];
			//do while curMin can get nextcross & nextcross is in the submap
			if (nextroad[i] == -1 || is_in_submap.count(nextcross[i]) == 0 || road_direction.count(pair<int, int>((curMinCross.id), nextcross[i])) == 0 || isVisited[nextcross[i]])
				continue;

			//update cur_cross's time & route
			Cross& cur_cross = cross_map[nextcross[i]];
			Road& cur_road = road_map[nextroad[i]];
			int cur_time = curMinCross.time + car.getRunTimeOfRoad(cur_road);
			if (cur_time < cur_cross.time) {
				cur_cross.time = cur_time;
				cur_cross.prev = curMinCross.id;
			}
		};
	}

	// save route from car.to to car.from by stack
	int crossInRoute = car.to;
	while (cross_map[crossInRoute].prev != -1)
	{
		reverseRoute.push(crossInRoute);
		crossInRoute = cross_map[crossInRoute].prev;
	}
	reverseRoute.push(car.from);

	// save route from car.from from car.to by vector
	while (!reverseRoute.empty())
	{
		car.route.push_back(reverseRoute.top());
		reverseRoute.pop();
	}

}

// get submap of rect from startid to endid, return Cross vector
vector<int> Graph::getSubMap(int start_id, int end_id) {
	int minx = min(cross_map[start_id].pos.x, cross_map[end_id].pos.x);
	int maxx = max(cross_map[start_id].pos.x, cross_map[end_id].pos.x);
	int miny = min(cross_map[start_id].pos.y, cross_map[end_id].pos.y);
	int maxy = max(cross_map[start_id].pos.y, cross_map[end_id].pos.y);

	vector<int> submap;
	for (int i = 0; i < this->cross_list.size(); i++) {
		Cross cross = cross_map[cross_list[i]];
		if (cross.pos.x >= minx && cross.pos.x <= maxx && cross.pos.y >= miny && cross.pos.y <= maxy) {
			submap.push_back(cross.id);
		}
	}

	return submap;
}

// modify every initial routes
void Graph::modifyInitialPath() {

}

//***************** Scheme ******************//
