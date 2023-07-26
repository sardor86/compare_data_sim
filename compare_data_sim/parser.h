#include <fstream>
#include <thread>
#include <string>

#include "Files.h"
#include "RESULT.h"
#include "logging.h"

#pragma once


class parser
{
public:
	Files file;
	list<RESULT> result;

	logging log;
	int data_size = 1;

	parser(Files file_data);

	void check_data(wstring file_path);
	void thread_check_data();
};

