#include "Sch_VramBus.h"

#include "Sch_Top.h"

using namespace Schematics;

// TEGU_01 << SOSE
// TEGU_02 << CPU_PIN_WR
// TEGU_03 >> SALE_03

#define DUMP(A) do { d("%-20s : %d\n", #A, wire(A)); } while(0);

void VramBus::dump(Dumper& d, const SchematicTop& top) const {
  /*
  int addr = pack(_VRAM_PIN_A00_AD, _VRAM_PIN_A01_AD, _VRAM_PIN_A02_AD, _VRAM_PIN_A03_AD,
                  _VRAM_PIN_A04_AD, _VRAM_PIN_A05_AD, _VRAM_PIN_A06_AD, _VRAM_PIN_A07_AD,
                  _VRAM_PIN_A08_AD, _VRAM_PIN_A09_AD, _VRAM_PIN_A10_AD, _VRAM_PIN_A11_AD,
                  _VRAM_PIN_A12_AD, 0, 0, 0);
  int data_a = pack(_VRAM_PIN_D0_A, _VRAM_PIN_D1_A, _VRAM_PIN_D2_A, _VRAM_PIN_D3_A,
                    _VRAM_PIN_D4_A, _VRAM_PIN_D5_A, _VRAM_PIN_D6_A, _VRAM_PIN_D7_A);
  int data_b = pack(_VRAM_PIN_D0_B, _VRAM_PIN_D1_B, _VRAM_PIN_D2_B, _VRAM_PIN_D3_B,
                    _VRAM_PIN_D4_B, _VRAM_PIN_D5_B, _VRAM_PIN_D6_B, _VRAM_PIN_D7_B);
  int data_c = pack(_VRAM_PIN_D0_C, _VRAM_PIN_D1_C, _VRAM_PIN_D2_C, _VRAM_PIN_D3_C,
                    _VRAM_PIN_D4_C, _VRAM_PIN_D5_C, _VRAM_PIN_D6_C, _VRAM_PIN_D7_C);
  int data_d = pack(_VRAM_PIN_D0_D, _VRAM_PIN_D1_D, _VRAM_PIN_D2_D, _VRAM_PIN_D3_D,
                    _VRAM_PIN_D4_D, _VRAM_PIN_D5_D, _VRAM_PIN_D6_D, _VRAM_PIN_D7_D);
  addr = (~addr) & 0x1FFF;
  */


  d("---------- VRAM Bus ----------\n");
  d("MAP X                : %d\n", get_map_x(top));
  d("MAP Y                : %d\n", get_map_y(top));


  /*p25.XEDU*/ DUMP(XEDU_CPU_VRAM_RDn);
  /*p04.AHOC*/ DUMP(AHOC_DMA_VRAM_RDn);
  /*p29.ABON*/ DUMP(ABON_SPR_VRM_RDn);
  /*p26.BAFY*/ DUMP(BAFY_BG_MAP_READn);
  /*p25.WUKO*/ DUMP(WUKO_WIN_MAP_READn);
  /*p27.NETA*/ DUMP(NETA_TILE_READp);
  /*p26.ASUL*/ DUMP(ASUL_TILE_READp);
  /*p26.BEJE*/ DUMP(BEJE_BGD_TILE_READn);
  /*p25.XUCY*/ DUMP(XUCY_WIN_TILE_READn);
  /*p25.VUZA*/ DUMP(VUZA_TILE_BANKp);

  int temp1 = pack(LEGU_TILE_DA0.q(), NUDU_TILE_DA1.q(), MUKU_TILE_DA2.q(), LUZO_TILE_DA3.q(),
                   MEGU_TILE_DA4.q(), MYJY_TILE_DA5.q(), NASA_TILE_DA6.q(), NEFO_TILE_DA7.q());
  int temp2 = pack(RAWU_TILE_DB0.q(), POZO_TILE_DB1.q(), PYZO_TILE_DB2.q(), POXA_TILE_DB3.q(),
                   PULO_TILE_DB4.q(), POJU_TILE_DB5.q(), POWY_TILE_DB6.q(), PYJU_TILE_DB7.q());
  int temp3 = pack(PEFO_SPRITE_DA0.q(), ROKA_SPRITE_DA1.q(), MYTU_SPRITE_DA2.q(), RAMU_SPRITE_DA3.q(),
                   SELE_SPRITE_DA4.q(), SUTO_SPRITE_DA5.q(), RAMA_SPRITE_DA6.q(), RYDU_SPRITE_DA7.q());
  int temp4 = pack(REWO_SPRITE_DB0.q(), PEBA_SPRITE_DB1.q(), MOFO_SPRITE_DB2.q(), PUDU_SPRITE_DB3.q(),
                   SAJA_SPRITE_DB4.q(), SUNY_SPRITE_DB5.q(), SEMO_SPRITE_DB6.q(), SEGA_SPRITE_DB7.q());

  d("TEMP DATA 1      : 0x%02x\n", temp1);
  d("TEMP DATA 2      : 0x%02x\n", temp2);
  d("TEMP DATA 3      : 0x%02x\n", temp3);
  d("TEMP DATA 4      : 0x%02x\n", temp4);

  d("VRAM BUS ADDR    : %04x %c%c%c%c%c:%c%c%c%c%c%c%c%c\n",
    get_bus_addr() | 0x8000,
    _VRAM_BUS_A12.c(), _VRAM_BUS_A11.c(), _VRAM_BUS_A10.c(), _VRAM_BUS_A09.c(),
    _VRAM_BUS_A08.c(), _VRAM_BUS_A07.c(), _VRAM_BUS_A06.c(), _VRAM_BUS_A05.c(),
    _VRAM_BUS_A04.c(), _VRAM_BUS_A03.c(), _VRAM_BUS_A02.c(), _VRAM_BUS_A01.c(),
    _VRAM_BUS_A00.c());

  d("VRAM BUS DATA    : %c%c%c%c%c%c%c%c\n",
    _VRAM_BUS_D7.c(), _VRAM_BUS_D6.c(), _VRAM_BUS_D5.c(), _VRAM_BUS_D4.c(),
    _VRAM_BUS_D3.c(), _VRAM_BUS_D2.c(), _VRAM_BUS_D1.c(), _VRAM_BUS_D0.c());

  d("VRAM PIN MCS     : %c%c%c\n", _VRAM_PIN_CS_A.c(), _VRAM_PIN_CS_C.c(), _VRAM_PIN_CS_D.c());
  d("VRAM PIN MOE     : %c%c%c\n", _VRAM_PIN_OE_A.c(), _VRAM_PIN_OE_C.c(), _VRAM_PIN_OE_D.c());
  d("VRAM PIN MWR     : %c%c%c\n", _VRAM_PIN_WR_A.c(), _VRAM_PIN_WR_C.c(), _VRAM_PIN_WR_D.c());


  d("VRAM PIN ADDR    : 0x%04x\n", get_pin_addr() | 0x8000);
  /*
  d("VRAM PIN ADDR    : %c%c%c%c%c:%c%c%c%c%c%c%c%c\n",
    _VRAM_PIN_A12.c(), _VRAM_PIN_A11.c(), _VRAM_PIN_A10.c(), _VRAM_PIN_A09.c(),
    _VRAM_PIN_A08.c(), _VRAM_PIN_A07.c(), _VRAM_PIN_A06.c(), _VRAM_PIN_A05.c(),
    _VRAM_PIN_A04.c(), _VRAM_PIN_A03.c(), _VRAM_PIN_A02.c(), _VRAM_PIN_A01.c(),
    _VRAM_PIN_A00.c());
  */

  d("VRAM PIN DATA A  : %c%c%c%c%c%c%c%c\n",
    _VRAM_PIN_D7_A.c(), _VRAM_PIN_D6_A.c(), _VRAM_PIN_D5_A.c(), _VRAM_PIN_D4_A.c(),
    _VRAM_PIN_D3_A.c(), _VRAM_PIN_D2_A.c(), _VRAM_PIN_D1_A.c(), _VRAM_PIN_D0_A.c());
  d("VRAM PIN DATA B  : %c%c%c%c%c%c%c%c\n",
    _VRAM_PIN_D7_B.c(), _VRAM_PIN_D6_B.c(), _VRAM_PIN_D5_B.c(), _VRAM_PIN_D4_B.c(),
    _VRAM_PIN_D3_B.c(), _VRAM_PIN_D2_B.c(), _VRAM_PIN_D1_B.c(), _VRAM_PIN_D0_B.c());
  d("VRAM PIN DATA C  : %c%c%c%c%c%c%c%c\n",
    _VRAM_PIN_D7_C.c(), _VRAM_PIN_D6_C.c(), _VRAM_PIN_D5_C.c(), _VRAM_PIN_D4_C.c(),
    _VRAM_PIN_D3_C.c(), _VRAM_PIN_D2_C.c(), _VRAM_PIN_D1_C.c(), _VRAM_PIN_D0_C.c());
  d("VRAM PIN DATA D  : %c%c%c%c%c%c%c%c\n",
    _VRAM_PIN_D7_D.c(), _VRAM_PIN_D6_D.c(), _VRAM_PIN_D5_D.c(), _VRAM_PIN_D4_D.c(),
    _VRAM_PIN_D3_D.c(), _VRAM_PIN_D2_D.c(), _VRAM_PIN_D1_D.c(), _VRAM_PIN_D0_D.c());
  d("\n");
}


int VramBus::get_map_x(const SchematicTop& /*top*/) const {
  return pack(_BABE_MAP_X0S, _ABOD_MAP_X1S, _BEWY_MAP_X2S, _BYCA_MAP_X3S, _ACUL_MAP_X4S, 0, 0, 0);
}

int VramBus::get_map_y(const SchematicTop& /*top*/) const {
  return pack(_ETAM_MAP_Y0S, _DOTO_MAP_Y1S, _DABA_MAP_Y2S, _EFYK_MAP_Y3S, _EJOK_MAP_Y4S, 0, 0, 0);
}

//------------------------------------------------------------------------------

void VramBus::tock(SchematicTop& top) {

  /*p08.TEXO*/ wire TEXO_8000_9FFFn = and2(top.cpu_bus.CPU_PIN_ADDR_EXT.q(), top.cpu_bus.TEVY_8000_9FFFn());
  /*p25.TEFA*/ wire TEFA_8000_9FFFp = nor2(top.cpu_bus.SYRO_FE00_FFFFp(), TEXO_8000_9FFFn);
  /*p25.SOSE*/ wire SOSE_8000_9FFFp = and2(top.cpu_bus.CPU_BUS_A15.q(), TEFA_8000_9FFFp);

  /*p29.ABON*/ ABON_SPR_VRM_RDn = not1(top.sprite_fetcher.TEXY_SPR_READ_VRAMp());

  //----------------------------------------
  // VRAM pins

  {
#if 0
    VRAM_PIN_WR = !and( CPU_PIN_WRp, AFAS_xxxDxxxx, SOSE_8000_9FFFp, !CPU_PIN_ADDR_EXT, !RENDERING);
#endif

    /*p25.TUJA*/ wire _TUJA_CPU_VRAM_WRp = and2(SOSE_8000_9FFFp, top.APOV_CPU_WRp_xxxDxxxx());
    /*p25.SUDO*/ wire _SUDO_MWRp_C = not1(_VRAM_PIN_WR_C.q());
    /*p25.TYJY*/ wire _TYJY_DBG_VRAM_WRp = mux2_p(_SUDO_MWRp_C, _TUJA_CPU_VRAM_WRp, top.clk_reg.TUTO_DBG_VRAMp());

    /*p25.TUCA*/ wire _TUCA_CPU_VRAM_RDp = and2(SOSE_8000_9FFFp, top.ABUZ_AVn());
    /*p25.TEFY*/ wire _TEFY_VRAM_MCSp = not1(_VRAM_PIN_CS_C.q());
    /*p25.TOLE*/ wire _TOLE_VRAM_RDp     = mux2_p(_TEFY_VRAM_MCSp, _TUCA_CPU_VRAM_RDp, top.clk_reg.TUTO_DBG_VRAMp());
    /*p25.SERE*/ wire _SERE_CPU_VRM_RDp = and2(_TOLE_VRAM_RDp, top.pix_pipe.ROPY_RENDERINGn());

    /*p25.SOHY*/ wire _SOHY_MWRn = nand2(_TYJY_DBG_VRAM_WRp, _SERE_CPU_VRM_RDp);
    /*p25.TAXY*/ wire _TAXY_MWRn_A = and2(_SOHY_MWRn, top.clk_reg.RACO_DBG_VRAMn());
    /*p25.SOFY*/ wire _SOFY_MWRn_D = or2(_SOHY_MWRn, top.clk_reg.TUTO_DBG_VRAMp());
    /*p25.SYSY*/ wire _SYSY_MWRp_A = not1(_TAXY_MWRn_A);
    /*p25.RAGU*/ wire _RAGU_MWRp_D = not1(_SOFY_MWRn_D);
    _VRAM_PIN_WR_A = _SYSY_MWRp_A;
    _VRAM_PIN_WR_D = _RAGU_MWRp_D;
  }


  {
    /*p25.XANE*/ wire _XANE_VRAM_LOCKn = nor2(top.dma_reg.LUFA_DMA_VRM_RDp(), top.pix_pipe.XYMU_RENDERINGp()); // def nor4
    /*p25.TAVY*/ wire _TAVY_MOEp = not1(_VRAM_PIN_OE_C.q());
    /*p25.TEGU*/ wire TEGU_CPU_VRAM_WRn = nand2(SOSE_8000_9FFFp, top.cpu_bus.CPU_PIN_WRp.q());  // Schematic wrong, second input is CPU_PIN_WRp
    /*p25.SALE*/ wire _SALE_VRAM_WRn = mux2_p(_TAVY_MOEp, TEGU_CPU_VRAM_WRn, top.clk_reg.TUTO_DBG_VRAMp());
    /*p25.RYLU*/ wire _RYLU_CPU_VRAM_RDn = nand2(_SALE_VRAM_WRn, _XANE_VRAM_LOCKn);

    /*p25.SOHO*/ wire _SOHO_SPR_VRAM_RDp = and2(top.sprite_fetcher.TACU_SPR_SEQ_5_TRIG(), ABON_SPR_VRM_RDn.q());
    /*p25.RAWA*/ wire _RAWA_SPR_VRAM_RDn = not1(_SOHO_SPR_VRAM_RDp);
    /*p25.APAM*/ wire _APAM_DMA_VRAM_RDn = not1(top.dma_reg.LUFA_DMA_VRM_RDp());
    /*p25.RACU*/ wire _RACU_MOEn = and4(_RYLU_CPU_VRAM_RDn, _RAWA_SPR_VRAM_RDn, top.tile_fetcher.MYMA_BGW_VRAM_RDn(), _APAM_DMA_VRAM_RDn); // def and

    /*p25.SEMA*/ wire _SEMA_MOEn_A = and2(_RACU_MOEn, top.clk_reg.RACO_DBG_VRAMn());
    /*p25.RUTE*/ wire _RUTE_MOEn_D = or2(_RACU_MOEn, top.clk_reg.TUTO_DBG_VRAMp()); // schematic wrong, second input is RACU
    /*p25.REFO*/ wire _REFO_MOEn_A = not1(_SEMA_MOEn_A);
    /*p25.SAHA*/ wire _SAHA_MOEn_D = not1(_RUTE_MOEn_D);
    _VRAM_PIN_OE_A = _REFO_MOEn_A;
    _VRAM_PIN_OE_D = _SAHA_MOEn_D;
  }

  {
    // Polarity issues here, ABON should be P
    // ABON = not1(TEXY)
    // SUTU = nor4(LENA, LUFA, ABON, SERE);

    wire LENA = top.tile_fetcher.LENA_BGW_VRM_RDp();
    wire LUFA = top.dma_reg.LUFA_DMA_VRM_RDp();

    /*p25.TUCA*/ wire _TUCA_CPU_VRAM_RDp = and2(SOSE_8000_9FFFp, top.ABUZ_AVn());
    /*p25.TEFY*/ wire _TEFY_VRAM_MCSp = not1(_VRAM_PIN_CS_C.q());
    /*p25.TOLE*/ wire _TOLE_VRAM_RDp     = mux2_p(_TEFY_VRAM_MCSp, _TUCA_CPU_VRAM_RDp, top.clk_reg.TUTO_DBG_VRAMp());
    /*p25.SERE*/ wire _SERE_CPU_VRM_RDp = and2(_TOLE_VRAM_RDp, top.pix_pipe.ROPY_RENDERINGn());
  
    /*p25.SUTU*/ wire _SUTU_MCSn = nor4(LENA, LUFA, ABON_SPR_VRM_RDn, _SERE_CPU_VRM_RDp);

    wire RACO = top.clk_reg.RACO_DBG_VRAMn();
    wire TUTU = top.clk_reg.TUTO_DBG_VRAMp();

    /*p25.TODE*/ wire _TODE_MCSn_A = and2(_SUTU_MCSn, RACO);
    /*p25.SEWO*/ wire _SEWO_MCSn_D = or2(_SUTU_MCSn, TUTU);
    /*p25.SOKY*/ wire _SOKY_MCSp_A = not1(_TODE_MCSn_A);
    /*p25.SETY*/ wire _SETY_MCSp_D = not1(_SEWO_MCSn_D);
    _VRAM_PIN_CS_A = _SOKY_MCSp_A;
    _VRAM_PIN_CS_D = _SETY_MCSp_D;
  }

  //----------------------------------------
  // VRAM address

  // CPU address -> vram address
  {
    /*p25.XANE*/ wire _XANE_VRAM_LOCKn = nor2(top.dma_reg.LUFA_DMA_VRM_RDp(), top.pix_pipe.XYMU_RENDERINGp()); // def nor4
    /*p25.XEDU*/ XEDU_CPU_VRAM_RDn = not1(_XANE_VRAM_LOCKn);
    /*p25.XAKY*/ _VRAM_BUS_A00 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A00.q());
    /*p25.XUXU*/ _VRAM_BUS_A01 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A01.q());
    /*p25.XYNE*/ _VRAM_BUS_A02 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A02.q());
    /*p25.XODY*/ _VRAM_BUS_A03 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A03.q());
    /*p25.XECA*/ _VRAM_BUS_A04 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A04.q());
    /*p25.XOBA*/ _VRAM_BUS_A05 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A05.q());
    /*p25.XOPO*/ _VRAM_BUS_A06 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A06.q());
    /*p25.XYBO*/ _VRAM_BUS_A07 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A07.q());
    /*p25.RYSU*/ _VRAM_BUS_A08 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A08.q());
    /*p25.RESE*/ _VRAM_BUS_A09 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A09.q());
    /*p25.RUSE*/ _VRAM_BUS_A10 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A10.q());
    /*p25.RYNA*/ _VRAM_BUS_A11 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A11.q());
    /*p25.RUMO*/ _VRAM_BUS_A12 = tribuf_6n(XEDU_CPU_VRAM_RDn, top.cpu_bus.CPU_BUS_A12.q());
  }

  // DMA address -> vram address
  {
    /*p04.AHOC*/ AHOC_DMA_VRAM_RDn = not1(top.dma_reg.LUFA_DMA_VRM_RDp());
    /*p04.ECAL*/ _VRAM_BUS_A00 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.NAKY_DMA_A00.q());
    /*p04.EGEZ*/ _VRAM_BUS_A01 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.PYRO_DMA_A01.q());
    /*p04.FUHE*/ _VRAM_BUS_A02 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.NEFY_DMA_A02.q());
    /*p04.FYZY*/ _VRAM_BUS_A03 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.MUTY_DMA_A03.q());
    /*p04.DAMU*/ _VRAM_BUS_A04 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.NYKO_DMA_A04.q());
    /*p04.DAVA*/ _VRAM_BUS_A05 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.PYLO_DMA_A05.q());
    /*p04.ETEG*/ _VRAM_BUS_A06 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.NUTO_DMA_A06.q());
    /*p04.EREW*/ _VRAM_BUS_A07 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.MUGU_DMA_A07.q());
    /*p04.EVAX*/ _VRAM_BUS_A08 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.NAFA_DMA_A08.q());
    /*p04.DUVE*/ _VRAM_BUS_A09 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.PYNE_DMA_A09.q());
    /*p04.ERAF*/ _VRAM_BUS_A10 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.PARA_DMA_A10.q());
    /*p04.FUSY*/ _VRAM_BUS_A11 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.NYDO_DMA_A11.q());
    /*p04.EXYF*/ _VRAM_BUS_A12 = tribuf_6n(AHOC_DMA_VRAM_RDn, top.dma_reg.NYGY_DMA_A12.q());
  }

  // Sprite fetcher read
  {
    /*p29.FUFO*/ wire _FUFO_LCDC_SPSIZEn = not1(top.pix_pipe.XYMO_LCDC_SPSIZE.q());
    /*p29.WUKY*/ wire _WUKY_FLIP_Y = not1(top.oam_bus.YZOS_OAM_DB6.q());
    /*p29.CYVU*/ wire _CYVU_OAM_DB0 = xor2(_WUKY_FLIP_Y, top.sprite_store.SPR_TRI_LINE_1.q());
    /*p29.BORE*/ wire _BORE_OAM_DB1 = xor2(_WUKY_FLIP_Y, top.sprite_store.SPR_TRI_LINE_2.q());
    /*p29.BUVY*/ wire _BUVY_OAM_DB2 = xor2(_WUKY_FLIP_Y, top.sprite_store.SPR_TRI_LINE_3.q());
    /*p29.WAGO*/ wire _WAGO = xor2(_WUKY_FLIP_Y, top.sprite_store.SPR_TRI_LINE_0.q());
    /*p29.GEJY*/ wire _GEJY_OAM_DB3 = amux2(_FUFO_LCDC_SPSIZEn, !top.oam_bus.XUSO_OAM_DA0.q(), top.pix_pipe.XYMO_LCDC_SPSIZE.q(), _WAGO);

    /*p29.ABEM*/ _VRAM_BUS_A00 = tribuf_6n(ABON_SPR_VRM_RDn, top.sprite_fetcher.XUQU_SPRITE_AB());
    /*p29.BAXE*/ _VRAM_BUS_A01 = tribuf_6n(ABON_SPR_VRM_RDn, _CYVU_OAM_DB0);
    /*p29.ARAS*/ _VRAM_BUS_A02 = tribuf_6n(ABON_SPR_VRM_RDn, _BORE_OAM_DB1);
    /*p29.AGAG*/ _VRAM_BUS_A03 = tribuf_6n(ABON_SPR_VRM_RDn, _BUVY_OAM_DB2);
    /*p29.FAMU*/ _VRAM_BUS_A04 = tribuf_6n(ABON_SPR_VRM_RDn, _GEJY_OAM_DB3);
    /*p29.FUGY*/ _VRAM_BUS_A05 = tribuf_6n(ABON_SPR_VRM_RDn, top.oam_bus.XEGU_OAM_DA1.q());
    /*p29.GAVO*/ _VRAM_BUS_A06 = tribuf_6n(ABON_SPR_VRM_RDn, top.oam_bus.YJEX_OAM_DA2.q());
    /*p29.WYGA*/ _VRAM_BUS_A07 = tribuf_6n(ABON_SPR_VRM_RDn, top.oam_bus.XYJU_OAM_DA3.q());
    /*p29.WUNE*/ _VRAM_BUS_A08 = tribuf_6n(ABON_SPR_VRM_RDn, top.oam_bus.YBOG_OAM_DA4.q());
    /*p29.GOTU*/ _VRAM_BUS_A09 = tribuf_6n(ABON_SPR_VRM_RDn, top.oam_bus.WYSO_OAM_DA5.q());
    /*p29.GEGU*/ _VRAM_BUS_A10 = tribuf_6n(ABON_SPR_VRM_RDn, top.oam_bus.XOTE_OAM_DA6.q());
    /*p29.XEHE*/ _VRAM_BUS_A11 = tribuf_6n(ABON_SPR_VRM_RDn, top.oam_bus.YZAB_OAM_DA7.q());
    /*p29.DYSO*/ _VRAM_BUS_A12 = tribuf_6n(ABON_SPR_VRM_RDn, 0);   // sprites always in low half of tile store
  }

  {
    /*p26.FAFO*/ _FAFO_TILE_Y0S = add_s(top.lcd_reg.MUWY_Y0.q(), top.tile_fetcher.GAVE_SCY0.q(), 0);
    /*p26.FAFO*/ _FAFO_TILE_Y0C = add_c(top.lcd_reg.MUWY_Y0.q(), top.tile_fetcher.GAVE_SCY0.q(), 0);
    /*p26.EMUX*/ _EMUX_TILE_Y1S = add_s(top.lcd_reg.MYRO_Y1.q(), top.tile_fetcher.FYMO_SCY1.q(), _FAFO_TILE_Y0C);
    /*p26.EMUX*/ _EMUX_TILE_Y1C = add_c(top.lcd_reg.MYRO_Y1.q(), top.tile_fetcher.FYMO_SCY1.q(), _FAFO_TILE_Y0C);
    /*p26.ECAB*/ _ECAB_TILE_Y2S = add_s(top.lcd_reg.LEXA_Y2.q(), top.tile_fetcher.FEZU_SCY2.q(), _EMUX_TILE_Y1C);
    /*p26.ECAB*/ _ECAB_TILE_Y2C = add_c(top.lcd_reg.LEXA_Y2.q(), top.tile_fetcher.FEZU_SCY2.q(), _EMUX_TILE_Y1C);
    /*p26.ETAM*/ _ETAM_MAP_Y0S  = add_s(top.lcd_reg.LYDO_Y3.q(), top.tile_fetcher.FUJO_SCY3.q(), _ECAB_TILE_Y2C);
    /*p26.ETAM*/ _ETAM_MAP_Y0C  = add_c(top.lcd_reg.LYDO_Y3.q(), top.tile_fetcher.FUJO_SCY3.q(), _ECAB_TILE_Y2C);
    /*p26.DOTO*/ _DOTO_MAP_Y1S  = add_s(top.lcd_reg.LOVU_Y4.q(), top.tile_fetcher.DEDE_SCY4.q(), _ETAM_MAP_Y0C);
    /*p26.DOTO*/ _DOTO_MAP_Y1C  = add_c(top.lcd_reg.LOVU_Y4.q(), top.tile_fetcher.DEDE_SCY4.q(), _ETAM_MAP_Y0C);
    /*p26.DABA*/ _DABA_MAP_Y2S  = add_s(top.lcd_reg.LEMA_Y5.q(), top.tile_fetcher.FOTY_SCY5.q(), _DOTO_MAP_Y1C);
    /*p26.DABA*/ _DABA_MAP_Y2C  = add_c(top.lcd_reg.LEMA_Y5.q(), top.tile_fetcher.FOTY_SCY5.q(), _DOTO_MAP_Y1C);
    /*p26.EFYK*/ _EFYK_MAP_Y3S  = add_s(top.lcd_reg.MATO_Y6.q(), top.tile_fetcher.FOHA_SCY6.q(), _DABA_MAP_Y2C);
    /*p26.EFYK*/ _EFYK_MAP_Y3C  = add_c(top.lcd_reg.MATO_Y6.q(), top.tile_fetcher.FOHA_SCY6.q(), _DABA_MAP_Y2C);
    /*p26.EJOK*/ _EJOK_MAP_Y4S  = add_s(top.lcd_reg.LAFO_Y7.q(), top.tile_fetcher.FUNY_SCY7.q(), _EFYK_MAP_Y3C);
    /*p26.EJOK*/ _EJOK_MAP_Y4C  = add_c(top.lcd_reg.LAFO_Y7.q(), top.tile_fetcher.FUNY_SCY7.q(), _EFYK_MAP_Y3C);

    /*p26.ATAD*/ _ATAD_TILE_X0S = add_s(top.pix_pipe.XEHO_X0.q(), top.tile_fetcher.DATY_SCX0.q(), 0);
    /*p26.ATAD*/ _ATAD_TILE_X0C = add_c(top.pix_pipe.XEHO_X0.q(), top.tile_fetcher.DATY_SCX0.q(), 0);
    /*p26.BEHU*/ _BEHU_TILE_X1S = add_s(top.pix_pipe.SAVY_X1.q(), top.tile_fetcher.DUZU_SCX1.q(), _ATAD_TILE_X0C);
    /*p26.BEHU*/ _BEHU_TILE_X1C = add_c(top.pix_pipe.SAVY_X1.q(), top.tile_fetcher.DUZU_SCX1.q(), _ATAD_TILE_X0C);
    /*p26.APYH*/ _APYH_TILE_X2S = add_s(top.pix_pipe.XODU_X2.q(), top.tile_fetcher.CYXU_SCX2.q(), _BEHU_TILE_X1C);
    /*p26.APYH*/ _APYH_TILE_X2C = add_c(top.pix_pipe.XODU_X2.q(), top.tile_fetcher.CYXU_SCX2.q(), _BEHU_TILE_X1C);
    /*p26.BABE*/ _BABE_MAP_X0S  = add_s(top.pix_pipe.XYDO_X3.q(), top.tile_fetcher.GUBO_SCX3.q(), _APYH_TILE_X2C);
    /*p26.BABE*/ _BABE_MAP_X0C  = add_c(top.pix_pipe.XYDO_X3.q(), top.tile_fetcher.GUBO_SCX3.q(), _APYH_TILE_X2C);
    /*p26.ABOD*/ _ABOD_MAP_X1S  = add_s(top.pix_pipe.TUHU_X4.q(), top.tile_fetcher.BEMY_SCX4.q(), _BABE_MAP_X0C);
    /*p26.ABOD*/ _ABOD_MAP_X1C  = add_c(top.pix_pipe.TUHU_X4.q(), top.tile_fetcher.BEMY_SCX4.q(), _BABE_MAP_X0C);
    /*p26.BEWY*/ _BEWY_MAP_X2S  = add_s(top.pix_pipe.TUKY_X5.q(), top.tile_fetcher.CUZY_SCX5.q(), _ABOD_MAP_X1C);
    /*p26.BEWY*/ _BEWY_MAP_X2C  = add_c(top.pix_pipe.TUKY_X5.q(), top.tile_fetcher.CUZY_SCX5.q(), _ABOD_MAP_X1C);
    /*p26.BYCA*/ _BYCA_MAP_X3S  = add_s(top.pix_pipe.TAKO_X6.q(), top.tile_fetcher.CABU_SCX6.q(), _BEWY_MAP_X2C);
    /*p26.BYCA*/ _BYCA_MAP_X3C  = add_c(top.pix_pipe.TAKO_X6.q(), top.tile_fetcher.CABU_SCX6.q(), _BEWY_MAP_X2C);
    /*p26.ACUL*/ _ACUL_MAP_X4S  = add_s(top.pix_pipe.SYBE_X7.q(), top.tile_fetcher.BAKE_SCX7.q(), _BYCA_MAP_X3C);
    /*p26.ACUL*/ _ACUL_MAP_X4C  = add_c(top.pix_pipe.SYBE_X7.q(), top.tile_fetcher.BAKE_SCX7.q(), _BYCA_MAP_X3C);

    // Background map read
    {
      /*p26.AXAD*/ wire _AXAD_WIN_MODEn = not1(top.pix_pipe.PORE_WIN_MODEp());
      /*p27.NOGU*/ wire _NOGU_FETCH_01p = nand2(top.tile_fetcher.NAKO_BFETCH_S1n(), top.tile_fetcher.NOFU_BFETCH_S2n());
      /*p27.NENY*/ wire _NENY_FETCH_01n = not1(_NOGU_FETCH_01p);
      /*p27.POTU*/ wire _POTU_BG_MAP_READp = and2(top.tile_fetcher.LENA_BGW_VRM_RDp(), _NENY_FETCH_01n);
      /*p26.ACEN*/ wire _ACEN_BG_MAP_READp = and2(_POTU_BG_MAP_READp, _AXAD_WIN_MODEn);
      /*p26.BAFY*/ BAFY_BG_MAP_READn = not1(_ACEN_BG_MAP_READp);
      /*p26.AXEP*/ _VRAM_BUS_A00 = tribuf_6n(BAFY_BG_MAP_READn, _BABE_MAP_X0S);
      /*p26.AFEB*/ _VRAM_BUS_A01 = tribuf_6n(BAFY_BG_MAP_READn, _ABOD_MAP_X1S);
      /*p26.ALEL*/ _VRAM_BUS_A02 = tribuf_6n(BAFY_BG_MAP_READn, _BEWY_MAP_X2S);
      /*p26.COLY*/ _VRAM_BUS_A03 = tribuf_6n(BAFY_BG_MAP_READn, _BYCA_MAP_X3S);
      /*p26.AJAN*/ _VRAM_BUS_A04 = tribuf_6n(BAFY_BG_MAP_READn, _ACUL_MAP_X4S);
      /*p26.DUHO*/ _VRAM_BUS_A05 = tribuf_6n(BAFY_BG_MAP_READn, _ETAM_MAP_Y0S);
      /*p26.CASE*/ _VRAM_BUS_A06 = tribuf_6n(BAFY_BG_MAP_READn, _DOTO_MAP_Y1S);
      /*p26.CYPO*/ _VRAM_BUS_A07 = tribuf_6n(BAFY_BG_MAP_READn, _DABA_MAP_Y2S);

      /*p26.CETA*/ _VRAM_BUS_A08 = tribuf_6n(BAFY_BG_MAP_READn, _EFYK_MAP_Y3S);
      /*p26.DAFE*/ _VRAM_BUS_A09 = tribuf_6n(BAFY_BG_MAP_READn, _EJOK_MAP_Y4S);
      /*p26.AMUV*/ _VRAM_BUS_A10 = tribuf_6n(BAFY_BG_MAP_READn, top.pix_pipe.XAFO_LCDC_BGMAP.q());
      /*p26.COVE*/ _VRAM_BUS_A11 = tribuf_6n(BAFY_BG_MAP_READn, 1);
      /*p26.COXO*/ _VRAM_BUS_A12 = tribuf_6n(BAFY_BG_MAP_READn, 1);

      // 0b10011000 00000000
    }

    // Window map read
    {
      /*p27.NOCU*/ wire NOCU_WIN_MODEn = not1(top.pix_pipe._PYNU_WIN_MODE_A.q());
      /*p27.PORE*/ wire PORE_WIN_MODEp = not1(NOCU_WIN_MODEn);
      /*p27.NAKO*/ wire NAKO_BFETCH_S1n = not1(top.tile_fetcher._MESU_BFETCH_S1.q());
      /*p27.NOFU*/ wire NOFU_BFETCH_S2n = not1(top.tile_fetcher._NYVA_BFETCH_S2.q());

      /*p27.NOGU*/ wire _NOGU_FETCH_01p = nand2(NAKO_BFETCH_S1n, NOFU_BFETCH_S2n);
      /*p27.NENY*/ wire _NENY_FETCH_01n = not1(_NOGU_FETCH_01p);

      /*p27.LUSU*/ wire LUSU_BGW_VRAM_RDn = not1(top.tile_fetcher._LONY_BG_READ_VRAM_LATCHp.q());
      /*p27.LENA*/ wire LENA_BGW_VRM_RDp = not1(LUSU_BGW_VRAM_RDn);

      /*p27.POTU*/ wire _POTU_BG_MAP_READp = and2(LENA_BGW_VRM_RDp, _NENY_FETCH_01n);
      /*p25.XEZE*/ wire _XEZE_WIN_MAP_READp = and2(_POTU_BG_MAP_READp, PORE_WIN_MODEp);
      /*p25.WUKO*/ WUKO_WIN_MAP_READn = not1(_XEZE_WIN_MAP_READp);
      /*p27.XEJA*/ _VRAM_BUS_A00 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.WYKA_WIN_X3());
      /*p27.XAMO*/ _VRAM_BUS_A01 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.WODY_WIN_X4());
      /*p27.XAHE*/ _VRAM_BUS_A02 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.WOBO_WIN_X5());
      /*p27.XULO*/ _VRAM_BUS_A03 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.WYKO_WIN_X6());
      /*p27.WUJU*/ _VRAM_BUS_A04 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.XOLO_WIN_X7());
      /*p27.VYTO*/ _VRAM_BUS_A05 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.TUFU_WIN_Y3());
      /*p27.VEHA*/ _VRAM_BUS_A06 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.TAXA_WIN_Y4());
      /*p27.VACE*/ _VRAM_BUS_A07 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.TOZO_WIN_Y5());
      /*p27.VOVO*/ _VRAM_BUS_A08 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.TATE_WIN_Y6());
      /*p27.VULO*/ _VRAM_BUS_A09 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.TEKE_WIN_Y7());
      /*p27.VEVY*/ _VRAM_BUS_A10 = tribuf_6n(WUKO_WIN_MAP_READn, top.pix_pipe.WOKY_LCDC_WINMAP.q());
      /*p27.VEZA*/ _VRAM_BUS_A11 = tribuf_6n(WUKO_WIN_MAP_READn, 1);
      /*p27.VOGU*/ _VRAM_BUS_A12 = tribuf_6n(WUKO_WIN_MAP_READn, 1);
    }

    // Background/window tile read
    {
#if 0

      BEBU_SCAN_DONE_TRIGn   = and2(!_BALU_LINE_RSTp, BYBA_SCAN_DONE_A(), !DOBA_SCAN_DONE_B());
      NYXU_TILE_FETCHER_RSTn = nor4(BEBU_SCAN_DONE_TRIGn, NUNY_WX_MATCHpe, TEVO_FINE_RSTp);
      LONY_BG_READ_VRAM_LATCHp = nand_latch(NYXU_TILE_FETCHER_RSTn, and2(_LOVY_FETCH_DONEp.qn(), XYMU_RENDERINGp));

      NOGU_FETCH_01p      = or2(MESU_BFETCH_S1.q(), NYVA_BFETCH_S2.q());
      XUCY_WIN_TILE_READn = nand2(LONY_BG_READ_VRAM_LATCHp, NOGU_FETCH_01p, PYNU_WIN_MODE_A);

#endif

      /*p27.NAKO*/ wire NAKO_BFETCH_S1n = not1(top.tile_fetcher._MESU_BFETCH_S1.q());
      /*p27.NOFU*/ wire NOFU_BFETCH_S2n = not1(top.tile_fetcher._NYVA_BFETCH_S2.q());
      /*p27.NOCU*/ wire NOCU_WIN_MODEn = not1(top.pix_pipe._PYNU_WIN_MODE_A.q());
      /*p27.PORE*/ wire PORE_WIN_MODEp = not1(NOCU_WIN_MODEn);
      /*p26.AXAD*/ wire _AXAD_WIN_MODEn = not1(PORE_WIN_MODEp);

      /*p27.NOGU*/ wire _NOGU_FETCH_01p = nand2(NAKO_BFETCH_S1n, NOFU_BFETCH_S2n);
      /*p27.XUHA*/ wire _XUHA_FETCH_S2p  = not1(NOFU_BFETCH_S2n);

      /*p27.LUSU*/ wire LUSU_BGW_VRAM_RDn = not1(top.tile_fetcher._LONY_BG_READ_VRAM_LATCHp.q());
      /*p27.LENA*/ wire LENA_BGW_VRM_RDp = not1(LUSU_BGW_VRAM_RDn);

      /*p27.NETA*/ NETA_TILE_READp = and2(LENA_BGW_VRM_RDp, _NOGU_FETCH_01p);
      /*p26.ASUL*/ ASUL_TILE_READp = and2(NETA_TILE_READp, _AXAD_WIN_MODEn);
      /*p26.BEJE*/ BEJE_BGD_TILE_READn = not1(ASUL_TILE_READp);


      /*p25.XUCY*/ XUCY_WIN_TILE_READn = nand2(NETA_TILE_READp, PORE_WIN_MODEp);
      /*p25.VUZA*/ VUZA_TILE_BANKp = nor2(top.pix_pipe.WEXU_LCDC_BGTILE.q(), top.vram_bus.PYJU_TILE_DB7.q()); // register reused
      
      /*p26.ASUM*/ _VRAM_BUS_A00 = tribuf_6n(BEJE_BGD_TILE_READn, _XUHA_FETCH_S2p);
      /*p26.EVAD*/ _VRAM_BUS_A01 = tribuf_6n(BEJE_BGD_TILE_READn, _FAFO_TILE_Y0S);
      /*p26.DAHU*/ _VRAM_BUS_A02 = tribuf_6n(BEJE_BGD_TILE_READn, _EMUX_TILE_Y1S);
      /*p26.DODE*/ _VRAM_BUS_A03 = tribuf_6n(BEJE_BGD_TILE_READn, _ECAB_TILE_Y2S);

      /*p25.XONU*/ _VRAM_BUS_A00 = tribuf_6n(XUCY_WIN_TILE_READn, _XUHA_FETCH_S2p);
      /*p25.WUDO*/ _VRAM_BUS_A01 = tribuf_6n(XUCY_WIN_TILE_READn, top.pix_pipe.VYNO_WIN_Y0());
      /*p25.WAWE*/ _VRAM_BUS_A02 = tribuf_6n(XUCY_WIN_TILE_READn, top.pix_pipe.VUJO_WIN_Y1());
      /*p25.WOLU*/ _VRAM_BUS_A03 = tribuf_6n(XUCY_WIN_TILE_READn, top.pix_pipe.VYMU_WIN_Y2());

      /*p25.VAPY*/ _VRAM_BUS_A04 = tribuf_6p(NETA_TILE_READp, RAWU_TILE_DB0.q());
      /*p25.SEZU*/ _VRAM_BUS_A05 = tribuf_6p(NETA_TILE_READp, POZO_TILE_DB1.q());
      /*p25.VEJY*/ _VRAM_BUS_A06 = tribuf_6p(NETA_TILE_READp, PYZO_TILE_DB2.q());
      /*p25.RUSA*/ _VRAM_BUS_A07 = tribuf_6p(NETA_TILE_READp, POXA_TILE_DB3.q());
      /*p25.ROHA*/ _VRAM_BUS_A08 = tribuf_6p(NETA_TILE_READp, PULO_TILE_DB4.q());
      /*p25.RESO*/ _VRAM_BUS_A09 = tribuf_6p(NETA_TILE_READp, POJU_TILE_DB5.q());
      /*p25.SUVO*/ _VRAM_BUS_A10 = tribuf_6p(NETA_TILE_READp, POWY_TILE_DB6.q());
      /*p25.TOBO*/ _VRAM_BUS_A11 = tribuf_6p(NETA_TILE_READp, PYJU_TILE_DB7.q());
      /*p25.VURY*/ _VRAM_BUS_A12 = tribuf_6p(NETA_TILE_READp, VUZA_TILE_BANKp);
    }
  }

  // VRAM addr bus -> VRAM addr pin
  {
    /*p25.MYFU*/ wire _MYFU = not1(_VRAM_BUS_A00.q());
    /*p25.MASA*/ wire _MASA = not1(_VRAM_BUS_A01.q());
    /*p25.MYRE*/ wire _MYRE = not1(_VRAM_BUS_A02.q());
    /*p25.MAVU*/ wire _MAVU = not1(_VRAM_BUS_A03.q());
    /*p25.MEPA*/ wire _MEPA = not1(_VRAM_BUS_A04.q());
    /*p25.MYSA*/ wire _MYSA = not1(_VRAM_BUS_A05.q());
    /*p25.MEWY*/ wire _MEWY = not1(_VRAM_BUS_A06.q());
    /*p25.MUME*/ wire _MUME = not1(_VRAM_BUS_A07.q());
    /*p25.VOVA*/ wire _VOVA = not1(_VRAM_BUS_A08.q());
    /*p25.VODE*/ wire _VODE = not1(_VRAM_BUS_A09.q());
    /*p25.RUKY*/ wire _RUKY = not1(_VRAM_BUS_A10.q());
    /*p25.RUMA*/ wire _RUMA = not1(_VRAM_BUS_A11.q());
    /*p25.REHO*/ wire _REHO = not1(_VRAM_BUS_A12.q());

    /*p25.LEXE*/ _VRAM_PIN_A00 = _MYFU;
    /*p25.LOZU*/ _VRAM_PIN_A01 = _MASA;
    /*p25.LACA*/ _VRAM_PIN_A02 = _MYRE;
    /*p25.LUVO*/ _VRAM_PIN_A03 = _MAVU;
    /*p25.LOLY*/ _VRAM_PIN_A04 = _MEPA;
    /*p25.LALO*/ _VRAM_PIN_A05 = _MYSA;
    /*p25.LEFA*/ _VRAM_PIN_A06 = _MEWY;
    /*p25.LUBY*/ _VRAM_PIN_A07 = _MUME;
    /*p25.TUJY*/ _VRAM_PIN_A08 = _VOVA;
    /*p25.TAGO*/ _VRAM_PIN_A09 = _VODE;
    /*p25.NUVA*/ _VRAM_PIN_A10 = _RUKY;
    /*p25.PEDU*/ _VRAM_PIN_A11 = _RUMA;
    /*p25.PONY*/ _VRAM_PIN_A12 = _REHO;
  }

  //----------------------------------------
  // VRAM data out

  // CPU bus -> VRAM bus -> VRAM pin
  {
#if 0
    CBUS_TO_VPIN = and2(SOSE_8000_9FFFp, CPU_PIN_WRp, SOSE_8000_9FFFp, !CPU_PIN_ADDR_EXT, !RENDERING);
#endif

    /*p25.TAVY*/ wire _TAVY_MOEp = not1(_VRAM_PIN_OE_C.q());
    /*p25.TEGU*/ wire TEGU_CPU_VRAM_WRn = nand2(SOSE_8000_9FFFp, top.cpu_bus.CPU_PIN_WRp.q());  // Schematic wrong, second input is CPU_PIN_WRp
    /*p25.SALE*/ wire _SALE_CPU_VRAM_WRn = mux2_p(_TAVY_MOEp, TEGU_CPU_VRAM_WRn, top.clk_reg.TUTO_DBG_VRAMp());

    /*p25.TUCA*/ wire _TUCA_CPU_VRAM_AVn = and2(SOSE_8000_9FFFp, top.ABUZ_AVn());
    /*p25.TEFY*/ wire _TEFY_VRAM_MCSp = not1(_VRAM_PIN_CS_C.q());
    /*p25.TOLE*/ wire _TOLE_VRAM_AVn     = mux2_p(_TEFY_VRAM_MCSp, _TUCA_CPU_VRAM_AVn, top.clk_reg.TUTO_DBG_VRAMp());
    /*p25.SERE*/ wire _SERE = and2(_TOLE_VRAM_AVn, top.pix_pipe.ROPY_RENDERINGn());
    /*p25.RUVY*/ wire _RUVY_VRAM_WRp = not1(_SALE_CPU_VRAM_WRn);
    /*p25.SAZO*/ wire _SAZO_CBD_TO_VPDp = and2(_RUVY_VRAM_WRp, _SERE);
    /*p25.RYJE*/ wire _RYJE_CBD_TO_VPDn = not1(_SAZO_CBD_TO_VPDp);
    /*p25.REVO*/ wire _REVO_CBD_TO_VPDp = not1(_RYJE_CBD_TO_VPDn);
    /*p25.ROCY*/ wire _ROCY_CBD_TO_VPDp = and2(_REVO_CBD_TO_VPDp, _SAZO_CBD_TO_VPDp);
    /*p25.RAHU*/ wire _RAHU_CBD_TO_VPDn = not1(_ROCY_CBD_TO_VPDp);

    /*p25.TEME*/ _VRAM_BUS_D0 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D0.q());
    /*p25.TEWU*/ _VRAM_BUS_D1 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D1.q());
    /*p25.TYGO*/ _VRAM_BUS_D2 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D2.q());
    /*p25.SOTE*/ _VRAM_BUS_D3 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D3.q());
    /*p25.SEKE*/ _VRAM_BUS_D4 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D4.q());
    /*p25.RUJO*/ _VRAM_BUS_D5 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D5.q());
    /*p25.TOFA*/ _VRAM_BUS_D6 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D6.q());
    /*p25.SUZA*/ _VRAM_BUS_D7 = tribuf_10n(_RAHU_CBD_TO_VPDn, top.cpu_bus.CPU_BUS_D7.q());

    {
      /*p25.ROVE*/ wire _ROVE_CBUS_TO_VPINp = not1(_RAHU_CBD_TO_VPDn);
      /*p25.SEFA*/ wire _SEFA = and2(_VRAM_BUS_D0.q(), _ROVE_CBUS_TO_VPINp);
      /*p25.SOGO*/ wire _SOGO = and2(_VRAM_BUS_D1.q(), _ROVE_CBUS_TO_VPINp);
      /*p25.SEFU*/ wire _SEFU = and2(_VRAM_BUS_D2.q(), _ROVE_CBUS_TO_VPINp);
      /*p25.SUNA*/ wire _SUNA = and2(_VRAM_BUS_D3.q(), _ROVE_CBUS_TO_VPINp);
      /*p25.SUMO*/ wire _SUMO = and2(_VRAM_BUS_D4.q(), _ROVE_CBUS_TO_VPINp);
      /*p25.SAZU*/ wire _SAZU = and2(_VRAM_BUS_D5.q(), _ROVE_CBUS_TO_VPINp);
      /*p25.SAMO*/ wire _SAMO = and2(_VRAM_BUS_D6.q(), _ROVE_CBUS_TO_VPINp);
      /*p25.SUKE*/ wire _SUKE = and2(_VRAM_BUS_D7.q(), _ROVE_CBUS_TO_VPINp);

      /*p25.REGE*/ wire _REGE = not1(_SEFA);
      /*p25.RYKY*/ wire _RYKY = not1(_SOGO);
      /*p25.RAZO*/ wire _RAZO = not1(_SEFU);
      /*p25.RADA*/ wire _RADA = not1(_SUNA);
      /*p25.RYRO*/ wire _RYRO = not1(_SUMO);
      /*p25.REVU*/ wire _REVU = not1(_SAZU);
      /*p25.REKU*/ wire _REKU = not1(_SAMO);
      /*p25.RYZE*/ wire _RYZE = not1(_SUKE);

      _VRAM_PIN_D0_A = _REGE;
      _VRAM_PIN_D1_A = _RYKY;
      _VRAM_PIN_D2_A = _RAZO;
      _VRAM_PIN_D3_A = _RADA;
      _VRAM_PIN_D4_A = _RYRO;
      _VRAM_PIN_D5_A = _REVU;
      _VRAM_PIN_D6_A = _REKU;
      _VRAM_PIN_D7_A = _RYZE;
    }

    {
      /*p25.RELA*/ wire _RELA_VRM_TO_CPUn = or2(_REVO_CBD_TO_VPDp, _SAZO_CBD_TO_VPDp);
      /*p25.RENA*/ wire _RENA_VRM_TO_CPUp = not1(_RELA_VRM_TO_CPUn);
      /*p25.ROFA*/ wire _ROFA_VRM_TO_CPUn = not1(_RENA_VRM_TO_CPUp);
      _VRAM_PIN_D0_B = _ROFA_VRM_TO_CPUn;
      _VRAM_PIN_D1_B = _ROFA_VRM_TO_CPUn;
      _VRAM_PIN_D2_B = _ROFA_VRM_TO_CPUn;
      _VRAM_PIN_D3_B = _ROFA_VRM_TO_CPUn;
      _VRAM_PIN_D4_B = _ROFA_VRM_TO_CPUn;
      _VRAM_PIN_D5_B = _ROFA_VRM_TO_CPUn;
      _VRAM_PIN_D6_B = _ROFA_VRM_TO_CPUn;
      _VRAM_PIN_D7_B = _ROFA_VRM_TO_CPUn;
    }

    {
      /*p25.SYNU*/ wire _SYNU = or2(_VRAM_BUS_D0.q(), _RAHU_CBD_TO_VPDn);
      /*p25.SYMA*/ wire _SYMA = or2(_VRAM_BUS_D1.q(), _RAHU_CBD_TO_VPDn);
      /*p25.ROKO*/ wire _ROKO = or2(_VRAM_BUS_D2.q(), _RAHU_CBD_TO_VPDn);
      /*p25.SYBU*/ wire _SYBU = or2(_VRAM_BUS_D3.q(), _RAHU_CBD_TO_VPDn);
      /*p25.SAKO*/ wire _SAKO = or2(_VRAM_BUS_D4.q(), _RAHU_CBD_TO_VPDn);
      /*p25.SEJY*/ wire _SEJY = or2(_VRAM_BUS_D5.q(), _RAHU_CBD_TO_VPDn);
      /*p25.SEDO*/ wire _SEDO = or2(_VRAM_BUS_D6.q(), _RAHU_CBD_TO_VPDn);
      /*p25.SAWU*/ wire _SAWU = or2(_VRAM_BUS_D7.q(), _RAHU_CBD_TO_VPDn);

      /*p25.RURA*/ wire _RURA = not1(_SYNU);
      /*p25.RULY*/ wire _RULY = not1(_SYMA);
      /*p25.RARE*/ wire _RARE = not1(_ROKO);
      /*p25.RODU*/ wire _RODU = not1(_SYBU);
      /*p25.RUBE*/ wire _RUBE = not1(_SAKO);
      /*p25.RUMU*/ wire _RUMU = not1(_SEJY);
      /*p25.RYTY*/ wire _RYTY = not1(_SEDO);
      /*p25.RADY*/ wire _RADY = not1(_SAWU);

      _VRAM_PIN_D0_D = _RURA;
      _VRAM_PIN_D1_D = _RULY;
      _VRAM_PIN_D2_D = _RARE;
      _VRAM_PIN_D3_D = _RODU;
      _VRAM_PIN_D4_D = _RUBE;
      _VRAM_PIN_D5_D = _RUMU;
      _VRAM_PIN_D6_D = _RYTY;
      _VRAM_PIN_D7_D = _RADY;
    }
  }

  //----------------------------------------
  // VRAM data in

  // VRAM pin -> VRAM tri
  {
#if 0
   
    VPD_TO_VBD = !and(CPU_PIN_WRp, SOSE_8000_9FFFp, !CPU_PIN_ADDR_EXT, ROPY_RENDERINGn);

#endif

    /*p25.TAVY*/ wire _TAVY_MOEp = not1(_VRAM_PIN_OE_C.q());
    /*p25.TEGU*/ wire TEGU_CPU_VRAM_WRn = nand2(SOSE_8000_9FFFp, top.cpu_bus.CPU_PIN_WRp.q());  // Schematic wrong, second input is CPU_PIN_WRp
    /*p25.SALE*/ wire _SALE_VRAM_WRn = mux2_p(_TAVY_MOEp, TEGU_CPU_VRAM_WRn, top.clk_reg.TUTO_DBG_VRAMp());

    /*p25.TUCA*/ wire _TUCA_CPU_VRAM_RDp = and2(SOSE_8000_9FFFp, top.ABUZ_AVn());
    /*p25.TEFY*/ wire _TEFY_VRAM_MCSp = not1(_VRAM_PIN_CS_C.q());
    /*p25.TOLE*/ wire _TOLE_VRAM_RDp     = mux2_p(_TEFY_VRAM_MCSp, _TUCA_CPU_VRAM_RDp, top.clk_reg.TUTO_DBG_VRAMp());
    /*p25.SERE*/ wire _SERE_CPU_VRM_RDp = and2(_TOLE_VRAM_RDp, top.pix_pipe.ROPY_RENDERINGn());
    /*p25.RUVY*/ wire _RUVY_VRAM_WR = not1(_SALE_VRAM_WRn);
    /*p25.SAZO*/ wire _SAZO_VRAM_RD = and2(_RUVY_VRAM_WR, _SERE_CPU_VRM_RDp);
    /*p25.RYJE*/ wire _RYJE_VRAM_RDn = not1(_SAZO_VRAM_RD);
    /*p25.REVO*/ wire _REVO_VRAM_RDp = not1(_RYJE_VRAM_RDn);
    /*p25.RELA*/ wire _RELA_VPD_TO_VBDn = or2(_REVO_VRAM_RDp, _SAZO_VRAM_RD);
    /*p25.RENA*/ wire _RENA_VPD_TO_VBDp = not1(_RELA_VPD_TO_VBDn);

    /*p25.RODY*/ _VRAM_BUS_D0 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D0_C.q());
    /*p25.REBA*/ _VRAM_BUS_D1 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D1_C.q());
    /*p25.RYDO*/ _VRAM_BUS_D2 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D2_C.q());
    /*p25.REMO*/ _VRAM_BUS_D3 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D3_C.q());
    /*p25.ROCE*/ _VRAM_BUS_D4 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D4_C.q());
    /*p25.ROPU*/ _VRAM_BUS_D5 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D5_C.q());
    /*p25.RETA*/ _VRAM_BUS_D6 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D6_C.q());
    /*p25.RAKU*/ _VRAM_BUS_D7 = tribuf_6p(_RENA_VPD_TO_VBDp, _VRAM_PIN_D7_C.q());
  }

  // VRAM tri -> cpu bus
  {
#if 0


    if (RENDERING) {
      VRAM_BUS_D0 = VRAM_PIN_D0_C;
      CPU_BUS_D0  = Z;
    }
    else {
      VPD_TO_VBD = !and(CPU_PIN_WRp, ADDR_VRAM, !CPU_PIN_ADDR_EXT);
      VBD_TO_CBD =  and2(CPU_PIN_RDp, ADDR_VRAM, !CPU_PIN_ADDR_EXT, CPU_PIN_HOLD_MEM);

      VRAM_BUS_D0 = tribuf_6p(VPD_TO_VBD, VRAM_PIN_D0_C);
      CPU_BUS_D0  = tribuf_6p(VBD_TO_CBD, !VRAM_BUS_D0);
    }


    VPD_TO_VBD = !and(CPU_PIN_WRp, ADDR_VRAM, !CPU_PIN_ADDR_EXT, ROPY_RENDERINGn);
    VBD_TO_CBD =  and2(CPU_PIN_RDp, ADDR_VRAM, !CPU_PIN_ADDR_EXT, ROPY_RENDERINGn, CPU_PIN_HOLD_MEM);

    VRAM_BUS_D0 = tribuf_6p(VPD_TO_VBD, VRAM_PIN_D0_C);
    CPU_BUS_D0  = tribuf_6p(VBD_TO_CBD, !VRAM_BUS_D0);
    
#endif

    /*p04.DECY*/ wire DECY = not1(top.cpu_bus.CPU_PIN_HOLD_MEM.q());
    /*p04.CATY*/ wire CATY = not1(DECY);

    /*p07.UJYV*/ wire UJYV_CPU_RDn = mux2_n(top.ext_bus.EXT_PIN_RD_C.q(), top.cpu_bus.CPU_PIN_RDp.q(), top.clk_reg.UNOR_MODE_DBG2p());
    /*p07.TEDO*/ wire TEDO_CPU_RDp = not1(UJYV_CPU_RDn);
    /*p07.AJAS*/ wire AJAS_CPU_RDn = not1(TEDO_CPU_RDp);
    /*p07.ASOT*/ wire ASOT_CPU_RDp = not1(AJAS_CPU_RDn);
    /*p28.MYNU*/ wire MYNU_CPU_RDn = nand2(ASOT_CPU_RDp, CATY);
    /*p28.LEKO*/ wire LEKO_CPU_RDp = not1(MYNU_CPU_RDn);

    /*p25.TUCA*/ wire _TUCA_CPU_VRAM_RDp = and2(SOSE_8000_9FFFp, top.ABUZ_AVn());
    /*p25.TEFY*/ wire _TEFY_VRAM_MCSp = not1(_VRAM_PIN_CS_C.q());
    /*p25.TOLE*/ wire _TOLE_VRAM_RDp     = mux2_p(_TEFY_VRAM_MCSp, _TUCA_CPU_VRAM_RDp, top.clk_reg.TUTO_DBG_VRAMp());
    /*p25.SERE*/ wire _SERE_CPU_VRM_RDp = and2(_TOLE_VRAM_RDp, top.pix_pipe.ROPY_RENDERINGn());
    /*p25.TYVY*/ wire _TYVY_VBD_TO_CBDn = nand2(_SERE_CPU_VRM_RDp, LEKO_CPU_RDp);
    /*p25.SEBY*/ wire _SEBY_VBD_TO_CBDp = not1(_TYVY_VBD_TO_CBDn);

    /*p25.RERY*/ wire _RERY_VBUS_D0 = not1(_VRAM_BUS_D0.q());
    /*p25.RUNA*/ wire _RUNA_VBUS_D1 = not1(_VRAM_BUS_D1.q());
    /*p25.RONA*/ wire _RONA_VBUS_D2 = not1(_VRAM_BUS_D2.q());
    /*p25.RUNO*/ wire _RUNO_VBUS_D3 = not1(_VRAM_BUS_D3.q());
    /*p25.SANA*/ wire _SANA_VBUS_D4 = not1(_VRAM_BUS_D4.q());
    /*p25.RORO*/ wire _RORO_VBUS_D5 = not1(_VRAM_BUS_D5.q());
    /*p25.RABO*/ wire _RABO_VBUS_D6 = not1(_VRAM_BUS_D6.q());
    /*p25.SAME*/ wire _SAME_VBUS_D7 = not1(_VRAM_BUS_D7.q());

    /*p25.RUGA*/ top.cpu_bus.CPU_BUS_D0 = tribuf_6p(_SEBY_VBD_TO_CBDp, _RERY_VBUS_D0);
    /*p25.ROTA*/ top.cpu_bus.CPU_BUS_D1 = tribuf_6p(_SEBY_VBD_TO_CBDp, _RUNA_VBUS_D1);
    /*p25.RYBU*/ top.cpu_bus.CPU_BUS_D2 = tribuf_6p(_SEBY_VBD_TO_CBDp, _RONA_VBUS_D2);
    /*p25.RAJU*/ top.cpu_bus.CPU_BUS_D3 = tribuf_6p(_SEBY_VBD_TO_CBDp, _RUNO_VBUS_D3);
    /*p25.TYJA*/ top.cpu_bus.CPU_BUS_D4 = tribuf_6p(_SEBY_VBD_TO_CBDp, _SANA_VBUS_D4);
    /*p25.REXU*/ top.cpu_bus.CPU_BUS_D5 = tribuf_6p(_SEBY_VBD_TO_CBDp, _RORO_VBUS_D5);
    /*p25.RUPY*/ top.cpu_bus.CPU_BUS_D6 = tribuf_6p(_SEBY_VBD_TO_CBDp, _RABO_VBUS_D6);
    /*p25.TOKU*/ top.cpu_bus.CPU_BUS_D7 = tribuf_6p(_SEBY_VBD_TO_CBDp, _SAME_VBUS_D7);
  }

  // VRAM tri -> tile pix temp
  {
    /*p32.METE*/ wire _METE_LATCH_TILE_DAn = not1(top.tile_fetcher.NYDY_LATCH_TILE_DAp());
    /*p32.LOMA*/ wire _LOMA_LATCH_TILE_DAp = not1(_METE_LATCH_TILE_DAn);

    // This one also looks like the input is inverted.... or something else is inverted somewhere.
    /*p32.LEGU*/ top.vram_bus.LEGU_TILE_DA0 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D0.q());
    /*p32.NUDU*/ top.vram_bus.NUDU_TILE_DA1 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D1.q());
    /*p32.MUKU*/ top.vram_bus.MUKU_TILE_DA2 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D2.q());
    /*p32.LUZO*/ top.vram_bus.LUZO_TILE_DA3 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D3.q());
    /*p32.MEGU*/ top.vram_bus.MEGU_TILE_DA4 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D4.q());
    /*p32.MYJY*/ top.vram_bus.MYJY_TILE_DA5 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D5.q());
    /*p32.NASA*/ top.vram_bus.NASA_TILE_DA6 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D6.q());
    /*p32.NEFO*/ top.vram_bus.NEFO_TILE_DA7 = dff8_A(_LOMA_LATCH_TILE_DAp, !_LOMA_LATCH_TILE_DAp, _VRAM_BUS_D7.q());

    // Why are the clocks swapped?
    /*p32.LESO*/ wire _LESO_LATCH_TILE_DBp = not1(top.tile_fetcher.MOFU_LATCH_TILE_DBn());
    /*p??.LUVE*/ wire _LUVE_MATCH_TILE_DBn = not1(_LESO_LATCH_TILE_DBp); // Schematic wrong, was labeled AJAR
    /*p32.LABU*/ wire _LABU_LATCH_TILE_DBp = not1(_LUVE_MATCH_TILE_DBn);

    // This is the only block of "dff11" on the chip, is there an extra inverter applied to the D input?
    /*p32.RAWU*/ top.vram_bus.RAWU_TILE_DB0 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D0.q());
    /*p32.POZO*/ top.vram_bus.POZO_TILE_DB1 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D1.q());
    /*p32.PYZO*/ top.vram_bus.PYZO_TILE_DB2 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D2.q());
    /*p32.POXA*/ top.vram_bus.POXA_TILE_DB3 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D3.q());
    /*p32.PULO*/ top.vram_bus.PULO_TILE_DB4 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D4.q());
    /*p32.POJU*/ top.vram_bus.POJU_TILE_DB5 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D5.q());
    /*p32.POWY*/ top.vram_bus.POWY_TILE_DB6 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D6.q());
    /*p32.PYJU*/ top.vram_bus.PYJU_TILE_DB7 = dff11_A(_LABU_LATCH_TILE_DBp, _LUVE_MATCH_TILE_DBn, 0, _VRAM_BUS_D7.q());
  }

  // VRAM tri -> sprite pix temp + x flip
  {
    /*p29.XONO*/ wire _XONO_FLIP_X = and2(top.oam_bus.BAXO_OAM_DB5.q(), top.sprite_fetcher.TEXY_SPR_READ_VRAMp());
    /*p33.POBE*/ wire _POBE_FLIP0 = mux2_p(_VRAM_BUS_D7.q(), _VRAM_BUS_D0.q(), _XONO_FLIP_X);
    /*p33.PACY*/ wire _PACY_FLIP1 = mux2_p(_VRAM_BUS_D6.q(), _VRAM_BUS_D1.q(), _XONO_FLIP_X);
    /*p33.PONO*/ wire _PONO_FLIP2 = mux2_p(_VRAM_BUS_D5.q(), _VRAM_BUS_D2.q(), _XONO_FLIP_X);
    /*p33.PUGU*/ wire _PUGU_FLIP3 = mux2_p(_VRAM_BUS_D4.q(), _VRAM_BUS_D3.q(), _XONO_FLIP_X);
    /*p33.PUTE*/ wire _PUTE_FLIP4 = mux2_p(_VRAM_BUS_D3.q(), _VRAM_BUS_D4.q(), _XONO_FLIP_X);
    /*p33.PULY*/ wire _PULY_FLIP5 = mux2_p(_VRAM_BUS_D2.q(), _VRAM_BUS_D5.q(), _XONO_FLIP_X);
    /*p33.PELO*/ wire _PELO_FLIP6 = mux2_p(_VRAM_BUS_D1.q(), _VRAM_BUS_D6.q(), _XONO_FLIP_X);
    /*p33.PAWE*/ wire _PAWE_FLIP7 = mux2_p(_VRAM_BUS_D0.q(), _VRAM_BUS_D7.q(), _XONO_FLIP_X);

    /*p29.PEBY*/ wire _PEBY_CLKp = not1(top.sprite_fetcher.RACA_LATCH_SPPIXB());
    /*p29.NYBE*/ wire _NYBE_CLKn = not1(_PEBY_CLKp);
    /*p29.PUCO*/ wire _PUCO_CLKp = not1(_NYBE_CLKn);

    /*p33.PEFO*/ top.vram_bus.PEFO_SPRITE_DA0 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _POBE_FLIP0);
    /*p33.ROKA*/ top.vram_bus.ROKA_SPRITE_DA1 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _PACY_FLIP1);
    /*p33.MYTU*/ top.vram_bus.MYTU_SPRITE_DA2 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _PONO_FLIP2);
    /*p33.RAMU*/ top.vram_bus.RAMU_SPRITE_DA3 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _PUGU_FLIP3);
    /*p33.SELE*/ top.vram_bus.SELE_SPRITE_DA4 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _PUTE_FLIP4);
    /*p33.SUTO*/ top.vram_bus.SUTO_SPRITE_DA5 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _PULY_FLIP5);
    /*p33.RAMA*/ top.vram_bus.RAMA_SPRITE_DA6 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _PELO_FLIP6);
    /*p33.RYDU*/ top.vram_bus.RYDU_SPRITE_DA7 = dff8_A(_PUCO_CLKp, !_PUCO_CLKp, _PAWE_FLIP7);

    /*p29.VYWA*/ wire _VYWA_CLKp = not1(top.sprite_fetcher.TOPU_LATCH_SPPIXA());
    /*p29.WENY*/ wire _WENY_CLKn = not1(_VYWA_CLKp);
    /*p29.XADO*/ wire _XADO_CLKp = not1(_WENY_CLKn);

    /*p33.REWO*/ top.vram_bus.REWO_SPRITE_DB0 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _POBE_FLIP0);
    /*p33.PEBA*/ top.vram_bus.PEBA_SPRITE_DB1 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _PACY_FLIP1);
    /*p33.MOFO*/ top.vram_bus.MOFO_SPRITE_DB2 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _PONO_FLIP2);
    /*p33.PUDU*/ top.vram_bus.PUDU_SPRITE_DB3 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _PUGU_FLIP3);
    /*p33.SAJA*/ top.vram_bus.SAJA_SPRITE_DB4 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _PUTE_FLIP4);
    /*p33.SUNY*/ top.vram_bus.SUNY_SPRITE_DB5 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _PULY_FLIP5);
    /*p33.SEMO*/ top.vram_bus.SEMO_SPRITE_DB6 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _PELO_FLIP6);
    /*p33.SEGA*/ top.vram_bus.SEGA_SPRITE_DB7 = dff8_A(_XADO_CLKp, !_XADO_CLKp, _PAWE_FLIP7);
  }
}

//------------------------------------------------------------------------------
