// กำหนดขา GPIO ของ ESP32 ที่เชื่อมต่อกับแต่ละ Segment
// เรียงตามลำดับ a, b, c, d, e, f, g
// ตามที่คุณระบุ: GPIO 19, 18, 5, 17, 16, 4, 0
const int segmentPins[] = {19, 18, 5, 17, 16, 4, 0}; 

// สร้าง Array สำหรับเก็บรูปแบบของตัวเลข 0-9
// แต่ละแถวแทน 1 ตัวเลข (0-9)
// แต่ละคอลัมน์แทน 1 Segment (a, b, c, d, e, f, g)
// 1 = Segment ติด (HIGH), 0 = Segment ดับ (LOW)
// สำหรับ Common Cathode: HIGH = On, LOW = Off
const byte numberPatterns[10][7] = {
  // a, b, c, d, e, f, g
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

// จำนวน Segment ทั้งหมด
const int NUM_SEGMENTS = 7;

void setup() {
  // กำหนดให้ขา GPIO ทุกขาที่ใช้เป็น OUTPUT
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // เริ่มต้น Serial Communication สำหรับ Debugging
  Serial.begin(115200); 
  Serial.println("ESP32 Seven Segment Display - Counting 0-9");
  Serial.println("Using GPIO Pins: 19, 18, 5, 17, 16, 4, 0");
  Serial.println("Remember to add pull-up resistors to GPIO 0 and GPIO 5 if boot issues occur.");
}

void loop() {
  // วนลูปแสดงตัวเลข 0 ถึง 9
  for (int number = 0; number <= 9; number++) {
    Serial.print("Displaying: ");
    Serial.println(number);
    displayNumber(number); // เรียกฟังก์ชันแสดงตัวเลข
    delay(1000);           // หน่วงเวลา 1000 มิลลิวินาที (1 วินาที) ก่อนแสดงตัวเลขถัดไป
  }
}

// ฟังก์ชันสำหรับแสดงตัวเลขบน Seven-Segment Display
void displayNumber(int num) {
  // ตรวจสอบว่าตัวเลขอยู่ในช่วงที่รองรับหรือไม่ (0-9)
  if (num >= 0 && num <= 9) {
    // วนลูปเพื่อควบคุมแต่ละ Segment
    for (int i = 0; i < NUM_SEGMENTS; i++) {
      // อ่านค่าจาก array numberPatterns สำหรับ Segment ปัจจุบัน
      // และส่งค่า (HIGH/LOW) ไปที่ขา GPIO ที่เกี่ยวข้อง
      digitalWrite(segmentPins[i], numberPatterns[num][i]);
    }
  } else {
    // ถ้าตัวเลขอยู่นอกช่วงที่รองรับ ให้ปิดทุก Segment
    clearDisplay();
    Serial.println("Error: Number out of range (0-9)");
  }
}

// ฟังก์ชันสำหรับปิดทุก Segment (เคลียร์หน้าจอ)
void clearDisplay() {
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    digitalWrite(segmentPins[i], LOW); // สำหรับ Common Cathode, LOW คือปิด
  }
}
