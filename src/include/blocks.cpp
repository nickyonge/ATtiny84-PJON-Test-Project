#include "global.h"
#include "blocks.h"
#include "Arduino.h"

BlockPowerMode GetBlockPowerMode(BlockType blockType)
{
    switch (blockType)
    {
        // sources
    case BT_PowerSupply:
        return PM_Source;

        // consumers
    case BT_House:
        return PM_Consumer;

        // invalid/default
    case BT_UNASSIGNED:
        LogException("BlockType BT_UNASSIGNED is invalid, cannot get BlockPowerMode");
    default:
        LogError("tested BlockType is not implemented");
    }

    return PM_UNASSIGNED;
}

bool IsBlockPowerModePowerAccessor(BlockPowerMode blockPowerMode)
{
    if (blockPowerMode == PM_UNASSIGNED)
    {
        LogException("BlockPowerMode PM_UNASSIGNED is invalid, cannot check if power accessor");
    }
    switch (blockPowerMode)
    {
    case PM_UNASSIGNED:
    case PM_Conduit:
        return false;
    default:
        return true;
    }
}

bool IsBlockTypePowerAccessor(BlockType blockType)
{
    if (blockType == BT_UNASSIGNED)
    {
        LogException("BlockType BT_UNASSIGNED is invalid, cannot check if power accessor");
    }
    switch (blockType)
    {
    case BT_UNASSIGNED:
        return false;
    default:
        return true;
    }
}

/**
 * @brief Checks if the given #BlockType is a power SOURCE (true), or power CONSUMER (false).
 *
 * @param blockType BlockType to check
 * @return true if block IS a power source, false if not
 */
bool IsBlockTypePowerSource(BlockType blockType)
{
    if (blockType == BT_UNASSIGNED)
    {
        LogException("BlockType BT_UNASSIGNED is invalid, cannot check if power source, returning false");
    }
    return GetBlockPowerMode(blockType) == PM_Source;
}
bool IsBlockTypePowerConsumer(BlockType blockType)
{
    if (blockType == BT_UNASSIGNED)
    {
        LogException("BlockType BT_UNASSIGNED is invalid, cannot check if power source, returning false");
    }
    return GetBlockPowerMode(blockType) == PM_Consumer;
}