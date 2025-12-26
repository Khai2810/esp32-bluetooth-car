#ifndef COMMAND_H
#define COMMAND_H

#include "CircleBuffer.h"
#define PACKAGE_START 0xAA
#define PACKAGE_END 0x55

typedef struct
{
  unsigned char start;
  // unsigned char dataLength;
  unsigned char command;
  unsigned char end;
} package_t;

typedef enum
{
  STATE_WAITING_START,
  STATE_READ_COMMAND,
  STATE_READ_END,
  STATE_PACKAGE_READY
} parse_state_t;

class Command
{
private:
  package_t frame;
  CircleBuffer &buffer;
  parse_state_t state;
  void PackageParse();
  void ParseState(unsigned char byte);

  // void CreatePackage();

  // protected:
  // virtual void PutByte() = 0;

public:
  Command(CircleBuffer &buff) : buffer(buff)
  {
    state = STATE_PACKAGE_READY;
    frame.start = 0;
    frame.command = 0;
    frame.end = 0;
  }
  package_t ReturnFrame();
  bool ValidatePackage();
};

#endif