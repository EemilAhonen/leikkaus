/*
  ==============================================================================

    UI-Constructor.cpp
    Created: 23 Jan 2024 8:53:51pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginEditor.h"

//==============================================================================

void LeikkausAudioProcessorEditor::uiConstructor()
{
  // Set font for this editor
  juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(juce::Typeface::createSystemTypefaceFor(BinaryData::RobotoRegular_ttf, BinaryData::RobotoRegular_ttfSize));

  // Create waveform visualizer
  addAndMakeVisible(audioProcessor._waveformVisualizer);
  // Set waveform and clipped area colours
  audioProcessor._waveformVisualizer.setColours(juce::Colour(80, 90, 100), juce::Colours::red);

  // Create overlay image component
  juce::Image overlayImage = juce::ImageCache::getFromMemory(BinaryData::Lines_png, BinaryData::Lines_pngSize);
  if (!overlayImage.isNull())
  {
    addAndMakeVisible(_overlayImageComponent);
    _overlayImageComponent.setImage(overlayImage);
  }

  // Create ceiling visualizer
  addAndMakeVisible(audioProcessor._ceilingVisualizer);

  // Create menu image component
  juce::Image menuImage = juce::ImageCache::getFromMemory(BinaryData::Menu_png, BinaryData::Menu_pngSize);
  if (!menuImage.isNull())
  {
    addAndMakeVisible(_menuImageComponent);
    _menuImageComponent.setImage(menuImage);
  }

  // Create uiComponents
  for (auto &uiComponent : audioProcessor._parameters.getUIComponents())
  {
    createUIComponent(uiComponent);
  }

  // Set editor size
  setSize(audioProcessor._width == 0.0 ? INIT_WIDTH : audioProcessor._width, audioProcessor._height);

  // Set resizable and constraints
  setResizable(true, true);
  getConstrainer()->setFixedAspectRatio(1.5);
  setResizeLimits(MIN_WIDTH, MIN_HEIGHT, MAX_WIDTH, MAX_HEIGHT);
}

void LeikkausAudioProcessorEditor::createUIComponent(std::unique_ptr<UIComponent> &uiComponent)
{
  // Check the type of received UIComponent and create it accordingly
  if (auto sliderComponent = dynamic_cast<SliderComponent *>(uiComponent.get()))
  {
    createSlider(*sliderComponent);
  }
  else if (auto toggleButtonComponent = dynamic_cast<ToggleButtonComponent *>(uiComponent.get()))
  {
    createToggleButton(*toggleButtonComponent);
  }
}
