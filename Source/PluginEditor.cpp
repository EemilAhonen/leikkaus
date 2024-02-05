/*
 ==============================================================================

 This file contains the basic framework code for a JUCE plugin editor.

 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LeikkausAudioProcessorEditor::LeikkausAudioProcessorEditor(LeikkausAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
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
