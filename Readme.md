# DartBoard

DartBoard aims to improve a stock dart electronic board and consists of modified hardware and a Qt application.

## Hardware

The hardware is build by combining a PS/2 keyboard and a electronic dart board which work similiar based on M to N connection matrices. Information about the mapping and build can be found in the Info folder.

## Software

The software is Qt Based and currently only works on Windows. It uses LowLevelKeyboardProc to catch all key events and keeps them from being forwareded. The keyboard input is only hooked when the window is in foreground.

Currently the application only displays what target has been hit but it is planned to be improved to provide a complete dart game with multiple modes, player statistics and more.
