import esphome.codegen as cg
from esphome.components import i2c

CODEOWNERS = ["@SolderedElectronics"]

bmp180_ns = cg.esphome_ns.namespace("bmp180")
BMP180Component = bmp180_ns.class_("BMP180Component", cg.PollingComponent, i2c.I2CDevice)
