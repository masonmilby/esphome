#pragma once

#include "esphome/components/number/number.h"
#include "../soundsend.h"

namespace esphome {
namespace soundsend {

class VolumeNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  VolumeNumber() = default;

 protected:
  void control(float value) override;
};

class LipSyncNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  LipSyncNumber() = default;

 protected:
  void control(float value) override;
};

class EqHighNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  EqHighNumber() = default;

 protected:
  void control(float value) override;
};

class EqMidRangeNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  EqMidRangeNumber() = default;

 protected:
  void control(float value) override;
};

class EqVoiceNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  EqVoiceNumber() = default;

 protected:
  void control(float value) override;
};

class EqMidBassNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  EqMidBassNumber() = default;

 protected:
  void control(float value) override;
};

class EqSubNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  EqSubNumber() = default;

 protected:
  void control(float value) override;
};

class TrimFrontLeftNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  TrimFrontLeftNumber() = default;

 protected:
  void control(float value) override;
};

class TrimFrontRightNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  TrimFrontRightNumber() = default;

 protected:
  void control(float value) override;
};

class TrimCenterNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  TrimCenterNumber() = default;

 protected:
  void control(float value) override;
};

class TrimSubwooferNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  TrimSubwooferNumber() = default;

 protected:
  void control(float value) override;
};

class TrimSurroundLeftNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  TrimSurroundLeftNumber() = default;

 protected:
  void control(float value) override;
};

class TrimSurroundRightNumber : public number::Number, public Parented<SoundSendComponent> {
 public:
  TrimSurroundRightNumber() = default;

 protected:
  void control(float value) override;
};

}  // namespace soundsend
}  // namespace esphome
