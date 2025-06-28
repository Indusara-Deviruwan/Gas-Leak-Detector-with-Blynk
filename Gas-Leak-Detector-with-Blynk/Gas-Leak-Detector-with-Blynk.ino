#define BLYNK_TEMPLATE_ID "TMPL6rLAtS9tX"
#define BLYNK_TEMPLATE_NAME "Gas Leak Detector"
#define BLYNK_AUTH_TOKEN "RqbikRg-eqq5ooUAU-LHrf8-L9rR9yQy"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "your ssid name";
char pass[] = "your password";

#define GAS_SENSOR A0
#define BUZZER D3
#define RED_LED D1
#define GREEN_LED D2
#define RESET_BTN D4

int GAS_THRESHOLD = 500;
bool alarmActive = false;

BlynkTimer timer;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
