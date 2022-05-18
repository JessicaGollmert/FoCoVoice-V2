//
//  SynthEditor.h
//  TestSynthAU
//
//  Used to specify the contents and layout of the TestSynthAU User Interface (UI).
//

#ifndef __SynthEditor_h__
#define __SynthEditor_h__

enum CONTROL_TYPE
{
    ROTARY, // rotary knob (pot)
    BUTTON, // push button (trigger)
    TOGGLE, // on/off switch (toggle)
    SLIDER, // linear slider (fader)
    MENU,   // drop-down list (menu)
};

typedef Rectangle<int> Bounds;

struct Control
{
    String name;            // name for control label / saved parameter
    int parameter;          // parameter index associated with control
    CONTROL_TYPE type;      // control type (see above)
    
    // ROTARY and SLIDER only:
    float min;              // minimum slider value (e.g. 0.0)
    float max;              // maximum slider value (e.g. 1.0)
    
    float initial;          // initial value for slider (e.g. 0.0)
    
    Bounds size;            // position (x,y) and size (height, width) of the control (use AUTO_SIZE for automatic layout)
    
    const char* const options[8]; // text options for menus and group buttons
};

const Bounds AUTO_SIZE = Bounds(-1,-1,-1,-1); // used to trigger automatic layout
enum { kParam0, kParam1, kParam2, kParam3, kParam4, kParam5, kParam6, kParam7, kParam8, kParam9 };

//=========================================================================
// UI_CONTROLS - Use this array to completely specify your UI
// - tell the system what controls you want
// - add or remove controls by adding or taking away from the list
// - each control is linked to the specified parameter name and identifier
// - controls can be of different types - rotary, button, toggle, slider (see above)
// - for rotary and linear sliders, you can set the range of values
// - by default, the controls are laid out in a grid, but you can also move and size them manually
//   i.e. replace AUTO_SIZE with Bounds(50,50,100,100) to place a 100x100 control at (50,50)

#define RESTRICTED(name, id, size) \
{   name,       id,         ROTARY, 0.0, 1.0, 0.0,    size        }

const auto componentSize = 70;
const auto componentY = 90;

const Control UI_CONTROLS[] = {
    
    {   "Transition Time a - i",  kParam0,    ROTARY, 0.1, 1.0, 0.4, { 30, componentY, componentSize, componentSize } },
    {   "Delay Z",  kParam1,    ROTARY, 0.1, 1.0, 0.45, {165 , componentY, componentSize, componentSize } },
    {   "End",      kParam2,    ROTARY, 0.5, 2.0, 2.0, { 300, componentY, componentSize, componentSize } },
//
//    RESTRICTED( "Mod 1", kParam5, AUTO_SIZE ), // ************ ASSIGNMENT RESTRICTED *************
//    RESTRICTED( "Mod 2", kParam6, AUTO_SIZE ), // These 5 parameters are controlled by the music.
//    RESTRICTED( "Mod 3", kParam7, AUTO_SIZE ), // You are allowed to change the name and size, but
//    RESTRICTED( "Mod 4", kParam8, AUTO_SIZE ), // MUST NOT CHANGE any other/hidden settings.
//    RESTRICTED( "Mod 5", kParam9, AUTO_SIZE ), // ************************************************
};

const int kNumberOfControls = sizeof(UI_CONTROLS) / sizeof(Control);
const int kNumberOfParameters = kNumberOfControls;

#endif
