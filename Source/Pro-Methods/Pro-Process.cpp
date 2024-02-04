/*
  ==============================================================================

    Pro-Process.cpp
    Created: 27 Jan 2024 8:07:32pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"
#include "../Keisari-Modules/Helper-Functions/HelperFunctions.h"

//==============================================================================

/**
 * Clips the input sample with a smooth transition (knee) around the specified ceiling.
 *
 * @param sample The input sample to be clipped.
 * @param ceiling The threshold for positive and negative clipping.
 * @param knee The factor determining the smoothness of the transition.
 * @return The clipped value with a smooth transition.
 */
float clipWithKnee(const float sample, const float ceiling, const float knee)
{
  if (sample > ceiling)
  {
    // Clip above the threshold with 'knee' for a gradual transition.
    return ceiling + (sample - ceiling) * knee;
  }
  else if (sample < -ceiling)
  {
    // Clip below the threshold with 'knee' for a gradual transition.
    return -(ceiling + (-sample - ceiling) * knee);
  }
  // No clipping needed
  return sample;
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
  juce::dsp::AudioBlock<float> upSampledBlock;

  // Determine if oversampling is enabled
  const bool oversamplingEnabled = _oversamplingValue;

  // Reference for processingBlock initialized to the original block
  juce::dsp::AudioBlock<float> &processingBlock = (oversamplingEnabled) ? upSampledBlock : block;

  // Apply oversampling processing if enabled
  if (oversamplingEnabled)
  {
    // Process samples up using oversampling module
    upSampledBlock = _oversamplingModule.processSamplesUp(block);
  }

  // Process block
  for (int channel = 0; channel < processingBlock.getNumChannels(); ++channel)
  {
    auto *channelData = processingBlock.getChannelPointer(channel);

    for (int sample = 0; sample < processingBlock.getNumSamples(); ++sample)
    {
      // Get original sample
      const float originalSample = channelData[sample];

      // Add input gain
      float processedSample = originalSample * _inputValue.getNextValue();

      // Add clipping with knee
      processedSample = clipWithKnee(processedSample, _ceilingValue.getNextValue(), _kneeValue.getNextValue());

      // Add input compensation
      if (_compensationValue)
      {
        processedSample /= _inputValue.getNextValue();
      }

      // Add output gain
      processedSample *= _outputValue.getNextValue();

      // Add delta
      if (_deltaValue)
      {
        processedSample += originalSample * -1.0f;
      }

      // Add mix
      float mixFactor = _mixValue.getNextValue();
      processedSample = (1.0f - mixFactor) * originalSample + mixFactor * processedSample;

      // Update channel data with the processed sample
      channelData[sample] = processedSample;
    }
  }

  // Restore original sampling rate if oversampling is enabled
  if (oversamplingEnabled)
  {
    _oversamplingModule.processSamplesDown(block);
  }
}
