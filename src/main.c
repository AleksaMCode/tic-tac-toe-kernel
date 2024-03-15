#include <descriptor_tables.h>
#include <kb.h>
#include <tictactoe.h>

int main() {
  // Initialise all the ISRs and segmentation
  init_descriptor_tables();
  // Initialise the screen
  monitor_clear();
  reset_heap();

  // asm volatile("int $0x3");
  // asm volatile("int $0x4");

  asm volatile("sti");
  init_timer(50);
  keyboard_init();
  toPlayOrNotToPlay();
  asm volatile("jmp hang");
  return 0;
}
