const int analogPin = A0;  // Gunakan A0 sebagai input analog untuk Arduino Nano
const int numSamples = 50;  // Jumlah sampel yang akan dirata-rata
const float Calibration = 0.94;

// Konstanta untuk pembagian tegangan
const float R1 = 100000.0;  // 100kΩ
const float R2 = 3300.0;    // 3.3kΩ
const float diodeDrop = 0.7;  // Tegangan maju dioda 1N4007, sekitar 0.7V

void setup() {
  Serial.begin(115200);  // Mulai komunikasi serial dengan baud rate 115200
  pinMode(analogPin, INPUT);
}

void loop() {
  int total = 0;

  // Ambil beberapa sampel untuk averaging
  for (int i = 0; i < numSamples; i++) {
    total += analogRead(analogPin);
    delay(5);  // Beri jeda kecil antara pembacaan
  }

  // Hitung rata-rata nilai ADC
  int avgValue = total / numSamples;

  // Konversi nilai ADC ke tegangan (Arduino Nano menggunakan ADC 10-bit, nilai max 1023, rentang 0-5V)
  float voltage = avgValue * (5.0 / 1023.0);

  // Konversi tegangan yang terbaca menjadi tegangan input sebenarnya dengan mempertimbangkan tegangan dioda
  float inputVoltage = ((voltage * ((R1 + R2) / R2)) + diodeDrop) * Calibration;

  // Tampilkan nilai pada Serial Monitor
  Serial.print("Avg ADC Value: ");
  Serial.print(avgValue);
  Serial.print(" - Measured Voltage: ");
  Serial.print(voltage, 2);
  Serial.print("V - Input Voltage: ");
  Serial.print(inputVoltage, 2);
  Serial.println("V");

  delay(100);  // Tunggu 1 detik sebelum membaca lagi
}
