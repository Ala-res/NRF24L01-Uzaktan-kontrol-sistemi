#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>


RF24 nrf(9,10); // nrf'nin ce ve csn pinlerinin bağlı olduğu pinleri seçtik
const byte adres[6]="10101"; //başka nrf lerden sinyal almamak için bir iletişim şifresi oluşturduk
int jaystick1;  //joystick değerleri için değişken oluşturduk
int joystick2;
int butonDurum; 

void setup() {
Serial.begin(9600); //seri haberleşme başlatıldı
nrf.begin(); //nrf haberleşmesi başlatıldı 
nrf.openWritingPipe(adres);
nrf.setPALevel(RF24_PA_MIN);
nrf.stopListening();

}

void loop() {

butonDurum = analogRead(A1); //A1 değeri buton durumunu okuyacak
butonDurum1 = map(analogRead(A2), 0, 1023, 0 , 180); //A2 joytick konumunu okuyacak ve bu değerleri 0-180 arasına atıyacak
butonDurum2 = map(analogRead(A3), 0, 1023, 0 , 180);
int Paket[3]={butonDurum , butonDurum1 , butonDurum2};

nrf.write(&Paket, sizeof(Paket)); //analog değerlerin tutulduğu diziyi nrf ile gönderdik


Serial.print("hız: ");
Serial.println(butonDurum); 
Serial.print("yatay: "); 
Serial.println(butonDurum1);
Serial.print("dikey: "); 
Serial.println(butonDurum2);

delay(5);

}
