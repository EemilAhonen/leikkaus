/*
  ==============================================================================

    CeilingVisualizer.h
    Created: 8 Feb 2024 2:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class CeilingVisualizer : public juce::Component
{
public:
  CeilingVisualizer()
  {
  }

  void setCeiling(const float ceiling)
  {
    _ceiling = ceiling;
    repaint();
  }

  void paint(juce::Graphics &g) override;

private:
  float _ceiling = 0.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CeilingVisualizer)
};
