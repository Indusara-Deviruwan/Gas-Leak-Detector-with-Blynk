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

void readGas() {
  int gasValue = analogRead(GAS_SENSOR); // read gas level
  Blynk.virtualWrite(V0, gasValue);       // send gas level to Blynk

  Serial.print("Gas value: ");
  Serial.println(gasValue);

  // Check reset button
  if (digitalRead(RESET_BTN) == LOW) {
    alarmActive = false;
    Serial.println("Alarm reset manually.");
  }

  if (gasValue > GAS_THRESHOLD) {
    alarmActive = true;
    digitalWrite(BUZZER, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    Blynk.virtualWrite(V1, "🚨 Danger");
    Blynk.virtualWrite(V2, 1); // Red LED status
    Blynk.virtualWrite(V3, 0); // Green LED status
    Blynk.logEvent("gas_alert", "🚨 Gas Leak Detected!");

    Serial.println("🚨 Gas leak detected!");
  } else {
    alarmActive = false;
    digitalWrite(BUZZER, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    Blynk.virtualWrite(V1, "✅ Safe");
    Blynk.virtualWrite(V2, 0); // Red LED off
    Blynk.virtualWrite(V3, 1); // Green LED on

    Serial.println("Gas is safe ✅");
  }
}

// Setup
void setup() {
  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RESET_BTN, INPUT_PULLUP); // reset button active low

  digitalWrite(BUZZER, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH); // green on initially

  Serial.println("=== Gas Leak Detector Initialized ===");
  Serial.println("Green LED on. Waiting for gas leak detection.");

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  // Wait for WiFi to connect
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500); // wait 500 ms
  }

  Serial.println("\n✅ WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, readGas); // check every 1s
}

void loop() {
  // put your main code here, to run repeatedly:

}
