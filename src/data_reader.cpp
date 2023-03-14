#include "data_reader.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>

namespace
{
constexpr auto DATA_FILE_PATH = ":/data.txt";
constexpr auto EXERCISE_NAME_FIRST_SYMBOL = '(';
constexpr auto EXERCISE_NAME_LAST_SYMBOL = ')';
}

Exercises DataReader::read()
{
    Exercises exercises;

    QFile file{DATA_FILE_PATH};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return {};
    }

    QTextStream in{&file};
    while (!in.atEnd())
    {
        const auto line = in.readLine();
        if (line.isEmpty())
        {
            continue;
        }

        // Read the name of exercise
        if (line[0] == EXERCISE_NAME_FIRST_SYMBOL)
        {
            const auto name = line.mid(1, line.indexOf(EXERCISE_NAME_LAST_SYMBOL) - 1);
            exercises.emplace_back(Exercise{});
            exercises.back().setName(name);
        }
        else if (!exercises.empty()) // Read the tasks set
        {
            exercises.back().addTask(line);
        }
    }

    return exercises;
}
