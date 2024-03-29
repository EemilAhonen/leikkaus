/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Keisari-Modules/LookAndFeel/ImageToggle/ImageToggle.h"

//==============================================================================

class LeikkausAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
  LeikkausAudioProcessorEditor(LeikkausAudioProcessor &);
  ~LeikkausAudioProcessorEditor() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  LeikkausAudioProcessor &audioProcessor;

  //== UI Methods ================================================================
  void uiConstructor();
  void paint(juce::Graphics &) override;
  void resized() override;
  void savePluginBounds();

  void createUIComponent(std::unique_ptr<UIComponent> &uiComponent);
  void createSlider(SliderComponent &sliderComponent);
  void createToggleButton(ToggleButtonComponent &toggleButtonComponent);
  void setupToggleLookAndFeel(ImageToggle &imageToggle, int lookAndFeelID);
  void handleRightClick(juce::String parameterID);

  //== Window Size ===============================================================
  const int INIT_WIDTH = 750;
  const int INIT_HEIGHT = 500;

  const int MIN_WIDTH = 500;
  const int MIN_HEIGHT = 333;

  const int MAX_HEIGHT = 2000;
  const int MAX_WIDTH = 3000;

  //== Widgets ===================================================================
  juce::SharedResourcePointer<juce::TooltipWindow> tooltipWindow;
  juce::ImageComponent _menuImageComponent;
  juce::ImageComponent _overlayImageComponent;

  //== Slider Attachments ========================================================
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> _sliderAttachments;
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>> _toggleButtonAttachments;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeikkausAudioProcessorEditor)
};
