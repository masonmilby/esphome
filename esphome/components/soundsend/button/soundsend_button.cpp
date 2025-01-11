#include "soundsend_button.h"

namespace esphome {
namespace soundsend {

void QueryButton::press_action() { this->parent_->press_query(); }

}  // namespace soundsend
}  // namespace esphome