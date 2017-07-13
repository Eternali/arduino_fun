// Declare important variables for storing sound
int micVal, prevVal;

void setup() {

  // define pins and begin the serial port
  pinMode(A0, INPUT);
  Serial.begin(9600);

}

void loop() {

  // compare the difference between the current sound level and the previous one
  prevVal = micVal;
  micVal = analogRead(A0);

  // if it exceeds a certain level send an alert
  if (abs(micVal - prevVal) > 400) {
    Serial.println("SPIKE OF SOUND!");
    // run the script that will send a notification to me
    system("python3 /home/alert_db.py");
    // wait a specified amount
    delay(2000);
  }
  
}

