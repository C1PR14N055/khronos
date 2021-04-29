# KHRONOS (+/- Galileo)

## TODO:
-   [x] Galileo mode ENABLED ~~w/ Xfancy animation~~
-   [ ] Add I/O - deviation correction option (accuracy realtime vs speed = 10 vs 5 second hold option)
-   [x] Add with charge / overdischarge / boost to 5V circuit
-   [x] Add Li-ION battery
-   [x] Circuit & cables
-   [x] Case
-   [x] Adapt
-   [ ] RGB LED Blink 
-   [ ] Swtiching RGB all blink + changing UI sets LED to RED || GREEN 
-   [ ] Charging LED flashes blue
-   [ ] Data +/i wires to USB charger
-   [ ] VREF jumper (when charging)
-   [ ] Quiesent current small consumer or diode?
-   [ ] Show BATT V as X/X in corner alternating with icon
-   [ ] Lower LED power

## 1. LiquidCrystal Library - Hello World circuit

```cpp
LiquidCrystal lcd(RS, E, D4, D5, D6, D7); + VCC - GND
LiquidCrystal lcd_(12, 11, 5, 4, 3, 2);
```

-   LCD RS pin to digital pin 12
-   LCD Enable pin to digital pin 11
-   LCD D4 pin to digital pin 5
-   LCD D5 pin to digital pin 4
-   LCD D6 pin to digital pin 3
-   LCD D7 pin to digital pin 2
-   LCD R/W pin to ground
-   LCD VSS pin to ground
-   LCD VCC pin to 5V
-   10K pott
-   ends to +5V and ground
-   wiper to LCD VO pin (pin 3)

**Note** http://www.arduino.cc/en/Tutorial/LiquidCrystal

## 2. Beitian dual BN-220 GPS info

PINOUT (Left to Right) with 2 holes face up, antena faced to the ground:

1. GND
2. GPS TX
3. GPS RX
4. (3.0V - 5.5V, typical: 5V)

## 3. Magnetic switch

1. GND
2. A0 = `const int REED_PIN = A0;`

## 4. RGB LED + INTERNAL LED

Internal led: `LED_BUILTIN`  
RGB led:
```cpp
// RGB LED pins
const int LED_R_PIN = A1;
const int LED_G_PIN = A2;
const int LED_B_PIN = A3
```

## 5. VCC_BAT_ADC & VREF source
```cpp
// ADC VCC BAT for Vumeter
const int ADC_VCC_BAT = A4

float v_bat = (float)5 * analogRead(ADC_VCC_BAT) / 1024; // 10 BIT int converted to float voltage
```
