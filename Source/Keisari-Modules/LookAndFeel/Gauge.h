/*
  ==============================================================================

    Gauge.h
    Created: 5 Feb 2024 10:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GaugeLabel.h"

//==============================================================================

class Gauge : public juce::LookAndFeel_V4
{
public:
  Gauge() : _fillColor(juce::Colour(255, 255, 255)), _textSize(1.0f) {}
  Gauge(juce::Colour fillColor, float textSize) : _fillColor(fillColor), _textSize(textSize) {}

  void setArrowImage(juce::Image arrowImage) { _arrowImage = arrowImage; }

protected:
  void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider) override;
  juce::Slider::SliderLayout getSliderLayout(juce::Slider &slider) override;
  juce::Label *createSliderTextBox(juce::Slider &) override;

private:
  juce::Colour _fillColor;
  juce::Image _arrowImage;
    
  const float _textSize;
};
