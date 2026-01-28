#ifndef CIRCLEBUFFER_H
#define CIRCLEBUFFER_H

#define BUFFER_SIZE 128

class CircleBuffer
{
private:
  unsigned char (&buffer)[BUFFER_SIZE];
  int head;
  int tail;
  unsigned char count;
  void Init();

public:
  CircleBuffer(unsigned char (&arr)[BUFFER_SIZE]) : buffer(arr)
  {
    Init();
  }
  bool IsEmpty();
  bool IsFull();
  bool Dequeue(unsigned char &byte);
  bool Enqueue(unsigned char byte);
};

#endif