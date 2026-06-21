  const int MOTOR_PIN = 9;
  int speed = 0;
  String buffer = "";
  unsigned long lastCharTime = 0;
  const unsigned long TIMEOUT = 50;  // ms

  void setup() {
    pinMode(MOTOR_PIN, OUTPUT);
    analogWrite(MOTOR_PIN, 0);
    Serial.begin(9600);
    delay(500);
    Serial.println();
    Serial.println("=== DIEU KHIEN MOTOR ===");
    Serial.println("Nhap so 0-255 roi Enter");
    Serial.println("Vi du: 150");
    Serial.println("========================");
  }

  void loop() {
    // Doc tung ky tu vao buffer
    while (Serial.available() > 0) {
      char c = Serial.read();
      lastCharTime = millis();
      
      if (c == '\n' || c == '\r') {
        processBuffer();
      } else if (c >= 32 && c <= 126) {  // Chi nhan ky tu in duoc
        buffer += c;
      }
    }
    
    // Neu co du lieu trong buffer va da 50ms khong co ky tu moi -> xu ly
    // (truong hop Serial Monitor khong gui Newline)
    if (buffer.length() > 0 && (millis() - lastCharTime) > TIMEOUT) {
      processBuffer();
    }
  }

  void processBuffer() {
    buffer.trim();
    if (buffer.length() == 0) {
      buffer = "";
      return;
    }
    
    int newSpeed = buffer.toInt();
    
    if (newSpeed < 0) newSpeed = 0;
    if (newSpeed > 255) newSpeed = 255;
    
    speed = newSpeed;
    analogWrite(MOTOR_PIN, speed);
    
    Serial.print(">> Toc do: ");
    Serial.print(speed);
    Serial.print("/255 (");
    Serial.print(speed * 100 / 255);
    Serial.println("%)");
    
    buffer = "";
  }