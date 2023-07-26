#include <ctime>
#include <iostream>

#include "DATA.h"
#include "SIM.h"

#pragma once
#pragma warning(disable : 4996)

using namespace std;

class logging
{
public:
	time_t start_time;
	time_t old_time;

	int number_of_logging = 1;
	int sim_size;
	int data_in_thread;

	double speed;

	logging(int sim_size = 0, int number_data_in_thread = 0);

	void console(DATA& data);
	void find(string file_name, string line);
	void end(string sim_path, int addresses_size);
};

