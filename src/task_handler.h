#ifndef TasksHandler_H
#define TasksHandler_H

#include <random>

#include <QStringList>

class TasksHandler
{
public:
    TasksHandler(const QStringList& tasks);

    QStringList getNextTask();

private:
    int getNextIndex();

private:
    const QStringList& m_tasks;
    std::mt19937::result_type m_previousTaskIndex = 0;
    std::uniform_int_distribution<std::mt19937::result_type> m_distribution;
};

#endif // TasksHandler_H
