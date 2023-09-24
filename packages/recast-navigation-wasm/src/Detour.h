#pragma once

#include "../recastnavigation/Recast/Include/Recast.h"
#include "../recastnavigation/Detour/Include/DetourStatus.h"
#include "../recastnavigation/Detour/Include/DetourNavMeshBuilder.h"
#include "../recastnavigation/DetourCrowd/Include/DetourCrowd.h"
#include "../recastnavigation/DetourTileCache/Include/DetourTileCacheBuilder.h"
#include "./Arrays.h"

class Detour
{
public:
    int FAILURE = DT_FAILURE;
    int SUCCESS = DT_SUCCESS;
    int IN_PROGRESS = DT_IN_PROGRESS;
    int STATUS_DETAIL_MASK = DT_STATUS_DETAIL_MASK;
    int WRONG_MAGIC = DT_WRONG_MAGIC;
    int WRONG_VERSION = DT_WRONG_VERSION;
    int OUT_OF_MEMORY = DT_OUT_OF_MEMORY;
    int INVALID_PARAM = DT_INVALID_PARAM;
    int BUFFER_TOO_SMALL = DT_BUFFER_TOO_SMALL;
    int OUT_OF_NODES = DT_OUT_OF_NODES;
    int PARTIAL_RESULT = DT_PARTIAL_RESULT;
    int ALREADY_OCCUPIED = DT_ALREADY_OCCUPIED;

    int VERTS_PER_POLYGON = DT_VERTS_PER_POLYGON;
    int NAVMESH_MAGIC = DT_NAVMESH_MAGIC;
    int NAVMESH_VERSION = DT_NAVMESH_VERSION;
    int NAVMESH_STATE_MAGIC = DT_NAVMESH_STATE_MAGIC;
    int NAVMESH_STATE_VERSION = DT_NAVMESH_STATE_VERSION;

    int TILECACHE_MAGIC = DT_TILECACHE_MAGIC;
    int TILECACHE_VERSION = DT_TILECACHE_VERSION;
    unsigned char TILECACHE_NULL_AREA = DT_TILECACHE_NULL_AREA;
    unsigned char TILECACHE_WALKABLE_AREA = DT_TILECACHE_WALKABLE_AREA;
    unsigned short TILECACHE_NULL_IDX = DT_TILECACHE_NULL_IDX;

    bool statusSucceed(dtStatus status)
    {
        return dtStatusSucceed(status);
    }

    bool statusFailed(dtStatus status)
    {
        return dtStatusFailed(status);
    }

    bool statusInProgress(dtStatus status)
    {
        return dtStatusInProgress(status);
    }

    bool statusDetail(dtStatus status, unsigned int detail)
    {
        return dtStatusDetail(status, detail);
    }

    dtCrowd *allocCrowd()
    {
        return dtAllocCrowd();
    }

    void freeCrowd(dtCrowd *crowd)
    {
        dtFreeCrowd(crowd);
    }
};

struct CreateNavMeshDataResult
{
    bool success;
    UnsignedCharArray *navMeshData;
};

class DetourNavMeshBuilder
{
public:
    void setPolyMeshCreateParams(dtNavMeshCreateParams *navMeshCreateParams, rcPolyMesh *polyMesh);

    void setPolyMeshDetailCreateParams(dtNavMeshCreateParams *navMeshCreateParams, rcPolyMeshDetail *polyMeshDetail);

    void setOffMeshConnections(dtNavMeshCreateParams *navMeshCreateParams, int offMeshConCount, float *offMeshConVerts, float *offMeshConRad, unsigned char *offMeshConDirs, unsigned char *offMeshConAreas, unsigned short *offMeshConFlags, unsigned int *offMeshConUserId);

    CreateNavMeshDataResult *createNavMeshData(dtNavMeshCreateParams &params);
};

class DetourTileCacheBuilder
{
public:
    int buildTileCacheLayer(
        dtTileCacheCompressor *comp,
        dtTileCacheLayerHeader *header,
        const UnsignedCharArray *heights,
        const UnsignedCharArray *areas,
        const UnsignedCharArray *cons,
        UnsignedCharArray *tileCacheData);
};
