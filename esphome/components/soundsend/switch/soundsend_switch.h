#pragma once

#include "esphome/components/switch/switch.h"
#include "../soundsend.h"

namespace esphome {
namespace soundsend {

class MuteSwitch : public switch_::Switch, public Parented<SoundSendComponent> {
 public:
  MuteSwitch() = default;

 protected:
  void write_state(bool state) override;
};

class PowerSwitch : public switch_::Switch, public Parented<SoundSendComponent> {
 public:
  PowerSwitch() = default;

 protected:
  void write_state(bool state) override;
};

class VirtualDolbySwitch : public switch_::Switch, public Parented<SoundSendComponent> {
 public:
  VirtualDolbySwitch() = default;

 protected:
  void write_state(bool state) override;
};

class BassManagementSwitch : public switch_::Switch, public Parented<SoundSendComponent> {
 public:
  BassManagementSwitch() = default;

 protected:
  void write_state(bool state) override;
};

}  // namespace soundsend
}  // namespace esphome
