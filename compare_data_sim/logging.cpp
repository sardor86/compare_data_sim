#include "logging.h"

logging::logging(int isim_size, int number_data_in_thread)
{
	start_time = time(0);
	old_time = start_time;

	sim_size = isim_size;
	data_in_thread = number_data_in_thread;
}

void logging::console(DATA& data)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	time_t time_of_work = now - start_time;
	tm* tow = localtime(&time_of_work);

	tm* old_t = localtime(&old_time);
	if (now - old_time != 0) speed = data_in_thread / (now - old_time);

	cout << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << ", ";
	cout << data.file_name << ", ";
	cout << sim_size << ", ";
	cout << tow->tm_hour << ":" << tow->tm_min << ":" << tow->tm_sec << ", ";
	cout << data_in_thread << " addresses, ";
	cout << data_in_thread * number_of_logging << " compared addresses, ";
	cout << speed << " addresses per second\n";

	old_time = now;

	number_of_logging++;
}

void logging::find(string file_name, string line)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	char date_time[128];
	strftime(date_time, sizeof(date_time), "%m.%d.%Y, %X", ltm);

	cout << "Found! " << date_time << ", ";
	cout << file_name << ", ";
	cout << line << ", Saved to file!" << endl;
}

void logging::end(string sim_path, int addresses_size)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	char date_time[128];
	strftime(date_time, sizeof(date_time), "%m.%d.%Y, %X", ltm);

	time_t time_of_work = now - start_time;
	tm* tow = localtime(&time_of_work);

	char time_of_work_buffer[128];
	strftime(time_of_work_buffer, sizeof(date_time), "%X", tow);

	cout << "==========================================================================" << endl;
	cout << "Current date and time: " << date_time << endl;
	cout << "Comparison of addresses in the Central Folder " << String(sim_path).split("\\").back() << " is completed!.\n";
	cout << "Total test time: " << time_of_work_buffer << endl;
	cout << "Total number of scanned files: " << sim_size << "files.\n";
	cout << "Total number of addresses to compare: " << addresses_size << " addresses.\n";
	cout << "Average speed: " << speed << " addresses per second.\n";
}
