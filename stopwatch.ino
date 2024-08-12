#include <TM1637Display.h>

#include <Timer.h>

const int CLK = 12;
const int DIO = 11;
const int START = 2;
const int STOP = 3;
const int BUZZER = 6;
int n = 0;
Timer timer;
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  pinMode(START, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(START), start, RISING);
  attachInterrupt(digitalPinToInterrupt(STOP), stop, RISING);
  display.clear();
  display.setBrightness(7);
  display.showNumberDecEx(0, 0x40, true);

}

void start() {
  if (timer.state() == STOPPED) {
    timer.start();
  }
  else if (timer.state() == RUNNING) {
    timer.pause();
  }
  else if (timer.state() == PAUSED) {
    timer.resume();
  }
  tone(BUZZER, 523, 1000);

}

void stop() {
  timer.stop();
  n = 0;
  tone(BUZZER, 783, 1000);
}

void loop() {
  if (timer.state() == RUNNING) {
    int count = round(timer.read() / 1000) + (n * 40);
    Serial.println(count);
    if ((count % 100) >= 60) {
      n += 1;
      tone(BUZZER, 659, 1000);
    }
    display.showNumberDecEx(count, 0x40, true);
  }


}
