#pragma once

#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/core/component.h"
#include "esphome/core/defines.h"

#include "soundsend_const.h"
#include "soundsend_packet.h"

#include <esp_gattc_api.h>

#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif

#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif

#ifdef USE_TEXT_SENSOR
#include "esphome/components/text_sensor/text_sensor.h"
#endif

#ifdef USE_SELECT
#include "esphome/components/select/select.h"
#endif

#ifdef USE_BUTTON
#include "esphome/components/button/button.h"
#endif

namespace esphome {
namespace soundsend {

namespace espbt = esphome::esp32_ble_tracker;

class SoundSendComponent : public Component, public esphome::ble_client::BLEClientNode {
#ifdef USE_NUMBER
  SUB_NUMBER(volume)
  SUB_NUMBER(lip_sync)
  SUB_NUMBER(eq_high)
  SUB_NUMBER(eq_mid_range)
  SUB_NUMBER(eq_voice)
  SUB_NUMBER(eq_mid_bass)
  SUB_NUMBER(eq_sub)

  SUB_NUMBER(trim_front_left)
  SUB_NUMBER(trim_front_right)
  SUB_NUMBER(trim_center)
  SUB_NUMBER(trim_subwoofer)
  SUB_NUMBER(trim_surround_left)
  SUB_NUMBER(trim_surround_right)
#endif

#ifdef USE_SWITCH
  SUB_SWITCH(mute)
  SUB_SWITCH(power)
  SUB_SWITCH(virtual_dolby)
  SUB_SWITCH(bass_management)
#endif

#ifdef USE_TEXT_SENSOR
  SUB_TEXT_SENSOR(module_versions)
  SUB_TEXT_SENSOR(audio_format)
#endif

#ifdef USE_SELECT
  SUB_SELECT(audio_source)
  SUB_SELECT(audio_mode)
#endif

#ifdef USE_BUTTON
  SUB_BUTTON(query)
#endif

 public:
  const char *const TAG = "soundsend";

  void dump_config() override;
  void setup() override {}
  void loop() override { this->process_queue_(); }

  float get_setup_priority() const override { return setup_priority::LATE; }

  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                           esp_ble_gattc_cb_param_t *param) override;

  // Numbers
  void get_volume();
  void get_lip_sync();
  void get_eq_high();
  void get_eq_mid_range();
  void get_eq_voice();
  void get_eq_mid_bass();
  void get_eq_sub();

  void get_trim_front_left();
  void get_trim_front_right();
  void get_trim_center();
  void get_trim_subwoofer();
  void get_trim_surround_left();
  void get_trim_surround_right();

  // Switches
  void get_mute();
  void get_power();
  void get_virtual_dolby();
  void get_bass_management();

  // Text sensors
  void get_module_versions();
  void get_audio_format();

  // Selects
  void get_audio_source();
  void get_audio_mode();

  bool is_power();
  bool is_audio_mode(AudioMode mode);

  void get_initial();
  void queue_command(PacketType type, Command command, std::vector<uint8_t> data = {});

 protected:
  void pop_queue_();
  void clear_queue_() { this->ble_tx_queue_ = {}; }
  void process_queue_();
  void parse_reply_(uint8_t *data, uint16_t length);

  const espbt::ESPBTUUID SERVICE_UUID_ = espbt::ESPBTUUID::from_raw("97ded94c-b564-48ab-ba96-7e1d2daa0edd");
  const espbt::ESPBTUUID CHAR_UUID_ = espbt::ESPBTUUID::from_raw("a4a8d442-b8d0-404c-a0fb-f120115acf5e");
  const uint16_t BLE_RX_TIMEOUT_MS_ = 3000;
  const uint8_t BLE_MAX_TX_ATTEMPTS_ = 3;

  uint16_t char_handle_;

  std::queue<SoundSendTxPacket> ble_tx_queue_;
  SoundSendRxPacket ble_rx_buffer_;
  uint32_t ble_last_rx_time_ = 0;
};

}  // namespace soundsend
}  // namespace esphome