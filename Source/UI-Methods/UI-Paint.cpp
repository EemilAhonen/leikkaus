/*
  ==============================================================================

    UI-Paint.cpp
    Created: 23 Jan 2024 8:54:08pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginEditor.h"

//==============================================================================

void LeikkausAudioProcessorEditor::paint(juce::Graphics &g)
{
  // Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll(juce::Colours::black);

  // Load and set background image if available
  juce::Image backgroundImage = juce::ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);

  if (!backgroundImage.isNull())
  {
    g.drawImage(backgroundImage, getLocalBounds().toFloat());
  }

  // NOTE: Temporary UI code
  juce::Image linesImage = juce::ImageCache::getFromMemory(BinaryData::Lines_png, BinaryData::Lines_pngSize);
  if (!linesImage.isNull())
  {
    g.drawImage(linesImage, getLocalBounds().toFloat());
  }

  juce::Image menuImage = juce::ImageCache::getFromMemory(BinaryData::Menu_Overlay_png, BinaryData::Menu_Overlay_pngSize);
  if (!menuImage.isNull())
  {
    g.drawImage(menuImage, getLocalBounds().toFloat());
  }
}
