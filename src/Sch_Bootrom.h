#pragma once
#include "Sch_Common.h"

namespace Schematics {

struct TestGB;

//-----------------------------------------------------------------------------

struct BootSignals {
  /*p07.TEPU*/ bool BOOT_BITn;
  /*p07.TUTU*/ bool TUTU_BOOTp;
};

struct Bootrom {
  BootSignals sig(const TestGB& gb) const;
  void tick(TestGB& gb);
  bool commit();
  /*p07.TEPU*/ Reg BOOT_BITn; // Starts 0, set to 1 by bootrom which blocks reading 0x0000-0x00FF.
};

//-----------------------------------------------------------------------------

}; // namespace Schematics