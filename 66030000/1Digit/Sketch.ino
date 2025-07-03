// กำหนดขา GPIO ที่เชื่อมต่อกับแต่ละ Segment ของ 7-segment display
// A, B, C, D, E, F, G (ตามลำดับ)
const int segmentPins[] = {19, 18, 5, 17, 16, 4, 0}; // ขา ESP32 ที่เชื่อมต่อกับ Resistor

// รูปแบบการเปิด/ปิด Segment สำหรับตัวเลข 0-9
// แต่ละแถวแทนหนึ่งตัวเลข และแต่ละคอลัมน์แทนหนึ่ง Segment (A-G)
// HIGH = เปิด Segment, LOW = ปิด Segment
// Common Cathode (ต้องส่ง HIGH เพื่อให้ Segment ติด)
const byte digitPatterns[][7] = {
  // A  B  C  D  E  F  G
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

const int NUM_DIGITS = 10; // จำนวนตัวเลขที่จะนับ (0-9)
const int DELAY_TIME = 1000; // หน่วงเวลา 1 วินาที (1000 มิลลิวินาที)

void setup() {
  // กำหนดขาแต่ละ Segment ให้เป็น OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // วนลูปเพื่อแสดงตัวเลข 0-9
  for (int digit = 0; digit < NUM_DIGITS; digit++) {
    // แสดงตัวเลขปัจจุบันบน 7-segment display
    displayDigit(digit);
    // หน่วงเวลา 1 วินาที
    delay(DELAY_TIME);
  }
}

// ฟังก์ชันสำหรับแสดงตัวเลขบน 7-segment display
void displayDigit(int digit) {
  // ตรวจสอบว่าตัวเลขอยู่ในช่วงที่ถูกต้องหรือไม่
  if (digit >= 0 && digit < NUM_DIGITS) {
    // วนลูปเพื่อกำหนดสถานะ (เปิด/ปิด) ของแต่ละ Segment
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], digitPatterns[digit][i]);
    }
  }
}
