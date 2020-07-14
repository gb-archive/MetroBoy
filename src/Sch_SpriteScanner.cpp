#include "Sch_SpriteScanner.h"
#include "Sch_Top.h"

using namespace Schematics;

//------------------------------------------------------------------------------

void SpriteScanner::tick(const SchematicTop& top) {
  wire GND = 0;

  {
    _XYLO_LCDC_SPEN = top.ppu_reg.XYLO_LCDC_SPEN.q();
    _XYMU_RENDERINGp = top.ppu_reg.XYMU_RENDERINGp();

    /*p29.BALU*/ _BALU_LINE_RSTp = not(top.lcd_reg.ANOM_LINE_RSTn());
    /*p29.BAGY*/ _BAGY_LINE_RSTn = not(_BALU_LINE_RSTp);
  }

  {
    /*p29.EBOS*/ wire _EBOS_Y0n = not(top.lcd_reg.MUWY_Y0.q());
    /*p29.DASA*/ wire _DASA_Y1n = not(top.lcd_reg.MYRO_Y1.q());
    /*p29.FUKY*/ wire _FUKY_Y2n = not(top.lcd_reg.LEXA_Y2.q());
    /*p29.FUVE*/ wire _FUVE_Y3n = not(top.lcd_reg.LYDO_Y3.q());
    /*p29.FEPU*/ wire _FEPU_Y4n = not(top.lcd_reg.LOVU_Y4.q());
    /*p29.FOFA*/ wire _FOFA_Y5n = not(top.lcd_reg.LEMA_Y5.q());
    /*p29.FEMO*/ wire _FEMO_Y6n = not(top.lcd_reg.MATO_Y6.q());
    /*p29.GUSU*/ wire _GUSU_Y7n = not(top.lcd_reg.LAFO_Y7.q());

    /*p29.ERUC*/ _ERUC_YDIFF_S0 = add_c(_EBOS_Y0n, top.XUSO_OAM_DB0.q(), GND);
    /*p29.ERUC*/ _ERUC_YDIFF_C0 = add_s(_EBOS_Y0n, top.XUSO_OAM_DB0.q(), GND);
    /*p29.ENEF*/ _ENEF_YDIFF_S1 = add_s(_DASA_Y1n, top.XEGU_OAM_DB1.q(), _ERUC_YDIFF_C0);
    /*p29.ENEF*/ _ENEF_YDIFF_C1 = add_c(_DASA_Y1n, top.XEGU_OAM_DB1.q(), _ERUC_YDIFF_C0);
    /*p29.FECO*/ _FECO_YDIFF_S2 = add_s(_FUKY_Y2n, top.YJEX_OAM_DB2.q(), _ENEF_YDIFF_C1);
    /*p29.FECO*/ _FECO_YDIFF_C2 = add_c(_FUKY_Y2n, top.YJEX_OAM_DB2.q(), _ENEF_YDIFF_C1);
    /*p29.GYKY*/ _GYKY_YDIFF_S3 = add_s(_FUVE_Y3n, top.XYJU_OAM_DB3.q(), _FECO_YDIFF_C2);
    /*p29.GYKY*/ _GYKY_YDIFF_C3 = add_c(_FUVE_Y3n, top.XYJU_OAM_DB3.q(), _FECO_YDIFF_C2);
    /*p29.GOPU*/ _GOPU_YDIFF_S4 = add_s(_FEPU_Y4n, top.YBOG_OAM_DB4.q(), _GYKY_YDIFF_C3);
    /*p29.GOPU*/ _GOPU_YDIFF_C4 = add_c(_FEPU_Y4n, top.YBOG_OAM_DB4.q(), _GYKY_YDIFF_C3);
    /*p29.FUWA*/ _FUWA_YDIFF_S5 = add_s(_FOFA_Y5n, top.WYSO_OAM_DB5.q(), _GOPU_YDIFF_C4);
    /*p29.FUWA*/ _FUWA_YDIFF_C5 = add_c(_FOFA_Y5n, top.WYSO_OAM_DB5.q(), _GOPU_YDIFF_C4);
    /*p29.GOJU*/ _GOJU_YDIFF_S6 = add_s(_FEMO_Y6n, top.XOTE_OAM_DB6.q(), _FUWA_YDIFF_C5);
    /*p29.GOJU*/ _GOJU_YDIFF_C6 = add_c(_FEMO_Y6n, top.XOTE_OAM_DB6.q(), _FUWA_YDIFF_C5);
    /*p29.WUHU*/ _WUHU_YDIFF_S7 = add_s(_GUSU_Y7n, top.YZAB_OAM_DB7.q(), _GOJU_YDIFF_C6);
    /*p29.WUHU*/ _WUHU_YDIFF_C7 = add_c(_GUSU_Y7n, top.YZAB_OAM_DB7.q(), _GOJU_YDIFF_C6);
  }

  {
    /*p29.GACE*/ wire _GACE_SPRITE_DELTA4 = not(_GOPU_YDIFF_S4);
    /*p29.GUVU*/ wire _GUVU_SPRITE_DELTA5 = not(_FUWA_YDIFF_S5);
    /*p29.GYDA*/ wire _GYDA_SPRITE_DELTA6 = not(_GOJU_YDIFF_S6);
    /*p29.GEWY*/ wire _GEWY_SPRITE_DELTA7 = not(_WUHU_YDIFF_S7);

    /*p29.GOVU*/ wire _GOVU_SPSIZE_MATCH = or (_GYKY_YDIFF_S3, top.ppu_reg.XYMO_LCDC_SPSIZE.q());
    /*p29.WOTA*/ wire _WOTA_SCAN_MATCH_Yn = nand(_GACE_SPRITE_DELTA4, _GUVU_SPRITE_DELTA5, _GYDA_SPRITE_DELTA6, _GEWY_SPRITE_DELTA7, _WUHU_YDIFF_C7, _GOVU_SPSIZE_MATCH);
    /*p29.GESE*/ wire _GESE_SCAN_MATCH_Y = not(_WOTA_SCAN_MATCH_Yn);
    /*p29.CARE*/ _CARE_STORE_ENp_ABxxEFxx = and (top.clk_reg.XOCE_AxxDExxH(), top.sprite_scanner.CEHA_SCANNINGp(), _GESE_SCAN_MATCH_Y); // Dots on VCC, this is AND. Die shot and schematic wrong.
  }
}

//------------------------------------------------------------------------------

void SpriteScanner::tock(const SchematicTop& top) {

  /*p28.FETO*/ wire _FETO_SCAN_DONE_d0 = and (_YFEL_SCAN0.q(), _WEWY_SCAN1.q(), _GOSO_SCAN2.q(), _FONY_SCAN5.q()); // die AND. 32 + 4 + 2 + 1 = 39

  //----------------------------------------
  // Sprite scan trigger & reset. Why it resets both before and after the scan I do not know.

  {
    /*p29.BYBA*/ _BYBA_SCAN_DONE_A.set(top.clk_reg.XUPY_ABxxEFxx(), _BAGY_LINE_RSTn, _FETO_SCAN_DONE_d0);
    /*p29.DOBA*/ _DOBA_SCAN_DONE_B.set(top.clk_reg.ALET_xBxDxFxH(), _BAGY_LINE_RSTn, _BYBA_SCAN_DONE_A.q());

    /*p28.ASEN*/ wire _ASEN_SCAN_DONE_PE = or (top.rst_reg.ATAR_VID_RSTp(), top.sprite_scanner.AVAP_RENDER_START_TRIGp());
    /*p28.BESU*/ _BESU_SCANNINGp.nor_latch(top.lcd_reg.CATU_VID_LINE_ENDp(), _ASEN_SCAN_DONE_PE);
    /*p29.CENO*/ _CENO_SCANNINGp.set(top.clk_reg.XUPY_ABxxEFxx(), top.rst_reg.ABEZ_VID_RSTn(), _BESU_SCANNINGp.q());
  }

  //----------------------------------------
  // Sprite scan counter
  // Sprite scan takes 160 phases, 4 phases per sprite.

  {
    /*p28.GAVA*/ wire _GAVA_SCAN_CLK = or(_FETO_SCAN_DONE_d0,   top.clk_reg.XUPY_ABxxEFxx());
    /*p28.YFEL*/ _YFEL_SCAN0.set(_GAVA_SCAN_CLK,   top.lcd_reg.ANOM_LINE_RSTn(), _YFEL_SCAN0.qn());
    /*p28.WEWY*/ _WEWY_SCAN1.set(_YFEL_SCAN0.qn(), top.lcd_reg.ANOM_LINE_RSTn(), _WEWY_SCAN1.qn());
    /*p28.GOSO*/ _GOSO_SCAN2.set(_WEWY_SCAN1.qn(), top.lcd_reg.ANOM_LINE_RSTn(), _GOSO_SCAN2.qn());
    /*p28.ELYN*/ _ELYN_SCAN3.set(_GOSO_SCAN2.qn(), top.lcd_reg.ANOM_LINE_RSTn(), _ELYN_SCAN3.qn());
    /*p28.FAHA*/ _FAHA_SCAN4.set(_ELYN_SCAN3.qn(), top.lcd_reg.ANOM_LINE_RSTn(), _FAHA_SCAN4.qn());
    /*p28.FONY*/ _FONY_SCAN5.set(_FAHA_SCAN4.qn(), top.lcd_reg.ANOM_LINE_RSTn(), _FONY_SCAN5.qn());
  }
}

//------------------------------------------------------------------------------

SignalHash SpriteScanner::commit() {
  SignalHash hash;

  hash << _XYLO_LCDC_SPEN.commit();
  hash << _XYMU_RENDERINGp.commit();
  hash << _BALU_LINE_RSTp.commit();

  /*p28.BESU*/ hash << _BESU_SCANNINGp.commit();
  /*p29.CENO*/ hash << _CENO_SCANNINGp.commit();

  /*p29.ERUC*/ hash << _ERUC_YDIFF_S0.commit();
  /*p29.ERUC*/ hash << _ERUC_YDIFF_C0.commit();
  /*p29.ENEF*/ hash << _ENEF_YDIFF_S1.commit();
  /*p29.ENEF*/ hash << _ENEF_YDIFF_C1.commit();
  /*p29.FECO*/ hash << _FECO_YDIFF_S2.commit();
  /*p29.FECO*/ hash << _FECO_YDIFF_C2.commit();
  /*p29.GYKY*/ hash << _GYKY_YDIFF_S3.commit();
  /*p29.GYKY*/ hash << _GYKY_YDIFF_C3.commit();
  /*p29.GOPU*/ hash << _GOPU_YDIFF_S4.commit();
  /*p29.GOPU*/ hash << _GOPU_YDIFF_C4.commit();
  /*p29.FUWA*/ hash << _FUWA_YDIFF_S5.commit();
  /*p29.FUWA*/ hash << _FUWA_YDIFF_C5.commit();
  /*p29.GOJU*/ hash << _GOJU_YDIFF_S6.commit();
  /*p29.GOJU*/ hash << _GOJU_YDIFF_C6.commit();
  /*p29.WUHU*/ hash << _WUHU_YDIFF_S7.commit();
  /*p29.WUHU*/ hash << _WUHU_YDIFF_C7.commit();

  /*p29.CARE*/ hash << _CARE_STORE_ENp_ABxxEFxx.commit();

  /*p28.YFEL*/ hash << _YFEL_SCAN0.commit();
  /*p28.WEWY*/ hash << _WEWY_SCAN1.commit();
  /*p28.GOSO*/ hash << _GOSO_SCAN2.commit();
  /*p28.ELYN*/ hash << _ELYN_SCAN3.commit();
  /*p28.FAHA*/ hash << _FAHA_SCAN4.commit();
  /*p28.FONY*/ hash << _FONY_SCAN5.commit();
  /*p29.BYBA*/ hash << _BYBA_SCAN_DONE_A.commit();
  /*p29.DOBA*/ hash << _DOBA_SCAN_DONE_B.commit();

  return hash;
}

//------------------------------------------------------------------------------
