#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "Txtparser.h"
#include "Model.h"



using namespace std;

//string dir = "config_1";
//string carPath = "../config/"+dir+"/car.txt";
//string roadPath = "../config/" + dir + "/road.txt";
//string crossPath = "../config/" + dir + "/cross.txt";
//string answerPath = "../config/" + dir + "/answer.txt";


int main(int argc,char *argv[])
{
	std::cout << "Begin" << std::endl;

	if (argc < 5) {
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}

	std::string carPath(argv[1]);
	std::string roadPath(argv[2]);
	std::string crossPath(argv[3]);
	std::string answerPath(argv[4]);

	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;

	Graph graph;
	Txtparser txtparser;

	// read car cross and road
	//txtparser.readData(dir, graph);
	txtparser.readData(carPath, crossPath, roadPath, graph);

	// init graph
	graph.initGraph();

	// init shortest of every cars
	graph.initPath();

	// modify every initial routes
	//graph.modifyInitialPath();

	// process simulation & record and Modification
	vector<Scheme> result;
	result.push_back(Scheme(graph));

	//txtparser.outAnswer(dir, result[0]);
	txtparser.outAnswer(answerPath, result[0]);

	//cout << "out answer succeed !" << endl;
	return 0;
}
