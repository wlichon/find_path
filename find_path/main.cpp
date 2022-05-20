#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include <map>
#include <vector>

std::map<char, std::vector<char>> m = {
	{'A', {'B','C'}},
	{'B', {'A','D'}},
	{'D', {'B','E'}}
};

std::string returnHello() {
	std::string hello = "Hello";
	return hello;
}

TEST_CASE("Test with 0")
{
	REQUIRE(returnHello() == "Hello");
}

void bfs

int main() {
	std::cout << m['A'].front();
}