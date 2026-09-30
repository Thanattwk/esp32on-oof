#include <Arduino.h>

const int ledPin = 2;             // กำหนดขาพิน 2 (LED บนบอร์ด ESP32)
unsigned long previousTime = 0;   // ตัวแปรสำหรับเก็บเวลาล่าสุดที่ทำงาน
const long interval = 1000;       // ระยะเวลาหน่วง 1000 มิลลิวินาที (1 วินาที)

void setup() {
  // 1. ตั้งค่าความเร็วการสื่อสาร (Baud Rate) ให้ตรงกับ platformio.ini
  Serial.begin(115200);
  
  // 2. กำหนดให้พิน 2 เป็นขาปล่อยสัญญาณออก (Output)
  pinMode(ledPin, OUTPUT);
  
  // แสดงข้อความว่าระบบพร้อมทำงาน
  Serial.println("System Initialized...");
}

void loop() {
  // ดึงเวลาปัจจุบันของบอร์ดมาเก็บไว้ (หน่วยเป็นมิลลิวินาที)
  unsigned long currentTime = millis();

  // เช็คว่าเวลาปัจจุบัน ห่างจากเวลาล่าสุด เกิน 1 วินาทีหรือยัง
  if (currentTime - previousTime >= interval) {
    
    // อัปเดตเวลาล่าสุดให้เป็นเวลาปัจจุบัน
    previousTime = currentTime;

    // อ่านสถานะไฟปัจจุบัน แล้วสั่งงานให้สลับสถานะ (ถ้าติดให้ดับ ถ้าดับให้ติด)
    int currentState = digitalRead(ledPin);
    digitalWrite(ledPin, !currentState);

    // พิมพ์สถานะส่งกลับมาให้อาจารย์ดูที่หน้าจอ
    Serial.print("LED Status: ");
    Serial.println(!currentState ? "ON" : "OFF");
  }
}