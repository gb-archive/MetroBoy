#pragma once
#include "Types.h"

//-----------------------------------------------------------------------------

struct Cart {
  void reset(size_t new_rom_size);
  void reset();

  void on_ebus_req(Req ebus_req);
  void get_ebus_ack(Ack& ebus_ack);

  void dump(std::string& d);

  uint8_t* get_flat_ptr(uint16_t addr);
  size_t get_rom_size() const { return rom_size; }

  uint8_t* get_cram() { return ram_buf; }

private:
  Ack ack;
  size_t rom_size;
  int rom_bank_count;
  int ram_bank_count;
  bool ram_enable;
  bool ram_dirty;
  int mode;
  int bank_latch1;
  int bank_latch2;

  uint8_t ram_buf[8 * 1024];
};

//-----------------------------------------------------------------------------
