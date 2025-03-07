#include "soundsend_select.h"
#include "../soundsend_const.h"

#include "esphome/core/helpers.h"

namespace esphome {
namespace soundsend {

void AudioSourceSelect::control(const std::string &value) {
  optional<size_t> index = this->index_of(value);
  if (index.has_value()) {
    this->parent_->queue_command(PacketType::WRITE, Command::AUDIO_SOURCE, {static_cast<uint8_t>(index.value())});
  }
}

void AudioModeSelect::control(const std::string &value) {
  optional<size_t> index = this->index_of(value);
  if (index.has_value()) {
    this->parent_->queue_command(PacketType::WRITE, Command::AUDIO_MODE, {static_cast<uint8_t>(index.value())});
  }
}

}  // namespace soundsend
}  // namespace esphome
