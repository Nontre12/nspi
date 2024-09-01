#ifndef NSPI_LINUX_SWITCH_H_
#define NSPI_LINUX_SWITCH_H_

// std
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

// types.c
typedef uint32_t Result;
// end types.c

// socket.c
static inline Result socketInitializeDefault(void) { return Result{0}; }

static inline void socketExit(void) {}
// end socket.c

// applet.c
typedef enum {
  AppletType_None = -2,
  AppletType_Default = -1,
  AppletType_Application = 0,
  AppletType_SystemApplet = 1,
  AppletType_LibraryApplet = 2,
  AppletType_OverlayApplet = 3,
  AppletType_SystemApplication = 4,
} AppletType;

static inline AppletType appletGetAppletType(void) { return AppletType_Application; }

static inline bool appletMainLoop(void) { return true; }
// end applet.c

// console.c
static inline void consoleInit(void*) {}

static inline void consoleExit(void*) {}

static inline void consoleUpdate(void*) {}

static inline void consoleClear(void) { std::cout << "\033[2J\033[1;1H"; }
// end console.c

// hid.c
typedef struct HidAnalogStickState {
  uint32_t x;  ///< X
  uint32_t y;  ///< Y
} HidAnalogStickState;

typedef enum {
  HidNpadStyleTag_NpadFullKey,       ///< Pro Controller
  HidNpadStyleTag_NpadHandheld,      ///< Joy-Con controller in handheld mode
  HidNpadStyleTag_NpadJoyDual,       ///< Joy-Con controller in dual mode
  HidNpadStyleTag_NpadJoyLeft,       ///< Joy-Con left controller in single mode
  HidNpadStyleTag_NpadJoyRight,      ///< Joy-Con right controller in single mode
  HidNpadStyleTag_NpadGc,            ///< GameCube controller
  HidNpadStyleTag_NpadPalma,         ///< Poké Ball Plus controller
  HidNpadStyleTag_NpadLark,          ///< NES/Famicom controller
  HidNpadStyleTag_NpadHandheldLark,  ///< NES/Famicom controller in handheld mode
  HidNpadStyleTag_NpadLucia,         ///< SNES controller
  HidNpadStyleTag_NpadLagon,         ///< N64 controller
  HidNpadStyleTag_NpadLager,         ///< Sega Genesis controller
  HidNpadStyleTag_NpadSystemExt,     ///< Generic external controller
  HidNpadStyleTag_NpadSystem,        ///< Generic controller

  HidNpadStyleSet_NpadFullCtrl =
      HidNpadStyleTag_NpadFullKey | HidNpadStyleTag_NpadHandheld |
      HidNpadStyleTag_NpadJoyDual,  ///< Style set comprising Npad styles containing the full set of
                                    ///< controls {FullKey, Handheld, JoyDual}
  HidNpadStyleSet_NpadStandard =
      HidNpadStyleSet_NpadFullCtrl | HidNpadStyleTag_NpadJoyLeft |
      HidNpadStyleTag_NpadJoyRight,  ///< Style set comprising all standard Npad styles {FullKey,
                                     ///< Handheld, JoyDual, JoyLeft, JoyRight}
} HidNpadStyleTag;

typedef enum {
  HidNpadButton_A = 1UL << (0),              ///< A button / Right face button
  HidNpadButton_B = 1UL << (1),              ///< B button / Down face button
  HidNpadButton_X = 1UL << (2),              ///< X button / Up face button
  HidNpadButton_Y = 1UL << (3),              ///< Y button / Left face button
  HidNpadButton_StickL = 1UL << (4),         ///< Left Stick button
  HidNpadButton_StickR = 1UL << (5),         ///< Right Stick button
  HidNpadButton_L = 1UL << (6),              ///< L button
  HidNpadButton_R = 1UL << (7),              ///< R button
  HidNpadButton_ZL = 1UL << (8),             ///< ZL button
  HidNpadButton_ZR = 1UL << (9),             ///< ZR button
  HidNpadButton_Plus = 1UL << (10),          ///< Plus button
  HidNpadButton_Minus = 1UL << (11),         ///< Minus button
  HidNpadButton_Left = 1UL << (12),          ///< D-Pad Left button
  HidNpadButton_Up = 1UL << (13),            ///< D-Pad Up button
  HidNpadButton_Right = 1UL << (14),         ///< D-Pad Right button
  HidNpadButton_Down = 1UL << (15),          ///< D-Pad Down button
  HidNpadButton_StickLLeft = 1UL << (16),    ///< Left Stick pseudo-button when moved Left
  HidNpadButton_StickLUp = 1UL << (17),      ///< Left Stick pseudo-button when moved Up
  HidNpadButton_StickLRight = 1UL << (18),   ///< Left Stick pseudo-button when moved Right
  HidNpadButton_StickLDown = 1UL << (19),    ///< Left Stick pseudo-button when moved Down
  HidNpadButton_StickRLeft = 1UL << (20),    ///< Right Stick pseudo-button when moved Left
  HidNpadButton_StickRUp = 1UL << (21),      ///< Right Stick pseudo-button when moved Up
  HidNpadButton_StickRRight = 1UL << (22),   ///< Right Stick pseudo-button when moved Right
  HidNpadButton_StickRDown = 1UL << (23),    ///< Right Stick pseudo-button when moved Left
  HidNpadButton_LeftSL = 1UL << (24),        ///< SL button on Left Joy-Con
  HidNpadButton_LeftSR = 1UL << (25),        ///< SR button on Left Joy-Con
  HidNpadButton_RightSL = 1UL << (26),       ///< SL button on Right Joy-Con
  HidNpadButton_RightSR = 1UL << (27),       ///< SR button on Right Joy-Con
  HidNpadButton_Palma = 1UL << (28),         ///< Top button on Poké Ball Plus (Palma) controller
  HidNpadButton_Verification = 1UL << (29),  ///< Verification
  HidNpadButton_HandheldLeftB = 1UL << (30), ///< B button on Left NES/HVC controller in Handheld mode
  HidNpadButton_LagonCLeft = 1UL << (31),    ///< Left C button in N64 controller
  HidNpadButton_LagonCUp = 1UL << (32),      ///< Up C button in N64 controller
  HidNpadButton_LagonCRight = 1UL << (33),   ///< Right C button in N64 controller
  HidNpadButton_LagonCDown = 1UL << (34),    ///< Down C button in N64 controller

  HidNpadButton_AnyLeft = HidNpadButton_Left | HidNpadButton_StickLLeft |
                          HidNpadButton_StickRLeft,  ///< Bitmask containing all buttons that are
                                                     ///< considered Left (D-Pad, Sticks)
  HidNpadButton_AnyUp = HidNpadButton_Up | HidNpadButton_StickLUp |
                        HidNpadButton_StickRUp,  ///< Bitmask containing all buttons that are
                                                 ///< considered Up (D-Pad, Sticks)
  HidNpadButton_AnyRight = HidNpadButton_Right | HidNpadButton_StickLRight |
                           HidNpadButton_StickRRight,  ///< Bitmask containing all buttons that are
                                                       ///< considered Right (D-Pad, Sticks)
  HidNpadButton_AnyDown = HidNpadButton_Down | HidNpadButton_StickLDown |
                          HidNpadButton_StickRDown,  ///< Bitmask containing all buttons that are
                                                     ///< considered Down (D-Pad, Sticks)
  HidNpadButton_AnySL =
      HidNpadButton_LeftSL |
      HidNpadButton_RightSL,  ///< Bitmask containing SL buttons on both Joy-Cons (Left/Right)
  HidNpadButton_AnySR =
      HidNpadButton_LeftSR |
      HidNpadButton_RightSR,  ///< Bitmask containing SR buttons on both Joy-Cons (Left/Right)
} HidNpadButton;
// end hid.c

// pad.c
typedef struct {
  uint8_t id_mask;
  uint8_t active_id_mask;
  bool read_handheld;
  bool active_handheld;
  uint32_t style_set;
  uint32_t attributes;
  uint64_t buttons_cur;
  uint64_t buttons_old;
  HidAnalogStickState sticks[2];
  uint32_t gc_triggers[2];
} PadState;

static inline void padUpdate(const PadState*) {}

static inline constexpr uint64_t padGetButtonsDown(const PadState*) { return HidNpadButton_Right; }

static inline HidAnalogStickState padGetStickPos(const PadState*, uint8_t) {
  return HidAnalogStickState{};
}

static inline void padConfigureInput(uint32_t max_players, uint32_t style_set) {}

static inline void padInitializeDefault(PadState* pad) {}
// end pad.h

#endif  // NSPI_LINUX_SWITCH_H_
