/*
  ==============================================================================

    Gauge.cpp
    Created: 6 Feb 2024 1:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "Gauge.h"

//==============================================================================

void Gauge::mouseEnter(const juce::MouseEvent &e)
{
  gaugeLookAndFeel->mouseEnter();
  Slider::mouseEnter(e);
}

void Gauge::mouseExit(const juce::MouseEvent &e)
{
  gaugeLookAndFeel->mouseExit();
  Slider::mouseExit(e);
}

void Gauge::mouseUp(const juce::MouseEvent &e)
{
  gaugeLookAndFeel->mouseUp();
  Slider::mouseUp(e);
}

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
    gaugeLookAndFeel->mouseDown();
    Slider::mouseDown(e);
  }
}