/*
 ==============================================================================

 This file contains the basic framework code for a JUCE plugin editor.

 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LeikkausAudioProcessorEditor::LeikkausAudioProcessorEditor(LeikkausAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p), _gauge(juce::Colour(static_cast<juce::uint8>(255), 100, 255, 0.5f), 0.75f)
{
    uiConstructor();
}

LeikkausAudioProcessorEditor::~LeikkausAudioProcessorEditor()
{
    // Release the component lookAndFeel
    // TODO: Just inherit Slider and do this there
    for (auto &sliderComponent : audioProcessor._parameters.getSliderComponents())
    {
        sliderComponent->getSlider().setLookAndFeel(nullptr);
    }
}
