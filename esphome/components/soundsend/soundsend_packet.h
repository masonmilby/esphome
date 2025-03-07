#pragma once

#include "esphome/core/hal.h"

#include "soundsend_const.h"

#include <vector>
#include <map>
#include <string>

namespace esphome {
namespace soundsend {

class SoundSendPacket {
 public:
  SoundSendPacket(){};
  SoundSendPacket(uint8_t *data, uint8_t length);
  SoundSendPacket(PacketType type, Command command, std::vector<uint8_t> data);

  PacketType type() { return this->type_; }
  Command command() { return this->command_; }
  uint8_t command_value() { return static_cast<uint8_t>(this->command_); }
  std::vector<uint8_t> data() { return this->data_; }

  StitchType stitch_type();
  std::vector<uint8_t> build();
  std::string to_log_string(uint8_t *data = nullptr, uint16_t length = 0);

 protected:
  PacketType type_ = PacketType::UNDEFINED;
  Command command_ = Command::UNDEFINED;
  std::vector<uint8_t> data_;
};

class SoundSendTxPacket : public SoundSendPacket {
 public:
  SoundSendTxPacket(PacketType type, Command command, std::vector<uint8_t> data)
      : SoundSendPacket(type, command, data) {}

  uint32_t tx_time() { return this->tx_time_; }
  bool is_sent() { return this->tx_time_ != 0; }
  void sent();

  uint8_t attempts() { return this->retry_attempts_; }
  void add_attempt();

 protected:
  uint32_t tx_time_ = 0;
  uint8_t retry_attempts_ = 0;
};

class SoundSendRxPacket : public SoundSendPacket {
 public:
  SoundSendRxPacket() : SoundSendPacket() {}
  SoundSendRxPacket(uint8_t *data, uint8_t length);

  void stitch(uint8_t *data, uint8_t length);
  bool is_satisfied();
  uint8_t stitch_length() { return this->stitch_length_; }
  std::map<uint8_t, std::vector<uint8_t>> stitch_map() { return this->stitch_map_; }

  uint8_t to_uint8() { return this->data()[0]; }
  int8_t to_int8() { return static_cast<int8_t>(this->data()[0]); }
  std::string to_string() {
    return std::string(reinterpret_cast<const char *>(this->stitch_map_.at(0).data()), this->stitch_map_.at(0).size());
  }

 protected:
  uint8_t stitch_length_ = 0;
  std::map<uint8_t, std::vector<uint8_t>> stitch_map_;
};

}  // namespace soundsend
}  // namespace esphome