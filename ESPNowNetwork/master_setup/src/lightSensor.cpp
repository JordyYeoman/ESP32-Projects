// #include <Wire.h>
// #include <BH1750.h>

// BH1750 lightMeter;

// void setup()
// {
//   Serial.begin(115200);

//   // SLC1 = D4
//   // SLC2 = D2

//   // Initialize the I2C bus (BH1750 library doesn't do this automatically)
//   Wire.begin(D4, D2);

//   lightMeter.begin();

//   Serial.println(F("BH1750 Test begin"));
// }

// void loop()
// {
//   float lux = lightMeter.readLightLevel();
//   Serial.print("Light: ");
//   Serial.print(lux);
//   Serial.println(" lx");
//   delay(100);
// }