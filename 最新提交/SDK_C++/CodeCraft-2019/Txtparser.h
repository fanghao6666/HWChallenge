
// This program is to parse txt file (Car,Cross,Road)
// @Date : 2019/3/9
// @Author: ??????????????

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "Model.h"

using namespace std;

class Txtparser {

public:

	//void readData(string dir, Graph& graph);
	void readData(string carpath,string crosspath,string roadpath, Graph& graph);

	void outAnswer(string dir, Scheme& scheme);

private:
	void readCar(string dir, Graph& graph);
	void readCross(string dir, Graph& graph);
	void readRoad(string dir, Graph& graph);

};
