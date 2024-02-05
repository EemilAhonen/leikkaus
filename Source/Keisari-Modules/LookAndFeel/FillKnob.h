/*
  ==============================================================================

    FillKnob.h
    Created: 23 Jan 2024 9:42:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FillKnobLabel.h"

//==============================================================================

class FillKnob : public juce::LookAndFeel_V4
{
public:
  FillKnob() : _fillColor(juce::Colour(255, 255, 255)) {}
  FillKnob(juce::Colour fillColor) : _fillColor(fillColor) {}

protected:
  void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider) override;
  juce::Slider::SliderLayout getSliderLayout(juce::Slider &slider) override;
  juce::Label *createSliderTextBox(juce::Slider &) override;

private:
  juce::Colour _fillColor;
};
