#include "Files.h"
#include "String.h"
#include "parser.h"

#include <windows.h>
#include <thread>

string get_path(string file_path)
{
    string result = "";
    bool find = false;

    for (int i = file_path.length() - 1; i >= 0; i--)
    {
        if (find) result = file_path[i] + result;
        if (file_path[i] == char(92)) find = true;
    }

    return result + "\\";
}

void sim_pars(Files& file, string path)
{
    file.get_sim_path(path);
    file.get_sim_data();
}

void data_pars(Files& file, string path)
{
    file.get_data_path(path);
}

int main(int argc, char* argv[])
{

    Files file;

    string path = get_path(argv[0]);

    thread sim(&sim_pars, std::ref(file), path + "data.txt");
    thread data(&data_pars, std::ref(file), path);

    sim.join();
    data.join();

    parser pars(file);
    pars.thread_check_data();

    file.save(pars.result, pars.log);

    system("pause");
    return 0;
}
