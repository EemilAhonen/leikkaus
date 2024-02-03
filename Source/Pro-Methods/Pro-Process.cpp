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

float hardClipWithKnee(float sample, float ceiling, float knee)
{
  float clippedValue;
  if (sample > ceiling)
  {
    // Apply knee for a smooth transition
    float excess = sample - ceiling;
    clippedValue = ceiling + (excess * (knee / 100));
  }
  else if (sample < -ceiling)
  {
    // Apply knee for a smooth transition
    float excess = -sample - ceiling;
    clippedValue = -(ceiling + (excess * (knee / 100)));
  }
  else
  {
    clippedValue = sample;
  }
  return clippedValue;
}

void LeikkausAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
  // Clear any output channels that didn't contain input data
  clearUnusedOutputChannels(buffer);

  // Initialize an AudioBlock using the audio buffer
  juce::dsp::AudioBlock<float> block{buffer};

  // Process clipping
  for (int channel = 0; channel < block.getNumChannels(); ++channel)
  {
    auto *channelData = block.getChannelPointer(channel);

    for (int sample = 0; sample < block.getNumSamples(); ++sample)
    {
      float originalSample = channelData[sample];
      float processedSample = originalSample;

      // Add input gain
      processedSample *= juce::Decibels::decibelsToGain(_inputValue.getNextValue());

      // Add clipping
      float ceilingGain = juce::Decibels::decibelsToGain(_ceilingValue.getNextValue());
      processedSample = hardClipWithKnee(processedSample, ceilingGain, _kneeValue.getNextValue());

      // Add input compensation
      if (_compensationValue)
      {
        processedSample *= juce::Decibels::decibelsToGain(_inputValue.getNextValue() * -1);
      }

      // Add output gain
      processedSample *= juce::Decibels::decibelsToGain(_outputValue.getNextValue());

      // Add delta
      if (_deltaValue)
      {
        processedSample += originalSample * -1;
      }

      // Add mix
      float mixFactor = _mixValue.getNextValue() / 100.0f;
      processedSample = (1.0f - mixFactor) * originalSample + mixFactor * processedSample;

      // Update channel data
      channelData[sample] = processedSample;
    }
  }
}
