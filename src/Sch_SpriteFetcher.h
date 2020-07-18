#pragma once
#include "Cells.h"

namespace Schematics {

struct SchematicTop;
struct VramBus;

//-----------------------------------------------------------------------------

struct SpriteFetcher {
  void tick(const SchematicTop& gb);
  void tock(SchematicTop& gb);
  SignalHash commit();


  // sfetch.veku, sst.store*_rstp, pxp.XEPY
  /*p29.WUTY*/ wire WUTY_SPRITE_DONEp() const { return not(VUSA_SPRITE_DONEn()); }

  // -> oam bus
  /*p25.VAPE*/ wire VAPE_FETCH_OAM_CLK() const {
    /*p29.TACU*/ wire TACU_SPR_SEQ_5_TRIG = nand(_TYFO_SFETCH_S0_D1.q(), TYTU_SFETCH_S0n());
    return and (TUVO_PPU_OAM_RDp(), TACU_SPR_SEQ_5_TRIG);
  }

  // -> oam bus
  /*p28.WEFY*/ wire WEFY_SPR_READp() const { return and(TUVO_PPU_OAM_RDp(), _TYFO_SFETCH_S0_D1.q()); }

  // -> vram bus
  /*p29.TACU*/ wire TACU_SPR_SEQ_5_TRIG() const { return nand(_TYFO_SFETCH_S0_D1.q(), TYTU_SFETCH_S0n()); }

  // -> vram bus
  /*p29.TEXY*/ wire TEXY_SPR_READ_VRAMp() const {
    /*p29.SAKY*/ wire _SAKY_SFETCH_MYSTERY = nor(_TULY_SFETCH_S1.q(), _VONU_SFETCH_S1_D4.q());
    /*p29.TYSO*/ wire TYSO_SPRITE_READn = or(_SAKY_SFETCH_MYSTERY, _TEPA_RENDERINGn); // def or
    return not(TYSO_SPRITE_READn);
  }

  // -> vram bus
  /*p29.ABON*/ wire ABON_SPR_VRM_RDn() const { return not(TEXY_SPR_READ_VRAMp()); }

  // -> vram bus
  /*p29.RACA*/ wire RACA_LATCH_SPPIXB() const { return and(_VONU_SFETCH_S1_D4.q(), SYCU_SFETCH_S0pe()); }

  // -> vram bus
  /*p29.TOPU*/ wire TOPU_LATCH_SPPIXA() const { return and(_TULY_SFETCH_S1.q(), SYCU_SFETCH_S0pe()); }

  // -> vram bus
  /*p29.XUQU*/ wire XUQU_SPRITE_AB() const { return not(!_VONU_SFETCH_S1_D4.q()); }


private:
  /*p29.SYCU*/ wire SYCU_SFETCH_S0pe() const { return nor(TYTU_SFETCH_S0n(), _LOBY_RENDERINGn, _TYFO_SFETCH_S0_D1.q()); }
  /*p29.TUVO*/ wire TUVO_PPU_OAM_RDp() const { return nor(_TEPA_RENDERINGn, _TULY_SFETCH_S1.q(), _TESE_SFETCH_S2.q()); }
  /*p29.TYTU*/ wire TYTU_SFETCH_S0n()     const { return not(_TOXE_SFETCH_S0.q()); }
  /*p29.VUSA*/ wire VUSA_SPRITE_DONEn() const {
    /*p29.TYNO*/ wire TYNO = nand(_TOXE_SFETCH_S0.q(), _SEBA_SFETCH_S1_D5.q(), _VONU_SFETCH_S1_D4.q());
    return or(_TYFO_SFETCH_S0_D1.qn(), TYNO);
  }

  Sig2 _TEPA_RENDERINGn;
  Sig2 _LOBY_RENDERINGn;

  /*p27.TAKA*/ Reg2 _TAKA_SFETCH_RUNNINGp = Reg2::D0C0;
  /*p27.SOBU*/ Reg2 _SOBU_SFETCH_REQp = Reg2::D0C0;
  /*p27.SUDA*/ Reg2 _SUDA_SFETCH_REQp = Reg2::D0C0;

  // When TOXE & TYFO & VONU & SEBA, sprites are loaded into the pipe.

  /*p29.TOXE*/ Reg2 _TOXE_SFETCH_S0 = Reg2::D0C0;
  /*p29.TYFO*/ Reg2 _TYFO_SFETCH_S0_D1 = Reg2::D0C0;

  /*p29.TULY*/ Reg2 _TULY_SFETCH_S1 = Reg2::D0C0;
  /*p29.TESE*/ Reg2 _TESE_SFETCH_S2 = Reg2::D0C0;

  /*p29.TOBU*/ Reg2 _TOBU_SFETCH_S1_D2 = Reg2::D0C0;
  /*p29.VONU*/ Reg2 _VONU_SFETCH_S1_D4 = Reg2::D0C0;
  /*p29.SEBA*/ Reg2 _SEBA_SFETCH_S1_D5 = Reg2::D0C0;

};


//-----------------------------------------------------------------------------

}; // namespace Schematics