// Pin definitions
const int CLK = D0;   // Encoder CLK pin
const int DT = D1;    // Encoder DT pin
const int SW = D2;    // Encoder switch pin

// Variables
int lastCLK = 0;     // Last CLK state
int encoderValue = 0;        // Encoder count value
bool isPositive = true;      // Positive/Negative state

void setup() {
  // Initialize serial communication
  Serial.begin(115200);  // ESP32S3 default baud rate
  
  // Initialize pins
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  
  // Read initial state
  lastCLK = digitalRead(CLK);
  isPositive = digitalRead(SW) == LOW;  // Switch ON = positive, OFF = negative
}

void loop() {
  // Read encoder
  int currentCLK = digitalRead(CLK);
  
  // Check CLK state change
  if (currentCLK != lastCLK) {
    // If CLK state changes, check DT state
    if (currentCLK == LOW) {  // Only detect on falling edge
      if (digitalRead(DT) == HIGH) {
        // Clockwise rotation (right turn)
        encoderValue += 10;
      } else {
        // Counter-clockwise rotation (left turn)
        encoderValue -= 10;
      }
      
      // Output current value with state
      if (encoderValue > 0) {
        Serial.print("+");
        Serial.print(encoderValue);
        Serial.print(" ");
        Serial.println(isPositive ? "positive" : "negative");
      } else if (encoderValue < 0) {
        Serial.print(encoderValue);
        Serial.print(" ");
        Serial.println(isPositive ? "positive" : "negative");
      } else {
        Serial.print("0 ");
        Serial.println();
      }
    }
  }
  
  lastCLK = currentCLK;

  // Check switch state
  bool currentSwitchState = digitalRead(SW) == LOW;
  if (currentSwitchState != isPositive) {
    isPositive = currentSwitchState;  // Switch ON = positive, OFF = negative
    // Output current value with new state
    if (encoderValue > 0) {
      Serial.print("+");
      Serial.print(encoderValue);
      Serial.print(" ");
      Serial.println(isPositive ? "positive" : "negative");
    } else if (encoderValue < 0) {
      Serial.print(encoderValue);
      Serial.print(" ");
      Serial.println(isPositive ? "positive" : "negative");
    } else {
      Serial.print("0 ");
      Serial.println(isPositive ? "positive" : "negative");
    }
  }
}