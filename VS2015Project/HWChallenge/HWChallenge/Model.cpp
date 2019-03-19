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
void Road::putNewCar(Car& car) {

}

//***************** GRAPH ******************//
// init gragh
void Graph::initGraph() {

	//Coordinated each cross with relative location

	int direction[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

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
void Graph::getShortestRouteInSubmap(Car& car, vector<int>& submap) {

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


//路径修正：返回一条可行路径
void Graph::modifyPath(int modinum) {

	//根据模拟结果返回修正指标：某些车不能走某些路，每次优先修正的车辆数目为modinum
	//每一位放汽车ID，其余位放该车不能经过的道路
	vector<vector<int>> midicars = getModiCars(modinum);

	//依次修正每一辆车的路线，若不存在该路线这放弃修正
	for (int i = 0; i < midicars.size(); i++) {
		/*
		Car& car = midicars[i][0];
		setNewPathWithoutRoads(car, midicars[i]);
		*/
		setNewPathWithoutRoads(midicars[i]);
	}
}

vector<vector<int>> Graph::getModiCars(int modinum) {
	vector<vector<int>> result;
	return result;
}

void Graph::setNewPathWithoutRoads(vector<int> midicars) {

}

//过程模拟
bool comparator_of_roadid(Road& road1, Road& road2) {
	return road1.id < road2.id;
}

int Graph::Simulation() {
	int totaltime = 0;

	//isFinish()判定条件：所有车到达终点
	while (areAllCarsFinished()) {
		totaltime++;

		//车辆出发，遍历所有车辆：不到出发时间，不上路（在路中没有位置），标记其为终止状态；到达出发时间，行驶至最远可行驶距离，标记终止。
		driveCarsInGarage(totaltime);

		//////////////////////Step1：标记所有车辆的终止状态（移动）与等待状态（不动）//////////////////////

		//在所有车辆均被标记前，按道路id增序进行：
		//1.标记所有能动且不出路口的车辆：移动车辆的位置，更新结束后标记其为终止状态
		//2.标记所有要出路口的车辆的车辆：车辆保持原位置，并标志为等待状态
		//3.标记所有有车辆阻挡的车辆：若前车为等待状态，车辆保持原位置，标其为等待状态；若前车为终止状态，移动车辆的位置，标其为终止状态.
		//isEveryCarsMarked()所有车辆判断条件为所有车辆均被标记
		while (areAllCarsMarked()) {
			for (int i = 0; i < road_list.size(); i++) {
				Road& road = road_map[road_list[i]];
				//见计划书第9节
				updateStepOne(road);
			}
		}

		//对所有路口被标记为等待的车辆进行调度，调度后将其标记为终止状态	
		for (int i = 0; i < cross_list.size(); i++) {
			Cross& cross = cross_map[cross_list[i]];
			vector<Road> roads;
			for (int j = 0; j < 4; j++) {
				//筛选出路口方向的路
				if (cross.next_road[j] != -1 && road_direction.count(pair<int, int>(cross.next_cross[j], cross.id))) {
					Road& road = road_map[cross.next_road[j]];
					roads.push_back(road);
				}
			}

			//对出路口的道路进行排序,并按道路编号增序进行调度
			sort(roads.begin(), roads.end(), comparator_of_roadid);


			//taffcount为死结标志，每一次循环+1（一次循环至少调度一辆车）
			int taffcount = 0;
			int carnums = getCarsNumsOfRoads(roads);
			//isEveryCarsRuns(roads)判断条件为该路口所有车辆均被标记为终止状态
			while (areAllCarsMoved(roads)) {

				//////////////////////Step2：调度路口等待出路口的车辆//////////////////////

				//设置标志位防止一次循环重复调度
				int handleflag[4] = { 0 };
				int handlecount = 0;
				int roadnums = roads.size();
				for (int j = 0; j < roadnums; j++) {
					if (handlecount >= roadnums)
						break;
					if (handleflag[j] != 0)
						continue;
					//见计划书第9节
					//updateStepTwo内部实现为：
					//1.判断handlecount与roadnums，如果所有路都已经获得调度权限，直接返回
					//2.判断j与handleflag，如果该路已经获得过调度权限，直接返回
					//3.调度该路等待出路口的可行车辆，更新handlecount与handleflag
					//4.若调度过程产生冲突，则递归进行updateStepTwo
					updateStepTwo(roads, j, handleflag, handlecount, roadnums);
				}

				//////////////////////Step3：调度路口等待路上行驶的车辆//////////////////////

				for (int j = 0; j < roadnums; j++) {
					updateStepThree(roads[j]);
				}

				//若经过taffcount次调度仍然无法调度完carnums辆车，说明存在死结，直接放弃方案返回最大时间
				taffcount++;
				if (taffcount > carnums) {
					return INT_MAX;
				}
			}
		}

	}

	//如果出现堵车，返回最大时间
	return totaltime;
}


// return true if all cars are finished
bool Graph::areAllCarsFinished() {
	for (int i = 0; i < car_list.size(); i++) {
		if (!car_map[car_list[i]].is_arrived)
			return false;
	}
	return true;
}

// drive cars that are not started
void Graph::driveCarsInGarage(int curtime) {
	for (int i = 0; i < car_list.size(); i++) {
		if (car_map[car_list[i]].start_time < curtime) {
			car_map[car_list[i]].label = 2;
		}
		else if (car_map[car_list[i]].start_time == curtime) {
			Car& car = car_map[car_list[i]];
			Road& road = road_map[road_direction[pair<int, int>(car.route[0], car.route[1])]];
			road.putNewCar(car);
		}
	}
}

// return true if all cars are marked
bool Graph::areAllCarsMarked() {
	for (int i = 0; i < car_list.size(); i++) {
		if (car_map[car_list[i]].label == 0)
			return false;
	}
	return true;
}

// get cars numbers of a cross
int Graph::getCarsNumsOfRoads(vector<Road> roads) {
	for (int i = 0; i < roads.size(); i++) {

	}
	return 0;
}

// return true if all cars are finished
bool Graph::areAllCarsMoved(vector<Road> roads) {
	for (int i = 0; i < car_list.size(); i++) {
		if (!car_map[car_list[i]].is_moved)
			return false;
	}
	return true;
}

// simulate by three steps
void Graph::updateStepOne(Road& road) {

}

void Graph::updateStepTwo(vector<Road> roads, int idx, int* handleflag, int handlecount, int roadnums) {

}

void Graph::updateStepThree(Road& road) {

}

//***************** Scheme ******************//
