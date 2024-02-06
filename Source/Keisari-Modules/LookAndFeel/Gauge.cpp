/*
  ==============================================================================

    Gauge.cpp
    Created: 6 Feb 2024 1:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "Gauge.h"

//==============================================================================

void Gauge::mouseDown(const juce::MouseEvent &e)
{
  juce::ModifierKeys modifiers = juce::ModifierKeys::getCurrentModifiersRealtime();

  // Right click
  if (modifiers.isRightButtonDown())
  {
    if (_rightClickCallback)
    {
      _rightClickCallback();
    }
  }
  else
  {
    Slider::mouseDown(e);
  }
}