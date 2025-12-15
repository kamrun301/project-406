#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

// --- Sensor & Actuator Pins ---
#define SOUND_ANALOG A0
#define WATER_SENSOR A1
#define BUZZER_PIN 8 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);

  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT); 

  Serial.println("UNO R4 Sensor Test Starting...");
}

void loop() {
  // ---------- Sound Sensor ----------
  int soundValue = analogRead(SOUND_ANALOG);

  // ---------- Water Level Sensor ----------
  int waterValue = analogRead(WATER_SENSOR);

  // ---------- DHT11 ----------
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); 

  // ---------- Buzzer Logic ----------
  // MODIFIED: Uses "&&" (AND)
  // Buzzer ONLY turns ON if Sound > 87 AND Water > 0 at the same time
  if (soundValue > 87 && waterValue > 0) {
    digitalWrite(BUZZER_PIN, HIGH);   // Turn buzzer ON
    Serial.println(">>> ALERT: BOTH Sound AND Water Detected! <<<"); 
  } else {
    digitalWrite(BUZZER_PIN, LOW);    // Turn buzzer OFF
  }

  // ---------- Serial Monitor Output ----------
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
  
  delay(1000); 
}