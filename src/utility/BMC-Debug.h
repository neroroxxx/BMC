/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_DEBUG_H
#define BMC_DEBUG_H
#include <Arduino.h>

#ifdef BMC_DEBUG

// uncomment line below to show the PRETTY_FUNC on debug
//#define BMC_DEBUG_PRETTY_FUNC

#define __PRINT(a)     Serial.print(a); Serial.print(" ");
#define __PRINTLN(a)   Serial.println(a);
#define __PRINTNS(a)   Serial.print(a);
#define __PRINTLNNS(a) __PRINTLN(a);

#define BMC__WARN_LINE  __PRINTLN("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
#define BMC__INFO_LINE  __PRINTLN("##############################################");
#define BMC__ERROR_LINE __PRINTLN("!?@$%!?@$%!?@$%!?@$%!?@$%!?@$%!?@$%!?@$%!?@$%!");


#define BMC_INFO_HEAD \
  __PRINTLN("") \
  BMC__INFO_LINE \
  BMC__INFO_LINE

#define BMC_INFO_FOOT \
  BMC__INFO_LINE \
  BMC__INFO_LINE \
  __PRINTLN("")

#define BMC_WARN_HEAD \
  __PRINTLN("") \
  BMC__WARN_LINE \
  BMC__WARN_LINE

#define BMC_WARN_FOOT \
  BMC__WARN_LINE \
  BMC__WARN_LINE \
  __PRINTLN("")

#define BMC_ERROR_HEAD \
  __PRINTLN("") \
  BMC__ERROR_LINE \
  BMC__ERROR_LINE \
  BMC__ERROR_LINE \
  BMC__ERROR_LINE

#define BMC_ERROR_FOOT \
  BMC__ERROR_LINE \
  BMC__ERROR_LINE \
  BMC__ERROR_LINE \
  BMC__ERROR_LINE \
  __PRINTLN("")


#if defined(BMC_DEBUG_PRETTY_FUNC)
  #define __PRETTY_FUNC Serial.print(__PRETTY_FUNCTION__);Serial.print(":");Serial.print(__LINE__);Serial.print(": ");
#else
  #define __PRETTY_FUNC
#endif

#define BMC_DEBUG_PRINT_BLANK Serial.println("");

  // The Following are meant to help Print multiple (mixed) variables to the Serial Monitor
  // they are used thruout BMC to print strings and variables throut BMC
  // example:
  //          uint8_t x = 127;
  //          float y = 3.14;
  //          int z = -100;
  //          BMC_DEBUG_PRINT("x =", x,",y =",y,",z =",z);
  //
  //          it will display on the Serial Monitor:
  //            x = 127 , y = 3.14 , z = -100

  // BMC_DEBUG_PRINT(...)
  // Print on Serial Monitor with spaces between arguments
  // Equivalent of Serial.println("1");Serial.println(" ");
  #define GET_BMCP_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_PRINT(...) GET_BMCP_MACRO(__VA_ARGS__,BMCP10,BMCP9,BMCP8,BMCP7,BMCP6,BMCP5,BMCP4,BMCP3,BMCP2,BMCP1)(__VA_ARGS__)
  #define BMCP1(s1) Serial.print(s1); Serial.print(" ");
  #define BMCP2(s1,s2) BMCP1(s1) BMCP1(s2)
  #define BMCP3(s1,s2,s3) BMCP2(s1,s2) BMCP1(s3)
  #define BMCP4(s1,s2,s3,s4) BMCP2(s1,s2) BMCP2(s3,s4)
  #define BMCP5(s1,s2,s3,s4,s5) BMCP4(s1,s2,s3,s4) BMCP1(s5)
  #define BMCP6(s1,s2,s3,s4,s5,s6) BMCP5(s1,s2,s3,s4,s5) BMCP1(s6)
  #define BMCP7(s1,s2,s3,s4,s5,s6,s7) BMCP6(s1,s2,s3,s4,s5,s6) BMCP1(s7)
  #define BMCP8(s1,s2,s3,s4,s5,s6,s7,s8) BMCP7(s1,s2,s3,s4,s5,s6,s7) BMCP1(s8)
  #define BMCP9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCP8(s1,s2,s3,s4,s5,s6,s7,s8) BMCP1(s9)
  #define BMCP10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMCP9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCP1(s10)

  // BMC_DEBUG_PRINTNS(...)
  // Same as BMC_DEBUG_PRINT() but without spaces between arguments
  #define GET_BMCPNS_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_PRINTNS(...) GET_BMCPNS_MACRO(__VA_ARGS__,BMCPNS10,BMCPNS9,BMCPNS8,BMCPNS7,BMCPNS6,BMCPNS5,BMCPNS4,BMCPNS3,BMCPNS2,BMCPNS1)(__VA_ARGS__)
  #define BMCPNS1(s1) Serial.print(s1);
  #define BMCPNS2(s1,s2) BMCPNS1(s1) BMCPNS1(s2)
  #define BMCPNS3(s1,s2,s3) BMCPNS2(s1,s2) BMCPNS1(s3)
  #define BMCPNS4(s1,s2,s3,s4) BMCPNS2(s1,s2) BMCPNS2(s3,s4)
  #define BMCPNS5(s1,s2,s3,s4,s5) BMCPNS4(s1,s2,s3,s4) BMCPNS1(s5)
  #define BMCPNS6(s1,s2,s3,s4,s5,s6) BMCPNS5(s1,s2,s3,s4,s5) BMCPNS1(s6)
  #define BMCPNS7(s1,s2,s3,s4,s5,s6,s7) BMCPNS6(s1,s2,s3,s4,s5,s6) BMCPNS1(s7)
  #define BMCPNS8(s1,s2,s3,s4,s5,s6,s7,s8) BMCPNS7(s1,s2,s3,s4,s5,s6,s7) BMCPNS1(s8)
  #define BMCPNS9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCPNS8(s1,s2,s3,s4,s5,s6,s7,s8) BMCPNS1(s9)
  #define BMCPNS10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMCPNS9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCPNS1(s10)

  // BMC_DEBUG_PRINTLN(...)
  // Print on Serial Monitor with spaces between arguments
  // also includes and EOL (end of line) with the last argument
  #define GET_BMCPL_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_PRINTLN(...) GET_BMCPL_MACRO(__VA_ARGS__,BMCPL10,BMCPL9,BMCPL8,BMCPL7,BMCPL6,BMCPL5, BMCPL4, BMCPL3, BMCPL2, BMCPL1)(__VA_ARGS__)
  #define BMCPL1(s1) __PRETTY_FUNC Serial.println(s1);
  #define BMCPL2(s1,s2) __PRETTY_FUNC Serial.print(s1); Serial.print(" "); BMCPL1(s2)
  #define BMCPL3(s1,s2,s3) __PRETTY_FUNC BMC_DEBUG_PRINT(s1, s2) BMCPL1(s3)
  #define BMCPL4(s1,s2,s3,s4) __PRETTY_FUNC BMC_DEBUG_PRINT(s1,s2,s3) BMCPL1(s4)
  #define BMCPL5(s1,s2,s3,s4,s5) __PRETTY_FUNC BMC_DEBUG_PRINT(s1,s2,s3,s4) BMCPL1(s5)
  #define BMCPL6(s1,s2,s3,s4,s5,s6) __PRETTY_FUNC BMC_DEBUG_PRINT(s1,s2,s3,s4,s5) BMCPL1(s6)
  #define BMCPL7(s1,s2,s3,s4,s5,s6,s7) __PRETTY_FUNC BMC_DEBUG_PRINT(s1,s2,s3,s4,s5,s6) BMCPL1(s7)
  #define BMCPL8(s1,s2,s3,s4,s5,s6,s7,s8) __PRETTY_FUNC BMC_DEBUG_PRINT(s1,s2,s3,s4,s5,s6,s7) BMCPL1(s8)
  #define BMCPL9(s1,s2,s3,s4,s5,s6,s7,s8,s9) __PRETTY_FUNC BMC_DEBUG_PRINT(s1,s2,s3,s4,s5,s6,s7,s8) BMCPL1(s9)
  #define BMCPL10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) __PRETTY_FUNC BMC_DEBUG_PRINT(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCPL1(s10)

  // BMC_DEBUG_PRINTLNNS(...)
  // Same as BMC_DEBUG_PRINTLN() but without spaces between arguments
  #define GET_BMCPLNS_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_PRINTLNNS(...) GET_BMCPLNS_MACRO(__VA_ARGS__,BMCPLNS10,BMCPLNS9,BMCPLNS8,BMCPLNS7,BMCPLNS6,BMCPLNS5, BMCPLNS4, BMCPLNS3, BMCPLNS2, BMCPLNS1)(__VA_ARGS__)
  #define BMCPLNS1(s1) __PRETTY_FUNC BMCPL1(s1);
  #define BMCPLNS2(s1,s2) __PRETTY_FUNC BMCPLNS1(s1); BMCPLNS1(s2)
  #define BMCPLNS3(s1,s2,s3) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1, s2) BMCPLNS1(s3)
  #define BMCPLNS4(s1,s2,s3,s4) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1,s2,s3) BMCPLNS1(s4)
  #define BMCPLNS5(s1,s2,s3,s4,s5) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1,s2,s3,s4) BMCPLNS1(s5)
  #define BMCPLNS6(s1,s2,s3,s4,s5,s6) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1,s2,s3,s4,s5) BMCPLNS1(s6)
  #define BMCPLNS7(s1,s2,s3,s4,s5,s6,s7) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1,s2,s3,s4,s5,s6) BMCPLNS1(s7)
  #define BMCPLNS8(s1,s2,s3,s4,s5,s6,s7,s8) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1,s2,s3,s4,s5,s6,s7) BMCPLNS1(s8)
  #define BMCPLNS9(s1,s2,s3,s4,s5,s6,s7,s8,s9) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1,s2,s3,s4,s5,s6,s7,s8) BMCPLNS1(s9)
  #define BMCPLNS10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) __PRETTY_FUNC BMC_DEBUG_PRINTNS(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCPLNS1(s10)

  // BMC_DEBUG_PRINTSL(...)
  // Print Multiple arguments each in a single line
  #define GET_BMCPSL_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_PRINTSL(...) GET_BMCPSL_MACRO(__VA_ARGS__,BMCPSL10,BMCPSL9,BMCPSL8,BMCPSL7,BMCPSL6,BMCPSL5, BMCPSL4, BMCPSL3, BMCPSL2, BMCPSL1)(__VA_ARGS__)
  #define BMCPSL1(s1) Serial.print(" ");Serial.println(s1);
  #define BMCPSL2(s1,s2) BMCPSL1(s1) BMCPSL1(s2)
  #define BMCPSL3(s1,s2,s3) BMCPSL2(s1,s2) BMCPSL1(s3)
  #define BMCPSL4(s1,s2,s3,s4) BMCPSL3(s1,s2,s3) BMCPSL1(s4)
  #define BMCPSL5(s1,s2,s3,s4,s5) BMCPSL4(s1,s2,s3,s4) BMCPSL1(s5)
  #define BMCPSL6(s1,s2,s3,s4,s5,s6) BMCPSL5(s1,s2,s3,s4,s5) BMCPSL1(s6)
  #define BMCPSL7(s1,s2,s3,s4,s5,s6,s7) BMCPSL6(s1,s2,s3,s4,s5,s6) BMCPSL1(s7)
  #define BMCPSL8(s1,s2,s3,s4,s5,s6,s7,s8) BMCPSL7(s1,s2,s3,s4,s5,s6,s7) BMCPSL1(s8)
  #define BMCPSL9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCPSL8(s1,s2,s3,s4,s5,s6,s7,s8) BMCPSL1(s9)
  #define BMCPSL10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMCPSL9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMCPSL1(s10)

  // BMC_DEBUG_WARN(...)
  // Print multiple arguments each in a separate line
  // also include 2 lines each with 20 ! characters before and after
  // use it during debugging to make Warning messages standout more
  #define GET_BMCPW_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_WARN(...) GET_BMCPW_MACRO(__VA_ARGS__,BMCPW10,BMCPW9,BMCPW8,BMCPW7,BMCPW6,BMCPW5, BMCPW4, BMCPW3, BMCPW2, BMCPW1)(__VA_ARGS__)
  #define BMCPW1(s1) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1) BMC_WARN_FOOT
  #define BMCPW2(s1,s2) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2) BMC_WARN_FOOT
  #define BMCPW3(s1,s2,s3) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3) BMC_WARN_FOOT
  #define BMCPW4(s1,s2,s3,s4) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4) BMC_WARN_FOOT
  #define BMCPW5(s1,s2,s3,s4,s5) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5) BMC_WARN_FOOT
  #define BMCPW6(s1,s2,s3,s4,s5,s6) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6) BMC_WARN_FOOT
  #define BMCPW7(s1,s2,s3,s4,s5,s6,s7) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7) BMC_WARN_FOOT
  #define BMCPW8(s1,s2,s3,s4,s5,s6,s7,s8) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8) BMC_WARN_FOOT
  #define BMCPW9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMC_WARN_FOOT
  #define BMCPW10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMC_WARN_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMC_WARN_FOOT

  // BMC_DEBUG_INFO(...)
  // Print multiple arguments each in a separate line
  // also include 2 lines each with 20 * characters before and after
  // use it during debugging to make Information messages standout more
  #define GET_BMCPI_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_INFO(...) GET_BMCPI_MACRO(__VA_ARGS__,BMCPI10,BMCPI9,BMCPI8,BMCPI7,BMCPI6,BMCPI5, BMCPI4, BMCPI3, BMCPI2, BMCPI1)(__VA_ARGS__)
  #define BMCPI1(s1) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1) BMC_INFO_FOOT
  #define BMCPI2(s1,s2) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2) BMC_INFO_FOOT
  #define BMCPI3(s1,s2,s3) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3) BMC_INFO_FOOT
  #define BMCPI4(s1,s2,s3,s4) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4) BMC_INFO_FOOT
  #define BMCPI5(s1,s2,s3,s4,s5) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5) BMC_INFO_FOOT
  #define BMCPI6(s1,s2,s3,s4,s5,s6) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6) BMC_INFO_FOOT
  #define BMCPI7(s1,s2,s3,s4,s5,s6,s7) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7) BMC_INFO_FOOT
  #define BMCPI8(s1,s2,s3,s4,s5,s6,s7,s8) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8) BMC_INFO_FOOT
  #define BMCPI9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMC_INFO_FOOT
  #define BMCPI10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMC_INFO_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMC_INFO_FOOT

  // BMC_DEBUG_ERROR(...)
  // Print multiple arguments each in a separate line
  // also include 2 lines each with 20 * characters before and after
  // use it during debugging to make Information messages standout more
  #define GET_BMCPE_MACRO(_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,NAME,...) NAME
  #define BMC_DEBUG_ERROR(...) GET_BMCPE_MACRO(__VA_ARGS__,BMCPE10,BMCPE9,BMCPE8,BMCPE7,BMCPE6,BMCPE5, BMCPE4, BMCPE3, BMCPE2, BMCPE1)(__VA_ARGS__)
  #define BMCPE1(s1) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1) BMC_ERROR_FOOT
  #define BMCPE2(s1,s2) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2) BMC_ERROR_FOOT
  #define BMCPE3(s1,s2,s3) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3) BMC_ERROR_FOOT
  #define BMCPE4(s1,s2,s3,s4) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4) BMC_ERROR_FOOT
  #define BMCPE5(s1,s2,s3,s4,s5) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5) BMC_ERROR_FOOT
  #define BMCPE6(s1,s2,s3,s4,s5,s6) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6) BMC_ERROR_FOOT
  #define BMCPE7(s1,s2,s3,s4,s5,s6,s7) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7) BMC_ERROR_FOOT
  #define BMCPE8(s1,s2,s3,s4,s5,s6,s7,s8) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8) BMC_ERROR_FOOT
  #define BMCPE9(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8,s9) BMC_ERROR_FOOT
  #define BMCPE10(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMC_ERROR_HEAD __PRETTY_FUNC BMC_DEBUG_PRINTSL(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) BMC_ERROR_FOOT

  #define BMC_DEBUG_PRINT_HEX(a) Serial.print(a,HEX);
  #define BMC_DEBUG_PRINTLN_HEX(a) Serial.println(a,HEX);
  #define BMC_DEBUG_PRINT_BIN(a) Serial.print(a,BIN);
  #define BMC_DEBUG_PRINTLN_BIN(a) Serial.println(a,BIN);
  #define BMC_DEBUG_PRINT_SYSEX(inHex, data, length) BMCSerialMonitor::printArray(inHex, data, length)

  #define BMC_PRINT(...) BMC_DEBUG_PRINT(__VA_ARGS__)
  #define BMC_PRINTNS(...) BMC_DEBUG_PRINTNS(__VA_ARGS__)
  #define BMC_PRINTLN(...) BMC_DEBUG_PRINTLN(__VA_ARGS__)
  #define BMC_PRINTLNNS(...) BMC_DEBUG_PRINTLNNS(__VA_ARGS__)
  #define BMC_PRINT_ARRAY(...) BMC_DEBUG_PRINT_SYSEX(__VA_ARGS__)
  #define BMC_PRINT_HEX(...) BMC_DEBUG_PRINT_HEX(__VA_ARGS__)
  #define BMC_PRINTLN_HEX(...) BMC_DEBUG_PRINTLN_HEX(__VA_ARGS__)
  #define BMC_PRINTSL(...) BMC_DEBUG_PRINTSL(__VA_ARGS__)

  #define BMC_WARN(...) BMC_DEBUG_WARN(__VA_ARGS__)
  #define BMC_WARNING(...) BMC_DEBUG_WARN(__VA_ARGS__)
  #define BMC_INFO(...) BMC_DEBUG_INFO(__VA_ARGS__)
  #define BMC_NOTICE(...) BMC_DEBUG_INFO(__VA_ARGS__)
  #define BMC_ERROR(...) BMC_DEBUG_ERROR(__VA_ARGS__)

#else

  #define BMC_WARN_HEAD
  #define BMC_WARN_FOOT
  #define BMC_INFO_HEAD
  #define BMC_INFO_FOOT
  #define BMC_ERROR_HEAD
  #define BMC_ERROR_FOOT

  #define BMC_DEBUG_PRINT(...)
  #define BMC_DEBUG_PRINTNS(...)
  #define BMC_DEBUG_PRINTLN(...)
  #define BMC_DEBUG_PRINTLNNS(...)

  #define BMC_DEBUG_WARN(...)
  #define BMC_DEBUG_INFO(...)
  #define BMC_DEBUG_ERROR(...)

  #define BMC_PRINT(...)
  #define BMC_PRINTNS(...)
  #define BMC_PRINTLN(...)
  #define BMC_PRINTLNNS(...)
  #define BMC_PRINT_ARRAY(...)
  #define BMC_PRINT_HEX(...)
  #define BMC_PRINTLN_HEX(...)
  #define BMC_PRINTSL(...)

  #define BMC_WARN(...)
  #define BMC_WARNING(...)
  #define BMC_INFO(...)
  #define BMC_NOTICE(...)
  #define BMC_ERROR(...)

#endif


#endif
