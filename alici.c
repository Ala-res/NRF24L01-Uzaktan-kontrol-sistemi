//alıcı

#include <Servo.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>

Servo servoM1;  
Servo servoM2;
int pos = 90;
RF24 nrf(9,10);  // nrf'nin ce ve csn pinlerinin bağlı olduğu pinleri seçtik
const byte adres[6]="10101";  //başka nrf lerden sinyal almamak için bir iletişim şifresi oluşturduk
int Paket[3]; // gelen verileri bir diziye tanımladık


void setup() {
Serial.begin(9600); //verileri seri portta görüntülemek için seri haberleşme başlattık
servoM1.attach(5);// servo pinlerini tanımladık
servoM2.attach(6);
pinMode(7, OUTPUT);
nrf.begin(); //nrf haberleşmeyi başlattık
nrf.openReadingPipe(0,adres);
nrf.setPALevel(RF24_PA_MIN);
nrf.startListening();

}
void loop() {

if(nrf.available())
{

 nrf.read(&Paket,sizeof(Paket)); //gelen veri paketini oku

if(Paket[0] == HIGH)
{
  digitalWrite(7, HIGH);}
  else{
  digitalWrite(7,LOW);}

  servoM1.write(Paket[1]); //paketin 1. ve 2. indeksini servo derecesi olarak atadık
  servoM2.write(Paket[2]);

}
Serial.print("hız: ");
Serial.println(Paket[0]); 
Serial.print("yatay: "); 
Serial.println(Paket[1]);
Serial.print("dikey: "); 
Serial.println(Paket[2]);
delay(5);
}
