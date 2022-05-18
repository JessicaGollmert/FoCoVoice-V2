//
//  SynthPlugin.cpp
//  TestSynthAU
//
//  Software Synthesizer template project for UWE AMT/CMT students.
//

#include "SynthPlugin.h"

////////////////////////////////////////////////////////////////////////////
// SYNTH - represents the whole synthesiser
////////////////////////////////////////////////////////////////////////////

// Called to create the synthesizer (use to point JUCE to your synthesizer)
Synth* JUCE_CALLTYPE createSynth() {
    
    std::string filePath = "/Users/jessicagollmert/Desktop/Year 3/FYP/Submission/19016714_Digital_Appendix/a) FoCoVoice/Version2_Daisy/TestSynthAU/rawwaves";     // CHANGE FILE PATH //
    
    stk::ADSR::setRawwavePath(filePath);
    
    return new MySynth();
}

// Called when the synthesiser is first created
void MySynth::initialise()
{
    // Initialise synthesiser variables here
}

// Used to apply any additional audio processing to the synthesisers' combined output
// (when called, outputBuffer contains all the voices' audio)
void MySynth::postProcess(float** outputBuffer, int numChannels, int numSamples)
{
    // Use to add global effects, etc.
    float fDry0, fDry1;
    float* pfOutBuffer0 = outputBuffer[0];
    float* pfOutBuffer1 = outputBuffer[1];
    
    while(numSamples--)
    {
        fDry0 = *pfOutBuffer0;
        fDry1 = *pfOutBuffer1;
        
        // Add your global effect processing here
        
        *pfOutBuffer0++ = fDry0;
        *pfOutBuffer1++ = fDry1;
    }
}

////////////////////////////////////////////////////////////////////////////
// VOICE - represents a single note in the synthesiser
////////////////////////////////////////////////////////////////////////////

// Called to create the voice (use to point JUCE to your voice)
Voice* JUCE_CALLTYPE createVoice() {
    return new MyVoice();
}

// Triggered when a note is started (use to initialise / prepare note)
void MyVoice::onStartNote (const int pitch, const float velocity)
{
    iPitch = pitch;
    // convert note number to fundamental frequency (Hz)
    fFrequency = 440.f * pow (2.f, (pitch - 69.f) / 12.f);
     
    fLevel = velocity;
    
    letter1.openResource("1.Consonants/D - Dance2.wav");
    letter1.setBaseFrequency(1);
    
    letter2.openResource("1.Consonants/Z - ZigZag4.wav");
    letter2.setBaseFrequency(1);
    
    vowel1.clear();
    vowel2.clear();
    vowel3.clear();
    
    vowel1.setFrequency(fFrequency);
    vowel1.setPhoneme("ehh");
    
    vowel2.setFrequency(fFrequency);
    vowel2.setPhoneme("eee");
    
    vowel3.setFrequency(fFrequency);
    vowel3.setPhoneme("eee");
    
    // Daisy -> D ehh-eee Z-eee
    float t0 = 0.0f;
    float t1 = letter1.getDuration(); // Duration of D
    float t2 = getParameter(0) + t1; // Transition time for ehh to eee
    float t3 = t2 + getParameter(1); // Delay until Z
    float t4 = t3 + (letter2.getDuration() / 10); // transition Z-eee
    float t5 = t4 + getParameter(2); // Fade out
    
    // Fades for Consonants
    consonantFadeD.set(Envelope::Points (t0, 1) (t1, 0) );
    consonantFadeZ.set(Envelope::Points (t0, 0) (t3, 1) );
    
    // Fades for Vowels
    vowelFade1.set(Envelope::Points (t0, 0) ((t1 / 10), 1) (t2, 0) );
    vowelFade2.set(Envelope::Points (t0, 0) (t1, 0) (t2, 1) (t3, 0) );
    vowelFade3.set(Envelope::Points (t0, 0) (t1, 0) (t2, 0) (t3, 0) (t4, 1) (t5, 0) );
    
    
    delay1.setMaximumDelay(10 * getSampleRate());
    delay1.setDelay(t3 * getSampleRate());
}

// Triggered when a note is stopped (return false to keep the note alive)
bool MyVoice::onStopNote (){
    return true;
}

// Called to render the note's next buffer of audio (generates the sound)
// (return false to terminate the note)
bool MyVoice::process (float** outputBuffer, int numChannels, int numSamples)
{
    float fMix = 0.0f;
    float* fOutL = outputBuffer[0];
    float* fOutR = outputBuffer[1];
    
    float fFade1 = 0.0f;
    float fFade2 = 0.0f;
    float fFade3 = 0.0f;
    float fFade4 = 0.0f;
    float fFade5 = 0.0f;
    
    while(numSamples--)
    {
        point1 = letter1.tick(); // D (d)
        point1 *= 0.5;
        
        point2 = vowel1.tick(); // a (ehh)

        point3 = vowel2.tick(); // i (eee)
        point3 *= 2;
        
        point4 = letter2.tick(); // s (z)
        point4 *= 0.1;
        point4 = delay1.tick(point4);
        
        point5 = vowel3.tick(); // y (eee)
        point5 *= 2;
        
        fFade1 = consonantFadeD.tick(); // D envelope
        fFade2 = vowelFade1.tick(); // Transition D to ehh
        fFade3 = vowelFade2.tick(); // Transition ehh to eee
        fFade4 = consonantFadeZ.tick() ; // Z envelope
        fFade5 = vowelFade3.tick() ; // Transition Z to eee
        
        point1 *= fFade1;
        point2 *= fFade2;
        point3 *= fFade3;
        point4 *= fFade4;
        point5 *= fFade5;

        fMix = point1 + point2 + point3 + point4 + point5;
        
        fMix *= fLevel;

        *fOutL = fMix;
        *fOutR = fMix;

        fOutL++;
        fOutR++;
    }
    
    return true;
};
