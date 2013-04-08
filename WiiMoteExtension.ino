#include "wiimote.h"
#include "genesis.h"

#include <avr/power.h>

#include <Wire.h> // This seems redundant, but we need to declare this
                  // dependency in the pde file or else it won't be included
                  // in the build.

// Classic Controller Buttons
byte wiiLeft = 0; // D-Pad Left state
byte wiiRight = 0; // D-Pad Right state
byte wiiUp = 0; // D-Pad Up state
byte wiiDown = 0; // D-Pad Down state
byte wiiA = 0; // A button state
byte wiiB = 0; // B button state
byte wiiX = 0; // X button state
byte wiiY = 0; // Y button state
byte wiiL = 0; // L button state
byte wiiR = 0; // R button state
byte wiiMinus = 0; // MINUS button state
byte wiiPlus = 0; // PLUS button state
byte wiiHome = 0; // HOME button state
byte wiiZLeft = 0; // ZL button state
byte wiiZRight = 0; // ZR button state

/*
 * Analog Buttons.
 * They are initialized with center values from the calibration buffer.
 */
byte wiiLeftAnalogX = calbuf[2]>>2;
byte wiiLeftAnalogY = calbuf[5]>>2;
byte wiiRightAnalogX = calbuf[8]>>3;
byte wiiRightAnalogY = calbuf[11]>>3;

// Wiimote button data stream
byte *stream_callback(byte *buffer) {
    // update wiimote inputs from genesis inputs
    getGenesisState(&wiiUp, &wiiDown, &wiiLeft, &wiiRight, &wiiA, &wiiB, &wiiX, &wiiY);
    
    wiimote_write_buffer(buffer, wiiLeft, wiiRight, wiiUp, wiiDown, wiiA, wiiB, wiiX, wiiY, wiiL, wiiR,
  	wiiMinus, wiiPlus, wiiHome, wiiLeftAnalogX, wiiLeftAnalogY, wiiRightAnalogX, wiiRightAnalogY, wiiZLeft, wiiZRight);
    
    return buffer;
}

void setup() {
    // Power Saving
    DDRB = 0x00; // Set direction to input on all pins
    PORTB = 0xFF; // Enable pull-ups on pins
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    
    power_adc_disable();
    power_spi_disable();
    power_usart0_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    
    // Genesis initialization
    initGenesis();

    // Prepare wiimote communications
    wiimote_stream = stream_callback;
    wiimote_init();
}

void loop()
{

}

