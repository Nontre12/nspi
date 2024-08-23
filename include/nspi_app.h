#ifndef NSPI_APP_H_
#define NSPI_APP_H_

#include <string>

#include "nspi_console.h"
#include "nspi_menu.h"
#include "nspi_pad.h"

namespace nspi {

class App {
 private:
  Console console;
  Pad pad;
  Menu menu{pad};

  bool quit;
  bool shouldClose() const;

  void init();
  void clean();

  void mainLoop();

  void handleInput();
  void draw();

  std::string retrieveRawDataFromEndpoint() const;
  std::vector<nspi::Title> retrieveTitlesFromRawData(const std::string& rawData) const;

 public:
  App();
  ~App();

  App(const App&) = delete;
  App& operator=(const App&) = delete;

  void run();
};

}  // namespace nspi

#endif  // NSPI_APP_H_