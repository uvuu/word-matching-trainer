#ifndef PAGINGPROXYMODEL_H
#define PAGINGPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QByteArray>
#include <QHash>
#include <QtQml/qqml.h>

class PagingProxyModel: public QAbstractProxyModel
{
    Q_OBJECT

#if QT_VERSION_6_OR_HIGHER
    QML_ELEMENT
#endif

    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(int pageSize READ getPageSize WRITE setPageSize NOTIFY pageSizeChanged)
    Q_PROPERTY(int pageCount READ getPageCount NOTIFY pageCountChanged)

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
    Q_INVOKABLE virtual int rowCount(const QModelIndex&) const override;
    Q_INVOKABLE virtual int columnCount(const QModelIndex&) const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex& index, int role) const override;

    // The minimal set of functions that have to be implemented for QAbstractProxyModel
    Q_INVOKABLE virtual QModelIndex mapToSource(const QModelIndex& proxyIndex) const override;
    Q_INVOKABLE virtual QModelIndex mapFromSource(const QModelIndex& sourceIndex) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void pageChanged();
    void pageSizeChanged();
    void pageCountChanged();

private:
    int getPage() const;
    void setPage(int page);
    int getPageSize() const;
    void setPageSize(int pageSize);
    int getPageCount()const;
    int getStartIndex() const;
    void reset();

private:
    int m_page{1};
    int m_pageSize{1};
};

#endif // PAGINGPROXYMODEL_H
