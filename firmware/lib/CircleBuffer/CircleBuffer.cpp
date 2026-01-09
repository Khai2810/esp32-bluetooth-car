#include "CircleBuffer.h"

void CircleBuffer::Init()
{
  head = 0;
  tail = 0;
  count = 0;
}

bool CircleBuffer::Dequeue(unsigned char &byte)
{
  if (IsEmpty())
  {
    return false;
  }

  byte = buffer[tail];
  tail = (tail + 1) % BUFFER_SIZE;
  count--;
  return true;
}

bool CircleBuffer::Enqueue(unsigned char byte)
{
  if (IsFull())
  {
    return false;
  }
  buffer[head] = byte;
  head = (head + 1) % BUFFER_SIZE;
  count++;
  return true;
}

bool CircleBuffer::IsEmpty()
{
  return count == 0;
}

bool CircleBuffer::IsFull()
{
  return count == BUFFER_SIZE;
}