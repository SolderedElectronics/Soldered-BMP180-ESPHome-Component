/**
 * @file bmp180.h
 * @brief Public API for the bmp180 ESPHome sensor component
 * @author Soldered Electronics
 */

#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

#include "bmp180_compensation.h"

namespace esphome {
namespace bmp180 {

/**
 * @brief Soldered BMP180 temperature and pressure sensor breakout board.
 *
 * Each update runs a temperature conversion and then a pressure conversion,
 * waiting for both with timeouts instead of blocking the main loop. The register
 * map and compensation math are in bmp180_compensation.h, shared unchanged with
 * the Soldered BMP180 ESP-IDF component.
 */
class BMP180Component : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  void set_pressure_sensor(sensor::Sensor *sensor) { this->pressure_sensor_ = sensor; }
  void set_temperature_sensor(sensor::Sensor *sensor) { this->temperature_sensor_ = sensor; }
  void set_oversampling(uint8_t oss) { this->oss_ = oss; }

 protected:
  /// Reads the temperature result and starts the pressure conversion.
  void read_temperature_();
  /// Reads the pressure result and publishes both values.
  void read_pressure_();

  sensor::Sensor *pressure_sensor_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};
  uint8_t oss_{3};
  int32_t ut_{0};
  ::bmp180_calib_t calib_{};
};

}  // namespace bmp180
}  // namespace esphome
