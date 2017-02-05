// mimik analog signals for a central fixation vs random eye positions 
//
// wolf zinke, Feb 2017

// define output pin for simulated x and y position 
int eyeX =  8;    
int eyeY  = 4;    

// define noise
int noiselevel = 8; // half of thelevel of shot noise on signal 
int noiseX     = 0; // initialize noisy signal
int noiseY     = 0;

// for simplicity use 9 point calibration with identical scale for X and Y
// analogWrite values range from 0 to 255
int EyePosMin =  50;  
int EyePosMax = 200;  
int cPos      = 125;
int cY        = cPos;
int cX        = cPos;

// specify range of fixation times
unsigned long FixEnd   =    0;  // timer to end current fixation
int CMinFix            = 200;   // time range of central fixations
int CMaxFix            = 1000;

int RMinFix            =  50;   // time range of random fixations
int RMaxFix            = 600;

int PropFix            =  65;   // proportion to keep gaze at center

// set uo
void setup()
{
    pinMode(eyeX, OUTPUT);   
    pinMode(eyeY, OUTPUT); 
    randomSeed(analogRead(0)); // use channel noise to set seed  
}

// run
void loop()
{ 
    // get current noise
    noiseX = round(random(cX - noiselevel, cX + noiselevel));
    noiseY = round(random(cY - noiselevel, cY + noiselevel));
  
    // write current 'eye position'
    analogWrite(eyeX, noiseX);     
    analogWrite(eyeY, noiseY);  
    
    if (millis() > FixEnd) {
    // time for a 'saccade'
    
        if(random(0, 100) > PropFix) {
            FixEnd = millis() + random(RMinFix, RMaxFix); // determine end time of new fixation
            // get coordinates for new fixation
            cX = random(EyePosMin, EyePosMax); 
            cY = random(EyePosMin, EyePosMax);   
            
        }else{
            FixEnd = millis() + random(CMinFix, CMaxFix); // determine end time of new fixation
            // get coordinates for new fixation
            cX = cPos; 
            cY = cPos;   
        }
    }
}
