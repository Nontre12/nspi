#ifndef NSPI_TITLE_H_
#define NSPI_TITLE_H_

#include <cstdint>

namespace nspi {

struct Title {
  uint32_t releaseDate;    // 4 bytes
  uint32_t size;           // 4 bytes
  char region[3];          // 3 bytes
  char id[17];             // 17 bytes
  char publisher[25];      // 25 bytes
  char name[49];           // 49 bytes
  char version[49];        // 49 bytes
  char description[1025];  // 1025 bytes
};

}  // namespace nspi

#endif  // NSPI_TITLE_H_