#include <Wire.h>                  // Library for I2C communication.
#include <Adafruit_Sensor.h>       // Base library for Adafruit sensors.
#include <Adafruit_MPU6050.h>      // Library for the MPU6050 sensor.
#include <TinyGPS++.h>             // Library for GPS module parsing.
#include <WiFi.h>                  // Library to connect to WiFi.
#include <HTTPClient.h>            // Library to make HTTP requests.

Adafruit_MPU6050 mpu;              // MPU6050 object declaration.

const int trigPin = 13;            // Pin for ultrasonic sensor trigger.
const int echoPin = 12;            // Pin for ultrasonic sensor echo.
const float SOUND_SPEED = 0.0343;  // Speed of sound in cm/µs.

TinyGPSPlus gps;                   // GPS object for data parsing.
HardwareSerial SerialGPS(1);       // Hardware serial object for GPS communication.

const char* ssid = "YOUR_WIFI_SSID";      // WiFi SSID.
const char* password = "YOUR_WIFI_PASSWORD"; // WiFi password.
const char* serverName = "http://<IP>:<PORT>/data"; // Flask server endpoint.

void setup() {
  Serial.begin(115200);                        // Initialize serial monitor.
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);   // Initialize GPS communication.

  pinMode(trigPin, OUTPUT);    // Set trigger pin as output.
  pinMode(echoPin, INPUT);     // Set echo pin as input.

  // Initialize MPU6050 sensor.
  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050!");
    while (1);
  }

  // Connect to WiFi.
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  // Wait until GPS data is available and valid.
  while (!gps.location.isValid()) {
    Serial.println("Searching for GPS signal...");
    delay(1000);
    while (SerialGPS.available() > 0) {
      gps.encode(SerialGPS.read());
    }
  }
  float gpsLongitude = gps.location.lng(); // Get longitude.
  float gpsLatitude = gps.location.lat();  // Get latitude.

  // Read MPU6050 sensor data.
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float mpuX = a.acceleration.x;  // Acceleration on X-axis.
  float mpuY = a.acceleration.y;  // Acceleration on Y-axis.
  float mpuZ = a.acceleration.z;  // Acceleration on Z-axis.

  // Measure distance using ultrasonic sensor.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float ultrasonicDistance = duration * SOUND_SPEED / 2;

  // Display data in Serial Monitor.
  Serial.println("Data ready to send:");
  Serial.print("GPS Longitude: "); Serial.println(gpsLongitude, 6);
  Serial.print("GPS Latitude: "); Serial.println(gpsLatitude, 6);
  Serial.print("MPU X: "); Serial.println(mpuX, 2);
  Serial.print("MPU Y: "); Serial.println(mpuY, 2);
  Serial.print("MPU Z: "); Serial.println(mpuZ, 2);
  Serial.print("Ultrasonic Distance: "); Serial.println(ultrasonicDistance, 2);

  // Send data to Flask server.
  sendDataToFlask(gpsLongitude, gpsLatitude, mpuX, mpuY, mpuZ, ultrasonicDistance);

  delay(5000); // Delay 5 seconds before next iteration.
}

void sendDataToFlask(float gpsLongitude, float gpsLatitude, float mpuX, float mpuY, float mpuZ, float ultrasonicDistance) {
  if (WiFi.status() == WL_CONNECTED) { // Check if WiFi is connected.
    HTTPClient http;
    http.begin(serverName);            // Specify the server endpoint.
    http.addHeader("Content-Type", "application/json"); // Specify JSON content type.

    // Create JSON payload.
    String jsonData = "{";
    jsonData += "\"GPS_Longitude\":" + String(gpsLongitude, 6) + ",";
    jsonData += "\"GPS_Latitude\":" + String(gpsLatitude, 6) + ",";
    jsonData += "\"MPU_X\":" + String(mpuX, 2) + ",";
    jsonData += "\"MPU_Y\":" + String(mpuY, 2) + ",";
    jsonData += "\"MPU_Z\":" + String(mpuZ, 2) + ",";
    jsonData += "\"Ultrasonic\":" + String(ultrasonicDistance, 2);
    jsonData += "}";

    // Send POST request.
    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      String response = http.getString(); // Get server response.
      Serial.println("Data successfully sent to Flask:");
      Serial.println(response);
    } else {
      Serial.print("Failed to send data. Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // End HTTP connection.
  } else {
    Serial.println("WiFi not connected!");
  }
}
