#error NOT FINISHED CODE
#include <ctype.h>
#include "ring_buffer.h"

int bufloc = 0;
int ring_buf_length = 3;
char *BUF;

void init_ringbuf(int length)
{
    BUF = (char *)malloc(sizeof(char) * length);
}

char check_buf(int loc)
{
    return BUF[(bufloc + loc) % ring_buf_length];
//  if (loc == 0) {
//      return BUF[bufloc];
//  } else if (loc == 1) {
//      if (bufloc <= 1) {
//          return BUF[bufloc + loc];
//      } if (bufloc == 2) {
//          return BUF[0];
//      }
//  } else /*if (loc == 2)*/ {
//      if (bufloc == 0) {
//          return BUF[2];
//      } else if (bufloc == 1) {
//          return BUF[0];
//      } else {
//          return BUF[1];
//      }
//  }
}
void capitalize_buf(int loc)
{
    if (loc == 0) {
        BUF[bufloc] = toupper(BUF[bufloc]);
    } else if (loc == 1) {
        if (bufloc <= 1) {
            BUF[bufloc + loc] = toupper(BUF[bufloc + loc]);
        } if (bufloc == 2) {
            BUF[0] = toupper(BUF[0]);
        }
    } else if (loc == 2) {
        if (bufloc == 0) {
            BUF[2] = toupper(BUF[2]);
        } else if (bufloc == 1) {
            BUF[0] = toupper(BUF[0]);
        } else {
            BUF[1] = toupper(BUF[1]);
        }
    }
}
char dump_buf_sub(void)
{
    char tmp = BUF[bufloc];
    if (bufloc == 2) {
        bufloc = 0;
    } else {
        bufloc++;
    }
    return tmp;
}
char* dump_buf(void)
{
    static char str[3];
    for (int i = 0; i < 3; i++) {
        str[i] = dump_buf_sub();
    }
    return str;
}
void push_buf(char ch)
{
    BUF[bufloc] = ch;
    if (bufloc == 2) {
        bufloc = 0;
    } else {
        bufloc++;
    }
}
char push(char ch)
{
    char tmp;
    tmp = check_buf(0);
    push_buf(ch);
    return tmp;
}
void free_ringbuf(void)
{
    free(BUF);
}
