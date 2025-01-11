#pragma once

#include "esphome/components/select/select.h"
#include "../soundsend.h"

namespace esphome {
namespace soundsend {

class AudioSourceSelect : public select::Select, public Parented<SoundSendComponent> {
 public:
  AudioSourceSelect() = default;

 protected:
  void control(const std::string &value) override;
};

class AudioModeSelect : public select::Select, public Parented<SoundSendComponent> {
 public:
  AudioModeSelect() = default;

 protected:
  void control(const std::string &value) override;
};

}  // namespace soundsend
}  // namespace esphome
