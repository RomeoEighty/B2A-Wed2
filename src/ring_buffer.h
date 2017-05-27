#ifndef RING_BUFFER_H_INCLUDED
#define RING_BUFFER_H_INCLUDED

void init_ringbuf(int length);
char check_buf(int loc);
void capitalize_buf(int loc);
char dump_buf_sub(void);
char* dump_buf(void);
void push_buf(char ch);
char push(char ch);
void free_ringbuf(void);

#endif
