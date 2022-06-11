#include <LiquidCrystal.h> 
int Contrast=75;
LiquidCrystal lcd(12, 9, 5, 4, 3, 2);  
int sensoroutput = A5; // the analog pin connected to the sensor
int ledoutput = 0; // pin connected to LED
int THRESHOLD = 1023;
long int t1 =0;
int per_step_V = 14.00;
int total_voltage = 0;
int step_count = 0;
int fl =0;
int c1 = 3000;
int c = 1;
char mi = 230;
float power = .035;
float total_power = 0;
float current = 2.5;

void setup()
{
  Serial.begin(9600);
  pinMode(10, OUTPUT); 
  digitalWrite(10, LOW);// this function is used to declare led connected pin as output
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Step Count: ");
  lcd.print(0);
}
void loop()
{
int value = random(1900);// function to read analog voltage from sensor
delay(2000);
Serial.println(value);

if (value >= THRESHOLD)                    // function to check voltage level from sensor
  {
 
 // to make the LED visible
  step_count+=1;
  total_voltage += 14.00;
   digitalWrite(10, HIGH); 
  lcd.setCursor(0, 0);
lcd.clear();
 
  lcd.print("Step Count: ");
  lcd.print(step_count);
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(total_voltage);
  lcd.print("v");
//  t1 = millis();
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("power: ");
    total_power = total_power + .035;
  lcd.print(total_power,5);
  lcd.print("W");
   lcd.setCursor(0, 1);
  lcd.print("I: ");
  lcd.print(current);
  current+= 2.5;
  lcd.print(" miliA");
  delay(1500);

  
  
  }
else
  {
      value = 0;
    digitalWrite(10, LOW); 
  
  
  }

 
   
}
