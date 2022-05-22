
/*
void dfs(std::map<char, std::vector<char>>& graph, char current, char searchItem, std::vector<char>& path, std::set<char>& visited, bool& found) { // from A to E path
	bool result = false;
	if (current == searchItem) {
		path.push_back(current);
		return;
	}
	if (visited.find(current) != visited.end())
		return;
	visited.insert(current);
	std::vector<char> neighbours = graph[current];
	for (auto i : neighbours) {
		dfs(graph, i, searchItem, path, visited, found);
		if (!path.empty()) {
			path.insert(path.begin(), current);
			return;
		}
	}
	return;
}

struct ChildParent {
	char child;
	char parent;
};

void bfs(std::map<char, std::vector<char>>& graph, char current, char searchItem, std::vector<char>& path, std::set<char>& visited, bool& found) {
	std::vector<char> Q;
	char startNode = current;
	Q.insert(Q.begin(), current);

	std::vector<ChildParent> list;

	while (!Q.empty()) {
		current = Q.back();
		Q.pop_back();
		visited.insert(current);
		if (current == searchItem) {
			char currentChild = current;
			while (path.empty() || currentChild != startNode) {
				for (auto i : list) {
					if (i.child == currentChild) {
						path.insert(path.begin(), currentChild);
						currentChild = i.parent;
						break;
					}
				}
			}
			path.insert(path.begin(), startNode);
			found = true;
			return;
		}
		for (auto neighbour : graph[current])
			if (visited.find(neighbour) == visited.end()) {
				Q.insert(Q.begin(), neighbour);
				ChildParent a = { neighbour,current };
				list.push_back(a);
			}
	}
}



void clean(std::vector<char>& path, std::set<char>& visited, bool& found, std::map<char, std::vector<char>> graph) {
	path.clear();
	visited.clear();
	found = false;
	graph.clear();
}


/*

TEST_CASE("DFS Graph search")
{
	std::vector<char> path;
	std::set<char> visited;
	bool found = false;
	std::map<char, std::vector<char>> graph = {};

	SECTION("Node_not_in_graph 1") {
		graph = {
			{'A', { 'B','C' }}
		};
		dfs(graph, 'A', 'C', path, visited, found);
		std::vector<char> actualPath = {'A','C'};
		CHECK(path == actualPath);
		clean(path, visited, found, graph);
	}

	SECTION("Node_in_graph 2") {
		std::map<char, std::vector<char>> graph = {
			{'A', {'B','C'}},
			{'B', {'A','D'}},
			{'D', {'B','E'}},
			{'E', {'F','G'}},
			{'G', {'H','I','J'}}
		};
		dfs(graph, 'A', 'H', path, visited, found);
		std::vector<char> actualPath = { 'A','B','D','E','G','H'};
		CHECK(path == actualPath);
		clean(path, visited, found, graph);
	}

	SECTION("Node_in_graph 3") {
		std::map<char, std::vector<char>> graph = {
			{'A', {'B','C'}},
			{'B', {'A','D'}},
			{'D', {'B','E'}},
			{'E', {'F','G'}},
			{'G', {'H','I','J'}}
		};
		dfs(graph, 'D', 'A', path, visited, found);
		std::vector<char> actualPath = { 'D','B','A'};
		CHECK(path == actualPath);
		clean(path, visited, found, graph);
	}


}



TEST_CASE("BFS Graph search")
{
	std::vector<char> path;
	std::set<char> visited;
	bool found = false;
	std::map<char, std::vector<char>> graph = {};

	SECTION("Node_in_graph 1") {
		std::map<char, std::vector<char>> graph = {
			{'A', {'B','C'}},
			{'B', {'A','D'}},
			{'D', {'B','E'}},
			{'E', {'F','G','D'}},
			{'G', {'H','I','J','E'}},
			{'J', {'S','G'}},
			{'S', {'L','M','N','O','J'}},
			{'L', {'R','T','S','Y'}},
			{'T', {'L','U','V'}},
			{'V', {'T','X'}},
			{'F', {'Y','E'}},
			{'Y', {'L','F'}},

		};
		bfs(graph, 'Y', 'G', path, visited, found);
		for (auto i : path) {
			std::cout << i << " ";
		}
		std::vector<char> actualPath = { 'Y','F','E','G'};
		CHECK(actualPath == path);
		clean(path, visited, found, graph);
	}


}
*/
/*
*/
