#ifndef TasksHandler_H
#define TasksHandler_H

#include <random>

#include <QStringList>

class TasksHandler
{
public:
    TasksHandler(QStringList tasks);

    void prepareNextTask();

    //QString getOriginal();
    QStringList getQuestion();
    QStringList getAnswer();

private:
    int getNextIndex();

private:
    QStringList m_tasks;
    int m_previousTaskIndex = 0;
    std::uniform_int_distribution<std::mt19937::result_type> m_distribution;
    QStringList m_question;
    QStringList m_answer;
};

#endif // TasksHandler_H
