//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
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
	const char* asd = "test_graph.txt";
	int size = 0;
	readFile(asd,stations,distance,size);
	Graph graph(stations, distance,size);
	graph.printMapping();
	/*
	Station s1 = { "Johnstrasse","U3:" };
	Connection c = { s1,2 };
	std::list<Connection>* l;
	l = new std::list<Connection>[10];
	l[2].push_back(c);
	//std::cout << l[1].back().station.name;

	std::map<Station, int> m;
	std::vector<Station> a = {
		{"Johnstrasse","U3:"},
		{"Blablagasse","52:"},
		{"Johnstrasse","U4:"}
	};
	m[a[0]] = 1;
	m[a[1]] = 2;
	m[a[2]] = 3;
	/*
	for (auto i : m) {
		std::cout << i.first.name << " " << i.first.linie << std::endl;
	}

	Station test = { "Blablagasse","52:" };
	int index = m[test];
	std::cout << l[index].front();
	*/
	
}