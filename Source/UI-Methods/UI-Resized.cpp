/*
  ==============================================================================

    UI-Resized.cpp
    Created: 23 Jan 2024 8:54:17pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginEditor.h"

//==============================================================================

void LeikkausAudioProcessorEditor::resized()
{
  // The size of the window where I copied the coordinates from
  float windowSizeForCoordinates = 3000.0f;

  float scaleFactor = getWidth() / windowSizeForCoordinates;

  // Scale UI components
  for (auto &uiComponentPtr : audioProcessor._parameters.getUIComponents())
  {
    UIComponent &uiComponent = *uiComponentPtr;
    uiComponent.setBounds(scaleFactor);
  }

  // Save the set bound to the treestate
  savePluginBounds();
}
