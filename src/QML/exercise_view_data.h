#ifndef EXERCISEVIEWDATA_H
#define EXERCISEVIEWDATA_H

#include <QObject>
#include <QtQml/qqml.h>

#include "exercise.h"

// Looks like the Qt6 can perform this registration on its own.
// The purpose of this registration is to allow the "exercise" property to set in QML.
// See the row "exercise: performer.exercise".
#if !defined(QT_VERSION_6_OR_HIGHER)
Q_DECLARE_METATYPE(const Exercise*)
#endif

class ExerciseViewData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const Exercise* exercise WRITE setExercise NOTIFY exerciseChanged)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(double gapLength READ getGapLength CONSTANT)

#if QT_VERSION_6_OR_HIGHER
    QML_ELEMENT
#endif

public:
    explicit ExerciseViewData(QObject *parent = nullptr);
    void setExercise(const Exercise* const exercise);
    QString getName() const;
    double getGapLength() const;

signals:
    void exerciseChanged();

private:
    void updateGapLength();

private:
    const Exercise* m_exercise{nullptr};
    double m_gapLength{0};
};

#endif // EXERCISEVIEWDATA_H
