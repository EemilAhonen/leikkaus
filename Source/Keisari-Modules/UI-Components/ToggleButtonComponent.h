/*
  ==============================================================================

    UIComponent.h
    Created: 7 Feb 2024 2:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once
#include "UIComponent.h"

//==============================================================================

class ToggleButtonComponent : public UIComponent

{
public:
  ToggleButtonComponent(const juce::String id, const juce::String name, const juce::String toolTip, const int x, const int y, const int width, const int height, int lookAndFeelID, bool initValue)
      : UIComponent(id, name, toolTip, x, y, width, height, lookAndFeelID), _initValue(initValue)
  {
    _component = std::make_unique<juce::ToggleButton>();
  }

public:
  const bool _initValue;
};