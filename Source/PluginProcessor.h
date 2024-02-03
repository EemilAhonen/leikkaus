/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Globals/Parameters.h"

//==============================================================================

class LeikkausAudioProcessor : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    LeikkausAudioProcessor();
    ~LeikkausAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    //== Parameters ================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    Parameters _parameters;
    juce::AudioProcessorValueTreeState _treeState;

    juce::ValueTree _valueTree{"Variables", {}, {{"Group", {{"name", "variables"}}, {
                                                                                        {"Parameter", {{"id", "width"}, {"value", 0.0}}},
                                                                                        {"Parameter", {{"id", "width"}, {"value", 0.0}}},
                                                                                    }

                                                }}};

    float _width = 0.0f;
    float _height = 0.0f;

    //== Processing ================================================================
    void clearUnusedOutputChannels(juce::AudioBuffer<float> &buffer);

private:
    //== Parameters =================================================================

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void parameterChanged(const juce::String &parameterID, float newValue) override;
    void addParameterListeners();

    //== Values ====================================================================
    // User sample rate
    float _lastSampleRate;

    // Setting the smoothing parameter for ramping value transitions in audio processing
    const double _smoothingParameter = 0.001;

    // Values for user modifiable parameters
    juce::SmoothedValue<float> _inputValue;   //-24db to 24db
    juce::SmoothedValue<float> _outputValue;  //-24db to 24db
    juce::SmoothedValue<float> _ceilingValue; // 0 to -24d
    juce::SmoothedValue<float> _kneeValue;    // 0 to 24db
    juce::SmoothedValue<float> _mixValue;     // 0 to 100%

    bool _compensationValue = false;
    bool _oversamplingValue = false;
    bool _deltaValue = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeikkausAudioProcessor)
};
