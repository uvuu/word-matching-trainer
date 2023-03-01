#include "performer.h"

#include <chrono>
#include <random>
#include <thread>

#include "data.h" // TODO: This way of getting data should be improved
#include "data_reader.h"
#include "task_handler.h"

Performer::Performer(QObject *parent) : QObject(parent)
{
    DataReader reader;
    m_exercises = reader.read(data);
}

Performer::~Performer()
{
    stop();
}

void Performer::run()
{
    m_flag = true;

    std::thread([this]()
    {
        const auto stepSize {100};
        const auto questionTime = m_options.getQuestionTime();
        const auto stepCount = questionTime / stepSize;

        TasksHandler tasksHandler(m_exercises[m_options.getExerciseIndex()].getTasks());

        // TODO: What is this?
        auto addSpaces = [](QStringList l)
        {
            for(int i = 1; i < l.size(); i +=2)
            {
                l.insert(i, " ");
            }

            return l;
        };

        // TODO: decide how to handle all this mess with m_flag
        while(m_flag)
        {
            tasksHandler.prepareNextTask();
            setTask(addSpaces(tasksHandler.getQuestion()));
            setRemainingTime(questionTime);

            for (auto i {0}; i < stepCount && m_flag; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(stepSize));
                setRemainingTime(questionTime - stepSize * (i + 1));
            }

            if (m_flag)
            {
                // Waiting for the result showing
                setTask(addSpaces(tasksHandler.getAnswer()));
                std::this_thread::sleep_for(std::chrono::milliseconds(m_options.getAnswerTime()));
            }
        }
    }).detach();
}

void Performer::stop()
{
    m_flag = false;
}

Options* Performer::getOptions()
{
    return &m_options;
}

QStringList Performer::getExercisesNames() const
{
    QStringList exercisesNames;
    for (const auto& exercise : m_exercises)
    {
        exercisesNames.append(exercise.getName());
    }

    return exercisesNames;
}

QString Performer::getExerciseName() const
{
    return m_exercises[m_options.getExerciseIndex()].getName();
}

int Performer::getRemainingTime() const
{
    return m_remainingTime;
}

void Performer::setRemainingTime(int remainingTime)
{
    if (m_remainingTime != remainingTime)
    {
        m_remainingTime = remainingTime;
        remainingTimeChanged();
    }
}

QStringList Performer::getTask() const
{
    return m_task;
}

void Performer::setTask(QStringList task)
{
    if (m_task != task)
    {
        m_task = task;
        taskChanged();
    }
}


/**
  I suppose that we can do this optional
 */
#include <QFont>
#include <QFontMetricsF>
#include <QtGlobal>
#include <QRegularExpression>

double Performer::getAnswerLength() const
{
    //QFont font("times", 24);
    QFont f;
    //f.setPixelSize(17);
    QFontMetricsF fm{{}};

    QRegularExpression re("(\\[(?:\\[??[^\\[]*?\\]))");

    double maxSize = 0;

    const auto& tasks = m_exercises[m_options.getExerciseIndex()].getTasks();
    for (const auto& task : tasks)
    {
        for (const QRegularExpressionMatch &match : re.globalMatch(task)) {
            if (match.hasMatch())
            {
                const auto w = fm.boundingRect(match.captured()).width();
                maxSize = qMax(maxSize, w);
            }
        }
    }


    //QQuickView view(QUrl::fromLocalFile("MyItem.qml"));

    return maxSize;
}
