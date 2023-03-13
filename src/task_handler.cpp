#include "task_handler.h"

#include <random>

namespace
{
std::random_device dev;
std::mt19937 mt(dev());
}

TasksHandler::TasksHandler(const QStringList& tasks)
    : m_tasks(tasks)
    , m_distribution(0, m_tasks.size() - 1)
{
}

QStringList TasksHandler::getNextTask()
{
    auto task = m_tasks[getNextIndex()].split(' ');

    // Put whitespaces between words as a separate item
    for(int i = 1; i < task.size(); i += 2)
    {
        task.insert(i, " ");
    }

    return task;
}

int TasksHandler::getNextIndex()
{
    auto index = m_distribution(mt);
    while(m_previousTaskIndex == index)
    {
        index = m_distribution(mt);
    }

    m_previousTaskIndex = index;

    return index;
}
