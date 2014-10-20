#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Circular buffer with one slot always kept open
*/

struct slot_s {
  int value;
};

typedef struct slot_s slot_t;

struct cbuffer_s {
  int size;
  int start;
  int end;
  slot_t* slots;
};

typedef struct cbuffer_s cbuffer_t;

void init(cbuffer_t* buffer, int size) {
  buffer->size = size;
  buffer->start = 0;
  buffer->end = 0;
  buffer->slots = malloc(sizeof(slot_t) * buffer->size);
  memset(buffer->slots, 0, sizeof(slot_t) * buffer->size);
}

/*
* In an empty buffer, start and end 'point' to the same slot
*/
int isEmpty(cbuffer_t* buffer) {
  return buffer->start == buffer->end;
}

/*
* Keeping one slot open means that the last slot is the one preceeding the first slot
*/
int isFull(cbuffer_t* buffer) {
  return (buffer->end +1) % buffer->size == buffer->start;
}

/*
* FIXME check how to handle full buffer
*/
void write(cbuffer_t* buffer, int value) {
  printf("end: %i\n", buffer->end);
  buffer->slots[buffer->end].value = value;
  buffer->end = (buffer->end + 1) % buffer->size;
  printf("end: %i\n", buffer->end);
}


slot_t* read(cbuffer_t* buffer) {
  if (isEmpty(buffer)) {
    return NULL;
  }
  int start = buffer->start;
  printf("start: %i\n", start);
  slot_t* slot = &(buffer->slots[buffer->start]);
  buffer->start = (buffer->start + 1) % buffer->size;
  return &(buffer->slots[start]);
}



int main() {
  cbuffer_t cb;
  init(&cb, 7);
  printf("is empty: %i\n", isEmpty(&cb));
  printf("is full: %i\n", isFull(&cb));
  write(&cb, 4);
  slot_t* slot = read(&cb);
  printf("value: %i\n", slot->value);
  return 0;
}