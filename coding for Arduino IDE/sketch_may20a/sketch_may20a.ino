#include <ESP8266WiFi.h>

#define LIGHT D0    

#include <SoftwareSerial.h>
SoftwareSerial s(D2,D3);

#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
const char *ssid =  "poxER";     // replace with your wifi ssid and wpa2 key
const char *pass =  "mexiCana551";
const char* server = "api.thingspeak.com";

int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 1657849;
const char * myWriteAPIKey = "RTU39LD3PVO33LBG";

int number = 0;
#define NUM_SAMPLES 20

int sum = 0; 
double tot_vol = 0.0;// sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.00;  
double tot_voltage = 0.0;
int t1,c1 = 0,count =0,t2=0,t4 =0;
int last_light_state =0;


void setup() {
   Serial.begin (9600);
  s.begin(9600);
  // Initialize serial
      while (!Serial)
      { 
      Serial.println("not Connecting ");
      continue;
      }
    
       delay(10);
  
  WiFi.mode(WIFI_STA); 
         WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
      {
            delay(500);
            Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");

      
    pinMode(D2, INPUT);
    pinMode(D3, OUTPUT);
    pinMode(LIGHT, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() 
{
  t1 = millis();
 
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A0);
        sample_count++;
        delay(15);
    }
  // put your main code here, to run repeatedly:
 
    // calculate the voltage
    // use 5.0 for a 5.0V ADC reference voltage
    // 5.015V is the calibrated reference voltage
    voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
    // send voltage for display on Serial Monitor
    // voltage multiplied by 11 when using voltage divider that
    // divides by 11. 11.132 is the calibrated voltage divide
    // value
    voltage*=11.132;
    sample_count = 0;
    sum = 0;

    String x = String(voltage);
    Serial.println(voltage);
    
    if (voltage >2.5 && (t4==0 || t4<t1))
    {
        t4 = t1 +3000;
      if (voltage <8.99  )
      {
        digitalWrite(D0,HIGH);
        digitalWrite(D1,LOW);
        
      }
      else if (voltage>13.99){
            digitalWrite(D0,HIGH);
            digitalWrite(D1,LOW);
       
      }
      else
      {
        digitalWrite(D1,HIGH);
        digitalWrite(D0,LOW);
        
      }
    s.print(x);
    s.println("\n");
    count++;
      if (c1==0 || t1>c1)
      {
        c1 = t1 + 15000;
        tot_voltage +=voltage;
        String xx= String(tot_voltage);
        ThingSpeak.setField(2,xx);
        ThingSpeak.setField(3,count);
        ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
        

//         ThingSpeak.writeField(myChannelNumber, [2,3], {tot_voltage,count}, myWriteAPIKey);
//        send data
     //if (x== 200)   //   "184.106.153.149" or api.thingspeak.com
                        
                            
                            
                             Serial.print("step count: ");
                             Serial.println(count);
                             Serial.print("Voltage Per Step: ");
                             Serial.println(voltage);
                             Serial.println("%. Send to Thingspeak.");
                    
          
          

        tot_voltage = 0;
      }

      else
      {
        tot_voltage+=voltage;
      }
    
    }

    if (t2==0 || t2+3000<t1)
            {
              t2=t1;
           last_light_state = ThingSpeak.readIntField(1662880, 1);
           Serial.println(last_light_state);
       int  statusCode = ThingSpeak.getLastReadStatus();
       Serial.println(statusCode);
         if(statusCode == 200){
           if (last_light_state==0){

          //  Serial.println(last_light_state);
            digitalWrite(D5, LOW);
            
           }
           else
           {
            digitalWrite(D5, HIGH);
           }
         }
            }
    int statusCode = 0;
  

}
