// Adafruit_DHT library is inserted
#include "DHT.h"
 
// Here the respective input pin can be declared
#define DHTPIN 23    
 
// The sensor is initialized
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
 
void setup() 
{
  Serial.begin(115200);
  Serial.println("KY-015 test - temperature and humidity test:");
 
  // Measurement is started
  dht.begin();
}
 
// Main program loop
// The program starts the measurement and reads out the measured values
// There is a pause of 2 seconds between measurements,
// so that a new measurement can be acquired on the next run.
void loop() {
 
  // Two seconds pause between measurements
  delay(2000);
 
  // Humidity is measured
  float h = dht.readHumidity();
  // temperature is measured
  float t = dht.readTemperature();
   
  // Checking if the measurements have passed without errors
  // if an error is detected, a error message is displayed here
  if (isnan(h) || isnan(t)) {
    Serial.println("Error reading the sensor");
    return;
  }
 
  // Output to serial console
  Serial.println("-----------------------------------------------------------");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(char(186)); //Output <°> symbol
  Serial.println("C ");
  Serial.println("-----------------------------------------------------------");
  Serial.println(" ");
}
