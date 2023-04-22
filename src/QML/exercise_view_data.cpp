#include <QFont>
#include <QFontMetricsF>
#include <QtGlobal>
#include <QRegularExpression>

#include "exercise_view_data.h"

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
QString ExerciseViewData::getName() const
{
    return m_exercise ? m_exercise->getName() : "";
}

double ExerciseViewData::getGapLength() const
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
        auto itMatch = re.globalMatch(task);
        while (itMatch.hasNext())
        {
            const auto match = itMatch.next();
            if (match.hasMatch())
            {
                m_gapLength = qMax(m_gapLength, fm.width(match.captured()));
            }
        }
    }
}
