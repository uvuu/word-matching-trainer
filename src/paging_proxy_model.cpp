#include "paging_proxy_model.h"

PagingProxyModel::PagingProxyModel(QObject *parent)
    : QAbstractProxyModel(parent)
{
}

QModelIndex PagingProxyModel::index(int row, int column, const QModelIndex&) const
{
    return createIndex(row, column);
}

QModelIndex PagingProxyModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int PagingProxyModel::rowCount(const QModelIndex &) const
{
    const auto restOfItems = sourceModel()->rowCount() - m_page * m_itemsPerPage ;
    return (restOfItems >= m_itemsPerPage) ? m_itemsPerPage : restOfItems;
}

int PagingProxyModel::columnCount(const QModelIndex &) const
{
    return sourceModel()->columnCount();
}

QVariant PagingProxyModel::data(const QModelIndex &index, int role) const
{
    if (role == SourceIndexRole)
    {
        return mapToSource(index).row();
    }

    return QAbstractProxyModel::data(index, role);
}

QModelIndex PagingProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
    const auto row = proxyIndex.row() + m_page * m_itemsPerPage;
    return sourceModel()->index(row, proxyIndex.column());
}

QModelIndex PagingProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    const auto row = sourceIndex.row() - m_page * m_itemsPerPage;
    //TODO: Should we use createIndex here?
    return index(row, sourceIndex.column(), {});
}

QHash<int, QByteArray> PagingProxyModel::roleNames() const
{
    auto roleNames = QAbstractProxyModel::roleNames();
    roleNames.insert(SourceIndexRole, "sourceIndex");

    return roleNames;
}

int PagingProxyModel::getPage() const
{
    return m_page;
}

void PagingProxyModel::setPage(int page)
{
    m_page = page;
    beginResetModel();
    endResetModel();
}

void PagingProxyModel::setItemsPerPage(int itemsPerPage)
{
    m_itemsPerPage = itemsPerPage;
    beginResetModel();
    endResetModel();
}

