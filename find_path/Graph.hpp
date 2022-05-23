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
#include <set>
#include <type_traits>

struct Station {
	std::string name;
	bool operator<(const Station& s) const {
		return name < s.name;
	}
	bool operator==(const Station& s) const {
		return name == s.name;
	}
};


struct ConnInfo{
	int distance;
	std::string linie;
};

struct Connection {
	Station station;
	ConnInfo info;
	//friend std::ostream& operator<<(std::ostream& os, const Connection& s1);
};

struct Node {
	Station station;
	int minDistance;
	bool operator<(const Node& s) const {
		return station.name < s.station.name;
	}
	Station pre;
	std::string linie;
	bool operator<(const std::string& s) const {
		return station.name < s;
	}
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
				//std::cout << linienName;
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
					temp += word;
					word = temp;
				}
				word = word.substr(1, word.size() - 2);
				Station temp = {word};
				stations.back().push_back(temp);
				size++;
				nextIsWord = false;
			}
			else {
				distance.push_back({ stoi(word),linienName });
				nextIsWord = true;
			}

		}
	} while (getline(fin, line));

	/*
	for (auto i : stations) {
		for (auto j : i) {
			std::cout << j.name << " ";
		}
	}
	*/

	fin.close();
}

bool Greater(const Node& lhs, const Node& rhs)
{
	return std::tie(lhs.station.name, lhs.minDistance) < std::tie(rhs.station.name, rhs.minDistance);
}

/*
*/

class Graph {
public:
	Graph(std::vector<std::vector<Station>>& stations, std::vector<ConnInfo>& distances,int size) {
		this->size = size;
		int index = 0;
		l = new std::list<Connection>[this->size];
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
				l[index].push_back({ s2,info });
				index = m[s2];
				l[index].push_back({ s1,info });
				distIndex++;
			}

		}
		std::list<Connection> asd = l[m[{"Johnstrasse"}]];
		for (auto i : asd) {
			std::cout << i.station.name << " Linie: " << i.info.linie << std::endl;
		}
		


	}

	void createNode(Node& n,Station station,int dist,Station pre,std::string linie) {
		n.minDistance = dist;
		n.station = station;
		n.pre = pre;
		n.linie = linie;
	}

	void dijkstra(Station start, Station destination, std::vector<std::string>& path) {
		std::vector<Node> paths;
		std::set<Node> visited;

		Node current = { start,0 };
		paths.push_back(current);
		std::vector<Node>::iterator it;
		std::list<Connection> neighbours;
		while (!paths.empty()) {
			it = paths.begin();
			current = *it;
			paths.erase(paths.begin());
			visited.insert(current);
			if (current.station.name == destination.name) {
				std::cout << "Distance of path: " << current.minDistance << std::endl;
				std::set<Node>::iterator it = visited.find(current);
				path.push_back(current.station.name);
				
				while (it->station.name != start.name) {
					path.insert(path.begin(), it->linie + " " + it->pre.name);
					Node lookFor = { it->pre.name,0 };
					it = visited.find(lookFor);
				}
				/*
				for (auto i : visited) {
					std::cout << "Station: " << i.station.name << " Pre: " << i.pre.name << std::endl;
				}
				*/
				return;
			}
			int index = m[current.station];
			neighbours = l[index];
			std::cout << current.station.name << " " << current.minDistance << std::endl;
			Node insert;
			for (auto i : neighbours) {
				createNode(insert, i.station, i.info.distance+current.minDistance,current.station,i.info.linie);
				if ((std::find_if(std::begin(visited), std::end(visited),
					[&](Node const& p) { return p.station.name == insert.station.name; }) == visited.end())) {
					paths.insert(std::lower_bound(paths.begin(), paths.end(), insert,Greater), insert);

				} //check if path to be inserted hasnt already been visited
			}
		}


	}

	void printMapping() {
		for (auto& i : m) {
			std::cout << i.first.name << " " << i.second << " Verbindungen: ";
			for (auto i : l[i.second]) {
				std::cout << i.station.name << " " << i.info.distance << " Linie: " << i.info.linie << "---";
			}
			printf("\n");
		}
		std::cout << this->size << std::endl;
	}


private:
	std::list<Connection>* l;
	std::map<Station, int> m;
	int size;
};
