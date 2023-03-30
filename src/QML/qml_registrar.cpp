#include <QQmlEngine>

#include "exercise_view_data.h"

struct QmlRegistrar
{
    QmlRegistrar()
    {
        qmlRegisterType<ExerciseViewData>(QML_URI, 1, 0, "ExerciseViewData");
    }
};

static const QmlRegistrar registrar;
