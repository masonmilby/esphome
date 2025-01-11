#include "soundsend_switch.h"

namespace esphome {
namespace soundsend {

void MuteSwitch::write_state(bool state) { this->parent_->set_mute(state); }
void PowerSwitch::write_state(bool state) { this->parent_->set_power(state); }
void VirtualDolbySwitch::write_state(bool state) { this->parent_->set_virtual_dolby(state); }
void BassManagementSwitch::write_state(bool state) { this->parent_->set_bass_management(state); }

}  // namespace soundsend
}  // namespace esphome
