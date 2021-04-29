# khronos

## TODO:

-   [ ] Galileo mode ENABLED w/ fancy animation
-   [ ] Add I/O - random deviations option
-   [x] Add with charge / overdischarge / boost to 5V circuit
-   [ ] Add Li-ION battery
-   [x] Circuit & cables
-   [x] Case
-   [ ] Adapt

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

## Magnetic switch

Ground and
