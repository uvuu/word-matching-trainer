#include "task_handler.h"

#include <random>

#include <QRegularExpression>

namespace
{
std::random_device dev;
std::mt19937 mt(dev());
}

TasksHandler::TasksHandler(QStringList tasks)
    : m_tasks(tasks)
    , m_distribution(0, m_tasks.size() - 1)
{
}

void TasksHandler::prepareNextTask()
{
    const auto& task = m_tasks[getNextIndex()];


    auto question = task;
    auto answer = task;

//    m_question = task;
//    m_answer = task;

//    //m_question.replace(QRegularExpression("\\[.*?\\]"), "__");
//    //m_question.

//    m_question.replace("[", "<font color=\"transparent\">");
//    m_question.replace("]", "</font>");

//    m_answer.replace("[", "<font color=\"#fce96d\">");
//    m_answer.replace("]", "</font>");

    //QRegularExpression rx("\\[|\\]");
    QStringList query = task.split(' ');

    //m_question = question.replace("[", "<font color=\"transparent\">").replace("]", "</font>").split(' ');
    //m_answer = answer.replace("[", "<font color=\"#fce96d\">").replace("]", "</font>").split(' ');

    //m_question = question.replace("[", "<u><font color=\"transparent\">").replace("]", "</font></u>").split(' ');
    //m_answer = answer.replace("[", "<font color=\"#fce96d\">").replace("]", "</font>").split(' ');

    m_question = question.split(' ');
    //m_question[1] = m_question[1].replace("[", "<u><font color=\"transparent\">").replace("]", "</font></u>");
    m_answer = answer.split(' ');

//    for (auto& w : m_question)
//    {
//        w.replace("[", "<font color=\"transparent\">").replace("]", "</font>");
//    }

//    for (auto& w : m_answer)
//    {
//        w.replace("[", "<font color=\"#fce96d\">").replace("]", "</font>");
//    }
}

QStringList TasksHandler::getQuestion()
{
    return m_question;
}

QStringList TasksHandler::getAnswer()
{
    return m_answer;
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
