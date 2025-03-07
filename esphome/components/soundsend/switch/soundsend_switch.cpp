#include "soundsend_switch.h"

#include "esphome/core/log.h"

namespace esphome {
namespace soundsend {

void MuteSwitch::write_state(bool state) { this->parent_->queue_command(PacketType::WRITE, Command::MUTE, {state}); }
void PowerSwitch::write_state(bool state) { this->parent_->queue_command(PacketType::WRITE, Command::POWER, {state}); }

void VirtualDolbySwitch::write_state(bool state) {
  if (this->parent_->is_audio_mode(AudioMode::DIRECT)) {
    ESP_LOGW(this->parent_->TAG,
             "Virtual Dolby cannot be configured in Direct audio mode (to prevent WiSA app issues)");
  } else {
    this->parent_->queue_command(PacketType::WRITE, Command::VIRTUAL_DOLBY, {state});
  }
}
void BassManagementSwitch::write_state(bool state) {
  this->parent_->queue_command(PacketType::WRITE, Command::BASS_MANAGEMENT, {state});
}

}  // namespace soundsend
}  // namespace esphome
