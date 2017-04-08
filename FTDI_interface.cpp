//(C) 2013 Michael Johnston (used work by Nicolas Moreau ENTTEC Pty Ltd as an example)

#include "FTDI_interface.h"


#include "ftd2xx.h"


FTDI_interface::FTDI_interface(void)
{
}


void FTDI_interface::DMXSend()
{
    ULONG bytes;

    FT_W32_EscapeCommFunction(ftHandle,CLRDTR);

    FT_W32_SetCommBreak(ftHandle);
    FT_W32_ClearCommBreak(ftHandle);

    //this actually outputs the DMX data to the FTDI device
    FT_W32_WriteFile(ftHandle, &StartCode, 1, &bytes, NULL);
    FT_W32_WriteFile(ftHandle, DMXData, 512, &bytes, NULL);


}


