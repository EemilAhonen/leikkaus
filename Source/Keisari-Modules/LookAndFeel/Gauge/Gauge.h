/*
  ==============================================================================

    Gauge.h
    Created: 6 Feb 2024 1:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GaugeLookAndFeel.h"

//==============================================================================

class Gauge : public juce::Slider
{
public:
  Gauge()
  {
    gaugeLookAndFeel = std::make_unique<GaugeLookAndFeel>();
    setLookAndFeel(gaugeLookAndFeel.get());
  }

  ~Gauge()
  {
    setLookAndFeel(nullptr);
  }

  void setTextHeight(float textHeight)
  {
    _textHeight = textHeight;
    gaugeLookAndFeel->setTextHeight(textHeight);
  }

  using RightClickCallback = std::function<void()>;

  void setRightClickCallback(RightClickCallback callback)
  {
    _rightClickCallback = callback;
  }

protected:
  void mouseEnter(const juce::MouseEvent &e) override;
  void mouseExit(const juce::MouseEvent &e) override;
  void mouseUp(const juce::MouseEvent &e) override;
  void mouseDown(const juce::MouseEvent &e) override;

  void mouseDoubleClick(const juce::MouseEvent &) override;

private:
  float _textHeight = 1.0f;
  RightClickCallback _rightClickCallback;

  std::unique_ptr<GaugeLookAndFeel> gaugeLookAndFeel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Gauge)
};
