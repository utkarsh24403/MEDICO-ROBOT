
#include <Wire.h>
#include <LiquidCrystal.h>
 #include <MAX30100_PulseOximeter.h>
#define REPORTING_PERIOD_MS     1000
#define rs 9 
#define en 8 
#define d4 7 
#define d5 6  
#define d6 5 
#define d7 4 
#define LM35 A3
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
   
   // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("Oximeter");
  delay(100);
  lcd.clear();
    //Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
  float lmvalue=analogRead(A3);
  float temp=(lmvalue*500)/1023;
  lcd.setCursor(0,0);
    lcd.print("Temperature:");
     lcd.print(temp);     
     lcd.print("*C");
     delay(2000);
    // Make sure to call update as fast as possible
    pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
 
 
        lcd.clear();
        lcd.setCursor(0,2);
        lcd.print("BPM: ");
        lcd.print(pox.getHeartRate());
        
        lcd.setCursor(0,1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");
       
        tsLastReport = millis();
    }
     
}
