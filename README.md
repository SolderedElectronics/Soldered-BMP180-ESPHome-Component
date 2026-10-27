# Soldered BMP180 ESPHome Component

| ![Pressure & temperature sensor BMP180 breakout](https://soldered.com/cdn/shop/files/333060_featured-photo_70581e_3ec34161-1c04-4f2b-b780-f5809f582bcf.jpg) |
| :---: |
| [Pressure & temperature sensor BMP180 breakout](https://www.solde.red/333060) |

The BMP180 is a Bosch barometric pressure and temperature sensor: 300 to 1100 hPa with 0.01 hPa resolution, and temperature with 0.1 °C resolution. Since pressure falls with height, it can also estimate altitude. The board uses I2C at the fixed address 0x77 and connects with an easyC/Qwiic cable, see the [Qwiic ecosystem](https://soldered.com/collections/qwiic-ecosystem).

## Repository Contents

- **components/** - the ESPHome external component (Python config + C++ implementation)
- **examples/** - example YAML configs showing how to use the component

## Usage

Reference this repo directly from your own ESPHome YAML (no need to clone it locally):

```yaml
external_components:
  - source: github://SolderedElectronics/Soldered-BMP180-ESPHome-Component
    components: [bmp180]

i2c:
  sda: GPIO21
  scl: GPIO22

sensor:
  - platform: bmp180
    update_interval: 10s
    temperature:
      name: "BMP180 Temperature"
    pressure:
      name: "BMP180 Pressure"
```

See [`examples/basic.yaml`](examples/basic.yaml) for a full working example.

### Configuration variables

- **update_interval** (*Optional*, [Time](https://esphome.io/guides/configuration-types#config-time)): how often the
  values are published. Defaults to `60s`.
- **oversampling** (*Optional*, int): pressure oversampling setting, `0` (1 sample, 5 ms) to `3` (8 samples, 26 ms).
  Higher is slower but less noisy. Defaults to `3`.
- **temperature** (*Optional*): [Sensor](https://esphome.io/components/sensor/) publishing temperature in °C.
- **pressure** (*Optional*): [Sensor](https://esphome.io/components/sensor/) publishing absolute pressure in hPa.

The I2C address is fixed at `0x77` on the BMP180.

### Hardware design

You can find hardware design for this board in the Pressure & temperature sensor BMP180 breakout hardware repository.

### Documentation

Access library documentation [here](https://docs.soldered.com/).

### About Soldered

<img src="https://raw.githubusercontent.com/SolderedElectronics/Soldered-Generic-Arduino-Library/dev/extras/Soldered-logo-color.png" alt="soldered-logo" width="500"/>

At Soldered, we design and manufacture a wide selection of electronic products to help you turn your ideas into acts and bring you one step closer to your final project. Our products are intented for makers and crafted in-house by our experienced team in Osijek, Croatia. We believe that sharing is a crucial element for improvement and innovation, and we work hard to stay connected with all our makers regardless of their skill or experience level. Therefore, all our products are open-source. Finally, we always have your back. If you face any problem concerning either your shopping experience or your electronics project, our team will help you deal with it, offering efficient customer service and cost-free technical support anytime. Some of those might be useful for you:

- [Web Store](https://www.soldered.com/shop)
- [Tutorials & Projects](https://soldered.com/learn)
- [Documentation](https://docs.soldered.com)

### Open-source license

Soldered invests vast amounts of time into hardware & software for these products, which are all open-source. Please support future development by buying one of our products.

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all designs in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, Soldered (TAVU) will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository.

## Have fun!

And thank you from your fellow makers at Soldered Electronics.
