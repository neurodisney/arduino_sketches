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
#define ListenPort 12    // input pulse to trigger pulse train expected on this port

#define LEDseries   4    // set line for LED to indicate that it is currently active with a pulse train
#define LEDactive   2    // set line for LED to indicate that arduino is active sending a series of pulse trains

///////////////#################################################################///////////////////
// pulse train parameters
const int            Npulse   = 10;    // number of pulses in pulse train                 
const unsigned long  PulseDur = 2;     // duration of pulse [ms]                             
const unsigned long  GapDur   = 198;  // gap between two subsequent pulses [ms]  (full period minus pulse duration)

const int            Ntrain   = 15;     // number of pulse trains                                        

const unsigned long  TrainGap = 60000;  // delay between two subsequent pulse trains [ms]                                        
///////////////#################################################################///////////////////

// set up
void setup() {  
  pinMode(ListenPort, INPUT);   // set ListenPort pin as input
  pinMode(PulsePort, OUTPUT);   // set PulsePort  pin as output
  pinMode(LEDseries, OUTPUT);   // set LEDseries  pin as output
  pinMode(LEDactive, OUTPUT);   // set LEDactive  pin as output
}

// main loop
void loop() {
    digitalWriteFast(PulsePort, LOW); // keep pulser low per default

    if (digitalReadFast(ListenPort) == HIGH) { // TTL detected, trigger pulse series (assumes that normal state is low)
        
        // loop over number of pulse trains
        digitalWriteFast(LEDactive, HIGH); 
        for (int S = 1; S <= Ntrain; S++) {  
       
            // loop over number of pulses 
            digitalWriteFast(LEDseries, HIGH); 
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
            digitalWriteFast(LEDseries, LOW); 

            // wait before next pulse train gets generated
            if ( S < Ntrain ) { delay(TrainGap); }
        }
        digitalWriteFast(LEDactive, LOW); 
    }
}

 
