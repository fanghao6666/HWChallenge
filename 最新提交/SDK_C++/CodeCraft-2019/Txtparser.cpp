#include<iostream>

#include "Txtparser.h"

using namespace std;


// read data
//void Txtparser::readData(string dir, Graph& graph)
//{
//	readCar(dir, graph);
//	readCross(dir, graph);
//	readRoad(dir, graph);
//}

void Txtparser::readData(string carpath, string crosspath, string roadpath, Graph& graph)
{
	readCar(carpath, graph);
	readCross(crosspath, graph);
	readRoad(roadpath, graph);
}


/** \brief Read Car data
*
* @param path is the path of txt file
* @data : id ,from, to,speed,planTime
*
*/
void Txtparser::readCar(string dir, Graph& graph)
{
	//string path = "../config/" + dir + "/car.txt";

	string path = dir;

	fstream file;
	file.open(path);
	int id, from, to, speed, planTime;
	bool is_first_str = false;
	while (!file.eof())
	{
		// judge whether the first string
		if (is_first_str == false)
		{
			string str;
			file >> str;
			if (str[0] == '#')
			{
				is_first_str = true;
				continue;
			}
		}
		// read rest string
		string str1, str2, str3, str4, str5;
		file >> str1 >> str2 >> str3 >> str4 >> str5;

		id = stoi(str1.substr(1, str1.length() - 2));
		from = stoi(str2.substr(0, str2.length() - 1));
		to = stoi(str3.substr(0, str3.length() - 1));
		speed = stoi(str4.substr(0, str4.length() - 1));
		planTime = stoi(str5.substr(0, str5.length() - 1));

		Car newcar = Car(id, from, to, speed, planTime);
		graph.car_map[id] = newcar;
		graph.car_list.push_back(id);
	}
	file.close();
}

/** \brief Read Cross data
*
* @param path is the path of txt file
* @data : id, roadId, roadId, roadId, roadId
*
*/
void Txtparser::readCross(string dir, Graph& graph)
{
	//string path = "../config/" + dir + "/cross.txt";

	string path = dir;

	fstream file;
	file.open(path);
	int id;
	bool is_first_str = false;
	while (!file.eof())
	{
		// judge whether the first string
		if (is_first_str == false)
		{
			string str;
			file >> str;
			if (str[0] == '#')
			{
				is_first_str = true;
				continue;
			}
		}
		// read rest string
		string str[5];
		file >> str[0] >> str[1] >> str[2] >> str[3] >> str[4];
		id = stoi(str[0].substr(1, str[0].length() - 2));

		Cross new_cross(id);
		for (int i = 0; i < 4; ++i)
		{
			new_cross.next_road.push_back(stoi(str[i + 1].substr(0, str[i + 1].length() - 1)));
		}

		graph.cross_map[id] = new_cross;
		graph.cross_list.push_back(id);
	}
	file.close();
}

/** \brief Read Road data
*
* @param path is the path of txt file
* @data : id, length, speed, channel, from, to, isDuplex
*/
void Txtparser::readRoad(string dir, Graph& graph)
{
	//string path = "../config/" + dir + "/road.txt";

	string path = dir;

	fstream file;
	file.open(path);
	int id, length, speed, channel, from, to, isDuplex;
	bool is_first_str = false;
	while (!file.eof())
	{
		// judge whether the first string
		if (is_first_str == false)
		{
			string str;
			file >> str;
			if (str[0] == '#')
			{
				is_first_str = true;
				continue;
			}
		}
		// read rest string
		string str1, str2, str3, str4, str5, str6, str7;
		file >> str1 >> str2 >> str3 >> str4 >> str5 >> str6 >> str7;

		id = stoi(str1.substr(1, str1.length() - 2));
		length = stoi(str2.substr(0, str2.length() - 1));
		speed = stoi(str3.substr(0, str3.length() - 1));
		channel = stoi(str4.substr(0, str4.length() - 1));
		from = stoi(str5.substr(0, str5.length() - 1));
		to = stoi(str6.substr(0, str6.length() - 1));

		//if the road is duplex, looks as tow road
		isDuplex = stoi(str7.substr(0, str7.length() - 1));
		if (isDuplex) {
			int reid = -id;
			Road reroad = Road(reid, length, speed, channel, to, from);
			graph.road_map[reid] = reroad;
			graph.road_list.push_back(reid);
			graph.road_direction[pair<int, int>(to, from)] = reid;
		}

		Road newroad = Road(id, length, speed, channel, from, to);
		graph.road_map[id] = newroad;
		graph.road_list.push_back(id);
		graph.road_direction[pair<int, int>(from, to)] = id;
	}
	file.close();
}

// output answer
void Txtparser::outAnswer(string dir, Scheme& scheme)
{
	//string path = "../config/" + dir + "/answer.txt";

	string path = dir;

	ofstream fout;
	fout.open(path);
	if (!fout) {
		cout << "can't open file" << endl;
	}
	fout << "#(carId,StartTime,RoadId...)" << endl;

	for (int i = 0; i < scheme.answers.size(); i++) {
		fout << "(" << abs(scheme.answers[i][0]);
		for (int j = 1; j < scheme.answers[i].size(); j++) {
			fout << "," << abs(scheme.answers[i][j]);
		}
		fout << ")" << endl;
	}
	fout.close();
}
