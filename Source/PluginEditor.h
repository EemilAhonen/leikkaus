/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Keisari-Modules/UI-Components/SliderComponent.h"
#include "Keisari-Modules/LookAndFeel/FillKnob.h"

//==============================================================================

class LeikkausAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
  LeikkausAudioProcessorEditor(LeikkausAudioProcessor &);
  ~LeikkausAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  LeikkausAudioProcessor &audioProcessor;

  //== UI Functions ==============================================================
  void uiConstructor();
  void uiPaint(juce::Graphics &g);
  void uiResized();

  void createSlider(std::unique_ptr<SliderComponent> &sliderComponent);

  //== Window Size ===============================================================

  const int INIT_WIDTH = 750;
  const int INIT_HEIGHT = 375;

  const int MIN_WIDTH = 500;
  const int MIN_HEIGHT = 250;

  const int MAX_HEIGHT = 1500;
  const int MAX_WIDTH = 3000;

  void savePluginBounds();

  //== Widgets ===================================================================
  FillKnob _fillKnob;

  //== Slider Attachments ========================================================
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> _sliderAttachments;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeikkausAudioProcessorEditor)
};
