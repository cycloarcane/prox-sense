// Proximity Alert System — ESP32 WROOM
// IN1/D19=Green  IN2/D21=Yellow  IN3/D22=Red  IN4/D23=Buzzer

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;

const int RELAY[4] = {19, 21, 22, 23};

const bool ACTIVE_LOW = true;  // These modules trigger on LOW

const int ZONE_THRESHOLDS[] = {50, 40, 30, 10};

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(RELAY[i], OUTPUT);
    setRelay(i, false);  // All off at start
  }

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

  delay(100);
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