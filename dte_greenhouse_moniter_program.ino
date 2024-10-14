/*
 * This program runs the control box for the greenhouse moniter 
 * and toggles as reley when specific conditions are met
 * version 1 -> reads in the temp and humidity sensor and activates a relay when above a threshhold
 */

//include the libarys that are required 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //led display
#include <DHT11.h> //temp and humidity sensor

//set the port for the temp and humidity sensor
DHT11 dht11(2);

void setup()
{
  //set the serial port for debugging
  Serial.begin(9600);
  pinMode(8, OUTPUT); //relay output
}

void loop()
{
    //declare constants and variables
    int temperature = 0;
    int humidity = 0;
    const int temperatureLimit = 55; //placeholder limit value

    //Read the temperature and humidity
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    // Check the results of the readings.
    if (result == 0) {
        //serial print the temp and humidity for debugging
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
        
        if (humidity > temperatureLimit)
        {
          Serial.println("Temp is above limit!");
          //activate the relay if the temp is too high
          digitalWrite(8, HIGH); 
          
        } else
        {
          digitalWrite(8, LOW); 
        }
    } else {
        // Print error message for sensor
        Serial.println(DHT11::getErrorString(result));
    }
}
