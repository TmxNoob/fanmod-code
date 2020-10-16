/*
 * TmxPro's fan controller code
 * Improve or do whatever you want with it :P
 */

unsigned long commandTimeout = 1000000; //60s
unsigned char minSpeed = 15; // about 6% fan speed, this is about the minimum pwm where the fans spin
unsigned char maxSpeed = 255; // idk why anyone would want to change this but left the option here
unsigned char defaultSpeed = 40; // about 15% fan speed - this is the default speed when on boot or when havent gotten a command in commandTimeout time period


//do not touch following values!
String serialBuffer = "";
bool stringComplete = false;
char fanPins[] = {3,5,6,9,10,11};
char numFans = sizeof(fanPins);
long lastCommand = 0;

void setupFans() {
  for(char c = 0;c<numFans;c++){
    pinMode(fanPins[c],OUTPUT);
    setFan(c,defaultSpeed);
  }
}

void setFan(char fan,unsigned char spd){
 unsigned char spdPwm = 255-(max(minSpeed,min(spd,maxSpeed))); //make sure speed is between max and min and hp proliant fans use inversed pwm
 analogWrite(fanPins[fan],spdPwm);
}

void resetSerialBuffer(){
  serialBuffer = "";
  stringComplete = false;
}

void setup(){
  setupFans(); //set fan pwm pins as outputs
  resetSerialBuffer();

  //set pwm frequency, stolen from https://github.com/Max-Sum/HP-fan-proxy
  TCCR0B = _BV(CS00);
  TCCR1B = _BV(CS00);
  TCCR2B = _BV(CS00);
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);



  Serial.begin(9600);
  Serial.setTimeout(100000);
  lastCommand = millis();
}

void loop(){
  if(millis()-lastCommand > commandTimeout){
    Serial.println("Resetting fans");
    setupFans();
    lastCommand = millis();
  }
  if(stringComplete){
    //process serial event
    unsigned char cmdbuf[64];
    serialBuffer.getBytes(cmdbuf,64);
    
    //really ugly but made it work with python, now too lazy to make it actually cool
    switch(cmdbuf[0]){
      case 's':
        Serial.println("fan number:");
        char cmdFanNum = Serial.parseInt();
        Serial.println("fan speed:");
        char cmdFanSpeed = Serial.parseInt();
        if(cmdFanNum > 0 && cmdFanNum <= numFans){
          setFan(cmdFanNum-1,cmdFanSpeed);
          Serial.println("OK");
        }else{
          Serial.println("fan out of range");
        }
        break;
    }
    lastCommand = millis();
    resetSerialBuffer();
  }
}

void serialEvent() {
  if(stringComplete) return; //skip if current string isnt processed yet
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    serialBuffer += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
