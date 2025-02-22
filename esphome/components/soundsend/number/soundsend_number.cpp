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

void TrimFrontLeftNumber::control(float value) { this->parent_->set_trim_front_left(value); }
void TrimFrontRightNumber::control(float value) { this->parent_->set_trim_front_right(value); }
void TrimCenterNumber::control(float value) { this->parent_->set_trim_center(value); }
void TrimSubwooferNumber::control(float value) { this->parent_->set_trim_subwoofer(value); }
void TrimSurroundLeftNumber::control(float value) { this->parent_->set_trim_surround_left(value); }
void TrimSurroundRightNumber::control(float value) { this->parent_->set_trim_surround_right(value); }

}  // namespace soundsend
}  // namespace esphome
