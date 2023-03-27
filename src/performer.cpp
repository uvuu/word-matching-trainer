#include "performer.h"

#include <chrono>
#include <random>
#include <thread>

#include "data_reader.h"
#include "task_handler.h"

Performer::Performer(QObject *parent)
    : QObject{parent}
    , m_exercises(DataReader{}.read())
{
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
        const auto stepSize = 100;
        const auto questionTime = m_options.getQuestionTime();
        const auto stepCount = questionTime / stepSize;

        TasksHandler tasksHandler{m_exercises[m_options.getExerciseIndex()].getTasks()};

        // TODO: decide how to handle all this mess with m_flag
        while(m_flag)
        {
            setTask(tasksHandler.getNextTask());
            setRemainingTime(questionTime);

            for (auto i = 0; (i < stepCount) && m_flag; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(stepSize));
                setRemainingTime(questionTime - stepSize * (i + 1));
            }

            if (m_flag)
            {
                // Waiting for the result showing
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

const Exercise* Performer::getExercise() const
{
    return &m_exercises[m_options.getExerciseIndex()];
}
