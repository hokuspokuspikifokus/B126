int const htcstPin = 2; //Pin til tcst pin
int const vtcstPin = 3; //Pin til tcst pin
int const hvcc = 5;
int const hgnd = 4;
int const vvcc = 7;
int const vgnd = 6;
int const motorH = 11; //Pin til højre motor
int const motorV = 10; //Pin til venstre motor
int hjulhhastighed = 255;
float const cm = 0.53; //Længde fra hul til hul
float htid = 0; //Start tid
float htidEfter = 0;//Slut tid
float vtid = 0; //Start tid
float vtidEfter = 0;//Slut tid
float hsamples[5]; //array til hsamples der skal gemmes
float vsamples[5];//array til vsamples der skal gemmes
float gennemsnit = 0; //Gennemsnit til udregning af hhastighed
float hhast = 0; // Gennemsnits hhastighed
float vhast = 0; // Gennemsnits hhastighed

void hinter()
{
  htid = millis();
  hsamples[4] = hsamples[3];
  hsamples[3] = hsamples[2];
  hsamples[2] = hsamples[1];
  hsamples[1] = hsamples[0];
  hsamples[0] = htid - htidEfter;
  gennemsnit = ((hsamples[0] + hsamples[1] + hsamples[2] + hsamples[3] + hsamples[4]) / 5);
  htidEfter = htid;
  hhast = (cm / gennemsnit) * 1000;
}

void vinter()
{
  vtid = millis();
  vsamples[4] = vsamples[3];
  vsamples[3] = vsamples[2];
  vsamples[2] = vsamples[1];
  vsamples[1] = vsamples[0];
  vsamples[0] = vtid - vtidEfter;
  gennemsnit = ((vsamples[0] + vsamples[1] + vsamples[2] + vsamples[3] + vsamples[4]) / 5);
  vtidEfter = vtid;
  vhast = (cm / gennemsnit) * 1000;
}


void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  pinMode(motorH, OUTPUT);  // sets the pin as output
  pinMode(motorV, OUTPUT);  // sets the pin as output
  pinMode(hgnd, OUTPUT);
  pinMode(hvcc, OUTPUT);
  pinMode(vgnd, OUTPUT);
  pinMode(vvcc, OUTPUT);
  digitalWrite(hvcc, HIGH);
  digitalWrite(hgnd, LOW);
  digitalWrite(vvcc, HIGH);
  digitalWrite(vgnd, LOW);
  analogWrite(motorH, hjulhhastighed);
  analogWrite(motorV, hjulhhastighed);
  attachInterrupt((digitalPinToInterrupt(htcstPin)), hinter, CHANGE);
  attachInterrupt((digitalPinToInterrupt(vtcstPin)), vinter, CHANGE);
}
void loop() {
  Serial.print(vhast);
  //Serial.print(" cm/s");
  //Serial.print("      :      ");
  //Serial.print(hhast);
  Serial.println("  ");
  //Serial.println(" cm/s");
  
  
  
  //Serial.println(digitalRead(htcstPin));
  //analogWrite(motorH, hjulhhastighed);
  //analogWrite(motorV, hjulhhastighed);
  //hjulhhastighed = hjulhhastighed + 5;
  delay(500);

}

//1,06 pr hak og 0,53 pr ændring
//Huller ved motorer 20
//Længde rundt om hjul 21,2
