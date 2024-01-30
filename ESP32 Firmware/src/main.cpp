#include <Arduino.h>
#include <def.h>

char myData[100];

void setup()
{
    Serial.begin(115200);
    Serial2.begin(9600);
    setupOLED();
    setupWiFiAndDatabase();
    Serial.println("All setup done! \n");
}

void loop()
{
    // delay(1000);//
    checkRelayStatus();
    displayData();

    // Read measured data from Arduino
    if (Serial2.available() > 0)
    {
        byte m = Serial2.readBytesUntil('\n', myData, 100);
        myData[m] = '\0';
        Serial.println(myData);
        updateMeasuredData(String(myData));
    }
}
