//#include <ArduinoJson.h>

#include <SoftwareSerial.h>
#include <String.h>
SoftwareSerial SIM900(8,9);// gsm module connected here
SoftwareSerial mySerial(8,9);
SoftwareSerial myGsm(8,9);
bool executed = false;
String textForSMS;
int Ammonia = A0;
int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;     // by default, no motion detected
int val = 0;// variable to store the sensor status (value)
int c=0;
int data;
void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);  // initialize serial
  SIM900.begin(9600);
}

void loop(){
  val = digitalRead(sensor);// read sensor value
   data = analogRead(Ammonia); 

  
   if (val == HIGH) {  // check if the sensor is HIGH
    
    digitalWrite(led, HIGH); // turn LED ON
    
                    // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
       count();
       
        
       }
      state = HIGH;       // update variable state to HIGH
    }
   
    
  else {
      digitalWrite(led, LOW); // turn LED OFF
                  // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
   ammonia();
   delay(100);
    }
    
  }
}
void count()
{
  c=c+1;
    Serial.println(c);
    if(c==4)
    {
      call();
       textForSMS =  "\nGo and clean bathroom";  
  sendSMS(textForSMS);
  
  Serial.println(textForSMS);
  Serial.println("message sent."); 
delay(5000);

c=0;
    }
    
}
void  call ()

// Function that allows to call a local cell

{

SIM900. println ( "ATD +918639592023;" ); // Cellular

delay ( 100 );

SIM900. println ();

delay ( 30000 ); // wait for 30 seconds …

SIM900. println ( " ATH" ); // Drop the phone

delay ( 1000 );
Serial.println("calling");

}
void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
 SIM900.println("AT + CMGS = \"+918639592023\"");  // recipient's mobile number, in international format

  delay(1000);
  SIM900.println(message);                         // message to send
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
  SIM900.println();
  delay(100);                                     // give module time to send SMS
 // SIM900power();                                   // turn off module
}


void ammonia(){
   Serial.print("Ammonia: "); 
  Serial.println(data);
 if(data>500)
 {
    call();
       textForSMS =  "\nGo and clean bathroom";  
  sendSMS(textForSMS);
  
  Serial.println(textForSMS);
  Serial.println("message sent."); 
delay(5000);
  }
}
