#include "./TileCache.h"

bool TileCache::init(const dtTileCacheParams *params, RecastLinearAllocator *allocator, RecastFastLZCompressor *compressor, TileCacheMeshProcessAbstract &meshProcess)
{
    if (!m_tileCache)
    {
        return false;
    }

    TileCacheMeshProcessWrapper *recastMeshProcess = new TileCacheMeshProcessWrapper(meshProcess);

    dtStatus status = m_tileCache->init(params, allocator, compressor, recastMeshProcess);
    if (dtStatusFailed(status))
    {
        return false;
    }

    m_talloc = allocator;
    m_tcomp = compressor;
    m_tmproc = recastMeshProcess;

    return true;
};

TileCacheAddTileResult TileCache::addTile(UnsignedCharArray *tileCacheData, unsigned char flags)
{
    TileCacheAddTileResult *result = new TileCacheAddTileResult;

    result->status = m_tileCache->addTile(tileCacheData->data, tileCacheData->size, flags, &result->tileRef);

    return *result;
}

dtStatus TileCache::buildNavMeshTile(const dtCompressedTileRef *ref, NavMesh *navMesh)
{
    return m_tileCache->buildNavMeshTile(*ref, navMesh->getNavMesh());
};

dtStatus TileCache::buildNavMeshTilesAt(const int tx, const int ty, NavMesh *navMesh)
{
    return m_tileCache->buildNavMeshTilesAt(tx, ty, navMesh->getNavMesh());
};

TileCacheUpdateResult TileCache::update(NavMesh *navMesh)
{
    TileCacheUpdateResult *result = new TileCacheUpdateResult;

    result->status = m_tileCache->update(0, navMesh->getNavMesh(), &result->upToDate);

    return *result;
};

dtObstacleRef *TileCache::addCylinderObstacle(const Vec3 &position, float radius, float height)
{
    dtObstacleRef ref(-1);
    if (!m_tileCache)
    {
        return nullptr;
    }

    m_tileCache->addObstacle(&position.x, radius, height, &ref);
    m_obstacles.push_back(ref);
    return &m_obstacles.back();
}

dtObstacleRef *TileCache::addBoxObstacle(const Vec3 &position, const Vec3 &extent, float angle)
{
    dtObstacleRef ref(-1);
    if (!m_tileCache)
    {
        return nullptr;
    }

    m_tileCache->addBoxObstacle(&position.x, &extent.x, angle, &ref);
    m_obstacles.push_back(ref);
    return &m_obstacles.back();
}

void TileCache::removeObstacle(dtObstacleRef *obstacle)
{
    if (!m_tileCache || !obstacle || *obstacle == -1)
    {
        return;
    }

    m_tileCache->removeObstacle(*obstacle);
    auto iter = std::find(m_obstacles.begin(), m_obstacles.end(), *obstacle);
    if (iter != m_obstacles.end())
    {
        m_obstacles.erase(iter);
    }
}

void TileCache::destroy()
{
    if (m_tileCache)
    {
        dtFreeTileCache(m_tileCache);
    }

    m_talloc->reset();
    m_talloc = 0;
    m_tcomp = 0;
    m_tmproc = 0;
}
