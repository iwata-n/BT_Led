/**
 * @brief Bluetoothで指示を受けたらLEDをつける
 */

#include <SPP.h>

USB Usb;
BTD Btd(&Usb);

SPP SerialBT(&Btd, "gabu phone", "0000");

boolean firstMessage = true;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nSPP Bluetooth Library Started"));
}

void loop() {
  Usb.Task();
  if(SerialBT.connected) {
    if(firstMessage) {
      firstMessage = false;
      SerialBT.println(F("Hello from Arduino")); // Send welcome message
    }
    if(Serial.available())
      SerialBT.print(Serial.read());
    if(SerialBT.available())
      Serial.write(SerialBT.read());
  } 
  else 
    firstMessage = true;
}
