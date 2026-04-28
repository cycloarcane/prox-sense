// Proximity Alert System — ESP32 WROOM
// HC-SR04 + 4 relays + GC9A01 Angry Eye Display

#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
const int RELAY[4] = {19, 21, 22, 23};
const bool ACTIVE_LOW = true;
const int ZONE_THRESHOLDS[] = {80, 60, 40, 20};

// Eye animation state
int currentZone = 0;
int lastZone = -1;

// Colours per zone — match LED relays
const uint32_t IRIS_COLOURS[] = {
  TFT_BLUE,    // Zone 0 — calm, no LED
  TFT_GREEN,   // Zone 1 — green LED
  TFT_YELLOW,  // Zone 2 — yellow LED
  TFT_RED,     // Zone 3 — red LED
  TFT_RED      // Zone 4 — flashing red + buzzer
};

bool flashOn = true;
unsigned long lastFlash = 0;
const unsigned long FLASH_INTERVAL_MS = 200;

// Brow angle offset per zone (how far inner brow drops)
const int BROW_ANGER[] = {0, 0, 15, 30, 45};

// Pupil radius per zone
const int PUPIL_RADIUS[] = {25, 20, 28, 35, 45};

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(RELAY[i], OUTPUT);
    setRelay(i, false);
  }

  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  drawEye(0, true);
  Serial.println("Proximity Alert System — Ready");
}

void loop() {
  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  int activeZones = 0;
  for (int i = 0; i < 4; i++) {
    if (distance < ZONE_THRESHOLDS[i]) activeZones = i + 1;
  }

  for (int i = 0; i < 4; i++) {
    setRelay(i, i < activeZones);
  }

  bool zoneChanged = (activeZones != lastZone);
  bool flashTick = false;
  if (activeZones == 4 && millis() - lastFlash >= FLASH_INTERVAL_MS) {
    flashOn = !flashOn;
    lastFlash = millis();
    flashTick = true;
  } else if (activeZones != 4) {
    flashOn = true;
  }

  if (zoneChanged || flashTick) {
    drawEye(activeZones, flashOn);
    lastZone = activeZones;
  }

  delay(50);
}

void drawEye(int zone, bool flashState) {
  int cx = 120, cy = 120;

  uint32_t irisColour = (zone == 4 && !flashState) ? TFT_BLACK : IRIS_COLOURS[zone];

  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(cx, cy, 95, TFT_WHITE);
  tft.fillCircle(cx, cy, 58, irisColour);
  tft.fillCircle(cx, cy, PUPIL_RADIUS[zone], TFT_BLACK);
  tft.fillCircle(cx - 15, cy - 15, 8, TFT_WHITE);

  int anger = BROW_ANGER[zone];
  int browY = cy - 85;
  int browThickness = 10 + (zone * 2);

  int bx1 = cx - 70, by1 = browY + anger;
  int bx2 = cx + 70, by2 = browY;
  int bx3 = cx + 70, by3 = browY + browThickness;
  int bx4 = cx - 70, by4 = browY + browThickness + anger;
  tft.fillTriangle(bx1, by1, bx2, by2, bx3, by3, TFT_BLACK);
  tft.fillTriangle(bx1, by1, bx3, by3, bx4, by4, TFT_BLACK);
}

void setRelay(int index, bool state) {
  digitalWrite(RELAY[index], ACTIVE_LOW ? !state : state);
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}