#ifndef EXERCISEVIEWDATA_H
#define EXERCISEVIEWDATA_H

#include <QObject>
#include <QtQml/qqml.h>

#include "exercise.h"

class ExerciseViewData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const Exercise* exercise WRITE setExercise NOTIFY exerciseChanged)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(double gapLength READ getGapLength CONSTANT)
//    QML_ELEMENT

public:
    explicit ExerciseViewData(QObject *parent = nullptr);
    void setExercise(const Exercise* const exercise);
    QString getName();
    double getGapLength();

signals:
    void exerciseChanged();

private:
    void updateGapLength();

private:
    const Exercise* m_exercise{nullptr};
    double m_gapLength{0};
};

#endif // EXERCISEVIEWDATA_H
