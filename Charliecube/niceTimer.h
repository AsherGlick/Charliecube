
/******************************************************************************\
| Some helpfull info for overflowing timers with different prescaler values    |
|  16000000 / (   1*256) = 16000000 / 256    =  62500 Hz                       |
|  16000000 / (   8*256) = 16000000 / 2048   =  ~7812 Hz                       |
|  16000000 / (  32*256) = 16000000 / 8192   =  ~1953 Hz                       |
|  16000000 / (  64*256) = 16000000 / 16384  =   ~976 Hz                       |
|  16000000 / ( 128*256) = 16000000 / 32768  =   ~488 Hz                       |
|  16000000 / ( 256*256) = 16000000 / 65536  =   ~244 Hz                       |
|  16000000 / (1024*256) = 16000000 / 262144 =    ~61 Hz                       |
\******************************************************************************/

#if defined(__AVR_ATmega328P__)
  #include "niceTimer_328.h"
#elif defined(__AVR_ATmega32U4__)
  #include "niceTimer_32U4.h"
#elif defined(__AVR_ATmega2560__)
  #include "niceTimer_328.h"
  //#include "niceTimer_2560.h"
#else
  #error you are trying to compile NiceTimer on a non-supported chip
#endif


