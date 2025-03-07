#include "soundsend_number.h"

namespace esphome {
namespace soundsend {

void VolumeNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::VOLUME, {static_cast<uint8_t>(value)});
}
void LipSyncNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::LIP_SYNC, {static_cast<uint8_t>(value)});
}
void EqHighNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::EQ_HIGH, {static_cast<uint8_t>(value)});
}
void EqMidRangeNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::EQ_MID_RANGE, {static_cast<uint8_t>(value)});
}
void EqVoiceNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::EQ_VOICE, {static_cast<uint8_t>(value)});
}
void EqMidBassNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::EQ_MID_BASS, {static_cast<uint8_t>(value)});
}
void EqSubNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::EQ_SUB, {static_cast<uint8_t>(value)});
}

void TrimFrontLeftNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::SPEAKER_TRIM,
                               {static_cast<uint8_t>(SpeakerType::FRONT_LEFT), static_cast<uint8_t>(value)});
}
void TrimFrontRightNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::SPEAKER_TRIM,
                               {static_cast<uint8_t>(SpeakerType::FRONT_RIGHT), static_cast<uint8_t>(value)});
}
void TrimCenterNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::SPEAKER_TRIM,
                               {static_cast<uint8_t>(SpeakerType::CENTER), static_cast<uint8_t>(value)});
}
void TrimSubwooferNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::SPEAKER_TRIM,
                               {static_cast<uint8_t>(SpeakerType::SUBWOOFER), static_cast<uint8_t>(value)});
}
void TrimSurroundLeftNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::SPEAKER_TRIM,
                               {static_cast<uint8_t>(SpeakerType::SURROUND_LEFT), static_cast<uint8_t>(value)});
}
void TrimSurroundRightNumber::control(float value) {
  this->parent_->queue_command(PacketType::WRITE, Command::SPEAKER_TRIM,
                               {static_cast<uint8_t>(SpeakerType::SURROUND_RIGHT), static_cast<uint8_t>(value)});
}

}  // namespace soundsend
}  // namespace esphome
