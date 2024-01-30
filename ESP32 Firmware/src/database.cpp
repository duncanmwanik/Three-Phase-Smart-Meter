#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <LinkedList.h>
#include <def.h>
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
// Insert your network credentials                 
#define WIFI_SSID "Hero"
#define WIFI_PASSWORD "heroinex"
// Insert Firebase project API Key
#define API_KEY "AIzaSyCj1GCpnu7yq5Pukr4feWZWZm3UyGcmpio"
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://mymorning-55468-default-rtdb.firebaseio.com/"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;

void setupWiFiAndDatabase()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        // Serial.println("ok");
        signupOK = true;
    }
    else
    {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("Firebase setup done");
}

void logError(String item, String error)
{
    Serial.print("FAILED TO LOG: ");
    Serial.println(item);
    Serial.print("REASON: ");
    Serial.println(error);
}

void postData()
{
    if (Firebase.ready() && signupOK)
    {
        // ----------- PHASE 1
        if (Firebase.RTDB.setInt(&fbdo, "lines/line1/voltage", V_P1))
        {
            // Serial.print("posting........v: ");
            // Serial.println(V_P1);
        }
        else
        {
            logError("Phase 1 Voltage", String(fbdo.errorReason()));
        }
        if (Firebase.RTDB.setInt(&fbdo, "lines/line1/current", A_P1))
        {
        }
        else
        {
            logError("Phase 1 Current", String(fbdo.errorReason()));
        }
        if (Firebase.RTDB.setInt(&fbdo, "lines/line1/wattage", W_P1))
        {
        }
        else
        {
            logError("Phase 1 Wattage", String(fbdo.errorReason()));
        }
        // ----------- PHASE 2
        if (Firebase.RTDB.setInt(&fbdo, "lines/line2/voltage", V_P2))
        {
        }
        else
        {
            logError("Phase 2 Voltage", String(fbdo.errorReason()));
        }
        if (Firebase.RTDB.setInt(&fbdo, "lines/line2/current", A_P2))
        {
        }
        else
        {
            logError("Phase 2 Current", String(fbdo.errorReason()));
        }
        if (Firebase.RTDB.setInt(&fbdo, "lines/line2/wattage", W_P2))
        {
        }
        else
        {
            logError("Phase 2 Wattage", String(fbdo.errorReason()));
        }
        // ----------- PHASE 3
        if (Firebase.RTDB.setInt(&fbdo, "lines/line3/voltage", V_P3))
        {
        }
        else
        {
            logError("Phase 3 Voltage", String(fbdo.errorReason()));
        }
        if (Firebase.RTDB.setInt(&fbdo, "lines/line3/current", A_P3))
        {
        }
        else
        {
            logError("Phase 3 Current", String(fbdo.errorReason()));
        }
        if (Firebase.RTDB.setInt(&fbdo, "lines/line3/wattage", W_P3))
        {
        }
        else
        {
            logError("Phase 3 Wattage", String(fbdo.errorReason()));
        }
    }
}

void checkRelayStatus()
{
    if (Firebase.ready())
    {
        //
        //
        // All relays
        //
        //
        if (Firebase.RTDB.getInt(&fbdo, "/lines/all/status"))
        {
            if ((fbdo.intData() == 1 || fbdo.intData() == 0) && fbdo.intData() == 1)
            {
                //
                // Phase 1
                //
                if (Firebase.RTDB.getInt(&fbdo, "/lines/line1/status"))
                {
                    if (fbdo.intData() == 1 || fbdo.intData() == 0)
                    {
                        if (fbdo.intData() == 1 || fbdo.intData() == 0)
                        {
                            Relay_P1_status = fbdo.intData();
                        }
                    }
                }
                else
                {
                    logError("Phase 1 Relay", String(fbdo.errorReason()));
                }
                //
                // Phase 2
                //
                if (Firebase.RTDB.getInt(&fbdo, "/lines/line2/status"))
                {
                    if (fbdo.intData() == 1 || fbdo.intData() == 0)
                    {
                        if (fbdo.intData() == 1 || fbdo.intData() == 0)
                        {
                            Relay_P2_status = fbdo.intData();
                        }
                    }
                }
                else
                {
                    logError("Phase 2 Relay", String(fbdo.errorReason()));
                }
                //
                // Phase 3
                //
                if (Firebase.RTDB.getInt(&fbdo, "/lines/line3/status"))
                {
                    if (fbdo.intData() == 1 || fbdo.intData() == 0)
                    {
                        if (fbdo.intData() == 1 || fbdo.intData() == 0)
                        {
                            Relay_P3_status = fbdo.intData();
                        }
                    }
                }
                else
                {
                    logError("Phase 3 Relay", String(fbdo.errorReason()));
                }
                //
                // Send relay data to esp32
                //
                String data = String(Relay_P1_status) + String(Relay_P2_status) + String(Relay_P3_status);

                Serial2.println(data);
                //
                //
            }
            else
            {
                Serial.println("All relays are off...");
                // Send relay data to esp32
                Serial2.println("000");
            }
        }
    }
}

void updateMeasuredData(String data)
{
    // ------------------------------------------ Phase 1
    int line1 = data.indexOf("|");
    String phase1_data = data.substring(0, line1);

    int comma1 = phase1_data.indexOf(",");
    String p1_v = phase1_data.substring(0, comma1);
    String p1_c = phase1_data.substring(comma1 + 1);

    // ------------------------------------------ Phase 2
    int line2 = data.indexOf("|", line1 + 1);
    String phase2_data = data.substring(line1 + 1, line2);

    int comma2 = phase2_data.indexOf(",");
    String p2_v = phase2_data.substring(0, comma2);
    String p2_c = phase2_data.substring(comma2 + 1);

    // ------------------------------------------ Phase 3
    String phase3_data = data.substring(line2 + 1);

    int comma3 = phase3_data.indexOf(",");
    String p3_v = phase3_data.substring(0, comma3);
    String p3_c = phase3_data.substring(comma3 + 1);

    V_P1 = p1_v.toFloat();
    A_P1 = p1_c.toFloat();
    W_P1 = V_P1 * A_P1;
    V_P2 = p2_v.toFloat();
    A_P2 = p2_c.toFloat();
    W_P2 = V_P2 * A_P2;
    V_P3 = p3_v.toFloat();
    A_P3 = p3_c.toFloat();
    W_P3 = V_P3 * A_P3;
if(data.length() > 31){

    postData();

}
}