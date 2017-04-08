
#ifndef FTDI_interfaceH
#define FTDI_interfaceH

//needed for linux builds
//#include "WinTypes.h"

#include "ftd2xx.h"

class FTDI_interface
{

public:
    FT_HANDLE ftHandle;
    unsigned char DMXData[512];
    unsigned char StartCode;
    FTDI_interface(void);
    void DMXSend(void);
};

#endif

