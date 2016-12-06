int switchstate = 0;

void setup() {
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(2,INPUT);

}

void loop() {
  switchstate = digitalRead(2);

  if(switchstate == LOW){
    digitalWrite(3,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(7,LOW);
  }
  else{
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    digitalWrite(7,HIGH);

    delay(250);
    digitalWrite(5,HIGH);
    digitalWrite(7,LOW);
    delay(250);
    
  }

}
