/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
//TODO: Actually Work out SPI
#include <stdint.h>
//#include "iom328p.h"
#define UBRRH

//static const uint8_t Pb2;
//static const uint8_t Pb1;
static const uint8_t PIN_SPI_SS   = 53;
static const uint8_t PIN_SPI_MOSI = 51;
static const uint8_t PIN_SPI_MISO = 50;
static const uint8_t PIN_SPI_SCK  = 52;

//#define PIN_SPI_SS (4)
//#define ARDUINO 101
//#define __AVR_ATmega328P__
//#define __AVR__
#define __SFR_OFFSET 0x00
#define _SFR_IO8(io_addr) ((io_addr) + __SFR_OFFSET)
//#define USE_PORTB
int PORTB;// _SFR_IO8(0x05)
int DDRB;
int PINB;
#define PORTB0 0
#define PORTB1 1
#define PORTB2 2
#define PORTB3 3
#define PORTB4 4
#define PORTB5 5
#define PORTB6 6
#define PORTB7 7
uint8_t Pd1;
uint8_t Pd2;
uint8_t Pd3;
uint8_t Pd4;
uint8_t Pd5;
uint8_t Pd6;
uint8_t Pd7;
uint8_t Pd8;
uint8_t Pd0;
//#include "iom328p.h"
//#include "USB_HOST_SERIAL.h"

#ifdef __cplusplus
extern "C" {
#endif

	// PSoC include, this has to be wrapped
	#include "project.h"

#ifdef __cplusplus
}
#endif

//Linker -lstdc++

#include <PS4BT.h>
#include "usbhub.h"


USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS4BT PS4(&Btd, PAIR);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void intFunc(void)
{
 UART_UartPutString("Terminal Count.");
Millis_Timer_GetInterruptSource();
Millis_Timer_ClearInterrupt(Millis_Timer_INTR_MASK_TC|Millis_Timer_INTR_MASK_CC_MATCH);
}
int main(void)
{
    
    Millis_Timer_Start();
    
    //isr_1_StartEx(intFunc);

    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    UART_Start();
    UART_UartPutString("Starting Bluetooth Test.\r\n");
    
      if (Usb.Init() == -1) {
    UART_UartPutString(("\r\nOSC did not start\r\n"));
    while (1); // Halt
  }
    else
    {
        UART_UartPutString("USB Initialized.\r\n");
    }
    for(;;)
    {
          Usb.Task();

  if (PS4.connected()) {
        /* Place your application code here. */
        if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      iprintf(("\r\nLeftHatX: "));
      iprintf("%d",PS4.getAnalogHat(LeftHatX));
      iprintf(("\tLeftHatY: "));
      iprintf("%d",PS4.getAnalogHat(LeftHatY));
      iprintf(("\tRightHatX: "));
      iprintf("%d",PS4.getAnalogHat(RightHatX));
      iprintf(("\tRightHatY: "));
      iprintf("%d",PS4.getAnalogHat(RightHatY));
    }
        
        
            if (PS4.getAnalogButton(L2) || PS4.getAnalogButton(R2)) { // These are the only analog buttons on the PS4 controller
      iprintf(("\r\nL2: "));
      iprintf("%d",PS4.getAnalogButton(L2));
      iprintf(("\tR2: "));
      iprintf("%d",PS4.getAnalogButton(R2));
    }
    if (PS4.getAnalogButton(L2) != oldL2Value || PS4.getAnalogButton(R2) != oldR2Value) // Only write value if it's different
      PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
    oldL2Value = PS4.getAnalogButton(L2);
    oldR2Value = PS4.getAnalogButton(R2);

    if (PS4.getButtonClick(PS)) {
      iprintf(("\r\nPS"));
      PS4.disconnect();
    }
    else {
      if (PS4.getButtonClick(TRIANGLE)) {
        iprintf(("\r\nTraingle"));
        PS4.setRumbleOn(RumbleLow);
      }
      if (PS4.getButtonClick(CIRCLE)) {
        iprintf(("\r\nCircle"));
        PS4.setRumbleOn(RumbleHigh);
      }
      if (PS4.getButtonClick(CROSS)) {
        iprintf(("\r\nCross"));
        PS4.setLedFlash(10, 10); // Set it to blink rapidly
      }
      if (PS4.getButtonClick(SQUARE)) {
        iprintf(("\r\nSquare"));
        PS4.setLedFlash(0, 0); // Turn off blinking
      }

      if (PS4.getButtonClick(UP)) {
        iprintf(("\r\nUp"));
        PS4.setLed(Red);
      } if (PS4.getButtonClick(RIGHT)) {
        iprintf(("\r\nRight"));
        PS4.setLed(Blue);
      } if (PS4.getButtonClick(DOWN)) {
        iprintf(("\r\nDown"));
        PS4.setLed(Yellow);
      } if (PS4.getButtonClick(LEFT)) {
        iprintf(("\r\nLeft"));
        PS4.setLed(Green);
      }

      if (PS4.getButtonClick(L1))
        iprintf(("\r\nL1"));
      if (PS4.getButtonClick(L3))
        iprintf(("\r\nL3"));
      if (PS4.getButtonClick(R1))
        iprintf(("\r\nR1"));
      if (PS4.getButtonClick(R3))
        iprintf(("\r\nR3"));

      if (PS4.getButtonClick(SHARE))
        iprintf(("\r\nShare"));
      if (PS4.getButtonClick(OPTIONS)) {
        iprintf(("\r\nOptions"));
        printAngle = !printAngle;
      }
      if (PS4.getButtonClick(TOUCHPAD)) {
        iprintf(("\r\nTouchpad"));
        printTouch = !printTouch;
      }

      //if (printAngle) { // Print angle calculated using the accelerometer only
      //  iprintf(("\r\nPitch: "));
      //  iprintf("%d",PS4.getAngle(Pitch));
      //  iprintf(("\tRoll: "));
      //  iprintf("%d",PS4.getAngle(Roll));
      //}

      if (printTouch) { // Print the x, y coordinates of the touchpad
        if (PS4.isTouching(0) || PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
          iprintf(("\r\n"));
        for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
          if (PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
            iprintf(("X")); iprintf("%d",i + 1); iprintf((": "));
            iprintf("%d",PS4.getX(i));
            iprintf(("\tY")); iprintf("%d",i + 1); iprintf((": "));
            iprintf("%d",PS4.getY(i));
            iprintf(("\t"));
          }
        }
      }
    }
    }
    }
}

/* [] END OF FILE */
