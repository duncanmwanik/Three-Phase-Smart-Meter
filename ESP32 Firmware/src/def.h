#include <Arduino.h>

void setupOLED();
void displayData();

void setupWiFiAndDatabase();
void updateMeasuredData(String data);
void postData();
void checkRelayStatus();

extern float V_P1;
extern float V_P2;
extern float V_P3;

extern float A_P1;
extern float A_P2;
extern float A_P3;

extern float W_P1;
extern float W_P2;
extern float W_P3;

extern int Relay_P1_status;
extern int Relay_P2_status;
extern int Relay_P3_status;
