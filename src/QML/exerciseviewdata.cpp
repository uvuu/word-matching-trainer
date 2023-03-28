#include <QFont>
#include <QFontMetricsF>
#include <QtGlobal>
#include <QRegularExpression>

#include "exerciseviewdata.h"

ExerciseViewData::ExerciseViewData(QObject *parent)
    : QObject{parent}
{
    connect(this, &ExerciseViewData::exerciseChanged, &ExerciseViewData::updateGapLength);
}

void ExerciseViewData::setExercise(const Exercise* exercise)
{
    if (m_exercise != exercise)
    {
        m_exercise = exercise;
        exerciseChanged();
    }
}
QString ExerciseViewData::getName()
{
    return m_exercise ? m_exercise->getName() : "";
}

double ExerciseViewData::getGapLength()
{
    return m_gapLength;
}

void ExerciseViewData::updateGapLength()
{
    QFontMetricsF fm{{}};
    QRegularExpression re{"(\\[(?:\\[??[^\\[]*?\\]))"};

    m_gapLength = 0;

    const auto& tasks = m_exercise->getTasks();
    for (const auto& task : tasks)
    {
        for (const auto& match : re.globalMatch(task))
        {
            if (match.hasMatch())
            {
                const auto w = fm.boundingRect(match.captured()).width();
                m_gapLength = qMax(m_gapLength, w);
            }
        }
    }
}
