/*
  ==============================================================================

    FillKnobLabel.h
    Created: 6 Feb 2024 9:42:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "FillKnobLabel.h"

//==============================================================================

/**
 * @brief Resizes the label and adjusts font size during component resizing.
 */
void FillKnobLabel::resized()
{
  if (getCurrentTextEditor() != nullptr)
    getCurrentTextEditor()->setBounds(getLocalBounds());

  juce::Font labelFont = getFont();
  labelFont.setHeight(getHeight() * 0.75f);
  setFont(labelFont);
}

/**
 * @brief Sets TextEditor justification to centered when shown.
 * @param editor A pointer to the shown TextEditor.
 */
void FillKnobLabel::editorShown(juce::TextEditor *editor)
{
  editor->setJustification(juce::Justification::centred);
}