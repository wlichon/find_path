#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <iostream>
#include <queue>
#include <utility>
#include <set>
#include <algorithm>

#define PENALTY 0

struct Station {
	std::string name;
	bool operator<(const Station& rhs) const  {
		return name < rhs.name;
	}
	bool operator==(const Station& rhs) const {
		return name == rhs.name;
	}
};


struct ConnInfo{
	int distance;
	std::string linie;
};

class Connection {
public:
	Connection(Station station, ConnInfo info) {
		this->station = station;
		this->info = info;
		this->pre = { "tbd" };
	}
	bool operator>(const Connection rhs) const {
		return info.distance > rhs.info.distance;
	}
	bool operator<(const Connection rhs) const {
		return station.name < rhs.station.name;
	}
	Station station;
	ConnInfo info;
	Station pre;
};


static void readFile(const char* fileName, std::vector<std::vector<Station>>& stations, std::vector<ConnInfo>& distance, int& size) {
	using namespace std;
	ifstream fin;
	fin.open(fileName);
	string line, word;
	istringstream iss;

	if (!fin.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}

	std::regex linie("(\\w|\\d)+:");
	string linienName;

	getline(fin, line);
	bool nextIsWord = false;
	do {
		iss.clear();
		iss.str(line);
		while (iss.good()) {
			iss >> word;
			if (regex_match(word, linie)) {
				linienName = word;
				nextIsWord = true;
				std::vector<Station> newLine;
				stations.push_back(newLine);
				continue;
			}
			if (nextIsWord) {
				while (word.back() != '\"') {
					string temp = word;
					iss >> word;
					if (word == temp) {
						getline(fin, line);
						iss.clear();
						iss.str(line);
						iss >> word;
					}
					temp += " " + word;
					word = temp;
				}
				word = word.substr(1, word.size() - 2);
				Station temp = {word};
				stations.back().push_back(temp);
				size++;
				nextIsWord = false;
			}
			else {
				std::cout << word << std::endl;
				int dist = stoi(word);
				distance.push_back({ dist,linienName });
				nextIsWord = true;
			}

		}
	} while (getline(fin, line));


	fin.close();
}

/*
*/


class Graph {
public:
	Graph(std::vector<std::vector<Station>>& stations, std::vector<ConnInfo>& distances,int size) {
		int index = 0;
		l = new std::list<Connection>[size];
		for (auto& line : stations) {
			for (auto& j : line) {
				if (m.count(j) > 0) {
					continue;
				}
				m[j] = index;
				index++;
			}
		}



		int distIndex = 0;
		for (auto& line : stations) {
			for (int i = 0; i < line.size() - 1; i++) {
				Station s1 = line[i];
				Station s2 = line[i + 1];
				ConnInfo info = distances[distIndex];
				int index = m[s1];
				l[index].push_back(Connection(s2,info));
				index = m[s2];
				l[index].push_back(Connection(s1,info));
				distIndex++;
			}

		}

		
		this->size = m.size();
		this->vis = new bool[this->size];
	}

	~Graph() {
		delete[] vis;
	}

	void initVis() {
		for (int i = 0; i < this->size; i++) {
			vis[i] = false;
		}
	}

	void dijkstra(Station start, Station destination, std::vector<Connection>& path) {
		std::priority_queue<Connection, std::vector<Connection>, std::greater<Connection>> minQ;
		Connection _start = { start,{0,"Start"} };
		minQ.push(_start);
		initVis();
		std::set<Connection> pre;
		int destID = m[destination];
		int startID = m[start];
		while (!minQ.empty()) {
			Connection current = minQ.top();
			minQ.pop();
			int ID = m[current.station];
			if (ID == destID) {
				std::cout << "Gewichtung kuerzester Pfad: " << current.info.distance << std::endl;
				path.push_back(current);
				std::set<Connection>::iterator it;
				while (m[path.back().station] != startID) {
					Connection temp = { {current.pre}, {-1,"egal"} };
					it = pre.find(temp);
					current = *it;
					path.push_back(current);

				}
				std::reverse(path.begin(), path.end());
				return;
			}

			if (vis[ID] != false) {
				continue;
			}
			vis[ID] = true;
			pre.insert(current);
			std::list<Connection> neighbours = l[ID];

			for(auto neighbour : neighbours){
				int ID = m[neighbour.station];
				if (vis[ID] != false)
					continue;
				if (current.info.linie != neighbour.info.linie && current.info.linie != "Start") {
					neighbour.info.distance += PENALTY; //Hoehere gewichtung fuers umsteigen
				}
				neighbour.info.distance += current.info.distance;
				neighbour.pre = current.station;
				minQ.push(neighbour);
			}
		}
	}

	void printPath(std::vector<Connection> path) {
		printf("\n");
		std::string lastLine = "Start";
		for (auto i : path) {
			if (i.info.linie != lastLine && lastLine != "Start") {
				std::cout << "\nUmsteigen\n\n";
			}
			std::cout << i.info.linie << " " << i.station.name << std::endl;
			lastLine = i.info.linie;
		}
	}

	/*

	void predecSetTest() {
		std::set<Connection> pre;


		Connection a = { {"Johnstrasse"}, {1,"U3:"} };
		Connection b = { {"Goldstr"},{2,"U3:"} };
		Connection c = { {"Asdstr"},{3,"U3:"} };
		Connection d = { {"Gasstr"},{2,"U4:"} };
		Connection e = { {"Pasdtstr"},{1,"U7:"} };


		pre.insert(a);
		pre.insert(b);
		pre.insert(c);
		pre.insert(d);
		pre.insert(e);

		/*
		for (auto i : pre) {
			std::cout << i.info.linie << " " << i.station.name << " " << i.pre.name << " ";
		}
		
		Station test = { "Goldstr" };
		std::set<Connection>::iterator it;
		it = pre.find({ test,{-1,"idk"} });
		std::cout << it->pre.name;



	}


	void heapTest() {
		
		std::priority_queue<Connection,std::vector<Connection>,std::greater<Connection>> pq;
		
		Connection a = { {"Johnstrasse"},{1,"U3:"} };
		Connection b = { {"Goldstr"},{2,"U3:"} };
		Connection c = { {"Asdstr"},{3,"U3:"} };
		Connection d = { {"Gasstr"},{2,"U4:"} };
		Connection e = { {"Pasdtstr"},{1,"U7:"} };

		
		pq.push(b);
		pq.push(a);
		pq.push(c);
		pq.push(d);
		pq.push(e);
		while(!pq.empty()) {
			std::cout << pq.top().info.distance << pq.top().station.name << " ";
			pq.pop();
		}
	

	}
	*/

private:
	std::list<Connection>* l;  //Adjazenz Liste
	std::map<Station, int> m;  //mapping von Station (Name) zu einer ID
	int size; //Anzahl von unique Stationen
	bool* vis; //Visited array mit einer groesse gleich der size variable
};