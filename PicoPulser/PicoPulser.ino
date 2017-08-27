// Pic Spritzer Pulse Train Generator
// 
// wait for a TTL pulse to trigger a pulse train that controls
// pressure injections of a pico spritzer.
//
// wolf zinke, Aug 2017

// load library for fast port control
#include <digitalWriteFast.h>


// Pin configuration

#define PulsePort  7     // pulse train will be generated on this port
#define ListenPort 4     // input pulse to trigger pulse train expected on this port

// pulse train parameters
const int     Npulse   = 12;    // number of pulses in pulse train                 
unsigned long PulseDur = 20;    // duration of pulse [us]                             
unsigned long GapDur   = 20;    // gap between two subsequent pulses [us]  

const int     Ntrain   = 3;     // number of pulse trains                                        
unsigned long TrainGap = 60;    // delay between two subsequent pulse trains [s]                                        


//#define digitalWriteFast(_pin_, _state_) ( _pin_ < 8 ? (_state_ ?  PORTD |= 1 << _pin_ : PORTD &= ~(1 << _pin_ )) : (_state_ ?  PORTB |= 1 << (_pin_ -8) : PORTB &= ~(1 << (_pin_ -8)  )))
// the macro sets or clears the appropriate bit in port D if the pin is less than 8 or port B if between 8 and 13

// set up
void setup() {  
  pinMode(ListenPort, INPUT);   // set PulsePort pin as output
  pinMode(PulsePort, OUTPUT);   // set PulsePort pin as output
}

void loop() {
   digitalWrite(PulsePort, LOW); // keep pulser low

   if (digitalRead(ListenPort) == HIGH) { // TTL detected, trigger pulse series
       for (int S = 1; S <= Ntrain; S++) {  // loop over number of pulse trains
       
         for (int P = 1; P >= Npulse; P++) {  // loop over number of pulses
             digitalWriteFast(PulsePort, HIGH); 
             delayMicroseconds(PulseDur);      // waits "on" microseconds
             digitalWriteFast(PulsePort, LOW); 
             if ( P < Npulse ) { delayMicroseconds(GapDur); }
         }
         
         if ( S < Ntrain ) { delay(TrainGap); }
       }
   }
}
 
 
