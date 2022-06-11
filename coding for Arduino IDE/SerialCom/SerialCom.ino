#include <SoftwareSerial.h>
#include<ArduinoJson.h>
SoftwareSerial s(8,11);

#include <LiquidCrystal.h> 
int Contrast=75;
LiquidCrystal lcd(12, 9, 5, 4, 3, 2);  

int step_count = 0;
float total_voltage = 0;
float total_power =0;
float current =0;

int t1,c=0,c1=0;

#define NUM_SAMPLES 10

int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
double voltage = 0.00;            // calculated voltage

//void led ()

void setup() {
  // put your setup code here, to run once:
s.begin(9600);
Serial.begin(9600);
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Step Count: ");
  lcd.print(0);
  pinMode(10,OUTPUT);




}

void loop() {

 t1 = millis();

 if (t1>c1)
 {

      digitalWrite(10, LOW); 
  
 }

   if (s.available()>0){


float val = s.parseFloat();

if (s.read()=='\n')
{
  float voltage = val;

  c1 = t1 + 3000;


//

  Serial.println(voltage);


   

       // to make the LED visible
    step_count+=1;

   digitalWrite(10, HIGH); 
   lcd.setCursor(0, 0);
   lcd.clear();
 
    lcd.print("Step Count: ");
    lcd.print(step_count);
    lcd.setCursor(0, 1);
    lcd.print("Voltage: ");
    lcd.print(voltage);
    lcd.print("v");
  
    delay(2000);
  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("power: ");
    total_power =+ (voltage * .0025);
    lcd.print(total_power,5);
    lcd.print("W");
    lcd.setCursor(0, 1);
    lcd.print("I: ");
    lcd.print(2.5);
    current+=2.5;
    lcd.print(" miliA");
    


   // String x;
    
    
    
}
}
}
