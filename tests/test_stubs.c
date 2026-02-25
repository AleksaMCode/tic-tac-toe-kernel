#include <common.h>
#include <monitor.h>

u32int test_last_alloc_size = 0;

void monitor_put(char c) { (void)c; }
void monitor_clear(void) {}
void monitor_write(const char *c) { (void)c; }
void monitor_write_dec(u32int n) { (void)n; }
void monitor_write_valn(char c, int n) {
  (void)c;
  (void)n;
}

char get_last_char(void) { return '0'; }

char *get_current_line(void) { return "unit-test"; }

void *allocate(u32int size) {
  static u8int fake_heap[1024];
  test_last_alloc_size = size;
  return fake_heap;
}
