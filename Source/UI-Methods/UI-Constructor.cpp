/*
  ==============================================================================

    UI-Constructor.cpp
    Created: 23 Jan 2024 8:53:51pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginEditor.h"
#include "../Keisari-Modules/LookAndFeel/Gauge.h"

//==============================================================================

void LeikkausAudioProcessorEditor::createSlider(std::unique_ptr<SliderComponent> &sliderComponent)
{
  // Create and set Gauge slider
  sliderComponent->setSlider(std::make_unique<Gauge>());

  // Retrieve the Gauge slider
  auto slider = dynamic_cast<Gauge *>(sliderComponent->getSlider());
  if (slider != nullptr)
  {
    addAndMakeVisible(slider);
    slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 400, 40);
    slider->setDoubleClickReturnValue(true, sliderComponent->_initValue);
    slider->setRange(sliderComponent->_minValue, sliderComponent->_maxValue, sliderComponent->_interval);
    slider->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider->setTooltip(sliderComponent->_toolTip);

    slider->setFillColor(juce::Colour(static_cast<juce::uint8>(255), 100, 255, 0.5f));
    slider->setFontSize(0.75f);

    slider->setRightClickCallback([this, parameterID = sliderComponent->_id]()
                                  {
      // Get the AudioProcessorParameter using the provided parameterID
      auto parameter = audioProcessor._treeState.getParameter(parameterID);
      if (parameter != nullptr)
      {
        // Get the host context. This is null for everything else except VST3
        auto hostContext = getHostContext();
        if (hostContext != nullptr)
        {
          // Get the context menu for the parameter
          auto contextMenu = hostContext->getContextMenuForParameter(parameter);
          if (contextMenu != nullptr)
          {
            // Show the native menu at the specified position (10, 20)
            // TODO: Get the position from the mouse event
            contextMenu->showNativeMenu(juce::Point<int>(10, 20));
          }
        }
      } });

    // Add slider attachment
    _sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, sliderComponent->_id, *slider));
  }
  else
  {
    jassertfalse;
  }
}

void LeikkausAudioProcessorEditor::uiConstructor()
{
  // Set font for this editor
  juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(juce::Typeface::createSystemTypefaceFor(BinaryData::RobotoRegular_ttf, BinaryData::RobotoRegular_ttfSize));

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

  // getHostContext()->getContextMenuForParameter(audioProcessor._treeState.getParameter("input"));
}
