/*
 * Copyright (C) 2015 Southern Storm Software, Pty Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
This example runs tests on the SHA256 implementation to verify correct behaviour.
*/
#include <Arduino.h>
#include <Crypto.h>
#include <SHA256.h>
#include <string.h>

#define HASH_SIZE 32
#define BLOCK_SIZE 64

SHA256 sha256;

void print_hex(uint8_t* val, int size) {
  for(int i = 0; i<size; i++ ) {
    if(val[i]<16)
      Serial.print("0");
    Serial.print(val[i], HEX);
  }
  Serial.println();
}

void setup()
{
    Serial.begin(9600);

    Serial.println();
    uint8_t result[HASH_SIZE];

    sha256.reset();
    sha256.finalize(result, HASH_SIZE);

    print_hex(result, HASH_SIZE);  //E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855

    const char *test = "abc";
    sha256.reset();
    sha256.update(test,3);
    sha256.finalize(result, HASH_SIZE);

    print_hex(result, HASH_SIZE);  //
}

void loop()
{
}