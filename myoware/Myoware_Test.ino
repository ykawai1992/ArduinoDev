#include<stdio.h>
  int y[500]={0};
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  sensorValue = MovingAV(sensorValue, 4);
  Serial.println(sensorValue);
  delay(10);        // delay in between reads for stability
}

int MovingAV(int xn, int N){
  int i;
  int yn;
  y[N-1] = xn;
  for(i=0;i<N;i++){
    yn += y[i];
  }
  for(i=0;i<N-1;i++){
    y[i] = y[i+1];
  }
  return (int)yn/(float)N;
}
