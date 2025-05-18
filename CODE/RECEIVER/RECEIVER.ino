#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include<SoftwareSerial.h>
SoftwareSerial ss(D1, D2);

String tdata, hdata, bpdata, f1data, f2data;
int count = 0, count1 = 0, count2 = 0, count3 = 0,  count4 = 0, uvc = 0;
#define WLAN_SSID       "WiFi name"
#define WLAN_PASS       "Password"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883 
#define AIO_USERNAME    "your_UserName"
#define AIO_KEY         "AdafruitIOkey"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish FEED = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/info");
Adafruit_MQTT_Publish PH = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");
Adafruit_MQTT_Publish WATER = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/vibaraton");
Adafruit_MQTT_Publish VOLTAGE = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/nir");

Adafruit_MQTT_Subscribe mode0 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Mode");

Adafruit_MQTT_Subscribe motor = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/motor");

void MQTT_connect();
char tdata1[50];
char hdata1[5];
char bpdata1[10];
char f1data1[5];
char f2data1[5];
void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
  delay(10);

  Serial.println(F("Adafruit MQTT"));
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&mode0);
  mqtt.subscribe(&motor);

}

void loop() {

  MQTT_connect();
  count = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  tdata = "";
  hdata = "";
  bpdata = "";
  f1data = "";
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    // Serial.print(c);
    if (c == '*')
    {
      while (Serial.available() > 0)
      {
        char t = Serial.read();
        if (count == 50)
        {
          break;
        }
        if (t == '#') {
          break;
        }
        tdata += t;
        count++;
      }
    }
    if (c == '@')
    {
      while (Serial.available() > 0)
      {
        char h = Serial.read();
        if (count1 == 3)
        {
          break;
        }
        if (h == '#') {
          break;
        }
        hdata += h;
        count1++;
      }
    }
    if (c == '%')
    {
      while (Serial.available() > 0)
      {
        char u = Serial.read();
        if (count2 == 3)
        {
          break;
        }
        if (u == '#') {
          break;
        }
        bpdata += u;
        count2++;
      }
    }
    if (c == '$')
    {
      while (Serial.available() > 0)
      {
        char v = Serial.read();
        if (count3 == 3)
        {
          break;
        }
        if (v == '#') {
          break;
        }
        f1data += v;
        count3++;
      }
    }
    if (c == '^')
    {
      while (Serial.available() > 0)
      {
        char r = Serial.read();
        if (count4 == 3)
        {
          break;
        }
        if (r == '#') {
          break;
        }
        f2data += r;
        count4++;
      }
    }
  }

  if ( tdata.length() > 0 )
  {
    for (int i = 0; i < 50; i++) {
      tdata1[i] = tdata[i];
    }

    Serial.println(tdata1);
    FEED.publish(tdata1);
    tdata = "";

    delay(2000);
  }

  if ( hdata.length() > 0 )
  {
    for (int i = 0; i < 4; i++) {
      hdata1[i] = hdata[i];
    }
    Serial.println(hdata1);
    PH.publish(hdata1);
    hdata = "";
    delay(2000);
  }
  if ( bpdata.length () > 0 )
  {
    for (int i = 0; i < 3; i++) {
      bpdata1[i] = bpdata[i];
    }

    Serial.println(bpdata1);
    WATER.publish(bpdata1);
    bpdata = "";
    delay(2000);
  }
  if ( f1data.length () > 0 )
  {
    for (int i = 0; i < 3; i++) {
      f1data1[i] = f1data[i];
    }

    Serial.println(f1data1);
    VOLTAGE.publish(f1data1);
    f1data = "";
    delay(2000);
  }
  if ( f2data.length () > 0 )
  {
    for (int i = 0; i < 3; i++) {
      f2data1[i] = f2data[i];
    }

    Serial.println(f2data1);
    curren.publish(f2data1);
    f2data = "";
    delay(2000);
  }
  tdata = "";
  hdata = "";
  bpdata = "";
  f1data = "";
  f2data = "";
  count = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  count4 = 0;

  delay(100); 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &mode0) {
      Serial.print(F("Got_mode0: "));
      Serial.println((char *)mode0.lastread);

      if (strcmp((char *)mode0.lastread, "0") == 0) {
        digitalWrite(D4, LOW);
        FEED.publish("AUTO MODE");
      }
      if (strcmp((char *)mode0.lastread, "1") == 0) {
        digitalWrite(D4, HIGH);
        FEED.publish("MANUAL MODE");
      }
    }
    if (subscription == &motor) {
      Serial.print(F("Got_motor: "));
      Serial.println((char *)motor.lastread);

      if (strcmp((char *)motor.lastread, "2") == 0) {
        Serial.write('2');
      }
      if (strcmp((char *)motor.lastread, "3") == 0) {
        Serial.write('3');
      }
    }
  }
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
