#define RELAY_PIN    19 
#define MOISTURE_PIN 39 
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_AUTH_TOKEN "NX80AECwfijz6jK-tYrkGLEpwp7KUk-a"
int value;
int percentage;
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "sanjaykumar";//Enter your WIFI name
char pass[] = "sanjay1224";//Enter your WIFI password

#define THRESHOLD 2000 // CHANGE YOUR THRESHOLD HERE
BlynkTimer timer;
BLYNK_WRITE(V0) {
  digitalWrite(17, param.asInt());
}

void myTimer() 
{
  

   Blynk.virtualWrite(V0,percentage); 
   
}

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(MOISTURE_PIN, INPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, myTimer);  
  
}

void loop() {
  Blynk.run();
  timer.run();
  value = 4095-analogRead(MOISTURE_PIN);
 
  percentage=value*0.0244200244;
  
  // read the analog value from sensor

  if (value > THRESHOLD) {
    Serial.print("The soil is WET => turn pump OFF");
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    Serial.print("The soil is DRY => turn pump ON");
    
    digitalWrite(RELAY_PIN, LOW);
  }

  Serial.print(" (Percentage=");
  Serial.print(percentage);
  Serial.print("%,value=");
  Serial.print(value);
  Serial.println(")");

}
