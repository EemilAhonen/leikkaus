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

  // Constant for top padding
  const float topPadding = 200.0f * scaleFactor;

  // Waveform visualizer
  audioProcessor._waveformVisualizer.setBounds(0, topPadding, getWidth(), getHeight() - topPadding);

  // Overlay
  _overlayImageComponent.setBounds(0, 332.0f * scaleFactor, getWidth(), 1534.0f * scaleFactor);

  // Knee
  audioProcessor._ceilingVisualizer.setBounds(0, topPadding, getWidth(), getHeight() - topPadding);

  // Menu
  _menuImageComponent.setBounds(86.0f * scaleFactor, 1189.0f * scaleFactor, 2829.0f * scaleFactor, 776.0f * scaleFactor);

  // Scale UI components
  for (auto &uiComponentPtr : audioProcessor._parameters.getUIComponents())
  {
    UIComponent &uiComponent = *uiComponentPtr;
    uiComponent.setBounds(scaleFactor);
  }

  // Save the set bound to the treestate
  savePluginBounds();
}
