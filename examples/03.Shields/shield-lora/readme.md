## RAW Example For ESPea Lora Shield ##

For the shield, the config for pins

```
// Example with NO DIO pin connected
const lmic_pinmap lmic_pins = {
    .nss = 16,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = LMIC_UNUSED_PIN,
    .dio = {LMIC_UNUSED_PIN, LMIC_UNUSED_PIN, LMIC_UNUSED_PIN},
};
```

### Installing ###

* Install library arduino-lmic by hallard
 * Install it using the Arduino Library manager ("Sketch" -> "Include Library" -> "Manage Libraries..."), or
 * Download a zipfile from [github](https://github.com/hallard/arduino-lmic) using the "Download ZIP" button and install it using the IDE ("Sketch" -> "Include Library" -> "Add .ZIP Library..."
 * Clone this git repository into your sketchbook/libraries folder.
* Run the sktech
