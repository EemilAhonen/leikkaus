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
  GaugeLookAndFeel()
  {
  }

  void setTextHeight(float textHeight)
  {
    _textHeight = textHeight;
  }

  void setFillColor(juce::Colour fillColor)
  {
    _fillColor = fillColor;
  }

  void mouseEnter()
  {
    _hovering = true;
  }

  void mouseExit()
  {
    _hovering = false;
  }

  void mouseDown()
  {
    _mouseDown = true;
  }

  void mouseUp()
  {
    _mouseDown = false;
  }

protected:
  void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider) override;
  juce::Slider::SliderLayout getSliderLayout(juce::Slider &slider) override;
  juce::Label *createSliderTextBox(juce::Slider &) override;

private:
  bool _hovering = false;
  bool _mouseDown = false;
  void drawArrow(juce::Graphics &g, float x, float y, float width, float height, bool flip);

  float _textHeight = 1.0f;
  juce::Colour _fillColor = juce::Colour(255, 255, 255);
};
