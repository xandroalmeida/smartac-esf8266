// Copyright 2018 David Conran

// Supports:
//   Brand: Panasonic,  Model: TV
//   Brand: Panasonic,  Model: JKE series A/C
//   Brand: Panasonic,  Model: DKE series A/C
//   Brand: Panasonic,  Model: CKP series A/C
//   Brand: Panasonic,  Model: CS-ME10CKPG A/C
//   Brand: Panasonic,  Model: CS-ME12CKPG A/C
//   Brand: Panasonic,  Model: CS-ME14CKPG A/C
//   Brand: Panasonic,  Model: RKR series A/C
//   Brand: Panasonic,  Model: CS-Z9RKR A/C
//   Brand: Panasonic,  Model: NKE series A/C
//   Brand: Panasonic,  Model: CS-YW9MKD A/C
//   Brand: Panasonic,  Model: A75C3747 remote
//   Brand: Panasonic,  Model: A75C3704 remote
//   Brand: Panasonic,  Model: A75C2311 remote (CKP)
//   Brand: Panasonic,  Model: A75C3747 remote
//   Brand: Panasonic,  Model: A75C3747 remote
//   Brand: Panasonic,  Model: A75C3747 remote

#ifndef IR_PANASONIC_H_
#define IR_PANASONIC_H_

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#ifdef ARDUINO
#include <Arduino.h>
#endif
#include "IRremoteESP8266.h"
#include "IRsend.h"
#ifdef UNIT_TEST
#include "IRsend_test.h"
#endif

// Panasonic A/C support heavily influenced by:
//   https://github.com/ToniA/ESPEasy/blob/HeatpumpIR/lib/HeatpumpIR/PanasonicHeatpumpIR.cpp

// Constants
const uint16_t kPanasonicFreq = 36700;
const uint16_t kPanasonicAcExcess = 0;
// Much higher than usual. See issue #540.
const uint16_t kPanasonicAcTolerance = 40;

const uint8_t kPanasonicAcAuto = 0;  // 0b0000
const uint8_t kPanasonicAcDry = 2;   // 0b0010
const uint8_t kPanasonicAcCool = 3;  // 0b0011
const uint8_t kPanasonicAcHeat = 4;  // 0b0010
const uint8_t kPanasonicAcFan = 6;   // 0b0110
const uint8_t kPanasonicAcFanMin = 0;
const uint8_t kPanasonicAcFanMax = 4;
const uint8_t kPanasonicAcFanAuto = 7;
const uint8_t kPanasonicAcFanOffset = 3;
const uint8_t kPanasonicAcPower = 1;         // 0b1
const uint8_t kPanasonicAcMinTemp = 16;      // Celsius
const uint8_t kPanasonicAcMaxTemp = 30;      // Celsius
const uint8_t kPanasonicAcFanModeTemp = 27;  // Celsius
const uint8_t kPanasonicAcQuiet = 1;         // 0b1
const uint8_t kPanasonicAcPowerful = 0x20;   // 0b100000
// CKP & RKR models have Powerful and Quiet bits swapped.
const uint8_t kPanasonicAcQuietCkp = 0x20;  // 0b100000
const uint8_t kPanasonicAcPowerfulCkp = 1;  // 0b1
const uint8_t kPanasonicAcSwingVAuto = 0xF;
const uint8_t kPanasonicAcSwingVUp = 0x1;
const uint8_t kPanasonicAcSwingVDown = 0x5;
const uint8_t kPanasonicAcSwingHAuto = 0xD;
const uint8_t kPanasonicAcSwingHMiddle = 0x6;
const uint8_t kPanasonicAcSwingHFullLeft = 0x9;
const uint8_t kPanasonicAcSwingHLeft = 0xA;
const uint8_t kPanasonicAcSwingHRight = 0xB;
const uint8_t kPanasonicAcSwingHFullRight = 0xC;
const uint8_t kPanasonicAcChecksumInit = 0xF4;
const uint8_t kPanasonicAcOnTimer = 0b00000010;
const uint8_t kPanasonicAcOffTimer = 0b00000100;
const uint16_t kPanasonicAcTimeMax = 23 * 60 + 59;  // Mins since midnight.
const uint16_t kPanasonicAcTimeSpecial = 0x600;

const uint8_t kPanasonicKnownGoodState[kPanasonicAcStateLength] = {
    0x02, 0x20, 0xE0, 0x04, 0x00, 0x00, 0x00, 0x06, 0x02,
    0x20, 0xE0, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
    0x00, 0x0E, 0xE0, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00};

enum panasonic_ac_remote_model_t {
  kPanasonicUnknown = 0,
  kPanasonicLke = 1,
  kPanasonicNke = 2,
  kPanasonicDke = 3,
  kPanasonicJke = 4,
  kPanasonicCkp = 5,
  kPanasonicRkr = 6,
};

class IRPanasonicAc {
 public:
  explicit IRPanasonicAc(const uint16_t pin);

  void stateReset(void);
#if SEND_PANASONIC
  void send(const uint16_t repeat = kPanasonicAcDefaultRepeat);
  uint8_t calibrate(void) { return _irsend.calibrate(); }
#endif  // SEND_PANASONIC
  void begin(void);
  void on(void);
  void off(void);
  void setPower(const bool on);
  bool getPower(void);
  void setTemp(const uint8_t temp, const bool remember = true);
  uint8_t getTemp(void);
  void setFan(const uint8_t fan);
  uint8_t getFan(void);
  void setMode(const uint8_t mode);
  uint8_t getMode(void);
  void setRaw(const uint8_t state[]);
  uint8_t *getRaw(void);
  static bool validChecksum(uint8_t *state,
                            const uint16_t length = kPanasonicAcStateLength);
  static uint8_t calcChecksum(uint8_t *state,
                              const uint16_t length = kPanasonicAcStateLength);
  void setQuiet(const bool on);
  bool getQuiet(void);
  void setPowerful(const bool on);
  bool getPowerful(void);
  void setModel(const panasonic_ac_remote_model_t model);
  panasonic_ac_remote_model_t getModel(void);
  void setSwingVertical(const uint8_t elevation);
  uint8_t getSwingVertical(void);
  void setSwingHorizontal(const uint8_t direction);
  uint8_t getSwingHorizontal(void);
  static uint16_t encodeTime(const uint8_t hours, const uint8_t mins);
  uint16_t getClock(void);
  void setClock(const uint16_t mins_since_midnight);
  uint16_t getOnTimer(void);
  void setOnTimer(const uint16_t mins_since_midnight, const bool enable = true);
  void cancelOnTimer(void);
  bool isOnTimerEnabled(void);
  uint16_t getOffTimer(void);
  void setOffTimer(const uint16_t mins_since_midnight,
                   const bool enable = true);
  void cancelOffTimer(void);
  bool isOffTimerEnabled(void);
  uint8_t convertMode(const stdAc::opmode_t mode);
  uint8_t convertFan(const stdAc::fanspeed_t speed);
  uint8_t convertSwingV(const stdAc::swingv_t position);
  uint8_t convertSwingH(const stdAc::swingh_t position);
  static stdAc::opmode_t toCommonMode(const uint8_t mode);
  static stdAc::fanspeed_t toCommonFanSpeed(const uint8_t speed);
  static stdAc::swingv_t toCommonSwingV(const uint8_t pos);
  static stdAc::swingh_t toCommonSwingH(const uint8_t pos);
  stdAc::state_t toCommon(void);
  String toString(void);
  static String timeToString(const uint16_t mins_since_midnight);
#ifndef UNIT_TEST

 private:
  IRsend _irsend;
#else
  IRsendTest _irsend;
#endif
  uint8_t remote_state[kPanasonicAcStateLength];
  uint8_t _swingh;
  uint8_t _temp;
  void fixChecksum(const uint16_t length = kPanasonicAcStateLength);
  static uint8_t calcChecksum(const uint8_t *state,
                              const uint16_t length = kPanasonicAcStateLength);
};

#endif  // IR_PANASONIC_H_
