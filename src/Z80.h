#pragma once
#include "Types.h"

//-----------------------------------------------------------------------------

struct alu_out {
  uint8_t x;
  uint8_t f;
};

struct Z80 {
  CpuOut reset(int new_model, uint16_t new_pc);
  CpuBus tick_t0(uint8_t imask, uint8_t intf, uint8_t mem_out);
  CpuOut tock_t2();

  uint16_t get_pc() const { return pc; }
  uint8_t  get_a()  const { return a; }
  uint8_t  get_op() const { return op_; }

  void dump(std::string& out);

  int model = 0;
  uint8_t int_ack_;
  uint8_t bus_data_;
  uint8_t imask_;
  uint8_t intf_;
  bool unhalt;

private:

  uint16_t mem_addr_;
  bool mem_read_;
  bool mem_write_;
  uint8_t mem_out_;

  // What's on the bus?
  enum MemTag {
    TAG_OPCODE,
    TAG_OPCODE_CB,
    TAG_ARG0,
    TAG_ARG1,

    TAG_DATA0,
    TAG_DATA1,

    TAG_NONE,
  };

  MemTag bus_tag, bus_tag_;
  uint16_t mem_addr;

  //----------

  enum Z80State {
    Z80_STATE_DECODE = 0,
    Z80_STATE_HALT,

    Z80_STATE_DELAY_A,

    Z80_STATE_MEM_READ1,
    Z80_STATE_MEM_READ2,
    Z80_STATE_MEM_READ3,

    Z80_STATE_DELAY_D,

    Z80_STATE_MEM_WRITE1,
    Z80_STATE_MEM_WRITE2,

    Z80_STATE_DECODE_CB,
    Z80_STATE_MEM_READ_CB,
    Z80_STATE_MEM_WRITE_CB,

    Z80_STATE_DELAY_B,
    Z80_STATE_DELAY_C,
  };

  Z80State state, state_;

#pragma warning(push)
#pragma warning(disable : 4201)
  // Registers
  union { uint16_t bc; struct { uint8_t c; uint8_t b; }; };
  union { uint16_t de; struct { uint8_t e; uint8_t d; }; };
  union { uint16_t hl; struct { uint8_t l; uint8_t h; }; };
  union { uint16_t af; struct { uint8_t f; uint8_t a; }; };
  union { uint16_t sp; struct { uint8_t p; uint8_t s; }; };
  uint16_t pc, pc_;
  uint8_t f_;

  union {
    struct {
      uint8_t data_lo;
      uint8_t data_hi;
    };
    uint16_t data16;
  };

  union {
    struct {
      uint8_t data_lo_;
      uint8_t data_hi_;
    };
    uint16_t data16_;
  };
#pragma warning(pop)

  // Signals

  uint16_t reg_in, reg_in_;

  uint8_t op_;
  uint8_t quad_;
  uint8_t row_;
  uint8_t col_;
  bool odd_row_;

  uint8_t cb_quad_;
  uint8_t cb_row_;
  uint8_t cb_col_;

  bool get_hl_;
  bool put_hl_;
  bool pop_d16_;
  bool push_d16_;
  bool fetch_d8_;
  bool fetch_d16_;
  bool any_read_;
  bool any_write_;
  bool take_branch_;

  // Interrupt stuff

  bool interrupt2;
  bool ime, ime_;
  bool ime_delay;

  uint8_t imask_latch;

  // Wires
  uint16_t alu_out_;

  // Misc

  uint32_t opcount;
  int cycle;

  //----------

private:

  void tick_decode();
  void tick_mem_read1();
  void tick_mem_read2();

  void tock_decode();

  void setup_decode();
  void setup_mem_write1();

  void tick_exec();
  void tick_exec_cb();

  uint8_t add2(uint8_t x, uint8_t z, uint8_t f);
  uint8_t adc2(uint8_t x, uint8_t z, uint8_t f);
};

//-----------------------------------------------------------------------------
