#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Txtparser.h"
#include "Model.h"


using namespace std;

int main()
{

	vector<Car> car = readCar("C:/Users/ai/Desktop/car.txt");
	vector<Cross> cross = readCross("C:/Users/ai/Desktop/cross.txt");
	vector<Road> road = readRoad("C:/Users/ai/Desktop/road.txt");

	for (int i = 0; i < car.size(); ++i)
	{
		cout << car[i].id << " " << car[i].from << " " << car[i].to << " " << car[i].cur_speed << " " << car[i].max_speed << " " << car[i].start_time << endl;
	}


	return 0;
}
