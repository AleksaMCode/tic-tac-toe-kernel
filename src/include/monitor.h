// monitor.h -- Defines the interface for monitor.h
// From JamesM's kernel development tutorials.
#ifndef MONITOR_H
#define MONITOR_H
#include <tictactoe.h>
#include <common.h>

void monitor_put(char c);
void monitor_clear();
void monitor_write(const char *c);
void monitor_write_dec(u32int n);
void monitor_write_valn(char c, int n);
char get_last_char();
char* get_current_line();

#endif // MONITOR_H