#include <Arduino.h>
#include <uECC.h>

extern "C" {

static int RNG(uint8_t *dest, unsigned size) {
  // Use the least-significant bits from the ADC for an unconnected pin (or connected to a source of 
  // random noise). This can take a long time to generate random data if the result of analogRead(0) 
  // doesn't change very frequently.
  while (size) {
    uint8_t val = 0;
    for (unsigned i = 0; i < 8; ++i) {
      int init = analogRead(0);
      int count = 0;
      while (analogRead(0) == init) {
        ++count;
      }
      
      if (count == 0) {
         val = (val << 1) | (init & 0x01);
      } else {
         val = (val << 1) | (count & 0x01);
      }
    }
    *dest = val;
    ++dest;
    --size;
  }
  // NOTE: it would be a good idea to hash the resulting random data using SHA-256 or similar.
  return 1;
}

}  // extern "C"

void setup() {
  Serial.begin(9600);
  Serial.print("Testing ecc\n");
  uECC_set_rng(&RNG);
}


void print_hex(uint8_t* val, int size) {
  for(int i = 0; i<size; i++ ) {
    if(val[i]<16)
      Serial.print("0");
    Serial.print(val[i], HEX);
  }
  Serial.println();
}


void loop() {
  const struct uECC_Curve_t * curve = uECC_secp256k1();

  uint8_t private_key[32]; // uECC_curve_private_key_size(curve);
  uint8_t public_key[64];  // uECC_curve_public_key_size(curve)
  
  unsigned long a = millis();
  uECC_make_key(public_key, private_key, curve);
  unsigned long b = millis();
  
  Serial.print("Private key "); print_hex(private_key, 32);
  Serial.print("Made key in "); Serial.println(b-a);
  Serial.print("Public key "); print_hex(public_key, 64);

  uint8_t message_hash[32];
  Serial.print("message_hash is "); print_hex(message_hash, 32);
  uint8_t signature[64];
  a = millis();
  uECC_sign(private_key,message_hash,32,signature,curve);
  b = millis();
  
  Serial.print("Signature made in "); Serial.println(b-a);
  Serial.print("Signature is "); print_hex(signature, 64);

  // it would be nice to use uECC_sign_deterministic but need a sha256 context which we can't found
  
  Serial.println();
}