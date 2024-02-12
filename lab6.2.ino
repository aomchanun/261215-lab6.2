#include "pitches.h"
#define buzzer 26
#define button 4
const float songSpeed = 1.0;
int i = 4;
hw_timer_t *My_timer = NULL;

// notes in the melody:
int notes[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0
};

int durations[] = {125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375};

double speed[] = {
  0.5, 0.75, 1, 1.25, 1.5
};

void IRAM_ATTR onTimer(){
  digitalWrite(buzzer, !digitalRead(buzzer));
}

void IRAM_ATTR IO_INT_ISR(){
  i--;
  if(i == -1){
    i = 4;
  }
}

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  attachInterrupt(button, IO_INT_ISR, FALLING);  
}

void loop() {
  for(int j=0; j<sizeof(notes)/sizeof(int); j++){
    playNotes(notes[j], durations[j], speed[i]);
  }
}

void playNotes(double Hz, int duration, double speed){
  timerAlarmWrite(My_timer, toTime(Hz), true);
  timerAlarmEnable(My_timer);  // enable the alarm
  int dur = duration * speed;
  delay(dur);
}

int toTime(double Hz) {
  return (int) ((1.0 / Hz) * 1000000.0 / 2.0);
}
