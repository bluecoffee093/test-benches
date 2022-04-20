#define _1A 7
#define _1B 6

#define _2A 5
#define _2B 4

#define _3A 3
#define _3B 2

const int ipH1 = 18;
const int ipH2 = 19;
const int ipH3 = 20;

volatile int sH1 = LOW;
volatile int sH2 = LOW;
volatile int sH3 = LOW;

char buff[50];


void setup() {
  // put your setup code here, to run once:
  //Serial.begin (9600);
  pinMode (_1A, OUTPUT);
  pinMode (_1B, OUTPUT);

  pinMode (_2A, OUTPUT);
  pinMode (_2B, OUTPUT);

  pinMode (_3A, OUTPUT);
  pinMode (_3B, OUTPUT);

  pinMode(ipH1, INPUT_PULLUP);
  pinMode(ipH2, INPUT_PULLUP);
  pinMode(ipH3, INPUT_PULLUP);

  sH1 = digitalRead(ipH1) ? 1 : 0;
  sH2 = digitalRead(ipH2) ? 1 : 0;
  sH3 = digitalRead(ipH3) ? 1 : 0;

  attachInterrupt(digitalPinToInterrupt(ipH1), intHall1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ipH2), intHall2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ipH3), intHall3, CHANGE);
}

void loop() {
  int _1a = (!sH1)&sH2;
  int _1b = (!sH1)|sH2;
  int _2a = (!sH2)&sH3;
  int _2b = (!sH2)|sH3;
  int _3a = (!sH3)&sH1;
  int _3b = (!sH3)|sH1;

  int val = analogRead(A0);
  analogWrite(_1A,_1a ? val/4: 0);
  digitalWrite(_1B,_1b);
  analogWrite(_2A,_2a ? val/4: 0);
  digitalWrite(_2B,_2b);
  analogWrite(_3A,_3a ? val/4: 0);  
  digitalWrite(_3B,_3b);

  //sprintf(buff, "sH1: %d   sH2: %d   sH3: %d",sH1,sH2,sH3);
  //Serial.println(buff);
}

void intHall1() {
  sH1 = digitalRead(ipH1) ? 1 : 0;
}
void intHall2() {
  sH2 = digitalRead(ipH2) ? 1 : 0;
}
void intHall3() {
  sH3 = digitalRead(ipH3) ? 1 : 0;
}
