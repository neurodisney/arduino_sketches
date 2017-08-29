// Pic Spritzer Pulse Train Generator
// 
// wait for a TTL pulse to trigger a pulse train that controls
// pressure injections of a pico spritzer.
//
// wolf zinke, Aug 2017
//
// This requires the included digitalWriteFast library to be in the known library path (i.e. ~//sketchbook/libraries)

// load library for fast port control
#include <digitalWriteFast.h>

// Pin configuration
#define PulsePort  10    // pulse train will be generated on this port
#define ListenPort  2    // input pulse to trigger pulse train expected on this port

// pulse train parameters
const int            Npulse   = 10;    // number of pulses in pulse train                 
const unsigned long  PulseDur = 2;     // duration of pulse [us]                             
const unsigned long  GapDur   = 2000;  // gap between two subsequent pulses [us]  

const int            Ntrain   = 4;     // number of pulse trains                                        
const unsigned long  TrainGap = 6000;  // delay between two subsequent pulse trains [s]                                        

// #define digitalWriteFast(_pin_, _state_) ( _pin_ < 8 ? (_state_ ?  PORTD |= 1 << _pin_ : PORTD &= ~(1 << _pin_ )) : (_state_ ?  PORTB |= 1 << (_pin_ -8) : PORTB &= ~(1 << (_pin_ -8)  )))
// the macro sets or clears the appropriate bit in port D if the pin is less than 8 or port B if between 8 and 13

// set up
void setup() {  
  pinMode(ListenPort, INPUT);   // set ListenPort pin as input
  pinMode(PulsePort, OUTPUT);   // set PulsePort  pin as output
}

// main loop
void loop() {
    digitalWrite(PulsePort, LOW); // keep pulser low per default

    if (digitalRead(ListenPort) == HIGH) { // TTL detected, trigger pulse series (assumes that normal state is low)
        
        // loop over number of pulse trains
        for (int S = 1; S <= Ntrain; S++) {  
       
            // loop over number of pulses 
            for (int P = 1; P <= Npulse; P++) {  
         
                // generate a rect pulse
                digitalWriteFast(PulsePort, HIGH); 
                delay(PulseDur);      // keep it high for that duration (use delaymicroseconds if a finer resolution is needed) 
                digitalWriteFast(PulsePort, LOW); 
             
                // wait before next pulse is generated
                if ( P < Npulse ) { 
                    delay(GapDur); 
                }
            }
         
            // wait before next pulse train gets generated
            if ( S < Ntrain ) { delay(TrainGap); }
        }
    }
}

 
