/*
  ==============================================================================

    UI-Constructor.cpp
    Created: 23 Jan 2024 8:53:51pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginEditor.h"

//==============================================================================

void LeikkausAudioProcessorEditor::createSlider(std::unique_ptr<SliderComponent> &sliderComponent)
{
  juce::Slider &slider = sliderComponent->getSlider();

  addAndMakeVisible(slider);
  slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 400, 40);
  slider.setDoubleClickReturnValue(true, sliderComponent->_initValue);
  slider.setRange(sliderComponent->_minValue, sliderComponent->_maxValue, sliderComponent->_interval);
  slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
  slider.setTooltip(sliderComponent->_toolTip);
  slider.setLookAndFeel(&_gauge);

  // Add slider attachment
  _sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, sliderComponent->_id, slider));
}

void LeikkausAudioProcessorEditor::uiConstructor()
{
  // Set font for this editor
  juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(juce::Typeface::createSystemTypefaceFor(BinaryData::RobotoRegular_ttf, BinaryData::RobotoRegular_ttfSize));

  juce::Image arrowImage = juce::ImageCache::getFromMemory(BinaryData::Gauge_Arrows_png, BinaryData::Gauge_Arrows_pngSize);
  _gauge.setArrowImage(arrowImage);

  // Create sliders
  for (auto &sliderComponent : audioProcessor._parameters.getSliderComponents())
  {
    createSlider(sliderComponent);
  }

  // Set editor size
  setSize(audioProcessor._width == 0.0 ? INIT_WIDTH : audioProcessor._width, audioProcessor._height);

  // Set resizable and constraints
  setResizable(true, true);
  getConstrainer()->setFixedAspectRatio(1.5);
  setResizeLimits(MIN_WIDTH, MIN_HEIGHT, MAX_WIDTH, MAX_HEIGHT);
}
