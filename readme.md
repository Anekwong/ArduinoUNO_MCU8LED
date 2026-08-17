# Arduino UNO R3 ควบคุม LED 8 หลอด

เอกสารนี้อธิบายการต่อวงจรและโปรแกรมควบคุม Arduino UNO R3 สำหรับเปิด/ปิดหลอด LED จำนวน 8 หลอด ผ่านการกดตัวอักษรใน Serial Monitor

## อุปกรณ์ที่ใช้

- Arduino UNO R3
- LED จำนวน 8 หลอด
- ตัวต้านทาน 220 โอห์ม หรือ 330 โอห์ม จำนวน 8 ตัว
- สาย Jumper
- Breadboard

## การเชื่อมต่อวงจร

ต่อขา Anode ของ LED แต่ละหลอดเข้ากับขา GPIO ของ Arduino ผ่านตัวต้านทาน และต่อขา Cathode ลง GND

| LED | ขา Arduino UNO R3 |
| --- | --- |
| LED1 | GPIO2 |
| LED2 | GPIO3 |
| LED3 | GPIO4 |
| LED4 | GPIO5 |
| LED5 | GPIO6 |
| LED6 | GPIO7 |
| LED7 | GPIO8 |
| LED8 | GPIO9 |

## คำสั่งควบคุม

เปิด Serial Monitor แล้วตั้งค่า Baud Rate เป็น `9600` จากนั้นกดตัวอักษรเพื่อควบคุม LED

| ตัวอักษร | การทำงาน |
| --- | --- |
| A | เปิด/ปิด LED1 |
| B | เปิด/ปิด LED2 |
| C | เปิด/ปิด LED3 |
| D | เปิด/ปิด LED4 |
| E | เปิด/ปิด LED5 |
| F | เปิด/ปิด LED6 |
| G | เปิด/ปิด LED7 |
| H | เปิด/ปิด LED8 |
| I | เปิด LED ทุกหลอด |
| J | ปิด LED ทุกหลอด |
| K | ไฟกระพริบทีละ 2 หลอด วิ่งจากซ้ายไปขวา |
| L | ไฟกระพริบทีละ 1 หลอด วิ่งจากขวาไปซ้าย |

## โปรแกรม Arduino

```cpp
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int ledCount = 8;
bool ledStates[] = {false, false, false, false, false, false, false, false};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("Arduino UNO R3 LED Control Ready");
  Serial.println("Press A-H to toggle LED1-LED8");
  Serial.println("Press I = all ON, J = all OFF, K = 2 LEDs run left to right, L = 1 LED run right to left");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command >= 'a' && command <= 'z') {
      command = command - 32;
    }

    switch (command) {
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
        toggleLed(command - 'A');
        break;

      case 'I':
        allOn();
        break;

      case 'J':
        allOff();
        break;

      case 'K':
        runTwoLedsLeftToRight();
        break;

      case 'L':
        runOneLedRightToLeft();
        break;
    }
  }
}

void toggleLed(int index) {
  ledStates[index] = !ledStates[index];
  digitalWrite(ledPins[index], ledStates[index] ? HIGH : LOW);
}

void allOn() {
  for (int i = 0; i < ledCount; i++) {
    ledStates[i] = true;
    digitalWrite(ledPins[i], HIGH);
  }
}

void allOff() {
  for (int i = 0; i < ledCount; i++) {
    ledStates[i] = false;
    digitalWrite(ledPins[i], LOW);
  }
}

void runTwoLedsLeftToRight() {
  allOff();

  for (int i = 0; i < ledCount - 1; i++) {
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[i + 1], HIGH);
    delay(300);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[i + 1], LOW);
  }
}

void runOneLedRightToLeft() {
  allOff();

  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(300);
    digitalWrite(ledPins[i], LOW);
  }
}
```

## วิธีใช้งาน

1. ต่อวงจรตามตารางการเชื่อมต่อ
2. เปิด Arduino IDE
3. คัดลอกโปรแกรมไปวางใน Arduino IDE
4. เลือกบอร์ด `Arduino UNO`
5. เลือก Port ที่เชื่อมต่อกับ Arduino
6. อัปโหลดโปรแกรมลงบอร์ด
7. เปิด Serial Monitor
8. ตั้ง Baud Rate เป็น `9600`
9. กดตัวอักษร `A` ถึง `L` เพื่อควบคุม LED

