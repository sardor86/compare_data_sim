#include "parser.h"

parser::parser(Files file_data)
{
	file = file_data;
}

void parser::check_data(wstring file_path)
{
	list<DATA> data_list = file.get_data(file_path);

	for (DATA data : data_list)
	{
		for (SIM_DATA sim : file.sim_data)
		{
			if (data.data == sim.data)
			{
				result.push_back(RESULT(sim, data));
				log.find(data.file_name, sim.full_line);
			}
			data_size++;
		}
	}
	log.data_in_thread = data_list.size();
	log.console(data_list.back());
}

void parser::thread_check_data()
{
	int thread_numbers = thread::hardware_concurrency();
	int number_files_in_thread = file.data_files.size() / thread_numbers;

	auto iter = file.data_files.begin();

	log.sim_size = file.sim_data.size();

	//#pragma omp parallel for num_threads(16) 
	for (int i = 0; i < thread_numbers; i++)
	{
		for (int k = 0; k < number_files_in_thread; k++)
		{
			check_data(*iter);
			iter++;
		}
	}

	while (iter != file.data_files.end())
	{
		check_data(*iter);
		iter++;
		data_size++;
	}

	log.end(file.sim_path, data_size);
}


