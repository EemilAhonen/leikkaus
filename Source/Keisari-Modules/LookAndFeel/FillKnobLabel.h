/*
  ==============================================================================

    FillKnobLabel.h
    Created: 6 Feb 2024 9:42:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class FillKnobLabel : public juce::Label
{
public:
  FillKnobLabel(float fontSize) : _fontSize(fontSize)
  {
  }

  ~FillKnobLabel()
  {
    setLookAndFeel(nullptr);
  }

protected:
  void resized() override;
  void editorShown(juce::TextEditor *editor) override;

private:
  const float _fontSize;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FillKnobLabel)
};
