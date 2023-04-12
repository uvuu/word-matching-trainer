#ifndef PAGINGPROXYMODEL_H
#define PAGINGPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QByteArray>
#include <QHash>
#include <QtQml/qqml.h>

class PagingProxyModel: public QAbstractProxyModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum PagingInfoRole
    {
        SourceIndexRole = Qt::UserRole + 1,
    };
    Q_ENUM(PagingInfoRole)

    PagingProxyModel(QObject *parent = nullptr);

    // The minimal set of functions that have to be implemented for QAbstractItemModel
    Q_INVOKABLE virtual QModelIndex index(int row, int column, const QModelIndex&) const override;
    Q_INVOKABLE virtual QModelIndex parent(const QModelIndex&) const override;
    Q_INVOKABLE virtual int rowCount(const QModelIndex &) const override;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &) const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role) const override;

    // The minimal set of functions that have to be implemented for QAbstractProxyModel
    Q_INVOKABLE virtual QModelIndex mapToSource(const QModelIndex& proxyIndex) const override;
    Q_INVOKABLE virtual QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE int getPage() const;
    Q_INVOKABLE void setPage(int page);
    Q_INVOKABLE void setItemsPerPage(int itemsPerPage);

private:
    int m_page{0};
    int m_itemsPerPage{1};
};

#endif // PAGINGPROXYMODEL_H
