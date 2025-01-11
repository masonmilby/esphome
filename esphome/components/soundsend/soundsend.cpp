#include "soundsend.h"

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace soundsend {
static const char *const TAG = "soundsend";

void SoundSendComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "SoundSend:");
  ESP_LOGCONFIG(TAG, "  MAC: %s", this->parent()->address_str().c_str());
}

void SoundSendComponent::gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                                             esp_ble_gattc_cb_param_t *param) {
  switch (event) {
    case ESP_GATTC_SEARCH_CMPL_EVT: {
      this->char_handle_ = 0;
      auto *chr = this->parent()->get_characteristic(SERVICE_UUID_, CHAR_UUID_);

      if (chr == nullptr) {
        ESP_LOGW(TAG, "Characteristic not found. Incorrect MAC address?");
        this->parent()->set_enabled(false);
        this->parent()->set_enabled(true);
        break;
      }

      this->char_handle_ = chr->handle;
      esp_err_t status = esp_ble_gattc_register_for_notify(this->parent()->get_gattc_if(),
                                                           this->parent()->get_remote_bda(), this->char_handle_);
      if (status != ESP_OK) {
        ESP_LOGW(TAG, "Notification registration failed (%s)", esp_err_to_name(status));
      }
      break;
    }

    case ESP_GATTC_REG_FOR_NOTIFY_EVT: {
      if (param->reg_for_notify.handle != this->char_handle_) {
        break;
      }

      this->node_state = espbt::ClientState::ESTABLISHED;
      ESP_LOGI(TAG, "Notifications enabled");
      this->get_initial();
      break;
    }

    case ESP_GATTC_NOTIFY_EVT: {
      if (param->notify.handle == this->char_handle_) {
        this->parse_reply_(param->notify.value, param->notify.value_len);
      }
      break;
    }

    default:
      break;
  }
}

// Numbers
void SoundSendComponent::get_volume() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::VOLUME);
}
void SoundSendComponent::get_lip_sync() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::LIP_SYNC);
}
void SoundSendComponent::get_eq_high() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::EQ_HIGH);
}
void SoundSendComponent::get_eq_mid_range() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::EQ_MID_RANGE);
}
void SoundSendComponent::get_eq_voice() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::EQ_VOICE);
}
void SoundSendComponent::get_eq_mid_bass() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::EQ_MID_BASS);
}
void SoundSendComponent::get_eq_sub() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::EQ_SUB);
}

void SoundSendComponent::set_volume(uint8_t value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::VOLUME, {value});
}
void SoundSendComponent::set_lip_sync(uint8_t value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::LIP_SYNC, {value});
}
void SoundSendComponent::set_eq_high(uint8_t value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::EQ_HIGH, {value});
}
void SoundSendComponent::set_eq_mid_range(uint8_t value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::EQ_MID_RANGE, {value});
}
void SoundSendComponent::set_eq_voice(uint8_t value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::EQ_VOICE, {value});
}
void SoundSendComponent::set_eq_mid_bass(uint8_t value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::EQ_MID_BASS, {value});
}
void SoundSendComponent::set_eq_sub(uint8_t value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::EQ_SUB, {value});
}

// Switches
void SoundSendComponent::get_mute() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::MUTE);
}
void SoundSendComponent::get_power() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::POWER);
}
void SoundSendComponent::get_virtual_dolby() {
  if (this->is_audio_mode(AudioMode::DIRECT)) {
    ESP_LOGW(TAG, "Disabling Virtual Dolby configuration while in Direct audio mode");
    this->virtual_dolby_switch_->publish_state(false);
  } else {
    this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::VIRTUAL_DOLBY);
  }
}
void SoundSendComponent::get_bass_management() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::BASS_MANAGEMENT);
}

void SoundSendComponent::set_mute(bool value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::MUTE, {value});
}
void SoundSendComponent::set_power(bool value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::POWER, {value});
}
void SoundSendComponent::set_virtual_dolby(bool value) {
  if (this->is_audio_mode(AudioMode::DIRECT)) {
    ESP_LOGW(TAG, "Virtual Dolby cannot be configured in Direct audio mode (to prevent WiSA app issues)");
  } else {
    this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::VIRTUAL_DOLBY, {value});
  }
}
void SoundSendComponent::set_bass_management(bool value) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::BASS_MANAGEMENT, {value});
}

// Text sensors
void SoundSendComponent::get_module_versions() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::MODULE_VERSIONS);
}
void SoundSendComponent::get_audio_format() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::AUDIO_FORMAT);
}

// Selects
void SoundSendComponent::get_audio_source() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::AUDIO_SOURCE);
}
void SoundSendComponent::get_audio_mode() {
  this->queue_command(SoundSendPacket::Type::READ, SoundSendPacket::Command::AUDIO_MODE);
}

void SoundSendComponent::set_audio_source(uint8_t index) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::AUDIO_SOURCE, {index});
}
void SoundSendComponent::set_audio_mode(uint8_t index) {
  this->queue_command(SoundSendPacket::Type::WRITE, SoundSendPacket::Command::AUDIO_MODE, {index});
}

// Buttons
void SoundSendComponent::press_query() { this->get_initial(); }

bool SoundSendComponent::is_power() {
  if (this->power_switch_ == nullptr) {
    return true;
  }
  return this->power_switch_->state;
}

bool SoundSendComponent::is_audio_mode(AudioMode mode) {
  if (this->audio_mode_select_ == nullptr) {
    return false;
  }
  return this->audio_mode_select_->state == AUDIO_MODE_NAMES.at(mode);
}

void SoundSendComponent::get_initial() {
  ESP_LOGI(TAG, "Getting initial state...");

  this->get_power();
  this->get_audio_mode();

  this->get_volume();
  this->get_lip_sync();
  this->get_eq_high();
  this->get_eq_mid_range();
  this->get_eq_voice();
  this->get_eq_mid_bass();
  this->get_eq_sub();

  this->get_mute();
  this->get_virtual_dolby();
  this->get_bass_management();

  this->get_module_versions();
  this->get_audio_format();

  this->get_audio_source();
}

void SoundSendComponent::queue_command(SoundSendPacket::Type type, SoundSendPacket::Command command,
                                       std::vector<uint8_t> data) {
  ESP_LOGD(TAG, "Queueing command (%s)", COMMAND_NAMES.at(command).c_str());
  SoundSendTxPacket packet(type, command, data);
  this->ble_tx_queue_.push(packet);
}

void SoundSendComponent::pop_queue_() {
  if (!this->ble_tx_queue_.empty()) {
    this->ble_tx_queue_.pop();
  }
  ESP_LOGD(TAG, "Tx queue size: %d", this->ble_tx_queue_.size());
}

void SoundSendComponent::process_queue_() {
  if (this->ble_tx_queue_.empty()) {
    return;
  }

  if (!this->parent()->connected()) {
    ESP_LOGW(TAG, "BLE not connected; Clearing queue");
    this->clear_queue_();
    return;
  }

  SoundSendTxPacket &tx_packet = this->ble_tx_queue_.front();

  if (tx_packet.is_sent()) {
    if ((millis() - tx_packet.tx_time()) > BLE_RX_TIMEOUT_MS_) {
      ESP_LOGW(TAG, "BLE Rx timeout; Popping queue");
      this->pop_queue_();
    }
    if (tx_packet.attempts() >= BLE_MAX_TX_ATTEMPTS_) {
      ESP_LOGW(TAG, "Max Rx attempts reached; Popping queue");
      this->pop_queue_();
    }
    return;
  }

  if (!this->is_power() && (tx_packet.command() != SoundSendPacket::Command::POWER)) {
    ESP_LOGW(TAG, "Power is off; Clearing queue");
    this->clear_queue_();
    return;
  }

  std::vector<uint8_t> tx_buffer = tx_packet.build();
  ESP_LOGD(TAG, "Processing command (%s - %s)", COMMAND_NAMES.at(tx_packet.command()).c_str(),
           format_hex_pretty(tx_buffer).c_str());

  tx_packet.sent();
  esp_ble_gattc_write_char(this->parent()->get_gattc_if(), this->parent()->get_conn_id(), this->char_handle_,
                           tx_buffer.size(), tx_buffer.data(), ESP_GATT_WRITE_TYPE_NO_RSP, ESP_GATT_AUTH_REQ_NONE);
}

void SoundSendComponent::parse_reply_(uint8_t *data, uint16_t length) {
  SoundSendRxPacket rx_packet(data, length);
  ESP_LOGD(TAG, "Parsing reply (%s - %s)", COMMAND_NAMES.at(rx_packet.command()).c_str(),
           format_hex_pretty(data, length).c_str());

  if (!rx_packet.is_satisfied()) {
    if (this->ble_rx_buffer_.command() == rx_packet.command()) {
      this->ble_rx_buffer_.stitch(data, length);
      if (this->ble_rx_buffer_.is_satisfied()) {
        ESP_LOGD(TAG, "Multi-packet satisfied; Continuing parse");
        rx_packet = this->ble_rx_buffer_;
        this->ble_rx_buffer_ = SoundSendRxPacket();
      } else {
        ESP_LOGW(TAG, "Multi-packet unsatisfied; Skipping parse");
        return;
      }
    } else {
      ESP_LOGW(TAG, "Received multi-packet with unexpected command; Swapping buffer");
      this->ble_rx_buffer_ = rx_packet;
      return;
    }
  }

  if (rx_packet.type() == SoundSendPacket::Type::REPLY) {
    switch (rx_packet.command()) {
      // Numbers
      case SoundSendPacket::Command::VOLUME:
        if (this->volume_number_ != nullptr) {
          this->volume_number_->publish_state(rx_packet.to_uint8());
        }
        break;
      case SoundSendPacket::Command::LIP_SYNC:
        if (this->lip_sync_number_ != nullptr) {
          this->lip_sync_number_->publish_state(rx_packet.to_uint8());
        }
        break;
      case SoundSendPacket::Command::EQ_HIGH:
        if (this->eq_high_number_ != nullptr) {
          this->eq_high_number_->publish_state(rx_packet.to_int8());
        }
        break;
      case SoundSendPacket::Command::EQ_MID_RANGE:
        if (this->eq_mid_range_number_ != nullptr) {
          this->eq_mid_range_number_->publish_state(rx_packet.to_int8());
        }
        break;
      case SoundSendPacket::Command::EQ_VOICE:
        if (this->eq_voice_number_ != nullptr) {
          this->eq_voice_number_->publish_state(rx_packet.to_int8());
        }
        break;
      case SoundSendPacket::Command::EQ_MID_BASS:
        if (this->eq_mid_bass_number_ != nullptr) {
          this->eq_mid_bass_number_->publish_state(rx_packet.to_int8());
        }
        break;
      case SoundSendPacket::Command::EQ_SUB:
        if (this->eq_sub_number_ != nullptr) {
          this->eq_sub_number_->publish_state(rx_packet.to_int8());
        }
        break;

      // Switches
      case SoundSendPacket::Command::MUTE:
        if (this->mute_switch_ != nullptr) {
          this->mute_switch_->publish_state(rx_packet.to_uint8());
        }
        break;
      case SoundSendPacket::Command::POWER:
        if (this->power_switch_ != nullptr) {
          if (!this->power_switch_->state && rx_packet.to_uint8()) {
            if (this->ble_last_rx_time_ != 0) {
              this->get_initial();
            }
          }
          this->power_switch_->publish_state(rx_packet.to_uint8());
        }
        break;
      case SoundSendPacket::Command::VIRTUAL_DOLBY: {
        if (this->virtual_dolby_switch_ != nullptr) {
          this->virtual_dolby_switch_->publish_state(rx_packet.to_uint8());
        }
        break;
      }
      case SoundSendPacket::Command::BASS_MANAGEMENT:
        if (this->bass_management_switch_ != nullptr) {
          this->bass_management_switch_->publish_state(rx_packet.to_uint8());
        }
        break;

      // Text sensors
      case SoundSendPacket::Command::MODULE_VERSIONS: {
        if (this->module_versions_text_sensor_ != nullptr) {
          ModuleVersions versions(rx_packet.data());
          this->module_versions_text_sensor_->publish_state(versions.to_string());
        }
        break;
      }
      case SoundSendPacket::Command::AUDIO_FORMAT:
        if (this->audio_format_text_sensor_ != nullptr) {
          this->audio_format_text_sensor_->publish_state(rx_packet.to_string());
        }
        break;

      // Selects
      case SoundSendPacket::Command::AUDIO_SOURCE: {
        if (this->audio_source_select_ != nullptr) {
          optional<std::string> source_str = this->audio_source_select_->at(rx_packet.to_uint8());
          if (source_str.has_value()) {
            this->audio_source_select_->publish_state(source_str.value());
          }
        }
        break;
      }
      case SoundSendPacket::Command::AUDIO_MODE: {
        if (this->audio_mode_select_ != nullptr) {
          optional<std::string> mode_str = this->audio_mode_select_->at(rx_packet.to_uint8());
          if (mode_str.has_value()) {
            this->audio_mode_select_->publish_state(mode_str.value());
          }
        }
        this->get_virtual_dolby();
        break;
      }

      default:
        ESP_LOGW(TAG, "Unhandled reply ^");
        break;
    }
  }

  this->ble_last_rx_time_ = millis();

  if (this->ble_tx_queue_.empty()) {
    ESP_LOGW(TAG, "Unexpected reply ^");
  } else {
    SoundSendTxPacket &tx_packet = this->ble_tx_queue_.front();
    if (tx_packet.command() == rx_packet.command()) {
      this->pop_queue_();
    } else {
      ESP_LOGW(TAG, "Retrying command (%d/%d)", tx_packet.attempts(), BLE_MAX_TX_ATTEMPTS_);
      tx_packet.add_attempt();
    }
  }
}

}  // namespace soundsend
}  // namespace esphome
