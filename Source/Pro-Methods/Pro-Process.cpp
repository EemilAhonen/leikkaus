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

  // Add dry block to dry-wet mixer
  _dryWetMixerModule.pushDrySamples(block);

  // Add input volume to block
  _inputModule.setGainDecibels(_inputValue);
  _inputModule.process(juce::dsp::ProcessContextReplacing<float>(block));

  // Add buffer to the waveform visualizer component
  _waveformVisualizer.pushBuffer(buffer);

  // Process clipping with oversampling if enabled
  if (_oversamplingValue)
  {
    // Upsample block using oversampling module
    juce::dsp::AudioBlock<float> upSampledBlock = _oversamplingModule.processSamplesUp(block);

    // Apply clipping processing to each sample
    processClipping(upSampledBlock);

    // Restore original sampling rate
    _oversamplingModule.processSamplesDown(block);
  }
  else
  {
    // Apply clipping processing to each sample
    processClipping(block);
  }

  // Add output volume to block
  // Apply input compensation if enabled
  if (_compensationValue)
  {
    // Invert the effect of the input gain on the processed sample
    _outputModule.setGainDecibels(_outputValue - _inputValue);
  }
  else
  {
    // Set the output gain in decibels based on the outputValue
    _outputModule.setGainDecibels(_outputValue);
  }
  _outputModule.process(juce::dsp::ProcessContextReplacing<float>(block));

  // Set the balance between dry-wet mix
  _dryWetMixerModule.setWetMixProportion(_mixValue);
  // Mix dry wet samples
  _dryWetMixerModule.mixWetSamples(block);
}

/**
 * @brief Process clipping for each sample in the given audio block.
 *
 * This function applies clipping with knee to each sample in each channel of the
 * provided audio block. Optionally, it adds the negation of the original signal
 * (delta) to the processed sample if enabled.
 *
 * @param block The audio block to process.
 */
void LeikkausAudioProcessor::processClipping(juce::dsp::AudioBlock<float> &block)
{
  // Process each channel in the audio block
  for (int channel = 0; channel < block.getNumChannels(); ++channel)
  {
    // Obtain a pointer to the audio data for the current channel
    auto *channelData = block.getChannelPointer(channel);

    // Iterate through each sample in the current channel
    for (int sample = 0; sample < block.getNumSamples(); ++sample)
    {
      // Get original sample
      const float originalSample = channelData[sample];

      // Add clipping with knee
      float processedSample = clipWithKnee(originalSample, _ceilingValue.getNextValue(), _kneeValue.getNextValue());

      // Apply delta if enabled
      // If _deltaValue is true, add the negation of the original signal to the processed sample
      // This effectively outputs the difference between the new and original signal
      if (_deltaValue)
      {
        processedSample += originalSample * -1.0f;
      }

      // Replace the channel data with the processed sample
      channelData[sample] = processedSample;
    }
  }
}