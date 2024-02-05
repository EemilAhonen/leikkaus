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
  // TODO: These
  _audioParameters.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{compensationID, 1}, compensationName, false));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{oversamplingID, 1}, oversamplingName, false));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{deltaID, 1}, deltaName, false));

  // Add your parameters here
  addSliderParameter(inputID, inputName, -24.0f, 24.0f, 0.0f, 0.1f, 1, 250, 1200, 400, 400, 0);
  addSliderParameter(outputID, outputName, -24.0f, 24.0f, 0.0f, 0.1f, 1, 1825, 1200, 400, 400, 0);
  addSliderParameter(ceilingID, ceilingName, -24.0f, 0.0f, 0.0f, 0.1f, 1, 775, 1200, 400, 400, 0);
  addSliderParameter(kneeID, kneeName, 0.0f, 100.0f, 0.0f, 0.1f, 0, 1300, 1200, 400, 400, 0);
  addSliderParameter(mixID, mixName, 0.0f, 100.0f, 100.0f, 0.1f, 0, 2350, 1200, 400, 400, 0);
}

void Parameters::addSliderParameter(const juce::String id, const juce::String name, float minValue, float maxValue, float initValue, float interval, int decimalPlaces, int x, int y, int width, int height, int lookAndFeelID)
{
  _sliderComponents.push_back(std::make_unique<SliderComponent>(id, name, minValue, maxValue, initValue, interval, x + juceScalingError, y + juceScalingError, width, height, lookAndFeelID));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{id, 1},
      inputName,
      juce::NormalisableRange<float>(minValue, maxValue, interval),
      initValue,
      juce::String(),
      juce::AudioProcessorParameter::Category::genericParameter,
      [decimalPlaces](float value, int)
      { return juce::String(value, decimalPlaces); },
      [](const juce::String &text)
      { return text.getFloatValue(); }));
}
