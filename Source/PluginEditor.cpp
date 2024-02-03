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
    // for (auto& sliderComponent : audioProcessor._parameters.getSliderComponents())
    //{
    //    sliderComponent->getSlider().setLookAndFeel(nullptr);
    //}
}

//==============================================================================
void LeikkausAudioProcessorEditor::paint(juce::Graphics &g)
{
    uiPaint(g);
}

void LeikkausAudioProcessorEditor::resized()
{
    uiResized();
}

void LeikkausAudioProcessorEditor::savePluginBounds()
{
    const int newWidth = getWidth();
    const int newHeight = getHeight();

    audioProcessor._valueTree.setProperty("width", newWidth, nullptr);
    audioProcessor._valueTree.setProperty("height", newHeight, nullptr);

    audioProcessor._width = newWidth;
    audioProcessor._height = newHeight;
}
