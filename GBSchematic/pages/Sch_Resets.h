#pragma once
#include "Sch_Common.h"

namespace Schematics {

//-----------------------------------------------------------------------------

struct ResetSignals1 {

  static ResetSignals1 tick(const SystemSignals& sys_sig,
                            const ResetRegisters& rst_reg,
                            bool CLK_BAD1,
                            bool CPUCLK_REQn,
                            bool BOGA_AxCDEFGH);

  void reset() {
    RESET_CLK = false;

    SYS_RESETn = true;
    SYS_RESET = false;
    CUNU_RESETn = true;

    VID_RESETn = true;
    WESY_RESET = true;
    VID_RESET5 = false;
    VID_RESET6 = false;
    VID_RESETn3 = true;
    VID_RESET4 = false;
    VID_RESET3 = false;
    WALU_RESET = true;
    XARE_RESET = true;
    SOTO_RESET = true;
  };

  /*p01.BOMA*/ bool RESET_CLK; // _____fgh -> PORTD_07
  /*p01.ALUR*/ bool SYS_RESETn;
  /*p01.DULA*/ bool SYS_RESET;

  /*p01.CUNU*/ bool CUNU_RESETn;
  /*p01.XAPO*/ bool VID_RESETn;

  /*p01.WESY*/ bool WESY_RESET;
  /*p01.ROSY*/ bool VID_RESET5;
  /*p01.ATAR*/ bool VID_RESET6;
  /*p01.ABEZ*/ bool VID_RESETn3;
  /*p01.PYRY*/ bool VID_RESET4;
  /*p01.TOFU*/ bool VID_RESET3;
  /*p01.WALU*/ bool WALU_RESET;
  /*p01.XARE*/ bool XARE_RESET;
  /*p01.SOTO*/ bool SOTO_RESET;
};

//-----------------------------------------------------------------------------

struct ResetSignals2 {

  static ResetSignals2 tick(const SystemSignals& sys_sig,
                            const ResetRegisters& rst_reg,
                            bool CLK_BAD1,
                            bool CPUCLK_REQn);

  void reset() {
    VID_RESETn = true;
    VID_RESET3 = false;
    VID_RESET4 = false;
    VID_RESET5 = false;
    VID_RESET6 = false;
    VID_RESETn3 = true;
  };

  /*p01.XAPO*/ bool VID_RESETn;
  /*p01.TOFU*/ bool VID_RESET3;
  /*p01.PYRY*/ bool VID_RESET4;
  /*p01.ROSY*/ bool VID_RESET5;
  /*p01.ATAR*/ bool VID_RESET6;
  /*p01.ABEZ*/ bool VID_RESETn3;
};

//-----------------------------------------------------------------------------

struct ResetRegisters {

  static void tock(const SystemSignals& sys_sig,
                   const ResetRegisters& rst_reg,
                   bool CLK_BAD1,
                   bool CPUCLK_REQn,
                   bool BOGA_AxCDEFGH,
                   ResetRegisters& next);

  void reset() {
    BAD_CLOCK_LATCH = true;
    RESET_REG.val = false;
    RESET_REG.clk = false;
  };

  /*p01.TUBO*/ bool BAD_CLOCK_LATCH;
  /*p01.AFER*/ Reg  RESET_REG;
};

//-----------------------------------------------------------------------------

};