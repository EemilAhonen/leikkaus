/*
  ==============================================================================

    Pro-Process.cpp
    Created: 27 Jan 2024 8:07:32pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"
#include "../Keisari-Modules/DSP/Distortion.h"

//==============================================================================

/**
 * Clears any unused output channels in the given audio buffer.
 *
 * This method is used to ensure that any output channels beyond the last used input
 * channel are set to zero, preventing potential artifacts from unused channels.
 *
 * @param buffer The audio buffer to clear unused output channels.
 */
void LeikkausAudioProcessor::clearUnusedOutputChannels(juce::AudioBuffer<float> &buffer)
{
  // Get the total number of input and output channels
  int totalNumInputChannels = getTotalNumInputChannels();
  int totalNumOutputChannels = getTotalNumOutputChannels();

  // Clear any unused output channels
  for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());
}

/**
 * @brief Processes the next audio block.
 *
 * This method is called by JUCE to process the next block of audio samples.
 * The buffer parameter contains input data and should be replaced with the processor's output data.
 * It's crucial to handle variable-sized blocks and MIDI messages properly to avoid artifacts or crashes.
 *
 * @param buffer The audio buffer containing input and output samples.
 * @param midiMessages A buffer containing incoming MIDI messages for this block.
 *
 * @note Ensure careful handling of bypass parameters and avoid UI interactions within this callback,
 * as it runs on the audio thread.
 */
void LeikkausAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
  // Clear any output channels that didn't contain input data
  clearUnusedOutputChannels(buffer);

  // Initialize an AudioBlock using the audio buffer
  juce::dsp::AudioBlock<float> block{buffer};

  // Declare an empty AudioBlock for potential oversampled processing
  juce::dsp::AudioBlock<float> upSampledBlock;

  // Determine if oversampling is enabled
  const bool oversamplingEnabled = _oversamplingValue;

  // Reference for processingBlock initialized to the original block by default
  // If oversampling is enabled, processingBlock references upSampledBlock
  juce::dsp::AudioBlock<float> &processingBlock = (oversamplingEnabled) ? upSampledBlock : block;

  // Apply oversampling processing if enabled
  if (oversamplingEnabled)
  {
    // Process samples up using oversampling module
    upSampledBlock = _oversamplingModule.processSamplesUp(block);
  }

  // Process each channel in the audio block
  for (int channel = 0; channel < processingBlock.getNumChannels(); ++channel)
  {
    // Obtain a pointer to the audio data for the current channel
    auto *channelData = processingBlock.getChannelPointer(channel);

    // Iterate through each sample in the current channel
    for (int sample = 0; sample < processingBlock.getNumSamples(); ++sample)
    {
      // Get original sample
      const float originalSample = channelData[sample];

      // Add input gain
      float processedSample = originalSample * _inputValue.getNextValue();

      // Add clipping with knee
      processedSample = clipWithKnee(processedSample, _ceilingValue.getNextValue(), _kneeValue.getNextValue());

      // Apply input compensation if enabled
      // If _compensationValue is true, invert the effect of the input gain on the processed sample
      if (_compensationValue)
      {
        processedSample /= _inputValue.getNextValue();
      }

      // Add output gain
      processedSample *= _outputValue.getNextValue();

      // Apply delta if enabled
      // If _deltaValue is true, add the negation of the original signal to the processed sample
      // This effectively outputs the difference between the new and original signal
      if (_deltaValue)
      {
        processedSample += originalSample * -1.0f;
      }

      // Apply mixing with the original signal based on the mix factor
      // The mix factor _mixValue controls the blending between the original and the processed sample
      float mixFactor = _mixValue.getNextValue();
      processedSample = (1.0f - mixFactor) * originalSample + mixFactor * processedSample;

      // Replace the channel data with the processed sample
      channelData[sample] = processedSample;
    }
  }

  // Restore original sampling rate if oversampling is enabled
  if (oversamplingEnabled)
  {
    _oversamplingModule.processSamplesDown(block);
  }
}
