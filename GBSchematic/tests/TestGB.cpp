#include "TestGB.h"
#include "../pages/Sch_Decoder.h"

namespace Schematics {

template<typename T>
inline void phase_begin(T& first) { first.pwron(); }

template<typename T, typename... Args> inline void phase_begin_all(T& first, Args&... args) {
  phase_begin(first);
  phase_begin(args...);
}

//-----------------------------------------------------------------------------

TestGB::TestGB() {
  pwron();
}

//----------------------------------------

void TestGB::pwron() {
  sys_reg.pwron();
  clk_reg.pwron();
  rst_reg.pwron();
  dbg_reg.pwron();
  vclk_reg.pwron();
  vid_reg.pwron();
  lcd_reg.pwron();
  bus_tri.pwron();
  tim_reg.pwron();
  ser_reg.pwron();
}

//----------------------------------------
// This should put the GB in the same state as the boot sequence.

void TestGB::reset() {
  sys_reg.reset();
  clk_reg.reset();
  rst_reg.reset();
  dbg_reg.reset();
  vclk_reg.reset();
  vid_reg.reset();
  lcd_reg.reset();
  bus_tri.reset();
  tim_reg.reset();
  ser_reg.reset();
}

//----------------------------------------

void TestGB::phase_begin() {
  sys_reg.phase_begin();
  clk_reg.phase_begin();
  rst_reg.phase_begin();
  dbg_reg.phase_begin();
  vclk_reg.phase_begin();
  vid_reg.phase_begin();
  lcd_reg.phase_begin();
  bus_tri.phase_begin();
  tim_reg.phase_begin();
  ser_reg.phase_begin();
}

void TestGB::phase_end() {
  sys_reg.phase_end();
  clk_reg.phase_end();
  rst_reg.phase_end();
  dbg_reg.phase_end();
  vclk_reg.phase_end();
  vid_reg.phase_end();
  lcd_reg.phase_end();
  bus_tri.phase_end();
  tim_reg.phase_end();
  ser_reg.phase_end();
}

void TestGB::pass_begin() {
  sys_reg.pass_begin();
  clk_reg.pass_begin();
  rst_reg.pass_begin();
  dbg_reg.pass_begin();
  vclk_reg.pass_begin();
  vid_reg.pass_begin();
  lcd_reg.pass_begin();
  bus_tri.pass_begin();
  tim_reg.pass_begin();
  ser_reg.pass_begin();
}

bool TestGB::pass_end() {
  bool changed = false;
  changed |= sys_reg.pass_end();
  changed |= clk_reg.pass_end();
  changed |= rst_reg.pass_end();
  //changed |= dbg_reg.pass_end();
  changed |= vclk_reg.pass_end();
  changed |= vid_reg.pass_end();
  changed |= lcd_reg.pass_end();
  changed |= bus_tri.pass_end();
  changed |= tim_reg.pass_end();
  changed |= ser_reg.pass_end();
  return changed;
}

//-----------------------------------------------------------------------------

int TestGB::sim_phase(int phase_count) {
  int passes = 0;
  for (int p = 0; p < phase_count; p++) {
    phase_begin();
    passes += sim_pass();
    phase_end();
  }
  return passes;
}

int TestGB::sim_pass() {

  int done = 0;

  for (int pass = 0; pass < 32; pass++) {
    pass_begin();

    SysSignals     sys_sig  = sys_reg.signals();
    ClkSignals     clk_sig  = clk_reg.tick_slow(sys_sig);
    RstSignals     rst_sig  = rst_reg.tick_slow(sys_sig, clk_sig);
    VclkSignals    vclk_sig = vclk_reg.tick_slow(clk_sig, rst_sig);
    DecoderSignals dec_sig  = DecoderSignals::tick(sys_sig, clk_sig, bus_tri);
    BusSignals     bus_sig  = BusSignals::tick(sys_sig, clk_sig, bus_tri);
    LcdSignals     lcd_sig  = lcd_reg.tock_slow(vclk_sig, rst_sig);

    dbg_reg.tick(sys_sig, bus_sig, rst_sig, clk_sig, dec_sig, bus_tri);

    //bool MATCHn = sst_reg.tick_fetch(lcd_sig, spr_sig, vid_reg);


    //VidSignals vid_sig = vid_reg.tick(clk_sig, rst_sig, vclk_sig, joypad_pins, bus_sig, dec_sig, cart_pins, lcd_sig, sst_sig, bus_tri);
    //SpriteStoreSignals sst_sig = sst_reg.tick(clk_sig, rst_sig, lcd_sig, spr_sig, vid_sig, oam_sig);

    TimerSignals tim_sig  = tim_reg.tick(sys_sig, clk_sig, rst_sig, bus_sig, dec_sig, bus_tri);
    VidSignals2 vid_sig2 = vid_cfg.tick(sys_sig, rst_sig, bus_sig, dec_sig, bus_tri);
    SerialSignals ser_sig = ser_reg.tick(bus_sig, rst_sig, dec_sig, serial_pins, bus_tri);

    //SpriteSignals spr_sig = spr_reg.tick(clk_sig, vid_clk, rst_sig, joy_pins, dma_sig, lcd_sig,
    //                                     vid_reg2, vid_sig, sst_sig, oam_sig, oam_pins, sil_out);


    //PixelPipeSignals pxp_sig = pxp_reg.tick(vid_reg2, vram_bus,
    //        BG_LATCH, VRAM_TEMP_CLK, SPRITE_VRAM_LATCH_A, SPRITE_VRAM_LATCH_B, SPRITE_DONE, FLIP_X);

    //OamSignals oam_sig = oam_reg.tick(cpu, clk_sig, bus_sig, cart_pins, joy_pins, vid_clk, dec_sig,
    //                                  spr_sig, dma_sig, vid_sig, sil, vram_tri, bus_tri, oam_pins);


    //JoypadSignals joy_sig = joy_reg.tick(clk_sig, rst_sig, bus_sig, dbg_sig, dec_sig, joy_pins, bus_tri);


    //DmaSignals dma_sig = dma_reg.tick(cpu_sig, bus_sig, dec_sig, clk_sig, rst_sig, bus_tri);

    //InterruptRegisters int_regs;

    //InterruptSignals int_sig = int_reg.tick(bus_sig, cpu_sig, lcd_sig, ser_sig, joy_sig, vid_sig,
    //                                        tim_sig, joy_pins, rst_sig, dec_sig, bus_tri);



    bool changed = pass_end();
    if (!changed) {
      done++;
      if (done == 4) return pass;
    } else {
      if (done) {
        printf("unstable!\n");
        __debugbreak();
      }
    }
  }

  printf("Sim did not stabilize after 32 passes\n");
  __debugbreak();
  return 32;
}

//-----------------------------------------------------------------------------
// Boots the chip. Currently no idea if this is actually what the boot
// sequence really looks like, but it's vaguely plausible.

void TestGB::boot() {
  sim_phase(16);
  sys_reg.PIN_RST = false;
  sim_phase(16);
  sys_reg.PIN_CLK_GOOD = true;
  sim_phase(16);
  sys_reg.CPU_CLK_REQ = true;
  sim_phase(16);
  sys_reg.LCDC_EN = true;
  sim_phase(456*2*154 - 7);
}


//-----------------------------------------------------------------------------

};