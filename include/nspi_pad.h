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
  ~Pad() = default;

  Pad(const Pad&) = delete;
  Pad& operator=(const Pad&) = delete;

  void update();

  u64 getButtonsDown() const;

  /**
   * @param[in] id ID of the analog stick to read (0=left, 1=right).
   */
  HidAnalogStickState getStickPos(const uint8_t& id) const;
};

}  // namespace nspi

#endif  // NSPI_PAD_H_