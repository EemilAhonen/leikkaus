/*
  ==============================================================================

    Pro-Parameters.cpp
    Created: 27 Jan 2024 8:01:08pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"
#include "../Globals/Globals.h"

//==============================================================================

/**
 * @brief Adds parameter listeners to the AudioProcessorValueTreeState.
 *
 * This function adds parameter listeners for the parameters in the AudioProcessorValueTreeState.
 * Note: Consider refactoring to a more efficient approach.
 */
void LeikkausAudioProcessor::addParameterListeners()
{
    _treeState.addParameterListener(inputID, this);
    _treeState.addParameterListener(outputID, this);
    _treeState.addParameterListener(ceilingID, this);
    _treeState.addParameterListener(kneeID, this);
    _treeState.addParameterListener(mixID, this);
    _treeState.addParameterListener(compensationID, this);
    _treeState.addParameterListener(oversamplingID, this);
    _treeState.addParameterListener(deltaID, this);
}

/**
 * @brief Creates the parameter layout for the AudioProcessorValueTreeState.
 *
 * This function constructs the parameter layout for the AudioProcessorValueTreeState by
 * retrieving the audio parameters from the Parameters object associated with the processor.
 *
 * @return A ParameterLayout containing the audio parameters for the ValueTreeState.
 */
juce::AudioProcessorValueTreeState::ParameterLayout LeikkausAudioProcessor::createParameterLayout()
{
    // Retrieve the audio parameters from the Parameters object and create the parameter layout
    return {_parameters.getAudioParameters().begin(), _parameters.getAudioParameters().end()};
}

/**
 * @brief Handles changes to audio processor parameters.
 *
 * This function is called when a parameter in the AudioProcessorValueTreeState is modified.
 * It updates the target values for relevant parameters, providing smoothing and scaling where necessary.
 *
 * @param parameterId The ID of the parameter that has changed.
 * @param newValue The new value of the changed parameter.
 */
void LeikkausAudioProcessor::parameterChanged(const juce::String &parameterId, float newValue)
{
    // Do as many parameter calculations as possible here, doing them in the process block is not a good idea
    // TODO: There has to be a better way to do this, right?
    // Unordered map or hashcode switch-cases are more CPU expensive than this.
    if (parameterId == inputID)
    {
        // Set the target value for the input with smoothing, using the decibels-to-gain conversion
        // on the raw parameter value retrieved from the AudioProcessorValueTreeState.
        _inputValue.setTargetValue(juce::Decibels::decibelsToGain(static_cast<float>(*_treeState.getRawParameterValue(inputID))));
    }
    else if (parameterId == outputID)
    {
        // Set the target value for the output with smoothing, using the decibels-to-gain conversion
        // on the raw parameter value retrieved from the AudioProcessorValueTreeState.
        _outputValue.setTargetValue(juce::Decibels::decibelsToGain(static_cast<float>(*_treeState.getRawParameterValue(outputID))));
    }
    else if (parameterId == ceilingID)
    {
        // Set the target value for the ceiling with smoothing, using the decibels-to-gain conversion
        // on the raw parameter value retrieved from the AudioProcessorValueTreeState.
        _ceilingValue.setTargetValue(juce::Decibels::decibelsToGain(static_cast<float>(*_treeState.getRawParameterValue(ceilingID))));
    }
    else if (parameterId == kneeID)
    {
        // Set the target value for the knee with smoothing,
        // scaling the raw parameter value (0-100) to the range 0-1.
        _kneeValue.setTargetValue(*_treeState.getRawParameterValue(kneeID) / 100.0f);
    }
    else if (parameterId == mixID)
    {
        // Set the target value for the mix with smoothing,
        // scaling the raw parameter value (0-100) to the range 0-1.
        _mixValue.setTargetValue(*_treeState.getRawParameterValue(mixID) / 100.0f);
    }
    else if (parameterId == compensationID)
    {
        // Set compensation target value
        _compensationValue = *_treeState.getRawParameterValue(compensationID);
    }
    else if (parameterId == oversamplingID)
    {
        // Set oversampling target value
        _oversamplingValue = *_treeState.getRawParameterValue(oversamplingID);
    }
    else if (parameterId == deltaID)
    {
        // Set delta target value
        _deltaValue = *_treeState.getRawParameterValue(deltaID);
    }
    else
    {
        // Update all parameter values
        _inputValue.setTargetValue(juce::Decibels::decibelsToGain(static_cast<float>(*_treeState.getRawParameterValue(inputID))));
        _outputValue.setTargetValue(juce::Decibels::decibelsToGain(static_cast<float>(*_treeState.getRawParameterValue(outputID))));
        _ceilingValue.setTargetValue(juce::Decibels::decibelsToGain(static_cast<float>(*_treeState.getRawParameterValue(ceilingID))));
        _kneeValue.setTargetValue(*_treeState.getRawParameterValue(kneeID) / 100.0f);
        _mixValue.setTargetValue(*_treeState.getRawParameterValue(mixID) / 100.0f);
        _compensationValue = *_treeState.getRawParameterValue(compensationID);
        _oversamplingValue = *_treeState.getRawParameterValue(oversamplingID);
        _deltaValue = *_treeState.getRawParameterValue(deltaID);
    }
}
