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
  if (auto sliderComponent = dynamic_cast<SliderComponent *>(uiComponent.get()))
  {
    createSlider(*sliderComponent);
  }
  else if (auto toggleButtonComponent = dynamic_cast<ToggleButtonComponent *>(uiComponent.get()))
  {
    createToggleButton(*toggleButtonComponent);
  }
}