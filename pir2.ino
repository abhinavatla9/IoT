int calibrationTime = 30;
long unsigned int lowln;
long unsigned int pause = 5000;
boolean locklow = true;
boolean takeLowTime;
int pirpin = 2;
int ledpin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(pirpin, INPUT);
  pinMode(ledpin, OUTPUT);
  digitalWrite(pirpin, LOW);

  Serial.print("Calibration in process");
  for(int i=0;i<calibrationTime;i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.print("Done");
  Serial.println("Sensor Active");
  delay(50);
}

void loop() {
  if(digitalRead(pirpin)==HIGH){
    digitalWrite(ledpin, HIGH);
    if(locklow){
      locklow = false;
      Serial.println("---");
      Serial.println("Motion Detected at");
      Serial.print(millis()/1000);
      Serial.println("sec");
      delay(50);
    }
    takeLowTime = true;
  }
  if(digitalRead(pirpin) == LOW){
    digitalWrite(ledpin, LOW);

    if(takeLowTime){
      lowln = millis();
      takeLowTime = false;
      if(!locklow&&millis()-lowln>pause){
        locklow=true;
        Serial.println("Motion Ended at ");
        Serial.println((millis() - pause)/1000);
        Serial.print("sec");
        delay(50);
      }
    }
  }

}
