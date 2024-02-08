/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Globals/Parameters.h"
#include "Keisari-Modules/LookAndFeel/CeilingVisualiser/CeilingVisualiser.h"

//==============================================================================

class LeikkausAudioProcessor : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    LeikkausAudioProcessor();
    ~LeikkausAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

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

    // Parameters object for managing plugin parameters
    Parameters _parameters;

    // State manager for plugin parameter tree
    juce::AudioProcessorValueTreeState _treeState;

    // ValueTree to store additional variables, such as width and height
    juce::ValueTree _valueTree{"Variables", {}, {{"Group", {{"name", "variables"}}, {
                                                                                        {"Parameter", {{"id", "width"}, {"value", 0.0}}},
                                                                                        {"Parameter", {{"id", "width"}, {"value", 0.0}}},
                                                                                    }

                                                }}};

    // Additional variables for width and height
    float _width = 0.0f;
    float _height = 0.0f;

    //== Processing ================================================================
    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
    void clearUnusedOutputChannels(juce::AudioBuffer<float> &buffer);

    //== Visualizers ===============================================================
    CeilingVisualiser _ceilingVisualiser;

private:
    //== Parameters ================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void parameterChanged(const juce::String &parameterID, float newValue) override;
    void addParameterListeners();

    //== Modules ===================================================================
    juce::dsp::Oversampling<float> _oversamplingModule{2, 2, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR};

    //== Parameters ================================================================
    // User sample rate
    float _lastSampleRate;

    // Setting the smoothing parameter for ramping value transitions in audio processing
    const double _smoothingParameter = 0.2;

    // Values for user modifiable parameters
    juce::SmoothedValue<float> _inputValue;   //-24db to 24db normalized to gain
    juce::SmoothedValue<float> _outputValue;  //-24db to 24db normalized to gain
    juce::SmoothedValue<float> _ceilingValue; // 0 to -24d normalized to gain
    juce::SmoothedValue<float> _kneeValue;    // 0 to 100% normalized to 0 to 1
    juce::SmoothedValue<float> _mixValue;     // 0 to 100% normalized to 0 to 1
    bool _compensationValue = false;
    bool _oversamplingValue = false;
    bool _deltaValue = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeikkausAudioProcessor)
};
