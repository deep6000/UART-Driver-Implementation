# UART-Driver-Implementation

The Project was implemented to run on FRDM Board and Linux Environment to perform following functionalities
1) A circular buffer implementation
2) Unit testing
3) Driver code for the UART
4) An application that responsive to input from the UART that reports statistics of said input in a formatted 
   report to the UART output

Circular buffers
The circular buffer uses single, fixed-size buffer as if it were connected end-to-end. Data added to the 
circular buffer is removed in the same order it was added.
Functionalities-
1) Ability to operate on multiple buffers of different sizes using the same code
2) Add a new item to the buffer
3) Remove oldest item from the buffer
4) Bounds checking and reporting of errors when adding to a full buffer and removing from an empty one
5) Ability to accommodate all 256 legal values for the data it stores

Unit testing
Set up a unit testing framework for testing the circular buffer implementation. 
Used C-Unit test framework to perform unit testing on the Linux platform.

UART device driver
Instead of using the existing library functions (printf(), scanf(), etc.) creating your own UART software 
driver to transmit data to and from a test terminal.
Functionalities-
An interrupt service routine (ISR) function to handle the interrupts. 
Function to check whether the transmitter is available to accept a new character for transmission
Function to transmit a character assuming transmitter is available
Function called by the ISR to supply a next character on completion of the previous
Function called by the ISR for receiving a character
Functions to echo received characters one at a time back to the sender. 

Application
Write an application that receives characters from the UART and and keeps track of the number of occurrences 
of each of the 256 possible characters and sends an updated ASCII formatted report back out the UART for 
display on a terminal.






