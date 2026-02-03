# Anti-Clog Detector — Arduino IDE

Este firmware permite flashear el Anti-Clog Detector **sin usar la web**,
directamente desde **Arduino IDE**.

## Placas soportadas
- ESP32-C3 (recomendado)
- ESP32 (Dev Module)
- ESP32-S3

## Librerías necesarias
- Ninguna externa (Arduino core ESP32)

## Ajustes en Arduino IDE

### ESP32-C3
- Board: **ESP32C3 Dev Module**
- USB CDC On Boot: **Enabled**
- Flash Size: **4MB**
- Upload Speed: **921600**
- Baud Monitor: **115200**

### ESP32 / ESP32-S3
- Board: **ESP32 Dev Module / ESP32S3 Dev Module**
- USB CDC: **Enabled**
- Flash Size: **4MB**
- Baud Monitor: **115200**

## Pinout (MVP)
- Encoder (OUT): **GPIO 2**
- Microswitch (NO → GND): **GPIO 4**
- Runout OUT: **GPIO 5**
- Sensores: **5V + GND**

## Funcionamiento
- Sin filamento → RUNOUT
- Filamento + movimiento → OK
- Filamento sin movimiento (timeout) → CLOG
- RUNOUT_OUT = LOW en error

## Ajustes recomendados
```cpp
#define CLOG_TIMEOUT_MS 6500
#define CONFIRM_CYCLES  3
