#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "Graph.hpp"


int main(int argc, char** argv) {
	std::vector<std::vector<Station>> stations;
	std::vector<ConnInfo> distance;
	
	
	const char* asd = argv[1];
	Station s = { argv[2] };
	Station d = { argv[3] };
	
	Station start = { s};
	Station destination = { d};


	int size = 0;

	std::cout << "b4 readfile" << std::endl;
	readFile(asd,stations,distance,size);
	std::cout << "b4 graph constrc" << std::endl;
	Graph graph(stations, distance,size);
	std::vector<Connection> path;
	std::cout << "b4 dijsk" << std::endl;
	graph.dijkstra(start, destination,path);
	graph.printPath(path);

}