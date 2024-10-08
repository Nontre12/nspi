#ifndef NSPI_APP_H_
#define NSPI_APP_H_

#include "nspi_console.h"
#include "nspi_menu.h"
#include "nspi_menu_manager.h"
#include "nspi_pad.h"

namespace nspi {

class App {
 private:
  Console *console;
  Pad pad;
  MenuManager menuManager{pad};

  bool quit;
  bool shouldClose() const;

  void init();
  void clean();

  void mainLoop();

  void handleInput();
  void draw() const;

 public:
  App();
  ~App();

  App(const App&) = delete;
  App& operator=(const App&) = delete;

  void run();
};

}  // namespace nspi

#endif  // NSPI_APP_H_