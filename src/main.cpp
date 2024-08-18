#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

// libnx
#include <switch.h>

int main(int argc, char **argv) {
  consoleInit(NULL);
  padConfigureInput(1, HidNpadStyleSet_NpadStandard);

  PadState pad;
  padInitializeDefault(&pad);

  std::cout << "Hello World!" << std::endl;

  while (appletMainLoop()) {
    padUpdate(&pad);
    u64 kDown = padGetButtonsDown(&pad);

    if (kDown & HidNpadButton_Plus) break;

    // code goes here

    consoleUpdate(NULL);
  }

  consoleExit(NULL);

  return 0;
}