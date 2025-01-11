#pragma once

#include "esphome/components/button/button.h"
#include "../soundsend.h"

namespace esphome {
namespace soundsend {

class QueryButton : public button::Button, public Parented<SoundSendComponent> {
 public:
  QueryButton() = default;

 protected:
  void press_action() override;
};

}  // namespace soundsend
}  // namespace esphome
