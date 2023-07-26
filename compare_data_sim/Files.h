#pragma once

#include <iostream>
#include <list>
#include <ctime>

#include "SIM.h"
#include "DATA.h"
#include "RESULT.h"
#include "logging.h"

using namespace std;

class Files
{
public:
	list <wstring> data_files;
	list <wstring> sim_files;

	list <SIM_DATA> sim_data;

	string sim_path;
	string data_path;

	list <wstring> get_file_path(string derictory, bool only_files, list <wstring> file_path_list);

	void get_sim_path(string derictory_path);
	void get_data_path(string derictory_path);

	void get_sim_data();
	list<DATA> get_data(wstring file_path);

	void save(list<RESULT> result, logging log);
};

