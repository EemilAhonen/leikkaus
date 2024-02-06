/*
  ==============================================================================

    GaugeLookAndFeel.h
    Created: 5 Feb 2024 10:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GaugeLabel.h"

//==============================================================================

class GaugeLookAndFeel : public juce::LookAndFeel_V4
{
public:
  GaugeLookAndFeel() : _fillColor(juce::Colour(255, 255, 255)), _fontSize(1.0f) {}

  void setFillColor(juce::Colour fillColor)
  {
    _fillColor = fillColor;
  }

  void setFontSize(float fontSize)
  {
    _fontSize = fontSize;
  }

protected:
  void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider) override;
  juce::Slider::SliderLayout getSliderLayout(juce::Slider &slider) override;
  juce::Label *createSliderTextBox(juce::Slider &) override;

private:
  juce::Colour _fillColor;
  float _fontSize;
};
