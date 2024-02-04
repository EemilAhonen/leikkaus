/*
  ==============================================================================

    Pro-Prepare.cpp
    Created: 27 Jan 2024 8:07:40pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"

//==============================================================================

/**
 * @brief Called before playback starts to allow the processor to prepare itself.
 *
 * The sample rate is the target sample rate, and it remains constant until playback stops.
 *
 * Use getTotalNumInputChannels and getTotalNumOutputChannels or query the busLayout member variable
 * to determine the number of channels your processBlock callback must process.
 *
 * The maximumExpectedSamplesPerBlock value is a strong hint about the maximum number of samples
 * that will be provided in each block. It can be used to resize internal buffers. Program defensively
 * in case a buggy host exceeds this value, as the actual block sizes can vary between callback calls.
 *
 * @param sampleRate The target sample rate for the audio stream.
 * @param maximumExpectedSamplesPerBlock A hint about the maximum number of samples per block.
 */
void LeikkausAudioProcessor::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
  // Store the sample rate for later use
  _lastSampleRate = sampleRate;

  // Reset and set the ramp duration for transitioning audio processing parameters
  _inputValue.reset(_lastSampleRate, _smoothingParameter);
  _outputValue.reset(_lastSampleRate, _smoothingParameter);
  _ceilingValue.reset(_lastSampleRate, _smoothingParameter);
  _kneeValue.reset(_lastSampleRate, _smoothingParameter);
  _mixValue.reset(_lastSampleRate, _smoothingParameter);

  // Reset and initialize oversampling module processing with the given samples per block
  _oversamplingModule.reset();
  _oversamplingModule.initProcessing(maximumExpectedSamplesPerBlock);

  // Update all parameter values
  parameterChanged(juce::String(), 0.0f);
}
