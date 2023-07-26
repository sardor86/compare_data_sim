#include "SIM.h"

SIM_DATA::SIM_DATA(string line)
{
	full_line = line;
	if (line != "")
	{
		data = String(line).divide(char(44))[1];
	}
	else data = "";
}
