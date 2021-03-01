
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <dht.h>;
dht DHT;
#define DHT11_PIN 8     

//#define DHTTYPE DHT11   
//#define DHTTYPE DHT22   

#define sensorPower 7
#define sensorPin 9
int Status=6;
//DHT dht(DHTPIN, DHTTYPE);

void setup() {
  //lcd.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.println("Smart irrigation");
  lcd.setCursor(0, 1);
  lcd.println("Batch 1");
  //dht.begin();
  pinMode(13, OUTPUT);
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  pinMode (Status , INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  delay(500);
  int chk = DHT.read11(DHT11_PIN);
  //float f = dht.readTemperature(true); 
  
  int val = readSensor();
  int rain = digitalRead(2);
  
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(DHT.temperature);
  lcd.print(" *C ");
  //lcd.print(f);
  //lcd.println(" *F");
     
  lcd.setCursor(0, 1);
  lcd.print("Humid:");
  lcd.print(DHT.humidity);
  lcd.print(" % ");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("moisture:");
  lcd.print(val);
  delay(1000);
  lcd.clear();
  
  if(digitalRead(Status)==HIGH){
    lcd.setCursor(0, 0);
    lcd.print("It is Raining");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor Off");
    delay(1000);
    digitalWrite(13, LOW);
    lcd.clear();
  }

  else{
    if (val)
     {
      lcd.setCursor(0, 0);
      lcd.print("Soil dry");
      delay(1000);
      lcd.clear();
      digitalWrite(13, HIGH); 
      lcd.setCursor(0, 0);
      lcd.print("Motor On");
      delay(1000);
      lcd.clear();
     //lcd.write("ON"); 
  
      }
    else
     {
      lcd.setCursor(0, 0);
      lcd.print("Soil good");
      delay(1000);
      lcd.clear();
      digitalWrite(13, LOW); 
      lcd.setCursor(0, 0);
      lcd.print("Motor Off");
      delay(1000);
      lcd.clear();
     //lcd.write("OFF"); 
     }
}
}
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // Allow power to settle
  int val = digitalRead(sensorPin); // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // Return analog moisture value
}
