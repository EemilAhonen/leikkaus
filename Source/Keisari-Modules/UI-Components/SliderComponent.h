/*
  ==============================================================================

    SliderComponent.h
    Created: 27 Jan 2024 3:27:03am
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once
#include "UIComponent.h"

//==============================================================================

class SliderComponent : public UIComponent
{
public:
  SliderComponent(const juce::String id, const juce::String name, const juce::String toolTip, const float minValue, const float maxValue, const float initValue, const float interval, const int x, const int y, const int width, const int height, int lookAndFeelID)
      : UIComponent(id, name, toolTip, x, y, width, height, lookAndFeelID), _minValue(minValue), _maxValue(maxValue), _initValue(initValue), _interval(interval)
  {
    _component = std::make_unique<juce::Slider>();
  }

public:
  const float _minValue;
  const float _maxValue;
  const float _initValue;
  const float _interval;
};
