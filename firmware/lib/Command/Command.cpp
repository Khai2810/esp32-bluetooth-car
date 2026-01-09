#include "Command.h"
#include "MotorUtils.h"

void Command::PackageParse()
{
  while (!buffer.IsEmpty() && frame.end != STATE_READ_END)
  {
    unsigned char byte;
    if (buffer.Dequeue(byte))
    {
      ParseState(byte);
    }
  }
}

void Command::ParseState(unsigned char byte)
{
  switch (state)
  {
  case STATE_PACKAGE_READY:
    frame.start = 0;
    frame.command = 0;
    frame.end = 0;
    state = STATE_WAITING_START;
    break;
  case STATE_WAITING_START:
    if (byte == PACKAGE_START)
    {
      frame.start = byte;
      state = STATE_READ_COMMAND;
    }
    break;
  case STATE_READ_COMMAND:
    frame.command = byte;
    state = STATE_READ_END;
    break;
  case STATE_READ_END:
    if (byte == PACKAGE_END)
    {
      state = STATE_PACKAGE_READY;
      frame.end = byte;
    }
    break;
  }
}

bool Command::ValidatePackage()
{
  if (frame.end == PACKAGE_END && frame.start == PACKAGE_START)
  {
    return true;
  }
  return false;
}

package_t Command::ReturnFrame()
{
  return frame;
}