#define BLYNK_TEMPLATE_ID "TMPL3MZDRAjJw"
#define BLYNK_TEMPLATE_NAME "Person in the Room 1"
#define BLYNK_AUTH_TOKEN "D77FacCmeoiL6HPUI6FWw5aC_ZM1WvGy"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define relay 27
#define button 33

char ssid[] = "Jains_2.4G";
char pass[] = "PPSK@5249_kanak";

// Variable to store relay state
bool relayState = false;

BLYNK_WRITE(V0) { // Triggered when Blynk button is pressed
  relayState = param.asInt(); // 1 = ON, 0 = OFF
  digitalWrite(relay, relayState ? HIGH : LOW);
}

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(button, INPUT_PULLUP); // internal pull-up enabled
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  static bool lastButtonState = LOW;
  bool currentButtonState = digitalRead(button);

  // Detect button press (state change from LOW to HIGH)
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    relayState = !relayState; // Toggle relay
    digitalWrite(relay, relayState ? HIGH : LOW);
    Blynk.virtualWrite(V0, relayState); // Sync with app
    delay(50); // Debounce
  }

  lastButtonState = currentButtonState;
}