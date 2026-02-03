#include <Arduino.h>

// ===== PINOUT (ESP32-C3 MVP) =====
#define ENCODER_PIN   2   // Encoder óptico (3 pines)
#define PRESENCE_PIN  4   // Microswitch (NO a GND)
#define RUNOUT_OUT    5   // Salida runout a impresora (LOW = error)

// ===== TUNING MVP =====
#define CLOG_TIMEOUT_MS 6500
#define CONFIRM_CYCLES  3
#define PRINT_MS        3500

// ===== ESTADOS =====
enum State { NO_FILAMENT, MOVING_OK, STOPPED_EXPECTED, CLOG_DETECTED };
State state = NO_FILAMENT;

// ===== RUNTIME =====
volatile uint32_t pulses = 0;
volatile unsigned long lastPulseMs = 0;
uint8_t noMoveCycles = 0;
unsigned long lastPrintMs = 0;

// ===== ISR =====
void IRAM_ATTR encoderISR() {
  pulses++;
  lastPulseMs = millis();
}

const char* s2str(State s){
  switch(s){
    case NO_FILAMENT: return "NO_FILAMENT";
    case MOVING_OK: return "MOVING_OK";
    case STOPPED_EXPECTED: return "STOPPED_EXPECTED";
    case CLOG_DETECTED: return "CLOG_DETECTED";
    default: return "UNKNOWN";
  }
}

void setup() {
  Serial.begin(115200);
  delay(800);
  Serial.println("Anti-Clog Detector - ARDUINO IDE (PASO 1)");

  pinMode(ENCODER_PIN, INPUT_PULLUP);
  pinMode(PRESENCE_PIN, INPUT_PULLUP);
  pinMode(RUNOUT_OUT, OUTPUT);
  digitalWrite(RUNOUT_OUT, HIGH); // normal

  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderISR, FALLING);
  lastPulseMs = millis();
}

void loop() {
  unsigned long now = millis();
  bool filamentPresent = (digitalRead(PRESENCE_PIN) == LOW);
  bool moving = (now - lastPulseMs) < CLOG_TIMEOUT_MS;

  if (!filamentPresent) {
    state = NO_FILAMENT;
    noMoveCycles = 0;
  } else if (moving) {
    state = MOVING_OK;
    noMoveCycles = 0;
  } else {
    if (++noMoveCycles >= CONFIRM_CYCLES) state = CLOG_DETECTED;
    else state = STOPPED_EXPECTED;
  }

  digitalWrite(RUNOUT_OUT,
    (state == CLOG_DETECTED || state == NO_FILAMENT) ? LOW : HIGH);

  if (now - lastPrintMs >= PRINT_MS) {
    lastPrintMs = now;
    Serial.println("----- STATUS -----");
    Serial.print("State: "); Serial.println(s2str(state));
    Serial.print("Filament: "); Serial.println(filamentPresent ? "YES" : "NO");
    Serial.print("Pulses: "); Serial.println(pulses);
    Serial.print("Last pulse (ms): "); Serial.println(now - lastPulseMs);
    Serial.print("RUNOUT_OUT: "); Serial.println(digitalRead(RUNOUT_OUT) ? "HIGH" : "LOW");
    Serial.println("------------------");
  }
}
