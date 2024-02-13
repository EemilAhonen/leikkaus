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

#include "WaveformVisualizer.h"

struct WaveformVisualizer::ChannelInfo
{
    ChannelInfo(WaveformVisualizer &o, int bufferSize) : owner(o)
    {
        setBufferSize(bufferSize);
        clear();
    }

    void clear() noexcept
    {
        levels.fill({});
        value = {};
        subSample = 0;
    }

    void pushSamples(const float *inputSamples, int num) noexcept
    {
        for (int i = 0; i < num; ++i)
            pushSample(inputSamples[i]);
    }

    void pushSample(float newSample) noexcept
    {
        if (--subSample <= 0)
        {
            if (++nextSample == levels.size())
                nextSample = 0;

            levels.getReference(nextSample) = value;
            subSample = owner.getSamplesPerBlock();
            value = juce::Range<float>(newSample, newSample);
        }
        else
        {
            value = value.getUnionWith(newSample);
        }
    }

    void setBufferSize(int newSize)
    {
        levels.removeRange(newSize, levels.size());
        levels.insertMultiple(-1, {}, newSize - levels.size());

        if (nextSample >= newSize)
            nextSample = 0;
    }

    WaveformVisualizer &owner;
    juce::Array<juce::Range<float>> levels;
    juce::Range<float> value;
    std::atomic<int> nextSample{0}, subSample{0};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChannelInfo)
};

//==============================================================================
WaveformVisualizer::WaveformVisualizer(int initialNumChannels)
    : numSamples(1024),
      inputSamplesPerBlock(256)
{
    setNumChannels(initialNumChannels);
    setRepaintRate(60);
}

WaveformVisualizer::~WaveformVisualizer()
{
}

void WaveformVisualizer::setNumChannels(int numChannels)
{
    channels.clear();

    for (int i = 0; i < numChannels; ++i)
        channels.add(new ChannelInfo(*this, numSamples));
}

void WaveformVisualizer::setBufferSize(int newNumSamples)
{
    numSamples = newNumSamples;

    for (auto *c : channels)
        c->setBufferSize(newNumSamples);
}

void WaveformVisualizer::clear()
{
    for (auto *c : channels)
        c->clear();
}

void WaveformVisualizer::pushBuffer(const float *const *d, int numChannels, int num)
{
    numChannels = juce::jmin(numChannels, channels.size());

    for (int i = 0; i < numChannels; ++i)
        channels.getUnchecked(i)->pushSamples(d[i], num);
}

void WaveformVisualizer::pushBuffer(const juce::AudioBuffer<float> &buffer)
{
    pushBuffer(buffer.getArrayOfReadPointers(),
               buffer.getNumChannels(),
               buffer.getNumSamples());
}

void WaveformVisualizer::pushBuffer(const juce::AudioSourceChannelInfo &buffer)
{
    auto numChannels = juce::jmin(buffer.buffer->getNumChannels(), channels.size());

    for (int i = 0; i < numChannels; ++i)
        channels.getUnchecked(i)->pushSamples(buffer.buffer->getReadPointer(i, buffer.startSample),
                                              buffer.numSamples);
}

void WaveformVisualizer::pushSample(const float *d, int numChannels)
{
    numChannels = juce::jmin(numChannels, channels.size());

    for (int i = 0; i < numChannels; ++i)
        channels.getUnchecked(i)->pushSample(d[i]);
}

void WaveformVisualizer::setSamplesPerBlock(int newSamplesPerPixel) noexcept
{
    inputSamplesPerBlock = newSamplesPerPixel;
}

void WaveformVisualizer::setRepaintRate(int frequencyInHz)
{
    startTimerHz(frequencyInHz);
}

void WaveformVisualizer::timerCallback()
{
    repaint();
}

void WaveformVisualizer::setColours(juce::Colour bk, juce::Colour fg) noexcept
{
    backgroundColour = bk;
    waveformColour = fg;
    repaint();
}

void WaveformVisualizer::paint(juce::Graphics &g)
{
    auto r = getLocalBounds().toFloat();

    for (auto *c : channels)
        paintChannel(g, r, c->levels.begin(), c->levels.size(), c->nextSample);
}

void WaveformVisualizer::getChannelAsPath(juce::Path &path, const juce::Range<float> *levels,
                                          int numLevels, int nextSample)
{
    path.preallocateSpace(4 * numLevels + 8);

    for (int i = 0; i < numLevels; ++i)
    {
        auto level = -(levels[(nextSample + i) % numLevels].getEnd());

        if (i == 0)
            path.startNewSubPath(0.0f, -33.0f);
        else
            path.lineTo((float)i, -33.0f);
    }

    for (int i = numLevels; --i >= 0;)
    {
        float absoluteValue = juce::Decibels::gainToDecibels(std::abs(levels[(nextSample + i) % numLevels].getStart()));
        if (absoluteValue < -33.0f)
            absoluteValue = -33.0f;
        path.lineTo((float)i, absoluteValue);
    }

    path.closeSubPath();
}

void WaveformVisualizer::getChannelAsPathClipped(juce::Path &path, const juce::Range<float> *levels,
                                                 int numLevels, int nextSample)
{
    path.preallocateSpace(4 * numLevels + 8);

    for (int i = 0; i < numLevels; ++i)
    {
        auto level = -(levels[(nextSample + i) % numLevels].getEnd());

        if (i == 0)
            path.startNewSubPath(0.0f, -33.0f);
        else
            path.lineTo((float)i, -33.0f);
    }

    for (int i = numLevels; --i >= 0;)
    {
        float absoluteValue = juce::Decibels::gainToDecibels(std::abs(levels[(nextSample + i) % numLevels].getStart()));
        if (absoluteValue < -33.0f)
            absoluteValue = -33.0f;
        path.lineTo((float)i, absoluteValue);
    }

    path.closeSubPath();
}

void WaveformVisualizer::paintChannel(juce::Graphics &g, juce::Rectangle<float> area,
                                      const juce::Range<float> *levels, int numLevels, int nextSample)
{
    juce::Path p;
    getChannelAsPath(p, levels, numLevels, nextSample);
    p = p.createPathWithRoundedCorners(1.0f);

    g.setColour(waveformColour);

    // Define ceiling min and max Y-coordinates
    float ceilingZero = 150.0f / 1800.0f * area.getHeight();
    float ceilingNeg24 = 0.75f * area.getHeight();

    p.applyTransform(juce::AffineTransform::fromTargetPoints(0.0f, 0.0f, area.getX(), area.getY() - ceilingZero,
                                                             0.0f, -33.0f, area.getX(), area.getBottom(),
                                                             (float)numLevels, 0.0f, area.getRight(), area.getY() - ceilingZero));

    g.fillPath(p);

    float scaledY = juce::jmap(_ceiling, -24.0f, 0.0f, ceilingNeg24, ceilingZero);

    g.reduceClipRegion(p);
    g.setColour(juce::Colours::red);
    g.fillRect(0, (int)(area.getY()), (int)area.getWidth(), (int)(scaledY));
}
