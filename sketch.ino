#include "DHT.h"

const int ButtonPin = 5;
bool isDown = false;

class LED {
private:
  int PIN;
  
public:

  LED(int PIN) {
    this->PIN = PIN;
    pinMode(this->PIN, OUTPUT);
  }

  void set_voltage(int voltage) {
    digitalWrite(PIN, voltage);
  }
};

#define DHTPIN 15
#define DHTTYPE DHT22

LED led = LED(2);
DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
  pinMode(ButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  int buttonState = digitalRead(ButtonPin);
  if (buttonState == HIGH && isDown == false) {
    isDown = true;
    led.set_voltage(HIGH);
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    Serial.print("[HUMIDITY]: "+String(humidity)+"\n[TEMPERATURE]: " + String(temperature) + "\n");
  }
  else if (buttonState == LOW && isDown == true) {
    led.set_voltage(LOW);
    isDown = false;
  }
}
