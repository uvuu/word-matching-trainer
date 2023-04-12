#include "paging_proxy_model.h"

PagingProxyModel::PagingProxyModel(QObject *parent)
    : QAbstractProxyModel(parent)
{
}

QModelIndex PagingProxyModel::index(int row, int column, const QModelIndex& parent) const
{
    if ((row < 0 || row >= rowCount(parent))|| (column < 0 || column >= columnCount(parent)))
    {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex PagingProxyModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int PagingProxyModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return sourceModel()->rowCount(parent);
    }

    const auto aheadItems = sourceModel()->rowCount() - getStartIndex();
    return (aheadItems >= m_pageSize) ? m_pageSize : aheadItems;
}

int PagingProxyModel::columnCount(const QModelIndex& parent) const
{
    return sourceModel()->columnCount(mapToSource(parent));
}

QVariant PagingProxyModel::data(const QModelIndex& index, int role) const
{
    if (role == SourceIndexRole)
    {
        return mapToSource(index).row();
    }

    return QAbstractProxyModel::data(index, role);
}

QModelIndex PagingProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
    const auto row = proxyIndex.row() + getStartIndex();
    return sourceModel()->index(row, proxyIndex.column());
}

QModelIndex PagingProxyModel::mapFromSource(const QModelIndex& sourceIndex) const
{
    const auto row = sourceIndex.row() - getStartIndex();
    return createIndex(row, sourceIndex.column());
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
    if (m_page != page)
    {
        m_page = page;
        pageChanged();

        reset();
    }
}

int PagingProxyModel::getPageSize() const
{
    return m_pageSize;
}

void PagingProxyModel::setPageSize(int pageSize)
{
    if (m_pageSize != pageSize)
    {
        m_pageSize = pageSize;
        pageSizeChanged();

        reset();
    }
}

int PagingProxyModel::getStartIndex() const
{
    return m_page * m_pageSize;
}

void PagingProxyModel::reset()
{
    beginResetModel();
    endResetModel();
}
