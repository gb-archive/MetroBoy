#pragma once
#include "Cells.h"

namespace Schematics {

struct SchematicTop;
struct OamBus;
struct VramBus;

//-----------------------------------------------------------------------------

struct CpuBus {
  void tock(const SchematicTop& top);

  void set_cpu_req(int phase, Req req);

  //-----------------------------------------------------------------------------
  // Address decoders

  /*p25.SYRO*/ wire SYRO_FE00_FFFFp() const { return not(TUNA_0000_FDFFp()); }
  /*p07.RYCU*/ wire RYCU_0000_FDFFn() const { return not(TUNA_0000_FDFFp()); }
  /*p07.SOHA*/ wire SOHA_FF00_FFFFn() const { return not(SYKE_FF00_FFFFp()); }
  /*p07.ROPE*/ wire ROPE_FE00_FEFFn() const { return nand(RYCU_0000_FDFFn(), SOHA_FF00_FFFFn()); }
  /*p07.SARO*/ wire SARO_FE00_FEFFp() const { return not(ROPE_FE00_FEFFn()); }
  /*p28.ADAH*/ wire ADAH_FE00_FEFFn() const { return not(SARO_FE00_FEFFp()); }
  /*p08.SORE*/ wire SORE_0000_7FFFp() const { return not(CPU_BUS_A15); }
  /*p08.TEVY*/ wire TEVY_8000_9FFFn() const { return or(CPU_BUS_A13, CPU_BUS_A14, SORE_0000_7FFFp()); }
  /*p08.TEXO*/ wire TEXO_8000_9FFFn() const { return and(_CPU_PIN_AV, TEVY_8000_9FFFn()); }
  /*p08.LEVO*/ wire LEVO_8000_9FFFp() const { return not(TEXO_8000_9FFFn()); }

  /*p22.XOLA*/ wire XOLA_A00n() const { return not(CPU_BUS_A00); }
  /*p22.XENO*/ wire XENO_A01n() const { return not(CPU_BUS_A01); }
  /*p22.XUSY*/ wire XUSY_A02n() const { return not(CPU_BUS_A02); }
  /*p22.XERA*/ wire XERA_A03n() const { return not(CPU_BUS_A03); }
  /*p07.TONA*/ wire TONA_A08n() const { return not(CPU_BUS_A08); }

  /*p22.WADO*/ wire WADO_A00p() const { return not(XOLA_A00n()); }
  /*p22.WESA*/ wire WESA_A01p() const { return not(XENO_A01n()); }
  /*p22.WALO*/ wire WALO_A02p() const { return not(XUSY_A02n()); }
  /*p22.WEPO*/ wire WEPO_A03p() const { return not(XERA_A03n()); }

  /*p03.TOVY*/ wire TOVY_A00n() const { return not(CPU_BUS_A00); }
  /*p08.TOLA*/ wire TOLA_A01n() const { return not(CPU_BUS_A01); }
  /*p06.SEFY*/ wire SEFY_A02n() const { return not(CPU_BUS_A02); }

  /*p07.TUNA*/ wire TUNA_0000_FDFFp() const {
    return nand(CPU_BUS_A15, CPU_BUS_A14, CPU_BUS_A13,
                CPU_BUS_A12, CPU_BUS_A11, CPU_BUS_A10,
                CPU_BUS_A09);
  }

  /*p22.WERO*/ wire WERO_FF4Xp() const {
    /*p22.XALY*/ wire XALY_0x00xxxxp  = nor(CPU_BUS_A07, CPU_BUS_A05, CPU_BUS_A04);
    /*p07.SYKE*/ wire SYKE_FF00_FFFFp = nor(TUNA_0000_FDFFp(), TONA_A08n());
    /*p22.WUTU*/ wire WUTU_FF4Xn = nand(SYKE_FF00_FFFFp, CPU_BUS_A06, XALY_0x00xxxxp);
    return not(WUTU_FF4Xn);
  }

  /*p07.SYKE*/ wire SYKE_FF00_FFFFp() const { return nor(TUNA_0000_FDFFp(), TONA_A08n()); }
  /*p06.SARE*/ wire SARE_XX00_XX07p() const { return nor(CPU_BUS_A07, CPU_BUS_A06, CPU_BUS_A05, CPU_BUS_A04, CPU_BUS_A03); }


  /*p25.SOSE*/ wire SOSE_8000_9FFFp() const {
    /*p25.TEFA*/ wire _TEFA_8000_9FFFp = nor(SYRO_FE00_FFFFp(), TEXO_8000_9FFFn());
    /*p25.SOSE*/ wire SOSE_8000_9FFFp = and (CPU_BUS_A15, _TEFA_8000_9FFFp);
    return SOSE_8000_9FFFp;
  }

  /*p07.TULO*/ wire TULO_ADDR_00XXp() const {
    return nor(CPU_BUS_A15, CPU_BUS_A14, CPU_BUS_A13, CPU_BUS_A12,
               CPU_BUS_A11, CPU_BUS_A10, CPU_BUS_A09, CPU_BUS_A08);
  }

  /*p07.ZUFA*/ wire ZUFA_ADDR_00XX() const {
    /*p07.ZORO*/ wire _ZORO_ADDR_0XXX = nor(CPU_BUS_A15, CPU_BUS_A14, CPU_BUS_A13, CPU_BUS_A12);
    /*p07.ZADU*/ wire _ZADU_ADDR_X0XX = nor(CPU_BUS_A11, CPU_BUS_A10, CPU_BUS_A09, CPU_BUS_A08);
    return and(_ZORO_ADDR_0XXX, _ZADU_ADDR_X0XX);
  }

  //-----------------------------------------------------------------------------

  uint16_t bus_addr() const {
    return (uint16_t)pack(CPU_BUS_A00, CPU_BUS_A01, CPU_BUS_A02, CPU_BUS_A03,
                          CPU_BUS_A04, CPU_BUS_A05, CPU_BUS_A06, CPU_BUS_A07,
                          CPU_BUS_A08, CPU_BUS_A09, CPU_BUS_A10, CPU_BUS_A11,
                          CPU_BUS_A12, CPU_BUS_A13, CPU_BUS_A14, CPU_BUS_A15);
  }

  uint8_t bus_data() const {
    return (uint8_t)pack(CPU_BUS_D0, CPU_BUS_D1, CPU_BUS_D2, CPU_BUS_D3,
                         CPU_BUS_D4, CPU_BUS_D5, CPU_BUS_D6, CPU_BUS_D7);
  }

  //-----------------------------------------------------------------------------

  void dump(Dumper& d) {
    d("---------- CPU Bus  ----------\n");
    d("CPU BOOT : %d\n", _CPU_PIN_BOOTp.as_wire());
    d("CPU AHI  : %d\n", _CPU_PIN_ADDR_HI.as_wire());
    d("CPU RDp  : %d\n", _CPU_PIN_RDp.as_wire());
    d("CPU WRp  : %d\n", _CPU_PIN_WRp.as_wire());
    d("CPU AVn  : %d\n", _CPU_PIN_AV.as_wire());
    d("CPU DVn  : %d\n", _CPU_PIN_DV.as_wire());

    d("CPU ADDR : %04x\n", bus_addr());

    d("CPU DATA : %02x\n", bus_data());

    d("CPU PIN ADDR    : %c%c%c%c%c%c%c%c:%c%c%c%c%c%c%c%c\n",
      CPU_BUS_A15.c(), CPU_BUS_A14.c(), CPU_BUS_A13.c(), CPU_BUS_A12.c(),
      CPU_BUS_A11.c(), CPU_BUS_A10.c(), CPU_BUS_A09.c(), CPU_BUS_A08.c(),
      CPU_BUS_A07.c(), CPU_BUS_A06.c(), CPU_BUS_A05.c(), CPU_BUS_A04.c(),
      CPU_BUS_A03.c(), CPU_BUS_A02.c(), CPU_BUS_A01.c(), CPU_BUS_A00.c());

    d("CPU PIN DATA    : %c%c%c%c%c%c%c%c\n",
      CPU_BUS_D7.c(), CPU_BUS_D6.c(), CPU_BUS_D5.c(), CPU_BUS_D4.c(),
      CPU_BUS_D3.c(), CPU_BUS_D2.c(), CPU_BUS_D1.c(), CPU_BUS_D0.c());

    d("\n");
  }

  //-----------------------------------------------------------------------------

  Pin2 CPU_BUS_A00 = Pin2::HOLD_0;  // bottom right port PORTB_00: -> A00
  Pin2 CPU_BUS_A01 = Pin2::HOLD_0;  // bottom right port PORTB_04: -> A01
  Pin2 CPU_BUS_A02 = Pin2::HOLD_0;  // bottom right port PORTB_08: -> A02
  Pin2 CPU_BUS_A03 = Pin2::HOLD_0;  // bottom right port PORTB_12: -> A03
  Pin2 CPU_BUS_A04 = Pin2::HOLD_0;  // bottom right port PORTB_16: -> A04
  Pin2 CPU_BUS_A05 = Pin2::HOLD_0;  // bottom right port PORTB_20: -> A05
  Pin2 CPU_BUS_A06 = Pin2::HOLD_0;  // bottom right port PORTB_24: -> A06
  Pin2 CPU_BUS_A07 = Pin2::HOLD_0;  // bottom right port PORTB_28: -> A07
  Pin2 CPU_BUS_A08 = Pin2::HOLD_0;  // bottom right port PORTB_02: -> A08
  Pin2 CPU_BUS_A09 = Pin2::HOLD_0;  // bottom right port PORTB_06: -> A09
  Pin2 CPU_BUS_A10 = Pin2::HOLD_0;  // bottom right port PORTB_10: -> A10
  Pin2 CPU_BUS_A11 = Pin2::HOLD_0;  // bottom right port PORTB_14: -> A11
  Pin2 CPU_BUS_A12 = Pin2::HOLD_0;  // bottom right port PORTB_18: -> A12
  Pin2 CPU_BUS_A13 = Pin2::HOLD_0;  // bottom right port PORTB_22: -> A13
  Pin2 CPU_BUS_A14 = Pin2::HOLD_0;  // bottom right port PORTB_26: -> A14
  Pin2 CPU_BUS_A15 = Pin2::HOLD_0;  // bottom right port PORTB_30: -> A15                               

  Pin2 CPU_BUS_D0  = Pin2::HIZ_PU;   // bottom left port: <>
  Pin2 CPU_BUS_D1  = Pin2::HIZ_PU;   // bottom left port: <>
  Pin2 CPU_BUS_D2  = Pin2::HIZ_PU;   // bottom left port: <>
  Pin2 CPU_BUS_D3  = Pin2::HIZ_PU;   // bottom left port: <>
  Pin2 CPU_BUS_D4  = Pin2::HIZ_PU;   // bottom left port: <>
  Pin2 CPU_BUS_D5  = Pin2::HIZ_PU;   // bottom left port: <>
  Pin2 CPU_BUS_D6  = Pin2::HIZ_PU;   // bottom left port: <>
  Pin2 CPU_BUS_D7  = Pin2::HIZ_PU;   // bottom left port: <>

//private:

  //-----------------------------------------------------------------------------
  // SOC-to-CPU control signals

  Pin2 _CPU_PIN_BOOTp   = Pin2::HIZ_NP;   // top right port PORTA_04: <- P07.READ_BOOTROM tutu?
  Pin2 _CPU_PIN_ADDR_HI = Pin2::HIZ_NP;   // top right port PORTA_03: <- P25.SYRO // Not really sure why this is here

  //-----------------------------------------------------------------------------
  // CPU-to-SOC control signals

  Pin2 _CPU_PIN6     = Pin2::HOLD_0; // top left port PORTD_00: -> LEXY, doesn't do anything. FROM_CPU6? 
  Pin2 _CPU_PIN_DV   = Pin2::HOLD_1; // top left port PORTD_06: -> ANUJ, DECY, LAVO

  Pin2 _CPU_PIN_RDp  = Pin2::HOLD_0; // top right port PORTA_00: -> LAGU, LAVO, TEDO
  Pin2 _CPU_PIN_WRp  = Pin2::HOLD_0; // top right port PORTA_01: ->
  Pin2 _CPU_PIN_AV   = Pin2::HOLD_1; // top right port PORTA_06: -> TEXO, APAP
};

//-----------------------------------------------------------------------------

}; // namespace Schematics