#include <Arduino.h> // Standard include

float alarmThreshold = 20.0;  // The buzzer will sound if temp is ABOVE this number

// --- PINS ---
const int PIN_PLUG   = 2;
const int PIN_LAMP   = 3;
const int PIN_SWITCH = 4;  
const int PIN_DOOR   = 5;
const int PIN_ALARM  = 6;  
const int PIN_LM35   = A0; 

char command;
unsigned long lastSend = 0;
const int interval = 1000;

// Variables
bool isLampOn = false;      
int lastSwitchState = HIGH; 

// New Variable: Is the alarm system watching the temp?
bool isAlarmArmed = false; 

// Helper function definition
float getStableTemp();

void setup() {
  Serial.begin(9600); 
  
  pinMode(PIN_LAMP, OUTPUT);
  pinMode(PIN_PLUG, OUTPUT);
  pinMode(PIN_ALARM, OUTPUT);
  pinMode(PIN_DOOR, INPUT_PULLUP);
  pinMode(PIN_SWITCH, INPUT_PULLUP); 

  // Initial States
  digitalWrite(PIN_LAMP, HIGH); 
  isLampOn = false;
  
  digitalWrite(PIN_PLUG, HIGH); 
  digitalWrite(PIN_ALARM, LOW); 

  Serial.println("--- SYSTEM STARTED ---");
  Serial.print("Target Temp is set to: ");
  Serial.print(alarmThreshold);
  Serial.println("C");
  Serial.println("Type 'C' to ARM the alarm system.");
}

void loop() {
  // 1. Get Temperature
  float t = getStableTemp();

  if (isAlarmArmed) {
    if (t >= alarmThreshold) {
      digitalWrite(PIN_ALARM, HIGH);
    } else {
      digitalWrite(PIN_ALARM, LOW);
    }
  }

  // 3. PHYSICAL SWITCH LOGIC
  int currentSwitchState = digitalRead(PIN_SWITCH);
  if (currentSwitchState != lastSwitchState) {
    isLampOn = !isLampOn; 
    digitalWrite(PIN_LAMP, isLampOn ? LOW : HIGH);
    lastSwitchState = currentSwitchState; 
    delay(50); 
  }

  // 4. SERIAL COMMANDS
  if (Serial.available() > 0) {
    command = Serial.read();

    if (command == 'A') { isLampOn = true; digitalWrite(PIN_LAMP, LOW); Serial.println("PC: Lamp ON"); }
    else if (command == 'a') { isLampOn = false; digitalWrite(PIN_LAMP, HIGH); Serial.println("PC: Lamp OFF"); }

    if (command == 'B') { digitalWrite(PIN_PLUG, LOW); Serial.println("Plug: ON"); }
    else if (command == 'b') { digitalWrite(PIN_PLUG, HIGH); Serial.println("Plug: OFF"); }

    // --- ALARM COMMANDS ---
    if (command == 'C') {
       isAlarmArmed = true; // Turn monitoring ON
       Serial.println("Alarm System: ARMED (Watching Temp...)");
    }
    else if (command == 'c') {
       isAlarmArmed = false; // Turn monitoring OFF
       digitalWrite(PIN_ALARM, LOW); // Silence immediately
       Serial.println("Alarm System: DISARMED");
    }
  }

  // 5. REPORTING
  if (millis() - lastSend > interval) {
    lastSend = millis();
    String switchText = (digitalRead(PIN_SWITCH) == LOW) ? "CLOSED" : "OPEN";
    String alarmStatus = isAlarmArmed ? "ARMED" : "OFF";
    
    Serial.print("Temp: "); Serial.print(t, 1);
    Serial.print("C (Limit: "); Serial.print(alarmThreshold, 0);
    Serial.print("C) | Alarm: "); Serial.print(alarmStatus);
    Serial.print(" | Switch: "); Serial.println(switchText);
  }
}

// Function to smooth LM35 readings
float getStableTemp() {
  float totalAmount = 0;
  for (int i = 0; i < 10; i++) {
    totalAmount += analogRead(PIN_LM35);
    delay(5); 
  }
  float averageVal = totalAmount / 10.0;
  return (averageVal * 5.0 / 1024.0) * 100.0;
}
