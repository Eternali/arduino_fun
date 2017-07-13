void setup() {

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(115200);
  Serial.println("starting testing");

}

void loop() {
  int inputO = analogRead(A4);
  int inputT = analogRead(A5);
  Serial.print("IN1 ");
  Serial.print(inputO);
  Serial.print("   INT ");
  Serial.print(inputT);
  Serial.print("\n");
}
