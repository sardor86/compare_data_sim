#pragma once
#include <iostream>
#include <list>
#include <array>

class String
{
public:
	std::string string;

	String(std::string text);

	std::string get_piece(int start, int end);

	std::array<std::string, 2> divide(char data);
	std::list <std::string> split(std::string data);
};

