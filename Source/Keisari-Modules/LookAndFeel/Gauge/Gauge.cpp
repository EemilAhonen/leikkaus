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

void Gauge::mouseDoubleClick(const juce::MouseEvent &e)
{
  // Get the local bounds of the component and convert to float
  juce::Rectangle<float> localBounds = getLocalBounds().toFloat();

  // Calculate the center y coordinate of the local bounds
  float centerY = localBounds.getCentreY();

  // Calculate the half of the desired range based on the _textHeight percentage
  float halfRange = localBounds.getHeight() * _textHeight / 2;

  // Check if the mouse Y coordinate is within the text height range
  if (auto mouseY = e.getMouseDownY(); std::abs(mouseY - centerY) <= halfRange)
  {
    // Show the Text Editor
    showTextBox();
  }
  else
  {
    // Call the base class implementation if the mouse Y is outside the range
    Slider::mouseDoubleClick(e);
  }
}