/*
  ==============================================================================

    Pro-Prepare.cpp
    Created: 27 Jan 2024 8:07:40pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"

//==============================================================================

void LeikkausAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  // Store the sample rate for later use
  _lastSampleRate = sampleRate;

  // Reset and set the ramp duration for transitioning audio processing parameters
  _inputValue.reset(_lastSampleRate, _smoothingParameter);
  _outputValue.reset(_lastSampleRate, _smoothingParameter);
  _ceilingValue.reset(_lastSampleRate, _smoothingParameter);
  _kneeValue.reset(_lastSampleRate, _smoothingParameter);
  _mixValue.reset(_lastSampleRate, _smoothingParameter);

  // Update all parameter values
  parameterChanged(juce::String(), 0.0f);
}
