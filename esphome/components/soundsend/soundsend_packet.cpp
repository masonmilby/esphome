#include "soundsend_packet.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace soundsend {

SoundSendPacket::SoundSendPacket(uint8_t *data, uint8_t length) {
  if (length < 3) {
    return;
  }
  this->type_ = static_cast<PacketType>(data[0]);
  this->command_ = static_cast<Command>(data[1]);
  this->data_ = {data + 3, data + 3 + data[2]};
}

SoundSendPacket::SoundSendPacket(PacketType type, Command command, std::vector<uint8_t> data) {
  this->type_ = type;
  this->command_ = command;
  this->data_ = data;
}

StitchType SoundSendPacket::stitch_type() {
  switch (this->command_) {
    case Command::AUDIO_FORMAT:
      return StitchType::TO_SINGLE;
    default:
      return StitchType::NONE;
  }
}

std::vector<uint8_t> SoundSendPacket::build() {
  std::vector<uint8_t> buffer;
  buffer.reserve(3 + data_.size());
  buffer.push_back(static_cast<uint8_t>(type_));
  buffer.push_back(static_cast<uint8_t>(command_));
  buffer.push_back(static_cast<uint8_t>(data_.size()));
  buffer.insert(buffer.end(), data_.begin(), data_.end());
  return buffer;
}

std::string SoundSendPacket::to_log_string(uint8_t *data, uint16_t length) {
  std::string base = PACKET_TYPE_NAMES.at(this->type_) + " - " + COMMAND_NAMES.at(this->command_);

  if (data != nullptr) {
    return base + " - " + format_hex_pretty(data, length);
  }
  if (!this->data().empty()) {
    return base + " - " + format_hex_pretty(this->data().data(), this->data().size());
  }
  return base;
}

void SoundSendTxPacket::sent() {
  if (this->tx_time_ == 0) {
    this->tx_time_ = millis();
  }
}

void SoundSendTxPacket::add_attempt() {
  this->tx_time_ = 0;
  this->retry_attempts_++;
}

SoundSendRxPacket::SoundSendRxPacket(uint8_t *data, uint8_t length) : SoundSendPacket(data, length) {
  if (length > 4) {
    this->stitch_length_ = data[4];
  }
  this->stitch(data, length);
}

void SoundSendRxPacket::stitch(uint8_t *data, uint8_t length) {
  if (data[1] != this->command_value()) {
    return;
  }

  switch (this->stitch_type()) {
    case StitchType::TO_SINGLE:
      if (this->stitch_map_.empty()) {
        this->stitch_map_.emplace(0, std::vector<uint8_t>());
        this->stitch_map_.at(0).reserve(this->stitch_length_);
      }
      this->stitch_map_.at(0).insert(this->stitch_map_.at(0).end(), data + 5, data + 5 + (data[2] - 2));
      break;
    case StitchType::TO_MULTI:
      this->stitch_map_[data[3]] = {data + 5, data + 5 + (data[2] - 2)};
      break;
    default:
      break;
  }
}

bool SoundSendRxPacket::is_satisfied() {
  switch (this->stitch_type()) {
    case StitchType::TO_SINGLE:
      return this->stitch_map_.at(0).size() == this->stitch_length_;
    case StitchType::TO_MULTI:
      return !(this->stitch_map_.empty()) && this->command() == Command::REPLY_FINISH;
    default:
      return true;
  }
}

}  // namespace soundsend
}  // namespace esphome