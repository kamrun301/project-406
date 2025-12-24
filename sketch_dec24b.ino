#include <DHT.h>

// --- DHT11 Setup ---
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- Sensor & Actuator Pins ---
#define SOUND_ANALOG A0
#define WATER_SENSOR A1
#define BUZZER_PIN 8

// --- Thresholds ---
#define SOUND_THRESHOLD 100
#define WATER_THRESHOLD 10

void setup() {
  Serial.begin(9600);
  delay(1000);

  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT); 

  Serial.println("UNO R3 Sensor Test Starting...");
}

void loop() {
  // ---------- Sound Sensor (Smooth with 5 readings) ----------
  int soundSum = 0;
  for (int i = 0; i < 5; i++) {
    soundSum += analogRead(SOUND_ANALOG);
    delay(2);
  }
  int soundValue = soundSum / 5;

  // ---------- Water Level Sensor ----------
  int waterValue = analogRead(WATER_SENSOR);

  // ---------- DHT11 ----------
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); 

  // ---------- Buzzer Logic ----------
  if (soundValue > SOUND_THRESHOLD && waterValue > WATER_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println(">>> ALERT: BOTH Sound AND Water Detected! <<<"); 
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // ---------- Human-readable Serial Output ----------
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11!");
  } else {
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print(" °C  |  Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Sound Level: ");
  Serial.println(soundValue);

  Serial.print("Water Level: ");
  Serial.println(waterValue);

  Serial.println("--------------------------");

  // ---------- JSON Output for Python MQTT ----------
  if (!isnan(humidity) && !isnan(temperature)) {
    Serial.print("{\"temperature\":");
    Serial.print(temperature);
    Serial.print(",\"humidity\":");
    Serial.print(humidity);
    Serial.print(",\"sound\":");
    Serial.print(soundValue);
    Serial.print(",\"water\":");
    Serial.print(waterValue);
    Serial.println("}");
  }

  delay(1000); 
}

