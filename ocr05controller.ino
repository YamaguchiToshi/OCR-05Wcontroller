#include <Adafruit_CircuitPlayground.h>

unsigned int on[] = {2552,2680,824,860,820, 860,824,1892,852,1868,824,1896,824,1892,828, 856,828, 856,848,53728,2552,2672,828,860,824, 856,824,1896,852,1864,824,1896,824,1896,852, 828,828, 856,828,53840,2560,2672,828,856,848, 836,824,1892,824,1892,828,1892,852,1868,852, 832,848, 832,828};
unsigned int off[] = {2552,2676,852,832,824,1896,848, 832,828, 856,828,1892,824, 856,852,1868,824,1892,852,53944,2556,2676,824,860,820,1896,828, 856,828, 852,848,1872,824, 856,828,1896,824,1892,824,53844,2552,2676,852,832,824,1896,848, 836,824, 856,828,1892,824, 860,820,1896,828,1888,848};

int sw = 0;
int exsw = 0;

void setup() {
  CircuitPlayground.begin();
  pinMode(3, INPUT_PULLUP);
}

void sendOn() {
  int datasize = sizeof(on)/sizeof(on[0]);

  for(int i = 0; i < datasize; ++i){
    unsigned long len = on[i];
    unsigned long now = micros();

    do{
      digitalWrite(25, 1-i&1);
      delayMicroseconds(8);
      digitalWrite(25, 0);
      delayMicroseconds(7);
    } while(long(now + len - micros()) > 0);
  }
}

void sendOff() {
  int datasize = sizeof(off)/sizeof(off[0]);

  for(int i = 0; i < datasize; ++i){
    unsigned long len = off[i];
    unsigned long now = micros();

    do{
      digitalWrite(25, 1-i&1);
      delayMicroseconds(8);
      digitalWrite(25, 0);
      delayMicroseconds(7);
    } while(long(now + len - micros()) > 0);
  }
}

void loop() {

  int externalButton = digitalRead(3);

  if( !digitalRead(3) && exsw == 0 ) {
    for(int i = 0; i < 3; ++i){
      sendOn();
    }
    exsw = 1;
  } else if(  digitalRead(3) && exsw == 1 ) {
    for(int i = 0; i < 3; ++i){
      sendOff();
    }
    exsw = 0;
  }

  
  if( CircuitPlayground.leftButton() && sw == 0 ) {
    for(int i = 0; i < 3; ++i){
      sendOn();
    }
    sw = 1;
  } else if( !CircuitPlayground.leftButton() && sw == 1 ) {
    for(int i = 0; i < 3; ++i){
      sendOff();
    }
    sw = 0;
  }

}
