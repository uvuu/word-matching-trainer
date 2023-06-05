#include <QQmlEngine>

#include "exercise_view_data.h"
#include "paging_proxy_model.h"

struct QmlRegistrar
{
    QmlRegistrar()
    {
        qmlRegisterType<ExerciseViewData>(QML_URI, 1, 0, "ExerciseViewData");
        qmlRegisterType<PagingProxyModel>(QML_URI, 1, 0, "PagingProxyModel");
    }
};

static const QmlRegistrar registrar;
