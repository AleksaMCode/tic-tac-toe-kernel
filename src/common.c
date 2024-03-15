// common.h -- Defines typedefs and some global functions.
// From JamesM's kernel development tutorials.

#include <common.h>

extern void *allocate(u32int size);
// Write value to specified port
void outb(u16int port, u8int value) {
  asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

u8int inb(u16int port) {
  u8int ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

u16int inw(u16int port) {
  u16int ret;
  asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

void memcpy(u8int *dest, const u8int *src, u32int len) {
  for (; len != 0; len--)
    *dest++ = *src++;
}

void memset(u8int *dest, u8int val, u32int len) {
  u8int *temp = dest;
  for (; len != 0; len--)
    *temp++ = val;
}

// Compare two strings. Should return -1 if
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2) {
  int i = 0;
  int failed = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      failed = 1;
      break;
    }
    i++;
  }
  // why did the loop exit?
  if ((str1[i] == '\0' && str2[i] != '\0') ||
      (str1[i] != '\0' && str2[i] == '\0'))
    failed = 1;

  return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src) {
  char *destsave = dest;
  do {
    *dest++ = *src++;
  } while (*src != 0);
  return destsave;
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src) {
  char *destsave = dest;
  while (*dest != 0)
    dest++;

  do {
    *dest++ = *src++;
  } while (*src != 0);
  return destsave;
}

void *malloc(u32int size) { return allocate(size); }