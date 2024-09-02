#include "nspi_selectable_menu.h"

#include <string>

#include "nspi_title.h"

template <typename T>
void nspi::SelectableMenu<T>::focusPrevious(uint16_t steps) {
  if (this->focusIndex < steps) {
    this->focusIndex = 0;
  }

  if (this->focusIndex != 0) {
    this->focusIndex -= steps;
  }
}

template <typename T>
void nspi::SelectableMenu<T>::focusNext(uint16_t steps) {
  if (this->dummyData.size() == 0) {
    this->focusIndex = 0;
    return;
  }

  if (this->focusIndex + steps > this->dummyData.size()) {
    this->focusIndex = this->dummyData.size() - 1;
  }

  if (this->focusIndex < this->dummyData.size() - 1) {
    this->focusIndex += steps;
  }
}

template <typename T>
nspi::SelectableMenu<T>::SelectableMenu(MenuManager& menuManager, Pad& pad)
    : focusIndex(0), focusOffset(0), menuManager(menuManager), pad(pad) {}

template <typename T>
void nspi::SelectableMenu<T>::handleInput() {
  uint64_t kDown = this->pad.getButtonsDown();
  HidAnalogStickState left_stick_state = this->pad.getStickPos(0);
  // HidAnalogStickState right_stick_state = this->pad.getStickPos(1);

  if (kDown & HidNpadButton_Up || left_stick_state.y > 30000) {
    this->focusPrevious();
  }

  if (kDown & HidNpadButton_Down || left_stick_state.y < -30000) {
    this->focusNext();
  }

  if (kDown & HidNpadButton_Left || left_stick_state.x < -30000) {
    this->focusPrevious(5);
  }

  if (kDown & HidNpadButton_Right || left_stick_state.x > 30000) {
    this->focusNext(5);
  }

  if (kDown & HidNpadButton_X) {
    if (this->marked.find(focusIndex) == this->marked.end()) {
      this->marked.insert(focusIndex);
    } else {
      this->marked.erase(focusIndex);
    }
  }

  if (kDown & HidNpadButton_B) {
    this->menuManager.back();
  }

  // Adjust focusOffset if necessary
  if (focusIndex < focusOffset) {
    focusOffset = focusIndex;
  } else if (focusIndex >= focusOffset + VISIBLE_ITEMS) {
    focusOffset = focusIndex - VISIBLE_ITEMS + 1;
  }
}

template class nspi::SelectableMenu<nspi::Title>;
template class nspi::SelectableMenu<std::string>;
