/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2022 - Raw Material Software Limited

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 7 End-User License
   Agreement and JUCE Privacy Policy.

   End User License Agreement: www.juce.com/juce-7-licence
   Privacy Policy: www.juce.com/juce-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#include <JuceHeader.h>

class WaveformVisualizer : public juce::Component,
                           private juce::Timer
{
public:
    /** Creates a visualiser with the given number of channels. */
    WaveformVisualizer(int initialNumChannels);

    /** Destructor. */
    ~WaveformVisualizer() override;

    /** Changes the number of channels that the visualiser stores. */
    void setNumChannels(int numChannels);

    /** Changes the number of samples that the visualiser keeps in its history.
        Note that this value refers to the number of averaged sample blocks, and each
        block is calculated as the peak of a number of incoming audio samples. To set
        the number of incoming samples per block, use setSamplesPerBlock().
     */
    void setBufferSize(int bufferSize);

    /** */
    void setSamplesPerBlock(int newNumInputSamplesPerBlock) noexcept;

    /** */
    int getSamplesPerBlock() const noexcept { return inputSamplesPerBlock; }

    /** Clears the contents of the buffers. */
    void clear();

    /** Pushes a buffer of channels data.
        The number of channels provided here is expected to match the number of channels
        that this WaveformVisualizer has been told to use.
    */
    void pushBuffer(const juce::AudioBuffer<float> &bufferToPush);

    /** Pushes a buffer of channels data.
        The number of channels provided here is expected to match the number of channels
        that this WaveformVisualizer has been told to use.
    */
    void pushBuffer(const juce::AudioSourceChannelInfo &bufferToPush);

    /** Pushes a buffer of channels data.
        The number of channels provided here is expected to match the number of channels
        that this WaveformVisualizer has been told to use.
    */
    void pushBuffer(const float *const *channelData, int numChannels, int numSamples);

    /** Pushes a single sample (per channel).
        The number of channels provided here is expected to match the number of channels
        that this WaveformVisualizer has been told to use.
    */
    void pushSample(const float *samplesForEachChannel, int numChannels);

    /** Sets the colours used to paint the */
    void setColours(juce::Colour waveformColour, juce::Colour clippedColour) noexcept;

    /** Sets the frequency at which the component repaints itself. */
    void setRepaintRate(int frequencyInHz);

    /** Draws a channel of audio data in the given bounds.
        The default implementation just calls getChannelAsPath() and fits this into the given
        area. You may want to override this to draw things differently.
    */
    virtual void paintChannel(juce::Graphics &, juce::Rectangle<float> bounds,
                              const juce::Range<float> *levels, int numLevels, int nextSample);

    /** Creates a path which contains the waveform shape of a given set of range data.
        The path is normalised so that -1 and +1 are its upper and lower bounds, and it
        goes from 0 to numLevels on the X axis.
    */
    void getChannelAsPath(juce::Path &result, const juce::Range<float> *levels, int numLevels, int nextSample);

    void setCeiling(float ceiling)
    {
        _ceiling = ceiling;
    }

protected:
    void paint(juce::Graphics &) override;

private:
    float _ceiling = 1.0f;
    juce::Colour _waveformColour, _clippedColour;

    struct ChannelInfo;
    juce::OwnedArray<ChannelInfo> channels;
    int numSamples, inputSamplesPerBlock;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformVisualizer)
};