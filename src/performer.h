#ifndef PERFORMER_H
#define PERFORMER_H

#include <atomic>

#include <QObject>
#include <QStringListModel>

#include "exercise.h"
#include "options.h"

class Performer : public QObject
{
    Q_OBJECT

    // Options page
    Q_PROPERTY(Options* options READ getOptions CONSTANT)
    Q_PROPERTY(QStringListModel* exercisesNames READ getExercisesNames CONSTANT)

    // Training page
    Q_PROPERTY(const Exercise* exercise READ getExercise NOTIFY exerciseChanged CONSTANT)
    Q_PROPERTY(int remainingTime READ getRemainingTime NOTIFY remainingTimeChanged)
    Q_PROPERTY(QStringList task READ getTask NOTIFY taskChanged)

public:
    explicit Performer(QObject *parent = nullptr);
    ~Performer();

    Q_INVOKABLE void run();
    Q_INVOKABLE void stop();

    Options* getOptions();
    QStringListModel* getExercisesNames();
    int getRemainingTime() const;
    void setRemainingTime(int remainingTime);
    QStringList getTask() const;
    void setTask(QStringList task);
    const Exercise* getExercise() const;

signals:
    void exerciseNamesChanged();
    void exerciseChanged();
    void remainingTimeChanged();
    void taskChanged();

private:
    Exercises m_exercises;
    Options m_options;

    int m_remainingTime{0};
    QStringList m_task;
    QStringListModel m_exerciesNames;

    std::atomic_bool m_flag{true};
};

#endif // PERFORMER_H
