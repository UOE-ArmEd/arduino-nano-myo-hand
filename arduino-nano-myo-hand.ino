/**
 * @Date:   2018-01-22T17:43:58+00:00
 * @Email:  prototriangle@gmail.com
 * @Project: ArmED
 * @Filename: arduino-nano-myo-hand.ino
 * @Last modified time: 2018-01-22T18:01:17+00:00
 */



#define array_len( x )  ( sizeof( x ) / sizeof( *x ) )
#define OUTPUT_COUNT 3

#include <Servo.h>

struct Mapping {
  int input;
  int output;
};

//Myo
const unsigned int triggerPin = A0

//Hand
const unsigned int buttonPin = 5;
const unsigned int outputPins[] = {2, 3, 4};
const Servo servos[OUTPUT_COUNT];
unsigned int servoRangeMin[] = {0, 0, 0};
unsigned int servoRangeMax[] = {85, 75, 75};

//Mapping: Range(0,1023) -> Range(0,1023)
Mapping mapping[3] = {
  {256, 256},
  {512, 512},
  {768, 768}
};

void setup() {
  Serial.begin(9600);
  setup_pin_modes();
  setup_servos();
}

void setup_pin_modes() {
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < array_len(outputPins); i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  for (int i = 0; i < array_len(inputPins); i++) {
    pinMode(inputPins[i], INPUT);
  }
}

void setup_servos() {
  for (int i = 0; i < array_len(outputPins); i++) {
    servos[i].attach(outputPins[i]);
  }
}

void setDigit(unsigned int index, unsigned int bend) {
  float angle = 180 - map(bend, 0, 1023, servoRangeMin[index], servoRangeMax[index]);
  servos[index].write(angle);
}

int remap(unsigned int input) {
  int value = constrain(input, 0, 1023);
  int inputRangeMin = 0;
  int inputRangeMax = 1023;
  int outputRangeMin = 0;
  int outputRangeMax = 1023;
  int i;
  for (i = 0; i < array_len(mapping); i++) {
    if (value > mapping[i].input) {
      inputRangeMin = mapping[i].input;
      outputRangeMin = mapping[i].output;
    }
  }
  if (i < array_len(mapping) - 1) {
    inputRangeMax = mapping[i + 1].output;
    outputRangeMax = mapping[i + 1].output;
  }
  value = map(value, inputRangeMin, inputRangeMax, outputRangeMin, outputRangeMax);
  return value;
}

void loop() {
  updateInput();
  for (int i = 0; i < array_len(inputPins); i++) {
    float avg = runningAvgs[i].get_average();
    Serial.print(avg);
    Serial.print(' ');
    unsigned int value = remap((int) avg);//basic floor for now
    setDigit(i, value);
    Serial.print(value);
    Serial.print(' ');
  }
  Serial.print('\n');
  calibrate(false);
}
