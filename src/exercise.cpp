#include "exercise.h"

QString Exercise::getName() const
{
    return m_name;
}

void Exercise::setName(QString name)
{
    m_name = name;
}

void Exercise::addTask(QString task)
{
    m_tasks.push_back(task);
}

const QStringList& Exercise::getTasks() const
{
    return m_tasks;
}
