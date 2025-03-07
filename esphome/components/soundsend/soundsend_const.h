#pragma once

#include <vector>
#include <map>
#include <string>

namespace esphome {
namespace soundsend {

enum class PacketType : uint8_t {
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
  SURROUND_LEFT = 0x5,
  SURROUND_RIGHT = 0x8,
  BACK_LEFT = 0x6,
  BACK_RIGHT = 0x7,

  TOP_FRONT_LEFT = 0xE,
  TOP_FRONT_RIGHT = 0xF,
  TOP_SURROUND_LEFT = 0x10,
  TOP_SURROUND_RIGHT = 0x11,
  TOP_BACK_LEFT = 0x12,
  TOP_BACK_RIGHT = 0x13,
};

static const std::map<PacketType, std::string> PACKET_TYPE_NAMES = {
    {PacketType::READ, "READ"},
    {PacketType::WRITE, "WRITE"},
    {PacketType::REPLY, "REPLY"},
    {PacketType::UNDEFINED, "UNDEFINED"},
};

static const std::map<Command, std::string> COMMAND_NAMES = {
    {Command::REPLY_FINISH, "REPLY_FINISH"},
    {Command::MODULE_VERSIONS, "MODULE_VERSIONS"},
    {Command::MUTE, "MUTE"},
    {Command::VOLUME, "VOLUME"},
    {Command::AUDIO_SOURCE, "AUDIO_SOURCE"},
    {Command::POWER, "POWER"},
    {Command::AUDIO_MODE, "AUDIO_MODE"},
    {Command::SPEAKER_TRIM, "SPEAKER_TRIM"},
    {Command::LIP_SYNC, "LIP_SYNC"},
    {Command::CHIME_SPEAKER, "CHIME_SPEAKER"},
    {Command::EQ_HIGH, "EQ_HIGH"},
    {Command::EQ_MID_RANGE, "EQ_MID_RANGE"},
    {Command::EQ_VOICE, "EQ_VOICE"},
    {Command::EQ_MID_BASS, "EQ_MID_BASS"},
    {Command::EQ_SUB, "EQ_SUB"},
    {Command::AUDIO_FORMAT, "AUDIO_FORMAT"},
    {Command::VIRTUAL_DOLBY, "VIRTUAL_DOLBY"},
    {Command::BASS_MANAGEMENT, "BASS_MANAGEMENT"},
    {Command::UNDEFINED, "UNDEFINED"},
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
    {SpeakerType::SURROUND_LEFT, "Surround Left"},
    {SpeakerType::SURROUND_RIGHT, "Surround Right"},
    {SpeakerType::BACK_LEFT, "Back Left"},
    {SpeakerType::BACK_RIGHT, "Back Right"},
    {SpeakerType::TOP_FRONT_LEFT, "Front Left Height"},
    {SpeakerType::TOP_FRONT_RIGHT, "Front Right Height"},
    {SpeakerType::TOP_SURROUND_LEFT, "Surround Left Height"},
    {SpeakerType::TOP_SURROUND_RIGHT, "Surround Right Height"},
    {SpeakerType::TOP_BACK_LEFT, "Back Left Height"},
    {SpeakerType::TOP_BACK_RIGHT, "Back Right Height"},
};

struct SpeakerTrim {
  SpeakerTrim(const std::vector<uint8_t> data) {
    this->speaker_ = static_cast<SpeakerType>(data[0]);
    this->value_ = static_cast<int8_t>(data[1]);
  }

  SpeakerType speaker() { return this->speaker_; }
  int8_t value() { return this->value_; }

 protected:
  SpeakerType speaker_;
  int8_t value_;
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

}  // namespace soundsend
}  // namespace esphome
