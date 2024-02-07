/*
  ==============================================================================

    ImageToggleAndFeel.h
    Created: 6 Feb 2024 10:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class ImageToggleLookAndFeel : public juce::LookAndFeel_V4
{
public:
  ImageToggleLookAndFeel()
  {
  }
  void setImages(juce::Image onImage, juce::Image offImage)
  {
    _onImage = onImage;
    _offImage = offImage;
  }

protected:
  void drawTickBox(juce::Graphics &g, juce::Component &toggle, float x, float y, float width, float height, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
  juce::Image _onImage;
  juce::Image _offImage;
};
