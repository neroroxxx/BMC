/* 
 * Added here for use in BMC, just a rename of the class

 * Elapsed time types - for easy-to-use measurements of elapsed time
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2011 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

 #ifndef BMCElapsedMillis_h
 #define BMCElapsedMillis_h
 #ifdef __cplusplus
 
 #if ARDUINO >= 100
 #include "Arduino.h"
 #else
 #include "WProgram.h"
 #endif
 
 class BMCElapsedMillis
 {
 private:
   unsigned long ms;
 public:
   BMCElapsedMillis(void) { ms = millis(); }
   BMCElapsedMillis(unsigned long val) { ms = millis() - val; }
   BMCElapsedMillis(const BMCElapsedMillis &orig) { ms = orig.ms; }
   operator unsigned long () const { return millis() - ms; }
   BMCElapsedMillis & operator = (const BMCElapsedMillis &rhs) { ms = rhs.ms; return *this; }
   BMCElapsedMillis & operator = (unsigned long val) { ms = millis() - val; return *this; }
   BMCElapsedMillis & operator -= (unsigned long val)      { ms += val ; return *this; }
   BMCElapsedMillis & operator += (unsigned long val)      { ms -= val ; return *this; }
   BMCElapsedMillis operator - (int val) const           { BMCElapsedMillis r(*this); r.ms += val; return r; }
   BMCElapsedMillis operator - (unsigned int val) const  { BMCElapsedMillis r(*this); r.ms += val; return r; }
   BMCElapsedMillis operator - (long val) const          { BMCElapsedMillis r(*this); r.ms += val; return r; }
   BMCElapsedMillis operator - (unsigned long val) const { BMCElapsedMillis r(*this); r.ms += val; return r; }
   BMCElapsedMillis operator + (int val) const           { BMCElapsedMillis r(*this); r.ms -= val; return r; }
   BMCElapsedMillis operator + (unsigned int val) const  { BMCElapsedMillis r(*this); r.ms -= val; return r; }
   BMCElapsedMillis operator + (long val) const          { BMCElapsedMillis r(*this); r.ms -= val; return r; }
   BMCElapsedMillis operator + (unsigned long val) const { BMCElapsedMillis r(*this); r.ms -= val; return r; }
 };
 
 class BMCElapsedMicros
 {
 private:
   unsigned long us;
 public:
   BMCElapsedMicros(void) { us = micros(); }
   BMCElapsedMicros(unsigned long val) { us = micros() - val; }
   BMCElapsedMicros(const BMCElapsedMicros &orig) { us = orig.us; }
   operator unsigned long () const { return micros() - us; }
   BMCElapsedMicros & operator = (const BMCElapsedMicros &rhs) { us = rhs.us; return *this; }
   BMCElapsedMicros & operator = (unsigned long val) { us = micros() - val; return *this; }
   BMCElapsedMicros & operator -= (unsigned long val)      { us += val ; return *this; }
   BMCElapsedMicros & operator += (unsigned long val)      { us -= val ; return *this; }
   BMCElapsedMicros operator - (int val) const           { BMCElapsedMicros r(*this); r.us += val; return r; }
   BMCElapsedMicros operator - (unsigned int val) const  { BMCElapsedMicros r(*this); r.us += val; return r; }
   BMCElapsedMicros operator - (long val) const          { BMCElapsedMicros r(*this); r.us += val; return r; }
   BMCElapsedMicros operator - (unsigned long val) const { BMCElapsedMicros r(*this); r.us += val; return r; }
   BMCElapsedMicros operator + (int val) const           { BMCElapsedMicros r(*this); r.us -= val; return r; }
   BMCElapsedMicros operator + (unsigned int val) const  { BMCElapsedMicros r(*this); r.us -= val; return r; }
   BMCElapsedMicros operator + (long val) const          { BMCElapsedMicros r(*this); r.us -= val; return r; }
   BMCElapsedMicros operator + (unsigned long val) const { BMCElapsedMicros r(*this); r.us -= val; return r; }
 };
 
 #endif // __cplusplus
 #endif // BMCElapsedMillis_h
 