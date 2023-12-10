# 2SerialATTINY85
Two Serials with ATTINY85 using SoftwareSerial. Not intended use  but possible. 
Experimenting with SoftwareSerial and ATTINY85, the prospect of having 2 serials was too much to ignore. After all, what if we needed to have one with two UART devices for ... reasons. 
While not the intended use, strangeness did occur. But this sort of thing is all about strange. Why not, after all, discard the ATTINY85 and use some arduino or PICO much bigger with many times the UARTs? These are times of plenty after all and it will always be this way forever. 
Nevertheless there were strange behaviors. For example, using the begin() call for starting both Serials, as normally done, only had the most recently called serial actually listening.
Beyond that, it's a push pull. Send something to Serial 1, it gets sent out of Serial 2, set Serial 2 to listen, get something back, set Serial 1 to listen. 

I did attempt to "toggle" which one was listening back and forth but only in a cursory manner. Lots of remants and such in the read buffer, but that approach is probably possible with better timing and management. 
