void setup() 
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
//  analogReference(EXTERNAL);
}

void loop() 
{
//  digitalWrite(13, LOW);
//  digitalWrite(12, LOW);
//  digitalWrite(11, LOW);
//  digitalWrite(10, LOW);
//  digitalWrite(9, LOW);
//  digitalWrite(8, LOW);
//  Serial.println(analogRead(A0));
//  delay(100);
  
  delay(500);
  for(int i=0; i<8; i++)
  {
    switch(i)
    {
      case 0: digitalWrite(13, LOW);
              digitalWrite(12, LOW);
              digitalWrite(11, LOW);
              break;
      case 1: digitalWrite(13, HIGH);
              digitalWrite(12, LOW);
              digitalWrite(11, LOW);
              break;
      case 2: digitalWrite(13, LOW);
              digitalWrite(12, HIGH);
              digitalWrite(11, LOW);
              break;
      case 3: digitalWrite(13, HIGH);
              digitalWrite(12, HIGH);
              digitalWrite(11, LOW);
              break;
      case 4: digitalWrite(13, LOW);
              digitalWrite(12, LOW);
              digitalWrite(11, HIGH);
              break;
      case 5: digitalWrite(13, HIGH);
              digitalWrite(12, LOW);
              digitalWrite(11, HIGH);
              break;
      case 6: digitalWrite(13, LOW);
              digitalWrite(12, HIGH);
              digitalWrite(11, HIGH);
              break;
      case 7: digitalWrite(13, HIGH);
              digitalWrite(12, HIGH);
              digitalWrite(11, HIGH);
              break;
    }
    for(int j=0; j<8; j++)
    {
      switch(j)
      {
        case 0: digitalWrite(10, LOW);
                digitalWrite(9, LOW);
                digitalWrite(8, LOW);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
        case 1: digitalWrite(10, HIGH);
                digitalWrite(9, LOW);
                digitalWrite(8, LOW);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
        case 2: digitalWrite(10, LOW);
                digitalWrite(9, LOW);
                digitalWrite(8, HIGH);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
        case 3: digitalWrite(10, HIGH);
                digitalWrite(9, LOW);
                digitalWrite(8, HIGH);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
        case 4: digitalWrite(10, LOW);
                digitalWrite(9, HIGH);
                digitalWrite(8, LOW);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
        case 5: digitalWrite(10, HIGH);
                digitalWrite(9, HIGH);
                digitalWrite(8, LOW);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
        case 6: digitalWrite(10, LOW);
                digitalWrite(9, HIGH);
                digitalWrite(8, HIGH);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
        case 7: digitalWrite(10, HIGH);
                digitalWrite(9, HIGH);
                digitalWrite(8, HIGH);
                delay(10);
                Serial.print(digitalRead(A0));
                Serial.print("\t");
                break;
      }
    }
    Serial.println("");
  }
  Serial.println("");
  delay(3000);
}
