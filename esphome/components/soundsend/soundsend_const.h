#pragma once

#include "esphome/core/hal.h"

#include <vector>
#include <map>
#include <string>

namespace esphome {
namespace soundsend {

enum class AudioSource : uint8_t {
  HDMI = 0x0,
  OPTICAL = 0x1,
};

enum class AudioMode : uint8_t {
  DIRECT = 0x0,
  MOVIE = 0x1,
  MUSIC = 0x2,
  NIGHT = 0x3,
};

enum class SpeakerType : uint8_t {
  FRONT_LEFT = 0x1,
  FRONT_RIGHT = 0x9,
  CENTER = 0x2,
  SUBWOOFER = 0x3,
  BACK_LEFT = 0x6,
  BACK_RIGHT = 0x7,
  SURROUND_LEFT = 0x5,
  SURROUND_RIGHT = 0x8,

  TOP_FRONT_LEFT = 0xE,
  TOP_FRONT_RIGHT = 0xF,
  TOP_SURROUND_LEFT = 0x10,
  TOP_SURROUND_RIGHT = 0x11,
  TOP_BACK_LEFT = 0x12,
  TOP_BACK_RIGHT = 0x13,
};

static const std::map<AudioSource, std::string> AUDIO_SOURCE_NAMES = {
    {AudioSource::HDMI, "HDMI ARC/eARC"},
    {AudioSource::OPTICAL, "Optical"},
};

static const std::map<AudioMode, std::string> AUDIO_MODE_NAMES = {
    {AudioMode::DIRECT, "Direct"},
    {AudioMode::MOVIE, "Movie"},
    {AudioMode::MUSIC, "Music"},
    {AudioMode::NIGHT, "Night"},
};

static const std::map<SpeakerType, std::string> SPEAKER_TYPE_NAMES = {
    {SpeakerType::FRONT_LEFT, "Front Left"},
    {SpeakerType::FRONT_RIGHT, "Front Right"},
    {SpeakerType::CENTER, "Center"},
    {SpeakerType::SUBWOOFER, "Subwoofer"},
    {SpeakerType::BACK_LEFT, "Back Left"},
    {SpeakerType::BACK_RIGHT, "Back Right"},
    {SpeakerType::SURROUND_LEFT, "Surround Left"},
    {SpeakerType::SURROUND_RIGHT, "Surround Right"},
    {SpeakerType::TOP_FRONT_LEFT, "Front Left Height"},
    {SpeakerType::TOP_FRONT_RIGHT, "Front Right Height"},
    {SpeakerType::TOP_SURROUND_LEFT, "Surround Left Height"},
    {SpeakerType::TOP_SURROUND_RIGHT, "Surround Right Height"},
    {SpeakerType::TOP_BACK_LEFT, "Back Left Height"},
    {SpeakerType::TOP_BACK_RIGHT, "Back Right Height"},
};

struct ModuleVersions {
  ModuleVersions(const std::vector<uint8_t> data) {
    this->mcu_ = std::to_string(data[0]) + "." + std::to_string(data[1]);
    this->dsp_ = std::to_string(data[2]) + "." + std::to_string(data[3]);
    this->summitTx_ = std::to_string(data[4]) + "." + std::to_string(data[5]);
    this->bluetooth_ = std::to_string(data[6]) + "." + std::to_string(data[7]) + "." + std::to_string(data[8]);
  }

  std::string to_string() {
    return "MCU v" + mcu_ + " | DSP v" + dsp_ + " | SummitTx v" + summitTx_ + " | Bluetooth v" + bluetooth_;
  }

 protected:
  std::string mcu_;
  std::string dsp_;
  std::string summitTx_;
  std::string bluetooth_;
};

class SoundSendPacket {
 public:
  enum class Type : uint8_t {
    READ = 0x0,
    WRITE = 0x1,
    REPLY = 0x2,
    UNDEFINED = 0xFF,
  };

  enum class Command : uint8_t {
    REPLY_FINISH = 0x0,
    MODULE_VERSIONS = 0x1,
    MUTE = 0x3,
    VOLUME = 0x4,
    AUDIO_SOURCE = 0x5,
    POWER = 0x6,
    AUDIO_MODE = 0x9,
    SPEAKER_TRIM = 0xC,
    LIP_SYNC = 0xD,
    CHIME_SPEAKER = 0xE,
    EQ_HIGH = 0x21,
    EQ_MID_RANGE = 0x22,
    EQ_VOICE = 0x23,
    EQ_MID_BASS = 0x24,
    EQ_SUB = 0x25,
    AUDIO_FORMAT = 0x36,
    VIRTUAL_DOLBY = 0x37,
    BASS_MANAGEMENT = 0x38,
    UNDEFINED = 0xFF,
  };

  enum class StitchType {
    NONE,
    TO_SINGLE,
    TO_MULTI,
  };

  SoundSendPacket(){};
  SoundSendPacket(uint8_t *data, uint8_t length) {
    if (length < 3) {
      return;
    }
    this->type_ = static_cast<Type>(data[0]);
    this->command_ = static_cast<Command>(data[1]);
    this->data_ = {data + 3, data + 3 + data[2]};
  }

  SoundSendPacket(Type type, Command command, std::vector<uint8_t> data) {
    this->type_ = type;
    this->command_ = command;
    this->data_ = data;
  }

  Type type() { return this->type_; }
  Command command() { return this->command_; }
  uint8_t command_value() { return static_cast<uint8_t>(this->command_); }
  std::vector<uint8_t> data() { return this->data_; }

  StitchType stitch_type() {
    switch (this->command_) {
      case Command::AUDIO_FORMAT:
        return StitchType::TO_SINGLE;
      default:
        return StitchType::NONE;
    }
  }

  std::vector<uint8_t> build() {
    std::vector<uint8_t> buffer;
    buffer.reserve(3 + data_.size());
    buffer.push_back(static_cast<uint8_t>(type_));
    buffer.push_back(static_cast<uint8_t>(command_));
    buffer.push_back(static_cast<uint8_t>(data_.size()));
    buffer.insert(buffer.end(), data_.begin(), data_.end());
    return buffer;
  }

 protected:
  Type type_ = Type::UNDEFINED;
  Command command_ = Command::UNDEFINED;
  std::vector<uint8_t> data_;
};

static const std::map<SoundSendPacket::Command, std::string> COMMAND_NAMES = {
    {SoundSendPacket::Command::REPLY_FINISH, "REPLY_FINISH"},
    {SoundSendPacket::Command::MODULE_VERSIONS, "MODULE_VERSIONS"},
    {SoundSendPacket::Command::MUTE, "MUTE"},
    {SoundSendPacket::Command::VOLUME, "VOLUME"},
    {SoundSendPacket::Command::AUDIO_SOURCE, "AUDIO_SOURCE"},
    {SoundSendPacket::Command::POWER, "POWER"},
    {SoundSendPacket::Command::AUDIO_MODE, "AUDIO_MODE"},
    {SoundSendPacket::Command::SPEAKER_TRIM, "SPEAKER_TRIM"},
    {SoundSendPacket::Command::LIP_SYNC, "LIP_SYNC"},
    {SoundSendPacket::Command::CHIME_SPEAKER, "CHIME_SPEAKER"},
    {SoundSendPacket::Command::EQ_HIGH, "EQ_HIGH"},
    {SoundSendPacket::Command::EQ_MID_RANGE, "EQ_MID_RANGE"},
    {SoundSendPacket::Command::EQ_VOICE, "EQ_VOICE"},
    {SoundSendPacket::Command::EQ_MID_BASS, "EQ_MID_BASS"},
    {SoundSendPacket::Command::EQ_SUB, "EQ_SUB"},
    {SoundSendPacket::Command::AUDIO_FORMAT, "AUDIO_FORMAT"},
    {SoundSendPacket::Command::VIRTUAL_DOLBY, "VIRTUAL_DOLBY"},
    {SoundSendPacket::Command::BASS_MANAGEMENT, "BASS_MANAGEMENT"},
    {SoundSendPacket::Command::UNDEFINED, "UNDEFINED"},
};

class SoundSendTxPacket : public SoundSendPacket {
 public:
  SoundSendTxPacket(Type type, Command command, std::vector<uint8_t> data) : SoundSendPacket(type, command, data) {}

  uint32_t tx_time() { return this->tx_time_; }
  bool is_sent() { return this->tx_time_ != 0; }
  void sent() {
    if (this->tx_time_ == 0) {
      this->tx_time_ = millis();
    }
  }

  uint8_t attempts() { return this->retry_attempts_; }
  void add_attempt() {
    this->tx_time_ = 0;
    this->retry_attempts_++;
  }

 protected:
  uint32_t tx_time_ = 0;
  uint8_t retry_attempts_ = 0;
};

class SoundSendRxPacket : public SoundSendPacket {
 public:
  SoundSendRxPacket() : SoundSendPacket() {}
  SoundSendRxPacket(uint8_t *data, uint8_t length) : SoundSendPacket(data, length) {
    if (length > 4) {
      this->stitch_length_ = data[4];
    }
    this->stitch(data, length);
  }

  void stitch(uint8_t *data, uint8_t length) {
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

  bool is_satisfied() {
    switch (this->stitch_type()) {
      case StitchType::TO_SINGLE:
        return this->stitch_map_.at(0).size() == this->stitch_length_;
      case StitchType::TO_MULTI:
        return this->stitch_map_.size() > 0 && this->command() == Command::REPLY_FINISH;
      default:
        return true;
    }
  }
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
