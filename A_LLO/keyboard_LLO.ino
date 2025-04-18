// Variables
int encoderValue = 0;        // Encoder count value
bool isPositive = true;      // Positive/Negative state

void setup() {
  // Initialize serial communication
  Serial.begin(115200);  // ESP32S3 default baud rate
}

void loop() {
  // Check if there's any serial data available
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    // Handle encoder simulation
    if (input == 'f') {  // Right turn (clockwise)
      encoderValue += 10;
    } else if (input == 'd') {  // Left turn (counter-clockwise)
      encoderValue -= 10;
    }
    // Handle switch simulation
    else if (input == 'a') {  // Toggle positive/negative
      isPositive = !isPositive;
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
      Serial.println(isPositive ? "positive" : "negative");
    }
  }
}