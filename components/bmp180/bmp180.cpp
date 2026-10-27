/**
 * @file bmp180.cpp
 * @brief Implementation for the bmp180 ESPHome sensor component
 * @author Soldered Electronics
 */

#include "bmp180.h"

#include "esphome/core/log.h"

namespace esphome {
namespace bmp180 {

static const char *const TAG = "bmp180";

static constexpr uint32_t TEMPERATURE_TIMEOUT_ID = 0;
static constexpr uint32_t PRESSURE_TIMEOUT_ID = 1;

void BMP180Component::setup() {
  uint8_t chip_id;
  if (!this->read_byte(BMP180_REG_CHIP_ID, &chip_id)) {
    ESP_LOGE(TAG, "Communication with the sensor failed");
    this->mark_failed();
    return;
  }
  if (chip_id != BMP180_CHIP_ID) {
    ESP_LOGE(TAG, "Wrong chip ID 0x%02X, expected 0x%02X", chip_id, BMP180_CHIP_ID);
    this->mark_failed();
    return;
  }

  uint8_t raw[BMP180_CALIB_LEN];
  if (!this->read_bytes(BMP180_REG_CALIB, raw, sizeof(raw))) {
    ESP_LOGE(TAG, "Reading the calibration failed");
    this->mark_failed();
    return;
  }
  bmp180_parse_calib(raw, &this->calib_);
}

void BMP180Component::update() {
  if (!this->write_byte(BMP180_REG_CONTROL, BMP180_CMD_TEMPERATURE)) {
    this->status_set_warning();
    return;
  }
  this->set_timeout(TEMPERATURE_TIMEOUT_ID, BMP180_TEMPERATURE_WAIT_MS, [this]() { this->read_temperature_(); });
}

void BMP180Component::read_temperature_() {
  uint8_t data[2];
  if (!this->read_bytes(BMP180_REG_RESULT, data, sizeof(data)) ||
      !this->write_byte(BMP180_REG_CONTROL, BMP180_CMD_PRESSURE(this->oss_))) {
    this->status_set_warning();
    return;
  }
  this->ut_ = (data[0] << 8) | data[1];
  this->set_timeout(PRESSURE_TIMEOUT_ID, BMP180_PRESSURE_WAIT_MS(this->oss_), [this]() { this->read_pressure_(); });
}

void BMP180Component::read_pressure_() {
  uint8_t data[3];
  if (!this->read_bytes(BMP180_REG_RESULT, data, sizeof(data))) {
    this->status_set_warning();
    return;
  }
  const int32_t up = ((data[0] << 16) | (data[1] << 8) | data[2]) >> (8 - this->oss_);

  int32_t temperature, pressure;
  bmp180_compensate(&this->calib_, this->ut_, up, this->oss_, &temperature, &pressure);

  ESP_LOGD(TAG, "Got temperature=%.1f degC pressure=%.2f hPa", temperature / 10.0f, pressure / 100.0f);
  if (this->temperature_sensor_ != nullptr)
    this->temperature_sensor_->publish_state(temperature / 10.0f);
  if (this->pressure_sensor_ != nullptr)
    this->pressure_sensor_->publish_state(pressure / 100.0f);
  this->status_clear_warning();
}

void BMP180Component::dump_config() {
  ESP_LOGCONFIG(TAG, "BMP180:");
  LOG_I2C_DEVICE(this);
  ESP_LOGCONFIG(TAG, "  Oversampling: %u", this->oss_);
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
  LOG_SENSOR("  ", "Pressure", this->pressure_sensor_);
}

}  // namespace bmp180
}  // namespace esphome
