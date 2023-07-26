#include "String.h"

String::String(std::string text)
{
	string = text;
}

std::string String::get_piece(int start, int end)
{
	std::string result = "";

	for (int i = start; i <= end; i++)
	{
		result += string[i];
	}

	return result;
}

std::array<std::string, 2> String::divide(char data)
{
	std::array<std::string, 2> result;

	bool find = 0;
	for (int i = 0; i <= string.length() - 1; i++)
	{
		if (find) result[1] += string[i];
		else
		{
			if (string[i] == data)
			{
				find = true;
				i++;
				result[1] += string[i];
			}
			else result[0] += string[i];
		}
	}
	return result;
}

std::list <std::string> String::split(std::string data)
{
	std::list <std::string> result = {};

	int old_index = 0;

	int data_length = data.length();

	for (int i = data_length; i <= string.length() - data_length; i++)
	{
		if (get_piece(i - data_length, i - 1) == data)
		{
			result.push_back(get_piece(old_index, i - data_length - 1));
			old_index = i;
		}
	}
	result.push_back(get_piece(old_index, string.length()));

	return result;
}
