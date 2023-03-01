#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>
#include <QStringList>

class Exercise
{
public:
    QString getName() const;
    void setName(QString name);
    void addTask(QString task);

    const QStringList& getTasks() const;

private:
    QString m_name;
    QStringList m_tasks;
};

using Exercises = QVector<Exercise>;

#endif // EXERCISE_H
