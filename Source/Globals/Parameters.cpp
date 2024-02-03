/*
  ==============================================================================

    Parameters.cpp
    Created: 27 Jan 2024 8:37:05pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "Parameters.h"
#include "Globals.h"

//==============================================================================

Parameters::Parameters()
{
  initParameters();
}

void Parameters::initParameters()
{
  _audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{inputID, 1}, inputName, -24.0, 24.0, 0.0));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{outputID, 1}, outputName, -24.0, 24.0, 0.0));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ceilingID, 1}, ceilingName, -24.0, 0.0, 0.0));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{kneeID, 1}, kneeName, 0.0, 24.0, 0.0));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{mixID, 1}, mixName, 0.0, 100.0, 100.0));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{compensationID, 1}, compensationName, false));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{oversamplingID, 1}, oversamplingName, false));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{deltaID, 1}, deltaName, false));

  // Add your parameters here
  // addSliderParameter(inputVolumeID, inputVolumeName, -24.0f, 24.0f, 0.0f, 0.1f, 35.0f, 442.0f, 497.5f, 497.5f, 0);
  // addSliderParameter(outputVolumeID, outputVolumeName, -24.0f, 24.0f, 0.0f, 0.1f, 2467.0f, 442.0f, 497.5f, 497.5f, 0);
  // addSliderParameter(driveID, driveName, 0.0f, 100.0f, 0.0f, 0.1f, 1100.0f, 290.0f, 800.0f, 800.0f, 0);
  // addSliderParameter(toneID, toneName, -100.0f, 100.0f, 0.0f, 0.1f, 567.0f, 442.0f, 497.5f, 497.5f, 0);
  // addSliderParameter(clarityID, clarityName, 0.0f, 100.0f, 0.0f, 0.1f, 1935.0f, 442.0f, 497.5f, 497.5f, 0);
  // addSliderParameter(mixID, mixName, 0.0f, 100.0f, 100.0f, 0.1f, 2620.0f, 0.0f, 340.0f, 150.0f, 1);
}

void Parameters::addSliderParameter(const juce::String id, const juce::String name, float minValue, float maxValue, float initValue, float interval, float x, float y, float width, float height, int lookAndFeelID)
{
  //_sliderComponents.push_back(std::make_unique<SliderComponent>(id, name, minValue, maxValue, initValue, interval, x, y, width, height, lookAndFeelID));

  //_audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{inputID, 1}, inputName, -24.0, 24.0, 0.0));
}
