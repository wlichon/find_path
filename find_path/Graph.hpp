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

struct Station {
	std::string name;
	bool operator<(const Station& s) const {
		return name < s.name;
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
				if (word.back() != '\"') {
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

/*
*/

class Graph {
public:

	void addNode() {

	}
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
