// Arduino IDE 1.8.16
/*
  Rolf Meurer 20-17-02
  UNIVERSAL int2any converter
  int2any(value, digits, base) any value (up to 32-Bit), any number of digits (up to 32 digits), any base (DEC, HEX, OCT, BIN)
  Memory usage: 3408 Bytes
  Global var: 230 Bytes
*/

char int2val[64];                                            // 64 byte Placeholder for the in2any function result
int base;
int digits;

void setup() {
  Serial.begin(57000);
  test();
}

void test() {
  for (int i = 0; i < 4; i++) {                               // BIN, OCT, DEC, HEX
    switch (i) {
      case 0:                                                 // BIN
        base = BIN;                                           // set base to BIN
        digits = 32;                                          // set number of digits to 32
        Serial.println("BIN");                                // display header
        break;
      case 1:                                                 // OCT
        base = OCT;                                           // set base to OCT
        digits = 11;                                          // set number of digits to 11
        Serial.println("OCT");                                // display header
        break;
      case 2:                                                 // DEC
        base = DEC;                                           // set base to DEC
        digits = 10;                                          // set number of digits to 10
        Serial.println("DEC");                                // display header
        break;
      case 3:                                                 // HEX
        base = HEX;                                           // set base to HEX
        digits = 8;                                           // set number of digits to 8
        Serial.println("HEX");                                // display header
        break;
    }

    uint32_t value = 0;                                       // 32-Bit unsigned integer value = 0
    while (value < 0xFFFFFFFF) {                              // 0 ... FFFFFFFE (FFFFFFFF -1 to avoid 32-bit overflow cycles)
      /*             int2any(value, digits, base) any value(uint32_t), number of digits(0 ... 32), any base(DEC, HEX, OCT, BIN)*/
      Serial.println(int2any(value, digits, base));           // Call the int2any function and display the result
      value += value++;                                       // exponentially increasing value (for a clear and quick display)
    }
    Serial.println(int2any(0xFFFFFFFF, digits, base));        // last but not least, Call the int2any function and display (0xFFFFFFFF)
    Serial.println();                                         // Create a blank display line before the next header
  }
  while (1);                                                  // STOP by infinity loop
}

void loop() {
  // we will never come here
}

String int2any(uint32_t val, uint8_t digits, uint8_t base) {  // with leading ZEROs
  String(val, base);
  uint8_t NumberOfDigits;
  if (!val) {
    NumberOfDigits = 1;                                       // 1 ZERO digit with Leading ZEROs
  }
  else {
    NumberOfDigits = 0;
    while (val) {
      val /= base;
      NumberOfDigits++;                                       // n digits with leading ZEROs
    }
  }
  digits = constrain(digits, 1, 32);                          // avoid a ZERO digits specification
  digits = max(digits, NumberOfDigits);                       // If the specified number of digits is not enough to represent the value, ignore them.
  uint8_t NumberOfZeros = digits - NumberOfDigits;            // calculate the number of leading ZEROs
  uint8_t digit[NumberOfZeros];                               // creat an array with leading ZEROs
  for (int i = 0; i < NumberOfZeros; i++) {
    digit[i] = '0';
  }
  strcpy(int2val, digit);                                     // Copy the digits into a global array (outside this function)
  String ret = int2val;                                       // Prepare the return string,
  ret.toUpperCase();                                          // convert to upper case (only for HEX representation)
  return ret;                                                 // and return it.
}
