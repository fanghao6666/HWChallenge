// This program is to parse txt file (Car,Cross,Road)
// @Date : 2019/3/9
// @Author: 第一名是我小号

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


/** \brief Read Car data
*
* @param path is the path of txt file
* @data : id ,from, to,speed,planTime
*
*/
void readCar(string path)
{
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
	
		cout << "id : " << id << " from : " << from << " to : " << to << " speed : " << speed << " planTime : " << planTime << endl;
	}
}

/** \brief Read Cross data
*
* @param path is the path of txt file
* @data : id, roadId, roadId, roadId, roadId
*
*/
void readCross(string path)
{
	fstream file;
	file.open(path);
	int id, roadId1, roadId2, roadId3, roadId4;
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
		roadId1 = stoi(str2.substr(0, str2.length() - 1));
		roadId2 = stoi(str3.substr(0, str3.length() - 1));
		roadId3 = stoi(str4.substr(0, str4.length() - 1));
		roadId4 = stoi(str5.substr(0, str5.length() - 1));

		cout << "id : " << id << " roadId1 : " << roadId1 << " roadId2 : " << roadId2 << " roadId3 : " << roadId3 << " roadId4 : " << roadId4 << endl;
	}
}

/** \brief Read Road data
*
* @param path is the path of txt file
* @data : id, length, speed, channel, from, to, isDuplex
*/
void readRoad(string path)
{
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
		string str1, str2, str3, str4, str5,str6,str7;
		file >> str1 >> str2 >> str3 >> str4 >> str5 >> str6 >> str7;

		id = stoi(str1.substr(1, str1.length() - 2));
		length = stoi(str2.substr(0, str2.length() - 1));
		speed = stoi(str3.substr(0, str3.length() - 1));
		channel = stoi(str4.substr(0, str4.length() - 1));
		from = stoi(str5.substr(0, str5.length() - 1));
		to = stoi(str6.substr(0, str6.length() - 1));
		isDuplex = stoi(str7.substr(0, str7.length() - 1));

		cout << "id : " << id << " length : " << length << " speed : " << speed << " channel : " << channel << " from : " << from << " to : " << to << " isDuplex : " << isDuplex << endl;
	}
}
