/*
  ==============================================================================

    ImageToggle.h
    Created: 7 Feb 2024 1:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ImageToggleLookAndFeel.h"

//==============================================================================

class ImageToggle : public juce::ToggleButton
{
public:
    ImageToggle()
    {
        imageToggleLookAndFeel = std::make_unique<ImageToggleLookAndFeel>();
        setLookAndFeel(imageToggleLookAndFeel.get());
    }

    ~ImageToggle()
    {
        setLookAndFeel(nullptr);
    }

    void setImages(juce::Image onImage, juce::Image offImage)
    {
        imageToggleLookAndFeel->setImages(onImage, offImage);
    }

    using RightClickCallback = std::function<void()>;

    void setRightClickCallback(RightClickCallback callback)
    {
        _rightClickCallback = callback;
    }

protected:
    void mouseDown(const juce::MouseEvent &e) override;

private:
    RightClickCallback _rightClickCallback;
    std::unique_ptr<ImageToggleLookAndFeel> imageToggleLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageToggle)
};
