#define BLYNK_TEMPLATE_ID "TMPL3MZDRAjJw"
#define BLYNK_TEMPLATE_NAME "Person in the Room 1"
#define BLYNK_AUTH_TOKEN "D77FacCmeoiL6HPUI6FWw5aC_ZM1WvGy"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define RELAY_PIN   27
#define SWITCH_PIN  33

char ssid[] = "Jains_2.4G";
char pass[] = "PPSK@5249_kanak";

// Relay state
bool relayState = false;
// Track last physical switch state
bool lastSwitchState = HIGH;

// ---- Blynk handler ----
BLYNK_WRITE(V0) {
  relayState = param.asInt();   // button value from app (1/0)
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
  Serial.print("Blynk set relay: ");
  Serial.println(relayState);
}

// ---- Helper ----
void setRelay(bool state) {
  relayState = state;
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
  Blynk.virtualWrite(V0, relayState);  // keep app in sync
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // default OFF

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lastSwitchState = digitalRead(SWITCH_PIN);
}

void loop() {
  Blynk.run();

  // Read physical switch
  bool currentSwitchState = digitalRead(SWITCH_PIN);

  // Detect change in switch position
  if (currentSwitchState != lastSwitchState) {
    if (currentSwitchState == LOW) {
      // Switch ON
      setRelay(true);
    } else {
      // Switch OFF
      setRelay(false);
    }
    delay(50); // debounce
  }

  lastSwitchState = currentSwitchState;
}
