/*
  ==============================================================================

    GaugeLabel.h
    Created: 5 Feb 2024 10:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "GaugeLabel.h"

//==============================================================================

/**
 * @brief Resizes the label and adjusts font size during component resizing.
 */
void GaugeLabel::resized()
{
  if (getCurrentTextEditor() != nullptr)
    getCurrentTextEditor()->setBounds(getLocalBounds());

  juce::Font labelFont = getFont();
  labelFont.setHeight(getHeight() * _fontSize);
  setFont(labelFont);
}

/**
 * @brief Sets TextEditor justification to centered when shown.
 * @param editor A pointer to the shown TextEditor.
 */
void GaugeLabel::editorShown(juce::TextEditor *editor)
{
  editor->setJustification(juce::Justification::centred);
}
