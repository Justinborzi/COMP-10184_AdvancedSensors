// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

// setup a device address.
DeviceAddress sensor;

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();

  // Application Start
  Serial.println("\nTemperature Application");

  // Check if device is installed.
  if (!DS18B20.getAddress(sensor, 0))
  {
    Serial.println("No DS18B20 temperature sensors are installed!");
  }
  else
  {
    Serial.println("Found DS18B20 sensor with the address: ");
    for (uint8_t i = 0; i < 8; i++)
    {
      if (sensor[i] < 16)
        Serial.print("0");
      Serial.print(sensor[i], HEX);
    }
    Serial.println();
  }
}

void loop()
{
  // Initialize a float value.
  float fTemp;

  // Request DS18B20 (devices) for the current temperature(s)
  DS18B20.requestTemperatures();

  // fetch the temperature.  We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);

  // Determine the device is connected as to not throw an error.
  if (DS18B20.getAddress(sensor, 0) || fTemp != DEVICE_DISCONNECTED_C)
  {
    // Initialize the string value.
    String tempatureString;

    // Set the variable to the correct output based on tempature.
    if (fTemp <= 10)
    {
      tempatureString = "Cold!";
    }
    else if (fTemp < 15)
    {
      tempatureString = "Cool";
    }
    else if (fTemp < 25)
    {
      tempatureString = "Perfect";
    }
    else if (fTemp < 30)
    {
      tempatureString = "Warm";
    }
    else if (fTemp < 35)
    {
      tempatureString = "Hot";
    }
    else if (fTemp >= 35)
    {
      tempatureString = "Too Hot!";
    }

    // print the temp to the USB serial monitor
    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + tempatureString);

    // wait 5s (5000ms) before doing this again
    delay(5000);
  }
}