#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// ---------------- LED Pins ----------------
int led1 = 6;
int led2 = 7;
int led3 = 8;
int led4 = 9;
int led5 = 10;
int led6 = 13;

// ---------------- Queue ----------------
String cmdQueue[20];
int head = 0;
int tail = 0;

// ---------------- Morse Arrays ----------------
const char* helloCode[]  = {"....", ".", ".-..", ".-..", "---"};
const char* okCode[]     = {"---", "-.-"};
const char* alertCode[]  = {".-", ".-..", ".", ".-.", "-"};
const char* dangerCode[] = {"-..", ".-", "-.", "--.", ".", ".-."};
const char* clearCode[]  = {"-.-.", ".-..", ".", ".-", ".-."};

// ==================================================
// SETUP
// ==================================================
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(20);

  lcd.begin(16, 2);
  showMsg("System Ready", "");
}

// ==================================================
// LOOP
// ==================================================
void loop() {

  // Read incoming command and add to queue
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    if (data.length() > 0) {
      enqueue(data);
    }
  }

  // Execute one queued command
  if (!isQueueEmpty()) {
    String cmd = dequeue();
    executeCommand(cmd);
  }
}

// ==================================================
// QUEUE FUNCTIONS
// ==================================================
bool isQueueEmpty() {
  return head == tail;
}

bool isQueueFull() {
  return ((tail + 1) % 20) == head;
}

void enqueue(String cmd) {
  if (!isQueueFull()) {
    cmdQueue[tail] = cmd;
    tail = (tail + 1) % 20;
  } else {
    showMsg("Queue Full", "");
  }
}

String dequeue() {
  if (!isQueueEmpty()) {
    String cmd = cmdQueue[head];
    head = (head + 1) % 20;
    return cmd;
  }
  return "";
}

// ==================================================
// COMMAND EXECUTION
// ==================================================
void executeCommand(String data) {

  // LED1
  if (data == "1") { digitalWrite(led1, HIGH); showMsg("LED1", "ON"); }
  else if (data == "a") { digitalWrite(led1, LOW); showMsg("LED1", "OFF"); }
  else if (data == "S") { showMsg("LED1", "SOS"); sendPattern(led1, "...---..."); }

  // LED2
  else if (data == "2") { digitalWrite(led2, HIGH); showMsg("LED2", "ON"); }
  else if (data == "b") { digitalWrite(led2, LOW); showMsg("LED2", "OFF"); }
  else if (data == "H") { showMsg("LED2", "HELLO"); sendLetters(led2, helloCode, 5); }

  // LED3
  else if (data == "3") { digitalWrite(led3, HIGH); showMsg("LED3", "ON"); }
  else if (data == "c") { digitalWrite(led3, LOW); showMsg("LED3", "OFF"); }
  else if (data == "O") { showMsg("LED3", "OK"); sendLetters(led3, okCode, 2); }

  // LED4
  else if (data == "4") { digitalWrite(led4, HIGH); showMsg("LED4", "ON"); }
  else if (data == "d") { digitalWrite(led4, LOW); showMsg("LED4", "OFF"); }
  else if (data == "Z") { showMsg("LED4", "ALERT"); sendLetters(led4, alertCode, 5); }

  // LED5
  else if (data == "5") { digitalWrite(led5, HIGH); showMsg("LED5", "ON"); }
  else if (data == "e") { digitalWrite(led5, LOW); showMsg("LED5", "OFF"); }
  else if (data == "Y") { showMsg("LED5", "DANGER"); sendLetters(led5, dangerCode, 6); }

  // LED6
  else if (data == "6") { digitalWrite(led6, HIGH); showMsg("LED6", "ON"); }
  else if (data == "f") { digitalWrite(led6, LOW); showMsg("LED6", "OFF"); }
  else if (data == "X") { showMsg("LED6", "CLEAR"); sendLetters(led6, clearCode, 5); }

  // STATUS
  else if (data == "STATUS") {
    lcd.clear();
    lcd.print("1:");
    lcd.print(digitalRead(led1));
    lcd.print(" 2:");
    lcd.print(digitalRead(led2));
    lcd.print(" 3:");
    lcd.print(digitalRead(led3));

    lcd.setCursor(0, 1);
    lcd.print("4:");
    lcd.print(digitalRead(led4));
    lcd.print(" 5:");
    lcd.print(digitalRead(led5));
    lcd.print(" 6:");
    lcd.print(digitalRead(led6));
  }

  // Custom Text
  else if (data.startsWith("T:")) {
    showMsg("Message", data.substring(2));
  }
// BRIGHTNESS SLIDER COMMANDS
  else if (data.startsWith("A")) {
    int value = constrain(data.substring(1).toInt(), 0, 255);
    analogWrite(led1, value);
    showMsg("LED1 Bright", String(value));
  }

  else if (data.startsWith("B")) {
    int value = constrain(data.substring(1).toInt(), 0, 255);
    analogWrite(led2, value);
    showMsg("LED2 Bright", String(value));
  }

  else if (data.startsWith("C")) {
    int value = constrain(data.substring(1).toInt(), 0, 255);
    analogWrite(led3, value);
    showMsg("LED3 Bright", String(value));
  }

  else if (data.startsWith("D")) {
    int value = constrain(data.substring(1).toInt(), 0, 255);
    analogWrite(led4, value);
    showMsg("LED4 Bright", String(value));
  }

  else if (data.startsWith("E")) {
    int value = constrain(data.substring(1).toInt(), 0, 255);
    analogWrite(led5, value);
    showMsg("LED5 Bright", String(value));
  }

  else if (data.startsWith("F")) {
    int value = constrain(data.substring(1).toInt(), 0, 255);
    analogWrite(led6, value);
    showMsg("LED6 Bright", String(value));
  }
  else {
    showMsg("Unknown Cmd", data);
  }
}

// ==================================================
// LCD FUNCTIONS
// ==================================================
void showMsg(String line1, String line2) {
  lcd.clear();

  if (line1.length() <= 16) {
    lcd.setCursor(0, 0);
    lcd.print(line1);
  } else {
    scrollLine(line1, 0);
  }

  if (line2.length() <= 16) {
    lcd.setCursor(0, 1);
    lcd.print(line2);
  } else {
    scrollLine(line2, 1);
  }
}

void scrollLine(String text, int row) {
  String space = "                ";
  String msg = space + text + space;

  for (int i = 0; i <= msg.length() - 16; i++) {
    lcd.setCursor(0, row);
    lcd.print(msg.substring(i, i + 16));
    delay(200);
  }
}

// ==================================================
// MORSE FUNCTIONS
// ==================================================
void dot(int pin) {
  digitalWrite(pin, HIGH);
  delay(100);
  digitalWrite(pin, LOW);
  delay(80);
}

void dash(int pin) {
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
  delay(80);
}

void sendPattern(int pin, String pattern) {
  for (int i = 0; i < pattern.length(); i++) {
    if (pattern[i] == '.') dot(pin);
    else if (pattern[i] == '-') dash(pin);
  }
  delay(400);
}

void sendLetters(int pin, const char* letters[], int count) {
  for (int i = 0; i < count; i++) {
    String p = letters[i];

    for (int j = 0; j < p.length(); j++) {
      if (p[j] == '.') dot(pin);
      else if (p[j] == '-') dash(pin);
    }

    delay(250);
  }
}