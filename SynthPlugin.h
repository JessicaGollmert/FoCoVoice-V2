//
//  SynthPlugin.h
//  TestSynthAU
//
//  Software Synthesizer template project for UWE AMT/CMT students.
//

#ifndef __SynthPlugin_h__
#define __SynthPlugin_h__

#include "PluginProcessor.h"
#include "SynthExtra.h"

//===================================================================================
/** An example STK-voice, based on a sine wave generator                           */
class MyVoice : public Voice
{
public:
    void onStartNote (const int pitch, const float velocity);
    bool onStopNote ();
    
//    void onPitchWheel (const int value);
//    void onControlChange (const int controller, const int value);
    
    bool process (float** outputBuffer, int numChannels, int numSamples);
    
private:    
    float fLevel;
    float fFrequency;

    int iPitch;
    
//    Saw formant[2];
//
//    float fFirstFiltered[4];
//    Formant firstFormant;
//    
//    float fSecondFiltered[4];
//    Formant secondFormant;
    
    stk::VoicForm vowel1;
    stk::VoicForm vowel2;
    stk::VoicForm vowel3;

    Envelope consonantFadeD;
    Envelope consonantFadeZ;
    
    Envelope vowelFade1;
    Envelope vowelFade2;
    Envelope vowelFade3;
    
    stk::DelayL delay1;
    stk::DelayL delay2;
    
    Buffer letter1;
    Buffer letter2;
    Buffer letter3;
    
    float point1 = 0.0f;
    float point2 = 0.0f;
    float point3 = 0.0f;
    float point4 = 0.0f;
    float point5 = 0.0f;
};

class MySynth : public Synth
{
public:
    MySynth() : Synth() {
        initialise();
    }
    
    void initialise();
    void postProcess(float** outputBuffer, int numChannels, int numSamples);

private:
    // Insert synthesizer variables here
};

#endif
