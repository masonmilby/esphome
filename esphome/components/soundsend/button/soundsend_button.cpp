#include "soundsend_button.h"

namespace esphome {
namespace soundsend {

void QueryButton::press_action() { this->parent_->get_initial(); }

}  // namespace soundsend
}  // namespace esphome