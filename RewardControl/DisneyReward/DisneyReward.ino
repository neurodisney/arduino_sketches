// Disney Reward Timer
// Pat Henry
// 20 July 2015
// modified by wolf zinke

// Disney timer for Juicer Control
// based on Version 3a - All pin numbers and global variables now defined in beginning of program
// make it easy to change input/output pin numbers.

// Define all the pins numbers and the global variables here:
const int button_Pin        =   5; // Pin 5 input for juicer hand-held runtime button [RED]
const int DIO_Pin           =   4; // Pin 4 DIO input from ext. computer, juicer control follows this input [YELLOW]
const int output_Pin        =  12; // Pin 12 output pin for jucier [WHITE]

const int DIO_inithigh      =   0; // set to one if the computer line changes from high to low for the reward

unsigned long rew_dur       = 100; // Juicer default run time in mSecs
unsigned long debounce_time =  60; // button debounce time (make sure it was an intended button press)
unsigned long dead_time     = 100; // dead time after button press

// Setup board with desired configuration
void setup()
{
  pinMode(DIO_Pin,     INPUT_PULLUP); // DIO input
  pinMode(button_Pin,  INPUT_PULLUP); // Switch input
  pinMode(output_Pin,  OUTPUT);       // on-board LED (Juicer control)
}

void loop()
{               
     digitalWrite(output_Pin, LOW);                 // turn juicer off
     
     // computer control with specified duration
     if(DIO_inithigh == 1) {
       if(digitalRead(DIO_Pin)   == LOW) {          // juicer follows DIO when active
          digitalWrite(output_Pin, HIGH);           // turn juicer on
       }
       while(digitalRead(DIO_Pin) == LOW) {}        // wait for the duration of the TTL pulse
            digitalWrite(output_Pin, LOW);          // Reset state of output line
       
     }else{    
       if(digitalRead(DIO_Pin)  == HIGH) {          // juicer follows DIO when active
          digitalWrite(output_Pin, HIGH);           // turn juicer on
       }
       while(digitalRead(DIO_Pin) == HIGH) {}       // wait for the duration of the TTL pulse
             digitalWrite(output_Pin, LOW);         // Reset state of output line
     }
     
     // Button control - needs to be converted into a pulse of defined duration 
     if(digitalRead(button_Pin) == LOW) {           // activate juicer on button press &
       delay(debounce_time);

     if(digitalRead(button_Pin) == LOW) {           // activate juicer on button press &
         digitalWrite(output_Pin, HIGH);            // turn juicer on
         delay(rew_dur);                            // wait for the duration of the reward pulse
         digitalWrite(output_Pin, LOW);             // Reset state of output line
         while(digitalRead(button_Pin)  == LOW) {}  // ensure that the button was released
         delay(dead_time);                          // add some dead time after button release
         }
     }
}

