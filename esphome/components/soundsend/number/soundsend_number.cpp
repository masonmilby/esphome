#include "soundsend_number.h"

namespace esphome {
namespace soundsend {

void VolumeNumber::control(float value) { this->parent_->set_volume(value); }
void LipSyncNumber::control(float value) { this->parent_->set_lip_sync(value); }
void EqHighNumber::control(float value) { this->parent_->set_eq_high(value); }
void EqMidRangeNumber::control(float value) { this->parent_->set_eq_mid_range(value); }
void EqVoiceNumber::control(float value) { this->parent_->set_eq_voice(value); }
void EqMidBassNumber::control(float value) { this->parent_->set_eq_mid_bass(value); }
void EqSubNumber::control(float value) { this->parent_->set_eq_sub(value); }

}  // namespace soundsend
}  // namespace esphome
