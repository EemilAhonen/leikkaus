/*
  ==============================================================================

    UI-Save.cpp
    Created: 5 Feb 2024 8:50:17pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginEditor.h"

//==============================================================================

/**
 * @brief Saves the current bounds (width and height) of AudioProcessorEditor.
 *
 * This method updates the stored width and height properties in the associated
 * ValueTree of the LeikkausAudioProcessor. It also updates the corresponding member
 * variables in the audioProcessor object for future reference.
 *
 * @note This method is called when the bounds of the GUI component change
 */
void LeikkausAudioProcessorEditor::savePluginBounds()
{
    // Retrieve the current width and height of the GUI component
    const int newWidth = getWidth();
    const int newHeight = getHeight();

    // Update the width and height properties in the associated ValueTree
    audioProcessor._valueTree.setProperty("width", newWidth, nullptr);
    audioProcessor._valueTree.setProperty("height", newHeight, nullptr);

    // Update the corresponding member variables in the audioProcessor object
    audioProcessor._width = newWidth;
    audioProcessor._height = newHeight;
}