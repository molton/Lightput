# Lightput

This is an old FTDI RS-485 to DMX project that was built using code::blocks, wxwidgets, libftdi2xx, portmidi for midi input, it used to work with VSXu which was an audio visualization software but I have not kept up with it.  The included files might still work for a windows build.

The lightput.cbp file is a code::blocks project file that is probably the easiest way to edit and build lightput, the gui was designed in wxsmith and the gui layout files are included

I'm working on getting this working on modern linux systems with the latest wxwidgets, etc.  It works at the moment but there are issues with saving and loading of information into and from text files at the moment.  All the user data is saved as text which works well until things change, in hindsight it's not the best way to do it.

sorry for the non-existant naming conventions and bad labels, this was an early project and I was just focusing on getting things working which is a style I like when I'm working solo.


# Linux using nautilus issue

I'm using Ubuntu 18.04 and I had to use dconf-editor to change /org/gnome/nautilus/preferences/executable-text-activation from 'display' to 'ask' because when set to display linux just kept trying to display the executable as an image

# Getting access to the FTDI USB device in Linux

libftd2xx linux installation guide
https://www.ftdichip.com/Support/Documents/AppNotes/AN_220_FTDI_Drivers_Installation_Guide_for_Linux.pdf

This does not work with all FTDI USB devices for whatever reason, it works great with some though.  I tried to get it to work with all of them in windows and linux in the past but I could not.  In order for lightput to get access to the USB FTDI serial device in linux, you need to disable some things linux typically automatically enables with these lines from a terminal window.


sudo rmmod ftdi_sio

sudo rmmod usbserial


then run lsusb


lsusb


look for the FTDI serial device in the list, heres an example of the lsusb output

Bus 005 Device 003: ID 046d:c077 Logitech, Inc. M105 Optical Mouse

Bus 005 Device 004: ID 0403:6001 Future Technology Devices International, Ltd FT232 Serial (UART) IC

Bus 005 Device 005: ID 04f2:0402 Chicony Electronics Co., Ltd Genius LuxeMate i200 Keyboard


so the ftdi device is on bus 5, device 4, using that information you'd edit this line accordingly


sudo chmod a+rw /dev/bus/usb/005/004


then lightput should have access to the serial device








