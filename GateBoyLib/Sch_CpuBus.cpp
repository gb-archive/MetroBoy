#include "GateBoyLib/Sch_CpuBus.h"

#include "GateBoyLib/Sch_Top.h"

using namespace Schematics;

//------------------------------------------------------------------------------

void CpuBus::dump(Dumper& d) const {
  d("\002===== CPU Bus =====\001\n");
  d("PIN_CPU_BOOTp     %c\n", PIN_CPU_BOOTp.c());
  d("PIN_CPU_ADDR_HIp  %c\n", PIN_CPU_ADDR_HIp.c());
  d("PIN_CPU_RDp       %c\n", PIN_CPU_RDp.c());
  d("PIN_CPU_WRp       %c\n", PIN_CPU_WRp.c());
  d("PIN_CPU_ADDR_EXT  %c\n", PIN_CPU_EXT_BUSp.c());
  d("PIN_CPU_LATCH_EXT %c\n", PIN_CPU_LATCH_EXT.c());
  d("BUS ADDR  0x%04x  %c%c%c%c%c%c%c%c:%c%c%c%c%c%c%c%c\n",
    get_bus_addr(),
    BUS_CPU_A15.c(), BUS_CPU_A14.c(), BUS_CPU_A13.c(), BUS_CPU_A12.c(),
    BUS_CPU_A11.c(), BUS_CPU_A10.c(), BUS_CPU_A09.c(), BUS_CPU_A08.c(),
    BUS_CPU_A07.c(), BUS_CPU_A06.c(), BUS_CPU_A05.c(), BUS_CPU_A04.c(),
    BUS_CPU_A03.c(), BUS_CPU_A02.c(), BUS_CPU_A01.c(), BUS_CPU_A00.c());
  d("BUS DATA  0x%02x   %c%c%c%c%c%c%c%c\n",
    get_bus_data(),
    BUS_CPU_D7p.c(), BUS_CPU_D6p.c(), BUS_CPU_D5p.c(), BUS_CPU_D4p.c(),
    BUS_CPU_D3p.c(), BUS_CPU_D2p.c(), BUS_CPU_D1p.c(), BUS_CPU_D0p.c());

  d("\n");

  d("PIN STARTp        %d\n", PIN_CPU_STARTp.qp());
  d("PIN SYS_RSTp      %d\n", PIN_CPU_SYS_RSTp.qp());
  d("PIN EXT_RST       %d\n", PIN_CPU_EXT_RST.qp());
  d("PIN UNOR_DBG      %d\n", PIN_CPU_UNOR_DBG.qp());
  d("PIN UMUT_DBG      %d\n", PIN_CPU_UMUT_DBG.qp());
  d("PIN EXT_CLKGOOD   %d\n", PIN_CPU_EXT_CLKGOOD.qp());
  d("PIN BOWA_xBCDEFGH %d\n", PIN_CPU_BOWA_Axxxxxxx.qp());
  d("PIN BEDO_Axxxxxxx %d\n", PIN_CPU_BEDO_xBCDEFGH.qp());
  d("PIN BEKO_ABCDxxxx %d\n", PIN_CPU_BEKO_ABCDxxxx.qp());
  d("PIN BUDE_xxxxEFGH %d\n", PIN_CPU_BUDE_xxxxEFGH.qp());
  d("PIN BOLO_ABCDEFxx %d\n", PIN_CPU_BOLO_ABCDEFxx.qp());
  d("PIN BUKE_AxxxxxGH %d\n", PIN_CPU_BUKE_AxxxxxGH.qp());
  d("PIN BOMA_Axxxxxxx %d\n", PIN_CPU_BOMA_xBCDEFGH.qp());
  d("PIN BOGA_xBCDEFGH %d\n", PIN_CPU_BOGA_Axxxxxxx.qp());
  d("\n");
}

//------------------------------------------------------------------------------