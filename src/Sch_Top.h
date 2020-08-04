#pragma once

#include "Sch_Timer.h"
#include "Sch_LCD.h"
#include "Sch_DMA.h"
#include "Sch_SpriteStore.h"
#include "Sch_Clocks.h"
#include "Sch_PixPipe.h"
#include "Sch_Joypad.h"
#include "Sch_Serial.h"
#include "Sch_Interrupts.h"
#include "Sch_Bootrom.h"
#include "Sch_SpriteFetcher.h"
#include "Sch_TileFetcher.h"
#include "Sch_SpriteScanner.h"

#include "Sch_CpuBus.h"
#include "Sch_ExtBus.h"
#include "Sch_OamBus.h"
#include "Sch_VramBus.h"

namespace Schematics {

//-----------------------------------------------------------------------------

struct SchematicTop {

  SchematicTop();

  void tick_slow(int phase);

  // top.BETE, top.AJUJ
  /*p28.AJON*/ wire AJON_OAM_BUSY() const {
    /*p28.BOGE*/ wire BOGE_DMA_RUNNINGn = not1(dma_reg.MATU_DMA_RUNNINGp());
    /*p28.AJON*/ wire AJON_OAM_BUSY = and2(BOGE_DMA_RUNNINGn, pix_pipe.XYMU_RENDERINGp()); // def AND. ppu can read oam when there's rendering but no dma
    return AJON_OAM_BUSY;
  }

  // -> top.AMAB, top.APAG
  /*p28.AJUJ*/ wire AJUJ_OAM_BUSYn() const { 
     /*p28.AJUJ*/ wire AJUJ_OAM_BUSYn = nor3(dma_reg.MATU_DMA_RUNNINGp(), ACYL_SCANNINGp(), AJON_OAM_BUSY()); // def nor4
     return AJUJ_OAM_BUSYn;
  }

  // -> oam.WYJA, oam.WUKU, oam.GUKO, top.APAG
  /*p28.AMAB*/ wire AMAB_CPU_READ_OAMp() const { 
      /*p28.AMAB*/ wire AMAB_CPU_READ_OAMp = and2(cpu_bus.SARO_FE00_FEFFp(), AJUJ_OAM_BUSYn()); // def and
      return AMAB_CPU_READ_OAMp;
  }

  //-----------------------------------------------------------------------------

  // ext.TOZA, ext.SEPY, vram.TUCA
  /*p01.ABUZ*/ wire ABUZ_AVn() const {
    /*p??.APAP*/ wire APAP_AVn = not1(cpu_bus.CPU_PIN_ADDR_EXT.q()); // Missing from schematic
    /*p01.AWOD*/ wire AWOD_AVp = nor2(clk_reg.UNOR_MODE_DBG2p(), APAP_AVn);
    /*p01.ABUZ*/ wire ABUZ_AVn = not1(AWOD_AVp);
    return ABUZ_AVn;
  }

  // boot.YULA, ext.SOBY, CPU_PIN_BOOTp
  /*p07.TUTU*/ wire TUTU_ADDR_BOOTp() const {
    /*p07.TERA*/ wire TERA_BOOT_BITp  = not1(bootrom.BOOT_BITn());
    return and2(TERA_BOOT_BITp, cpu_bus.TULO_ADDR_00XXp());
  }

  // pxp.loze, pxp.luxa, tile.lony/lovy/laxu/mesu/nyva/moce
  wire NYXU_TILE_FETCHER_RSTn() const {
    /*p27.NYXU*/ wire NYXU_TILE_FETCHER_RSTn = nor3(sprite_scanner.AVAP_RENDER_START_TRIGp(), pix_pipe.MOSU_TILE_FETCHER_RSTp(), TEVO_FINE_RSTp());
    return NYXU_TILE_FETCHER_RSTn;
  }

  //-----------------------------------------------------------------------------

  // -> buncha stuff
  /*p07.TEDO*/ wire TEDO_CPU_RDp() const {
    /*p07.UJYV*/ wire UJYV_CPU_RDn = mux2_n(ext_bus.EXT_PIN_RD_C.q(), cpu_bus.CPU_PIN_RDp.q(), clk_reg.UNOR_MODE_DBG2p());
    /*p07.TEDO*/ wire TEDO_CPU_RDp = not1(UJYV_CPU_RDn);
    return TEDO_CPU_RDp;
  }

  // -> buncha stuff
  /*p07.ASOT*/ wire ASOT_CPU_RDp() const {
    /*p07.AJAS*/ wire _AJAS_CPU_RDn = not1(TEDO_CPU_RDp());
    /*p07.ASOT*/ wire ASOT_CPU_RDp = not1(_AJAS_CPU_RDn);
    return ASOT_CPU_RDp;
  }

  // vram.TUJA, top.UBAL/MEXO
  /*p01.APOV*/ wire APOV_CPU_WRp_xxxDxxxx() const {
    /*p01.AREV*/ wire AREV_CPU_WRn_ABCxEFGH = nand2(cpu_bus.CPU_PIN_WRp.q(), clk_reg.AFAS_xxxDxxxx());
    /*p01.APOV*/ wire APOV_CPU_WRp_xxxDxxxx = not1(AREV_CPU_WRn_ABCxEFGH);
    return APOV_CPU_WRp_xxxDxxxx;
  }

  // boot.TUGE, int.REFA, joy.ATOZ, ser.URYS/UWAM, timer.TAPE/TOPE/TYJU/SARA, top.DYKY
  /*p07.TAPU*/ wire TAPU_CPU_WRp_xxxDxxxx() const {
#if 0
    TAPU_CPU_WRp_xxxDxxxx = and2(CPU_PIN_WRp, xxxxEFGx);
#endif

    /*p01.AREV*/ wire AREV_CPU_WRn_ABCxEFGH = nand2(cpu_bus.CPU_PIN_WRp.q(), clk_reg.AFAS_xxxDxxxx());
    /*p01.APOV*/ wire APOV_CPU_WRp_xxxDxxxx = not1(AREV_CPU_WRn_ABCxEFGH);
    /*p07.UBAL*/ wire UBAL_CPU_WRn_ABCxEFGH = mux2_n(ext_bus.EXT_PIN_WR_C.q(), APOV_CPU_WRp_xxxDxxxx, clk_reg.UNOR_MODE_DBG2p());
    /*p07.TAPU*/ wire TAPU_CPU_WRp_xxxDxxxx = not1(UBAL_CPU_WRn_ABCxEFGH);
    return TAPU_CPU_WRp_xxxDxxxx;
  }

  // dma.lavy, lcd.xufa, oam.wyja, pxp.vely/xoma/myxe, ppu.waru/sepa, tile.bedy/arur, top.xuto, win.weko/wuza (most all the FF4X regs)
  /*p07.CUPA*/ wire CUPA_CPU_WRp_xxxDxxxx() const {
    /*p07.DYKY*/ wire DYKY_CPU_WRn_ABCxEFGH = not1(TAPU_CPU_WRp_xxxDxxxx());
    /*p07.CUPA*/ wire CUPA_CPU_WRp_xxxDxxxx = not1(DYKY_CPU_WRn_ABCxEFGH);
    return CUPA_CPU_WRp_xxxDxxxx;
  }

  // ext.NEVY
  /*p08.MEXO*/ wire MEXO_CPU_WRn_ABCxEFGH() const {
    /*p08.MEXO*/ wire MEXO_CPU_WRn_ABCxEFGH = not1(APOV_CPU_WRp_xxxDxxxx());
    return MEXO_CPU_WRn_ABCxEFGH;
  }

  //-----------------------------------------------------------------------------
  // PPU signals

  // int.asam, oam.aver/ajep, ppu.xaty, top.apar/.ajuj
  // so dma stops oam scan?
  /*p28.ACYL*/ wire ACYL_SCANNINGp() const {
    /*p28.ACYL*/ wire ACYL_SCANNINGp = and2(dma_reg.BOGE_DMA_RUNNINGn(), sprite_scanner.BESU_SCANNINGp());
    return ACYL_SCANNINGp;
  }

  // -> ppu.PASO, window.VETU, top.NYXU_TILE_FETCHER_RSTn
  /*p27.TEVO*/ wire TEVO_FINE_RSTp() const { 
    /*p27.TEVO*/ wire TEVO_FINE_RSTp = or3(pix_pipe.SEKO_WX_MATCHne(), pix_pipe.SUZU_WIN_FIRST_TILEne(), tile_fetcher.TAVE_PORCH_DONE_TRIGp()); // Schematic wrong, this is OR
    return TEVO_FINE_RSTp;
  }

  //-----------------------------------------------------------------------------
  // Sys pins

#if 0
  if (RST) {
    // This can't be run mode, TAPE doesn't affect UKUP
    ADYK_xxxDEFGx = ff9( ATAL_xBxDxFxH, !ATAL_xBxDxFxH, or2(T1, T2), APUK_xxCDEFxx.q());
    UKUP_DIV_00 = ff9(BOGA_ABCDExxx, 0, UKUP_DIV_00.qn());
  }
  else {
    if (CLKIN_A) {
      // So this must be run mode, and ADYK must have _negative_ reset
      // RST = 0
      // CLKIN_A = 1
      ADYK_xxxDEFGx = ff9( ATAL_xBxDxFxH, !ATAL_xBxDxFxH, 1, APUK_xxCDEFxx.q());
      UKUP_DIV_00 = ff9(BOGA_ABCDExxx, !TAPE, UKUP_DIV_00.qn());  
    }
    else {
      // This also can't be run mode
      ADYK_xxxDEFGx = ff9( ATAL_xBxDxFxH, !ATAL_xBxDxFxH, 1, APUK_xxCDEFxx.q());
      UKUP_DIV_00 = ff9(BOGA_ABCDExxx, 0, UKUP_DIV_00.qn());  
    }
  }
#endif

  //-----------------------------------------------------------------------------
  // Sub-modules

  //private:

  OamBus oam_bus;
  ExtBus ext_bus;
  CpuBus cpu_bus;
  VramBus vram_bus;

  ClockRegisters clk_reg;
  DmaRegisters dma_reg;
  InterruptRegisters int_reg;
  Joypad joypad;
  LcdRegisters lcd_reg;
  PixelPipe pix_pipe;
  SerialRegisters ser_reg;
  SpriteStore sprite_store;
  Timer tim_reg;
  TileFetcher tile_fetcher;
  SpriteFetcher sprite_fetcher;
  SpriteScanner sprite_scanner;
  Bootrom bootrom;
};

//-----------------------------------------------------------------------------

};