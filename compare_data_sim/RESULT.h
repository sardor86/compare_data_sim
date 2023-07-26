#include "SIM.h"
#include "DATA.h"

#pragma once

class RESULT
{
public:
	SIM_DATA sim;
	DATA data;

	RESULT(SIM_DATA sim_data, DATA data_data);
};

