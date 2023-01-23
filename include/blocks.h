#ifndef BLOCKS_H
#define BLOCKS_H

#include "../src/blocks/base/block_base_Base.h"
#include "../src/blocks/base/block_base_Conduit.h"
#include "../src/blocks/base/block_base_Consumer.h"
#include "../src/blocks/base/block_base_Source.h"

typedef BlockBase_Conduit Conduit;
typedef BlockBase_Consumer Consumer;
typedef BlockBase_Source Source;


/**
 * @brief Mode that a given Block should operate under. Used to determine what type
 * of comms device this block should inherit from.
 * @see #BlockType
 * @see /ref comms_device
 */
enum BlockPowerMode
{
    /// @brief Unassigned block power mode. Default value, invalid for execution.
    PM_UNASSIGNED = 0,
    /// @brief Source of power, providing power to other devices.
    /// @see /ref comms_transmitter
    PM_Source = 1,
    /// @brief PM_Consumer of power, taking power from a source.
    /// @see /ref comms_receiver
    PM_Consumer = 2,
    /// @brief Unique block type that only passes energy, and is neither a Source nor a PM_Consumer.
    PM_Conduit = 3,
};

/**
 * @brief Type for a given block - more granular contents,
 * @see BlockPowerMode
 */
enum BlockType
{
    /// @brief Unassigned block type. Default value, invalid for execution
    BT_UNASSIGNED = 0,

    /// @brief BT_PowerSupply. Provides power to other blocks.
    /// @see #BlockPowerMode ::Source
    /// @see /ref comms_transmitter
    BT_PowerSupply = 1,
    /// @brief BT_House. General use block, likely has a few LEDs or simple device.
    /// @see #BlockPowerMode ::PM_Consumer
    /// @see /ref comms_receiver
    BT_House = 2,
};

BlockPowerMode GetBlockPowerMode(BlockType);

bool IsBlockPowerModePowerAccessor(BlockPowerMode blockPowerMode);
bool IsBlockTypePowerAccessor(BlockType blockType);
bool IsBlockTypePowerSource(BlockType blockType);

#endif