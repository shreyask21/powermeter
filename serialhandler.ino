void send_serial_data(float power, float voltage, float current) {
  Serial.println(String(power) + "," + String(voltage, 3) + "," + String(current, 1));
}
