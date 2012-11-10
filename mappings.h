#ifndef _MAPPINGS_H_
#define _MAPPINGS_H_

/****************************** PIN PORT MAPPINGS *****************************\
| There are 16 logical groups for controlling the LEDs. This defines which     |
| physical pin coresponds to each. For example, to use analogue pin 2 (PORTC   |
| bit 3) for group 15, we set P13C=0x04 and P13B=P13D=0;                       |
|                                                                              |
| See ATmega328 specs for more info about direct port access.                  |
\******************************************************************************/
#define P1B 0x00
#define P1C 0x00
#define P1D 0x04 //2

#define P2B 0x00
#define P2C 0x00
#define P2D 0x08//3

#define P3B 0x00
#define P3C 0x00
#define P3D 0x10//4

#define P4B 0x00
#define P4C 0x00
#define P4D 0x20//5

#define P5B 0x00
#define P5C 0x00
#define P5D 0x40//6

#define P6B 0x00
#define P6C 0x00
#define P6D 0x80//7

#define P7B 0x01//8
#define P7C 0x00
#define P7D 0x00

#define P8B 0x02//9
#define P8C 0x00
#define P8D 0x00

#define P9B 0x04//10
#define P9C 0x00
#define P9D 0x00

#define P10B 0x08//11
#define P10C 0x00
#define P10D 0x00

#define P11B 0x10//12
#define P11C 0x00
#define P11D 0x00

#define P12B 0x20//13
#define P12C 0x00
#define P12D 0x00

#define P13B 0x00
#define P13C 0x01//A0
#define P13D 0x00

#define P14B 0x00
#define P14C 0x02//A1
#define P14D 0x00

#define P15B 0x00
#define P15C 0x04//A2
#define P15D 0x00

#define P16B 0x00
#define P16C 0x08//A3
#define P16D 0x00



/* LED group mappings
 *
 * This defines which group to turn on for each LED. The first group specifies the anode (+5V),
 * the second the cathode (GND).
 * The pins are named based on color, x, y, z.
 */
#define b111 4,8
#define b112 16,4
#define b113 12,16
#define b114 8,12
#define b121 4,7
#define b122 13,4
#define b123 11,13
#define b124 7,11
#define b131 4,6
#define b132 15,4
#define b133 10,15
#define b134 6,10
#define b141 4,5
#define b142 14,4
#define b143 9,14
#define b144 5,9
#define b211 3,8
#define b212 15,3
#define b213 11,15
#define b214 8,11
#define b221 3,7
#define b222 14,3
#define b223 12,14
#define b224 7,12
#define b231 3,6
#define b232 16,3
#define b233 9,16
#define b234 6,9
#define b241 3,5
#define b242 13,3
#define b243 10,13
#define b244 5,10
#define b311 2,8
#define b312 14,2
#define b313 10,14
#define b314 8,10
#define b321 2,7
#define b322 15,2
#define b323 9,15
#define b324 7,9
#define b331 2,6
#define b332 13,2
#define b333 12,13
#define b334 6,12
#define b341 2,5
#define b342 16,2
#define b343 11,16
#define b344 5,11
#define b411 1,8
#define b412 13,1
#define b413 9,13
#define b414 8,9
#define b421 1,7
#define b422 16,1
#define b423 10,16
#define b424 7,10
#define b431 1,6
#define b432 14,1
#define b433 11,14
#define b434 6,11
#define b441 1,5
#define b442 15,1
#define b443 12,15
#define b444 5,12
#define g111 16,8
#define g112 12,4
#define g113 8,16
#define g114 4,12
#define g121 13,7
#define g122 11,4
#define g123 7,13
#define g124 4,11
#define g131 15,6
#define g132 10,4
#define g133 6,15
#define g134 4,10
#define g141 14,5
#define g142 9,4
#define g143 5,14
#define g144 4,9
#define g211 15,8
#define g212 11,3
#define g213 8,15
#define g214 3,11
#define g221 14,7
#define g222 12,3
#define g223 7,14
#define g224 3,12
#define g231 16,6
#define g232 9,3
#define g233 6,16
#define g234 3,9
#define g241 13,5
#define g242 10,3
#define g243 5,13
#define g244 3,10
#define g311 14,8
#define g312 10,2
#define g313 8,14
#define g314 2,10
#define g321 15,7
#define g322 9,2
#define g323 7,15
#define g324 2,9
#define g331 13,6
#define g332 12,2
#define g333 6,13
#define g334 2,12
#define g341 16,5
#define g342 11,2
#define g343 5,16
#define g344 2,11
#define g411 13,8
#define g412 9,1
#define g413 8,13
#define g414 1,9
#define g421 16,7
#define g422 10,1
#define g423 7,16
#define g424 1,10
#define g431 14,6
#define g432 11,1
#define g433 6,14
#define g434 1,11
#define g441 15,5
#define g442 12,1
#define g443 5,15
#define g444 1,12
#define r111 12,8
#define r112 8,4
#define r113 4,16
#define r114 16,12
#define r121 11,7
#define r122 7,4
#define r123 4,13
#define r124 13,11
#define r131 10,6
#define r132 6,4
#define r133 4,15
#define r134 15,10
#define r141 9,5
#define r142 5,4
#define r143 4,14
#define r144 14,9
#define r211 11,8
#define r212 8,3
#define r213 3,15
#define r214 15,11
#define r221 12,7
#define r222 7,3
#define r223 3,14
#define r224 14,12
#define r231 9,6
#define r232 6,3
#define r233 3,16
#define r234 16,9
#define r241 10,5
#define r242 5,3
#define r243 3,13
#define r244 13,10
#define r311 10,8
#define r312 8,2
#define r313 2,14
#define r314 14,10
#define r321 9,7
#define r322 7,2
#define r323 2,15
#define r324 15,9
#define r331 12,6
#define r332 6,2
#define r333 2,13
#define r334 13,12
#define r341 11,5
#define r342 5,2
#define r343 2,16
#define r344 16,11
#define r411 9,8
#define r412 8,1
#define r413 1,13
#define r414 13,9
#define r421 10,7
#define r422 7,1
#define r423 1,16
#define r424 16,10
#define r431 11,6
#define r432 6,1
#define r433 1,14
#define r434 14,11
#define r441 12,5
#define r442 5,1
#define r443 1,15
#define r444 15,12


#endif
