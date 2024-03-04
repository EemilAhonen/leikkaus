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
  _treeState.addParameterListener(ratioID, this);
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
  // TODO: REDO THIS
  // Update all parameter values

  // Set the target value for the input.
  _inputValue = *_treeState.getRawParameterValue(inputID);
  // Set the target value for the output.
  _outputValue = *_treeState.getRawParameterValue(outputID);

  // Set the target value for the ceiling with smoothing, using the decibels-to-gain conversion
  // on the raw parameter value retrieved from the AudioProcessorValueTreeState.
  float ceilingRawValue = *_treeState.getRawParameterValue(ceilingID);
  _ceilingValue.setTargetValue(juce::Decibels::decibelsToGain(ceilingRawValue));
  _ceilingVisualizer.setCeiling(ceilingRawValue);
  _waveformVisualizer.setCeiling(ceilingRawValue);

  // Set the target value for the ratio with smoothing,
  // scaling the raw parameter value (0-100) to the range 0-1.
  float ratioRawValue = *_treeState.getRawParameterValue(ratioID) / 100.0f;
  _ratioValue.setTargetValue(ratioRawValue);
  _ceilingVisualizer.setRatio(ratioRawValue);

  // Set the target value for the mix with smoothing,
  // scaling the raw parameter value (0-100) to the range 0-1.
  _mixValue = *_treeState.getRawParameterValue(mixID) / 100.0f;

  // Set compensation target value
  _compensationValue = *_treeState.getRawParameterValue(compensationID);

  // Set oversampling target value
  _oversamplingValue = *_treeState.getRawParameterValue(oversamplingID);

  // Set delta target value
  _deltaValue = *_treeState.getRawParameterValue(deltaID);
}
