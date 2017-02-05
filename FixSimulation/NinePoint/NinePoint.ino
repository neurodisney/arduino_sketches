// mimik analog signals for a nine point calibration routine  
//
// wolf zinke, Feb 2017

// define output pin for simulated x and y position 
int eyeX =  8;    
int eyeY  = 4;    

// define noise
int noiselevel = 5; // level of shot noise on signal
int noiseX     = 0; // initialize noisy signal
int noiseY     = 0;

// for simplicity use 9 point calibration with identical scale for X and Y
// analogWrite values range from 0 to 255
int EyePos[] = {50, 125, 200};  

int cX = EyePos[1];
int cY = EyePos[1];

// specify range of fixation times
int MinFix             = 200;
int MaxFix             = 1000;
unsigned long FixEnd   =    0;  // timer to end current fixation

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
    
        FixEnd = millis() + random(MinFix, MaxFix); // determine end time of new fixation
    
        // get coordinates for new fixation
        cX = EyePos[random(0,3)]; 
        cY = EyePos[random(0,3)];   
    }
}
