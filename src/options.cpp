#include "options.h"

Options::Options(QObject *parent)
    : QObject{parent}
{
}

int Options::getQuestionTime() const
{
    return m_questionTime;
}

void Options::setQuestionTime(int time)
{
    if (m_questionTime != time)
    {
        m_questionTime = time;
        questionTimeChanged();
    }
}

int Options::getAnswerTime() const
{
    return m_answerTime;
}

void Options::setAnswerTime(int time)
{
    if (m_answerTime != time)
    {
        m_answerTime = time;
        answerTimeChanged();
    }
}

int Options::getExerciseIndex() const
{
    return m_exerciseIndex;
}

void Options::setExerciseIndex(int exerciseIndex)
{
    if (m_exerciseIndex != exerciseIndex)
    {
        m_exerciseIndex = exerciseIndex;
        exerciseIndexChanged();
    }
}
