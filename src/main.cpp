#include <Arduino.h>
#include "SoftwareSerial.h"

SoftwareSerial raspi(3,2);   //RX,TX

String terima = "A,1,0,255;B,0,0,0;C,1,0,255;D,0,0,0";
int index;
int indexBaru;
String hasil = "";
String kecepatan = "";

int list[3][4] = {};

#define belakangKiriMaju 4
#define belakangKiriMundur 5
#define pwmBelakangKiri 6
#define belakangKananMaju 8
#define belakangKananMundur 7
#define pwmBelakangKanan 9

#define depanKiriMaju A4
#define depanKiriMundur A5
#define pwmDepanKiri 11
#define depanKananMaju A1
#define depanKananMundur A0
#define pwmDepanKanan 10

void motorA(int maju, int mundur,int kecepatan);
void motorB(int maju, int mundur,int kecepatan);
void motorC(int maju, int mundur,int kecepatan);
void motorD(int maju, int mundur,int kecepatan);

void setup() {
  for(int i=4; i<=11; i++){
    pinMode(i, OUTPUT);
  }

  pinMode(depanKiriMaju, OUTPUT);
  pinMode(depanKananMundur, OUTPUT);
  pinMode(depanKananMaju, OUTPUT);
  pinMode(depanKiriMundur, OUTPUT);


  Serial.begin(115200);
  raspi.begin(38400);

}

void loop() {
  // terima = raspi.readStringUntil("\r\n"); //terima = "A,0,1,255 ..."
  index = terima.indexOf(';');
  Serial.println(index);
  hasil = terima.substring(0,index); // hasil = "A,1,0,255"
  if(hasil[0] == 'A'){
    Serial.print("Maju: ");
    Serial.println(hasil[2]);
    Serial.print("Mundur:" );
    Serial.println(hasil[4]);
    kecepatan = hasil.substring(6, index); 
    Serial.print("Kecepatan: ");
    Serial.println(kecepatan);
  }

  indexBaru = terima.indexOf(';', index+1);
  hasil = terima.substring(index+1, indexBaru);
  
  if(hasil[0] == 'B'){
    Serial.print("Maju: ");
    Serial.println(hasil[2]);
    Serial.print("Mundur:" );
    Serial.println(hasil[4]);
    kecepatan = hasil.substring(6, indexBaru); 
    Serial.print("Kecepatan: ");
    Serial.println(kecepatan);
  }

  index = indexBaru;

}

void motorA(int maju, int mundur,int kecepatan){
  digitalWrite(depanKiriMaju, maju);
  digitalWrite(depanKiriMundur, mundur);
  analogWrite(pwmDepanKiri, kecepatan);
}

void motorB(int maju, int mundur,int kecepatan){
  digitalWrite(depanKananMaju, maju);
  digitalWrite(depanKananMundur, mundur);
  analogWrite(pwmDepanKanan, kecepatan);
}

void motorC(int maju, int mundur,int kecepatan){
  digitalWrite(belakangKiriMaju, maju);
  digitalWrite(belakangKiriMundur, mundur);
  analogWrite(pwmBelakangKiri, kecepatan);
}

void motorD(int maju, int mundur,int kecepatan){
  digitalWrite(belakangKananMaju, maju);
  digitalWrite(belakangKananMundur, mundur);
  analogWrite(pwmBelakangKanan, kecepatan);
}
