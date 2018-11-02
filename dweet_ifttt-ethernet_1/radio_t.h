#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
class nrf
{
 struct data
{
  bool tube = 0, led = 0, fan = 0, red = 0, med = 0;
}o;
public:
void sendData(data);
void start();

      
};
void nrf::sendData(data a)
{
  o.tube=a.tube;
  o.led=a.led;
  o.fan=a.fan;
  o.red=a.red;
  o.med=a.med;
  start();
  digitalWrite(10,HIGH);
  radio.write(&o, sizeof(o));
  Serial.println("ok");
  delay(1000);
}
void nrf::start()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

/*void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}*/
