#pragma once
#include "Types.h"

//-----------------------------------------------------------------------------

struct VRAM {
  BusOut reset();
  BusOut tock(CpuBus bus);
  uint8_t ram[8192];
};

//-----------------------------------------------------------------------------
