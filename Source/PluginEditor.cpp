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
}
