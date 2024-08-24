#ifndef NSPI_CONSOLE_H_
#define NSPI_CONSOLE_H_

namespace nspi {

class Console {
 private:
  void init();
  void clean();

 public:
  Console();
  ~Console();

  Console(const Console&) = delete;
  Console& operator=(const Console&) = delete;

  void update() const;
};

}  // namespace nspi

#endif  // NSPI_CONSOLE_H_