/*
 ==============================================================================

 This file contains the basic framework code for a JUCE plugin processor.

 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

LeikkausAudioProcessor::LeikkausAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
      _treeState(*this, nullptr, "PARAMETERS", createParameterLayout()),
      _waveformVisualizer(2)
#endif
{
    _waveformVisualizer.setRepaintRate(30);
    _waveformVisualizer.setBufferSize(512);
    addParameterListeners();
}

LeikkausAudioProcessor::~LeikkausAudioProcessor()
{
    addParameterListeners();
}

//==============================================================================

const juce::String LeikkausAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LeikkausAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool LeikkausAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool LeikkausAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double LeikkausAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LeikkausAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int LeikkausAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LeikkausAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String LeikkausAudioProcessor::getProgramName(int index)
{
    return {};
}

void LeikkausAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
}

//==============================================================================

void LeikkausAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LeikkausAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

//==============================================================================
bool LeikkausAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *LeikkausAudioProcessor::createEditor()
{
    return new LeikkausAudioProcessorEditor(*this);
    // Generic UI for debugging
    // return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new LeikkausAudioProcessor();
}
