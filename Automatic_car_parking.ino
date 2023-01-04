#define IR1 0  
#define IR2 14  

#define   IR3 12
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_AUTH_TOKEN "tot8m510j1ApWkp3vW_UrfArkb1lql1C"
int ir1,ir2,ir3;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "sanjaykumar";//Enter your WIFI name
char pass[] = "sanjay12";//Enter your WIFI password

#define THRESHOLD 2000 // ENTER YOUR THRESHOLD HERE
BlynkTimer timer;
BLYNK_WRITE(V0) {
  digitalWrite(17, param.asInt());
}

void myTimer() 
{
   

   Blynk.virtualWrite(V10,1-ir1); 
   Blynk.virtualWrite(V11,1-ir2); 
   Blynk.virtualWrite(V12,1-ir3); 
   
}

void setup() {
  Serial.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, myTimer);  
  
}

void loop() {
  Blynk.run();
  timer.run();
 ir1=digitalRead(IR1);
 ir2=digitalRead(IR2);
 ir3=digitalRead(IR3);
 Serial.println("writing");
// delay(2000);


}
