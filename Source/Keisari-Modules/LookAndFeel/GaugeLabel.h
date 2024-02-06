/*
  ==============================================================================

    GaugeLabel.h
    Created: 5 Feb 2024 10:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class GaugeLabel : public juce::Label
{
public:
  GaugeLabel()
  {
  }

  ~GaugeLabel()
  {
    setLookAndFeel(nullptr);
  }

protected:
  void resized() override;
  void editorShown(juce::TextEditor *editor) override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GaugeLabel)
};
