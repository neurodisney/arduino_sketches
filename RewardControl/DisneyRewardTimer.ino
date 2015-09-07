// Disney Reward Timer
// Pat Henry
// 20 July 2015
// modified by wolf zinke

// Disney timer for Juicer Control
// based on Version 3a - All pin numbers and global variables now defined in beginning of program
//  make it easy to change input/output pin numbers.

// Define all the pins numbers and the global variables here:
const int button_Pin  =  5; // Pin 5 input for juicer hand-held runtime button [RED]
const int DIO_Pin     =  4; // Pin 4 DIO input from ext. computer, juicer control follows this input [YELLOW]
const int output_Pin  = 12; // Pin 12 output pin for jucier [WHITE]
const int timeset_Pin =  2; // Pin 2 juicer run time set, juicer runs while active and runtime is reset to new value [currently not used]

unsigned long run_time      = 2000; // Juicer default run time in mSecs
unsigned long debounce_time =  100; // button debounce time
unsigned long dead_time     = 2000; // dead time after button press

// Setup board with desired configuration
void setup()
{
  pinMode(timeset_Pin, INPUT_PULLUP);     // run_time set
  pinMode(DIO_Pin,     INPUT_PULLUP);     // DIO input
  pinMode(button_Pin,  INPUT_PULLUP);     // Switch input
  pinMode(output_Pin,  OUTPUT);           // on-board LED (Juicer control)
}

void loop()
{
     unsigned long start_time;
               
     digitalWrite(output_Pin,0);        // turn LED (juicer) off
     
     while(digitalRead(DIO_Pin)==0) {   // juicer follows DIO when active
         digitalWrite(output_Pin,1);    // turn LED (juicer) on
     }
     digitalWrite(output_Pin,0);

     if(digitalRead(button_Pin)==0) {    // activate juicer on button press &
         start_time=millis();            // initialize run time countdown
     
         while(millis() - start_time <= run_time) {
             digitalWrite(output_Pin,1);
         }
         digitalWrite(output_Pin,0);
         delay(dead_time);
     }

     if(digitalRead(timeset_Pin)==0) {    // reset juicer run time
          start_time=millis();
          delay(debounce_time);
          
          while(digitalRead(timeset_Pin)==0){
              digitalWrite(output_Pin,1);
          }
          run_time=millis()-start_time;
          delay(debounce_time);
          digitalWrite(output_Pin,0);
     }
}

