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
  // Add your parameters here
  addSliderParameter(inputID, inputName, inputToolTip, -24.0f, 24.0f, 0.0f, 0.1f, 1, 250, 1200, 400, 400, 0);
  addSliderParameter(outputID, outputName, outputToolTip, -24.0f, 24.0f, 0.0f, 0.1f, 1, 1825, 1200, 400, 400, 0);
  addSliderParameter(ceilingID, ceilingName, ceilingToolTip, -24.0f, 0.0f, 0.0f, 0.1f, 1, 775, 1200, 400, 400, 0);
  addSliderParameter(kneeID, kneeName, kneeToolTip, 0.0f, 100.0f, 0.0f, 0.1f, -1, 1300, 1200, 400, 400, 0);
  addSliderParameter(mixID, mixName, mixToolTip, 0.0f, 100.0f, 100.0f, 0.1f, -1, 2350, 1200, 400, 400, 0);

  addToggleButtonParameter(compensationID, compensationName, compensationToolTip, 562, 1753, 300, 100, 0, false);
  addToggleButtonParameter(oversamplingID, oversamplingName, oversamplingToolTip, 1350, 1753, 300, 100, 1, false);
  addToggleButtonParameter(deltaID, deltaName, deltaToolTip, 2137, 1753, 300, 100, 2, false);
}

void Parameters::addSliderParameter(const juce::String id, const juce::String name, const juce::String toolTip, float minValue, float maxValue, float initValue, float interval, int decimalPlaces, int x, int y, int width, int height, int lookAndFeelID)
{
  _uiComponents.push_back(std::make_unique<SliderComponent>(id, name, toolTip, minValue, maxValue, initValue, interval, x + JUCE_SCALING_ERROR, y + JUCE_SCALING_ERROR, width, height, lookAndFeelID));
  _audioParameters.push_back(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{id, 1},
      inputName,
      juce::NormalisableRange<float>(minValue, maxValue, interval),
      initValue,
      juce::String(),
      juce::AudioProcessorParameter::Category::genericParameter,
      [decimalPlaces](float value, int)
      {
        if (decimalPlaces == 0)
          return juce::String((int)value);
        else
          return juce::String(value, decimalPlaces);
      },
      [](const juce::String &text)
      { return text.getFloatValue(); }));
}

void Parameters::addToggleButtonParameter(const juce::String id, const juce::String name, const juce::String toolTip, int x, int y, int width, int height, int lookAndFeelID, bool initValue)
{
  _audioParameters.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{id, 1}, name, initValue));
  _uiComponents.push_back(std::make_unique<ToggleButtonComponent>(id, name, toolTip, x + JUCE_SCALING_ERROR, y + JUCE_SCALING_ERROR, width, height, lookAndFeelID, initValue));
}
