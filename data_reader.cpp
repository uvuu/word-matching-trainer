#include "data_reader.h"

#include <iostream>
#include <sstream>
#include <string>

Exercises DataReader::read(const char* data)
{
    Exercises exercises;

    std::istringstream iss{data};
    std::string line;
    while(std::getline(iss, line))
    {
        // Read the name of exercise
        if (line[0] == '(')
        {
            const auto name = line.substr(1, line.find_first_of(')') - 1);
            exercises.emplace_back(Exercise{});
            exercises.back().setName(QString::fromStdString(name));
        }
        else if (!exercises.empty()) // Read the tasks set
        {
            exercises.back().addTask(QString::fromStdString(line));
        }
    }

    return exercises;
}
