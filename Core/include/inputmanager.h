#pragma once
#include <map>
#include <stdio.h>

typedef struct {
  bool pressed;
  bool down;
  bool released;
} keystate;

class InputManager
{
public:
  InputManager();
};
