/*
  ==============================================================================

    Globals.cpp
    Created: 23 Jan 2024 10:21:41pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "Globals.h"

//== Parameters ================================================================

const juce::String inputID = "input";
const juce::String inputName = "Input";
const juce::String inputToolTip = "Adjust the input gain. Increase for more volume, decrease for less.";

const juce::String outputID = "output";
const juce::String outputName = "Output";
const juce::String outputToolTip = "Adjust the output gain. Increase for more volume, decrease for less";

const juce::String ceilingID = "ceiling";
const juce::String ceilingName = "Ceiling";
const juce::String ceilingToolTip = "Adjust the clipping ceiling to control the clipping threshold. Decrease for more distortion, increase for less.";

const juce::String ratioID = "ratio";
const juce::String ratioName = "Ratio";
const juce::String ratioToolTip = "Adjust the ratio to control clipping softness. 0% for hard clip (inf:1), 100% for complete bypass (1:1).";

const juce::String mixID = "mix";
const juce::String mixName = "Mix";
const juce::String mixToolTip = "Adjust the dry/wet mix. 0% for full dry (input), 100% for full wet (processed)";

const juce::String compensationID = "compensation";
const juce::String compensationName = "Compensation";
const juce::String compensationToolTip = "Toggle compensation to counteract input gain changes. When enabled, the opposite of the input gain is added to the output for consistent volume levels.";

const juce::String oversamplingID = "oversampling";
const juce::String oversamplingName = "Oversampling";
const juce::String oversamplingToolTip = "Toggle 2x oversampling. Enable for smoother processing at the cost of increased CPU usage.";

const juce::String deltaID = "delta";
const juce::String deltaName = "Delta";
const juce::String deltaToolTip = "Toggle to output the delta signal, representing the difference between the input and processed signal.";
