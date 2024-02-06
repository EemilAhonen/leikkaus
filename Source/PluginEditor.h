/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Keisari-Modules/UI-Components/SliderComponent.h"
#include "Keisari-Modules/LookAndFeel/Gauge.h"

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

  void createSlider(std::unique_ptr<SliderComponent> &sliderComponent);

  //== Window Size ===============================================================
  const int INIT_WIDTH = 750;
  const int INIT_HEIGHT = 500;

  const int MIN_WIDTH = 500;
  const int MIN_HEIGHT = 333;

  const int MAX_HEIGHT = 2000;
  const int MAX_WIDTH = 3000;

  //== Widgets ===================================================================
  juce::SharedResourcePointer<juce::TooltipWindow> tooltipWindow;
  Gauge _gauge;
  //== Slider Attachments ========================================================
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> _sliderAttachments;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeikkausAudioProcessorEditor)
};
