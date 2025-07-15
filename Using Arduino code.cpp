#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Light variables
int lightValue = 600;       // Start from mid value
int lightChangeStep = 5;    // Small change per loop

unsigned long startTime;

void setup() {
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT_PULLUP);
  dht.begin();
  startTime = millis();
  Serial.println("DHT11 Sensor Output with Light and Time (seconds)");
}

void loop() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Simulate minimal change in light value
  int direction = random(-1, 2);  // -1, 0, or 1
  lightValue += direction * lightChangeStep;

  // Keep light value in safe range
  if (lightValue < 500) lightValue = 500;
  if (lightValue > 700) lightValue = 700;

  if (isnan(h) || isnan(t)) {
    Serial.println("❌ Failed to read from DHT11 sensor!");
    return;
  }

  unsigned long currentTime = millis();
  unsigned long elapsedTimeSec = (currentTime - startTime) / 1000;

  Serial.print("🕒 Time: ");
  Serial.print(elapsedTimeSec);
  Serial.print(" sec\t");

  Serial.print("🌡 Temp: ");
  Serial.print(t);
  Serial.print(" °C\t");

  Serial.print("💧 Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");

  Serial.print("💡 Light: ");
  Serial.println(lightValue);
}
