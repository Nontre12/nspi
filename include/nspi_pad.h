#ifndef NSPI_PAD_H_
#define NSPI_PAD_H_

#include <switch.h>

namespace nspi {

class Pad {
 private:
  PadState pad;
  void init();

 public:
  Pad();
  ~Pad();

  Pad(const Pad&) = delete;
  Pad& operator=(const Pad&) = delete;

  void update();

  u64 getButtonsDown() const;
};

}  // namespace nspi

#endif  // NSPI_PAD_H_