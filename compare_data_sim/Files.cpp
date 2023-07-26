#include <fstream>
#include <windows.h>
#include <vector> 
#include <omp.h>

#include "Files.h"

list<wstring> Files::get_file_path(string derictory, bool only_files = false, list <wstring> file_path_list = {})
{
	wstring wtpath(derictory.begin(), derictory.end());

	wtpath += L"*";

	const wchar_t* path = wtpath.c_str();

	WIN32_FIND_DATAW wfd;

	HANDLE const hFind = FindFirstFileW(path, &wfd);
	setlocale(LC_ALL, "");

	wtpath.pop_back();

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			wstring file_name = &wfd.cFileName[0];
			if (file_name.find(L"..") == string::npos && file_name.length() > 1)
			{
				if (file_name.find(L".") == string::npos && only_files) file_path_list.push_back(wtpath + file_name);
				else file_path_list.push_back(path + file_name);
			}
		} while (NULL != FindNextFileW(hFind, &wfd));

		FindClose(hFind);
	}

	return file_path_list;
}

void Files::get_sim_path(string derictory_path)
{
	ifstream file(derictory_path);
	string file_data;

	if (!file.is_open())
	{
		cout << "file " << derictory_path << " not found!" << endl;
	}

	while (!file.eof())
	{
		file >> file_data;
		sim_path = file_data;

		sim_files = get_file_path(file_data + "\\", true, sim_files);
	}
	file.close();
}

void Files::get_data_path(string derictory_path)
{
	data_path = derictory_path;
	list<wstring> path_list = get_file_path(derictory_path);
	for (wstring wpath : path_list)
	{
		string path(wpath.begin(), wpath.end());

		if (String(path).split("\\").back().find("DATA") != std::string::npos)
		{
			data_files = get_file_path(path + "\\", true, data_files);
		}
	}
}

void Files::get_sim_data()
{
	string line("");

	for (wstring file_path : sim_files)
	{
		ifstream file(file_path);

		while (!file.eof())
		{
			file >> line;
			sim_data.push_back(SIM_DATA(line));
		}

		file.close();
	}
}

list<DATA> Files::get_data(wstring file_path)
{
	list<DATA> result;
	string file_data;

	string file_name = String(string(file_path.begin(), file_path.end())).split("\\").back();
	ifstream file(file_path);

	while (!file.eof())
	{
		file >> file_data;
		result.push_back(DATA(file_name, file_data));
	}

	file.close();

	return result;
}

string last_line(const string& filename)
{
	ifstream inp(filename.c_str());
	if (!inp.is_open())
		return string("0, ");
	string str = "";
	string buf;
	while (getline(inp, buf, '\n'))
		str = buf;

	inp.close();

	return str;
}

void Files::save(list<RESULT> result, logging log)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	char date_time[128];
	strftime(date_time, sizeof(date_time), "%m.%d.%Y, %X", ltm);

	ofstream result_compare("Results_compare.txt");
	for (RESULT res : result)
	{
		result_compare << string(string(date_time) + ", " + res.data.file_name + ", " + res.sim.full_line + "\n");
	}
	result_compare.close();

	string old_line = last_line("check_log.csv");

	std::ofstream check_log;
	check_log.open("check_log.csv", std::ios::app);

	tm* lstart_time = localtime(&log.start_time);

	char start_time[128];
	strftime(start_time, sizeof(start_time), "%m.%d.%Y, %X", lstart_time);

	string check_log_string = "";

	if (old_line != "")
	{
		check_log_string += to_string(stoi(String(old_line).divide(char(44))[0]) + 1) + ", ";
	}
	else check_log_string += "1, ";

	check_log_string += String(sim_path).split("\\").back() + ", ";
	check_log_string += String(data_path).split("\\").back() + ", ";
	check_log_string += to_string(data_files.size()) + ", ";
	check_log_string += to_string(sim_files.size()) + ", ";
	check_log_string += to_string(sim_data.size()) + ", ";
	check_log_string += to_string(int(log.speed)) + ", ";
	check_log_string += string(date_time) + ", ";
	check_log_string += to_string(result.size()) + "\n";


	check_log << check_log_string;

	check_log.close();
}
