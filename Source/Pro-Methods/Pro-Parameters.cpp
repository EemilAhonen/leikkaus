/*
  ==============================================================================

    Pro-Parameters.cpp
    Created: 27 Jan 2024 8:01:08pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"
#include "../Globals/Globals.h"
#include "../Keisari-Modules/Helper-Functions/HelperFunctions.h"

//==============================================================================

void LeikkausAudioProcessor::addParameterListeners()
{
    // TODO: Invent better way to do this
    _treeState.addParameterListener(inputID, this);
    _treeState.addParameterListener(outputID, this);
    _treeState.addParameterListener(ceilingID, this);
    _treeState.addParameterListener(kneeID, this);
    _treeState.addParameterListener(mixID, this);
    _treeState.addParameterListener(compensationID, this);
    _treeState.addParameterListener(oversamplingID, this);
    _treeState.addParameterListener(deltaID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout LeikkausAudioProcessor::createParameterLayout()
{
    return {_parameters.getAudioParameters().begin(), _parameters.getAudioParameters().end()};
}

void LeikkausAudioProcessor::parameterChanged(const juce::String &parameterId, float newValue)
{
    // There has to be a better way to do this
    if (parameterId == inputID)
    {
        // Set input target value (smoothed)
        _inputValue.setTargetValue(*_treeState.getRawParameterValue(inputID));
    }
    else if (parameterId == outputID)
    {
        // Set output target value (smoothed)
        _outputValue.setTargetValue(*_treeState.getRawParameterValue(outputID));
    }
    else if (parameterId == ceilingID)
    {
        // Set ceiling target value (smoothed)
        _ceilingValue.setTargetValue(*_treeState.getRawParameterValue(ceilingID));
    }
    else if (parameterId == kneeID)
    {
        // Set knee target value (smoothed)
        _kneeValue.setTargetValue(*_treeState.getRawParameterValue(kneeID));
    }
    else if (parameterId == mixID)
    {
        // Set mix target value (smoothed)
        _mixValue.setTargetValue(*_treeState.getRawParameterValue(mixID));
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
        // Set input target value (smoothed)
        _inputValue.setTargetValue(*_treeState.getRawParameterValue(inputID));

        // Set output target value (smoothed)
        _outputValue.setTargetValue(*_treeState.getRawParameterValue(outputID));

        // Set ceiling target value (smoothed)
        _ceilingValue.setTargetValue(*_treeState.getRawParameterValue(ceilingID));

        // Set knee target value (smoothed)
        _kneeValue.setTargetValue(*_treeState.getRawParameterValue(kneeID));

        // Set mix target value (smoothed)
        _mixValue.setTargetValue(*_treeState.getRawParameterValue(mixID));

        // Set compensation target value
        _compensationValue = *_treeState.getRawParameterValue(compensationID);

        // Set oversampling target value
        _oversamplingValue = *_treeState.getRawParameterValue(oversamplingID);

        // Set delta target value
        _deltaValue = *_treeState.getRawParameterValue(deltaID);
    }
}
