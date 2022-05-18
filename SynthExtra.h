//
//  SynthExtra.h
//  TestSynthAU
//
//  This file is a workspace for developing new DSP objects or functions to use in your plugin.
//

#include "PluginWrapper.h"

//class Formant
//{
//public:
//
//    void setFilters(float frequencies[5], float qValues[4]) {
//        for (int i = 0; i < 4; i++) {
//            formantFilters[i].setQ(frequencies[i], qValues[i]);
//        }
//        outputFilter.setCutoff(frequencies[4]);
//    }
//        
//    void setGain(float gain[4]) {
//        for (int i = 0; i < 4; i++) {
//            fFormantGain[i] = gain[i];
//        }
//    }
//    
//    void applyFormantFilters(float filteredSignal[4], float input) {
//        for (int i = 0; i < 4; i++) {
//            filteredSignal[i] = formantFilters[i].tick(input * fFormantGain[i]);
//        }
//    }
//    
//    float filterOutput(float input) {
//        return input = outputFilter.tick(input);
//    }
//
//private:
//    float fFormantGain[4];
//    BPF formantFilters[4];
//    LPF outputFilter;
//};
