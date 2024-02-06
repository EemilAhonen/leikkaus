/*
  ==============================================================================

    SliderComponent.h
    Created: 27 Jan 2024 3:27:03am
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================

// TODO: Make an elder class and inherit from that, this is only for sliders now

class SliderComponent
{
public:
  SliderComponent(const juce::String id, const juce::String name, const juce::String toolTip, const float minValue, const float maxValue, const float initValue, const float interval, const int x, const int y, const int width, const int height, int lookAndFeelID)
      : _id(id), _name(name), _toolTip(toolTip), _minValue(minValue), _maxValue(maxValue), _initValue(initValue), _interval(interval), _x(x), _y(y), _width(width), _height(height), _lookAndFeelID(lookAndFeelID)
  {
    _slider = std::make_unique<juce::Slider>();
  }

  void setBounds(float ratio = 1.0f);
  void setSlider(std::unique_ptr<juce::Slider> newSlider)
  {
    _slider = std::move(newSlider);
  }
  juce::Slider *getSlider() { return _slider.get(); }

public:
  const juce::String _id;
  const juce::String _name;
  const juce::String _toolTip;

  const float _minValue;
  const float _maxValue;
  const float _initValue;
  const float _interval;

  const int _x;
  const int _y;
  const int _width;
  const int _height;

  const int _lookAndFeelID;

private:
  std::unique_ptr<juce::Slider> _slider;
};
