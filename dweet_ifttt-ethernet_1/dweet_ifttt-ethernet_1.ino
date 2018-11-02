
#include <SPI.h>
#include <Ethernet.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <IRremote.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char server[] = "www.dweet.io";    // name address for Google (using DNS)

IPAddress ip(192, 168, 0, 177);
EthernetClient client;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";//address of radio

struct data
{
  bool tube = 0, led = 0, fan = 0, red = 0, med = 0;
}o;
int i = 0, j = 0;
char c;
int a = 0;
bool y;
void setup() {
  pinMode(10,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);
 radio.begin();
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

   if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

}

void loop() {
  i=0;
  j=0;
  a=0;
  
   digitalWrite(7, HIGH);
    digitalWrite(10,LOW);
   x:
  // if you get a connection, report back via serial:
   if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /get/latest/dweet/for/jaigarg2401");
    client.println("Host: www.dweet.io");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    delay(1000);
    goto x;
  }

  if(client.available())
  {
    while (i <= 289)
    {
      if (client.available())
      {
        c = client.read();
        i++;
      }
    }
    while (true)
      if (client.available())
      {
        c = client.read();
        break;
      }
      Serial.println(c);
    while (j <=3)
    {
      if (client.available())
      {
        a = client.read();
        j++;
      }
    }
    while (true)
      if (client.available())
      {
        a = client.read() - '0';
        break;
      }
      Serial.println(a);
    if (a == 1)
      y = true;
    else
      y = false;
    /*
       a=fan
       b=tube
       c=med
       d=led
       e=red
    */
    if (c == 'a') o.fan = y;
    else if (c == 'b')o.tube = y;
    else if (c == 'c')o.med = y;
    else if (c == 'd')o.led = y;
    else if (c == 'e')o.red = y;
    Serial.println(o.tube);
    digitalWrite(10,HIGH);
       digitalWrite(7,LOW);
 radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
  radio.write(&o, sizeof(o));
  Serial.println("ok");
  delay(1500);

  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }

}

