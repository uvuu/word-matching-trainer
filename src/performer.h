#ifndef PERFORMER_H
#define PERFORMER_H

#include <atomic>

#include <QObject>

#include "exercise.h"
#include "options.h"

class Performer : public QObject
{
    Q_OBJECT

    // Options page
    Q_PROPERTY(Options* options READ getOptions CONSTANT)
    Q_PROPERTY(QStringList exercisesNames READ getExercisesNames CONSTANT)

    // Training page
    Q_PROPERTY(const Exercise* exercise READ getExercise NOTIFY exerciseChanged)
    Q_PROPERTY(int remainingTime READ getRemainingTime NOTIFY remainingTimeChanged)
    Q_PROPERTY(QStringList task READ getTask NOTIFY taskChanged)

public:
    explicit Performer(QObject *parent = nullptr);
    ~Performer();

    Q_INVOKABLE void run();
    Q_INVOKABLE void stop();

    Options* getOptions();
    QStringList getExercisesNames() const;
    int getRemainingTime() const;
    void setRemainingTime(int remainingTime);
    QStringList getTask() const;
    void setTask(QStringList task);
    const Exercise* getExercise() const;

signals:
    void exerciseChanged();
    void remainingTimeChanged();
    void taskChanged();

private:
    Exercises m_exercises;
    Options m_options;

    int m_remainingTime;
    QStringList m_task;
    int m_answerLength = 0;

    std::atomic_bool m_flag = true;
};

#endif // PERFORMER_H
