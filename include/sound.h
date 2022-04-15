#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <SDL_mixer.h>

namespace Sound {
  bool state();
  void on();
  void off();
  void open(std::string path, int loops = 1);
}

#endif // SOUND_H
