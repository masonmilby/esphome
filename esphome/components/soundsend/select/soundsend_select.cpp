#include "soundsend_select.h"
#include "../soundsend_const.h"

#include "esphome/core/helpers.h"

namespace esphome {
namespace soundsend {

void AudioSourceSelect::control(const std::string &value) {
  optional<size_t> index = this->index_of(value);
  if (index.has_value()) {
    this->parent_->set_audio_source(index.value());
  }
}

void AudioModeSelect::control(const std::string &value) {
  optional<size_t> index = this->index_of(value);
  if (index.has_value()) {
    this->parent_->set_audio_mode(index.value());
  }
}

}  // namespace soundsend
}  // namespace esphome
