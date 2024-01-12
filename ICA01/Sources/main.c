/********************************************************************/
// HC12 Program:  ICA01 - Switches a red light every time a counter resets
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        Hajay J. Lawson
// Details:       Runs a counter and index, once both have passes a certain threshold, it inverts a red led          
// Date:          12/1/24 (DD/MM/YY)
// Revision History :None
/********************************************************************/


/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

/********************************************************************/
//Defines
/********************************************************************/

#define RED_LED 0b10000000 // Address for the red led
#define INDEX_MAX 10       // The amount of loops it takes index before switching the state of the LEF

/********************************************************************/
// Global Variables
/********************************************************************/

unsigned int counter, index; // Stores the amount of cycles that has passed

/********************************************************************/
// Main Entry
/********************************************************************/

void main(void) {
  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  PT1AD1 |= RED_LED;  // Sets the state of LED_RED
  DDR1AD1 |= RED_LED; // Gets the state of LED-RED
  counter = 0;        // Starts counter at 0
  index = 0;          // Starts index at 0

  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    if(++counter == 0) // Only run once counter overflows
    {
      if(++index >= INDEX_MAX) // Only run once index is greater or equal to the index max
      {
        index = 0;         // Resets the index count
        PT1AD1 ^= RED_LED; // Invert the state of RED_LED
      }
    }
  }

}
