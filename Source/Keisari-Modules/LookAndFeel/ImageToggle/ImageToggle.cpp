/*
  ==============================================================================

    ImageToggle.cpp
    Created: 7 Feb 2024 1:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "ImageToggle.h"

//==============================================================================

void ImageToggle::mouseDown(const juce::MouseEvent &e)
{
    juce::ModifierKeys modifiers = juce::ModifierKeys::getCurrentModifiersRealtime();

    // Right click
    if (modifiers.isRightButtonDown())
    {
        if (_rightClickCallback)
        {
            _rightClickCallback();
        }
    }
    else
    {
        ToggleButton::mouseDown(e);
    }
}
