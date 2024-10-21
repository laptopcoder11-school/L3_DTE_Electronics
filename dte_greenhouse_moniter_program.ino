/*
 * This program runs the control box for the greenhouse moniter 
 * and toggles as reley when specific conditions are met
 * version 3 -> reads in the dht sensor and
 * displays the sensor readings on a simple 2 line Alphanumeric LED display
 * Also uses an interupt to toggle the display backlight when a button is pressed
 */

//include the libarys that are required 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //led display
#include <DHT11.h> //temp and humidity sensor

// set up the LCD display to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

//set the port for the temp and humidity sensor
DHT11 dht11(2);

//interupt
const int interruptPin = 3;
bool ledbacklight = LOW;


void setup()
{
   // initialize the lcd display
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(3,0);
  
  //set the serial port for debugging
  Serial.begin(9600);
  pinMode(8, OUTPUT); //relay output

  //atatch an interupt for ottggling backlight
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), toggleDisplayBacklight, RISING);
}

void toggleDisplayBacklight()
{
ledbacklight = !ledbacklight;
Serial.println("Interupt");
}


void loop()
{
    //declare constants and variables
    int temperature = 0;
    int humidity = 0;
    const int temperatureLimit = 42; //placeholder limit value

    //Read the temperature and humidity
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    //change the backlight
    if (ledbacklight)
    {
    lcd.backlight();
    }else
    {
    lcd.noBacklight();
    }
  
    // Check the results of the readings.
    if (result == 0) {
        //serial print the temp and humidity for debugging
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");

         //draw the output on the LCD
         lcd.setCursor(0,0);
         lcd.print("Temp : ");
         lcd.print(temperature);
         lcd.print("°C");
         lcd.setCursor(0,1);
         lcd.print("Humid : ");
         lcd.print(humidity);
         lcd.print("%");
        
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
