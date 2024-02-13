/*
  ==============================================================================

    UI-Create.cpp
    Created: 7 Feb 2024 6:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginEditor.h"
#include "../Keisari-Modules/LookAndFeel/Gauge/Gauge.h"
#include "../Keisari-Modules/LookAndFeel/ImageToggle/ImageToggle.h"

//==============================================================================

void LeikkausAudioProcessorEditor::createSlider(SliderComponent &sliderComponent)
{
    // Create and set the Gauge
    sliderComponent.setComponent(std::make_unique<Gauge>());

    // Retrieve the Gauge
    auto gauge = dynamic_cast<Gauge *>(sliderComponent.getComponent());
    if (gauge != nullptr)
    {
        addAndMakeVisible(gauge);

        // These values don't actually matter, as they are set in the resized() method
        gauge->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 400, 400);

        gauge->setDoubleClickReturnValue(true, sliderComponent._initValue);
        gauge->setRange(sliderComponent._minValue, sliderComponent._maxValue, sliderComponent._interval);
        gauge->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        gauge->setTooltip(sliderComponent._toolTip);

        // Set Gauge colours
        gauge->setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(static_cast<juce::uint8>(255), 100, 255, 1.0f));
        gauge->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(100, 120, 130));
        gauge->setColour(juce::Slider::trackColourId, juce::Colour(15, 15, 20));

        // Set Gauge TextEditor colours
        gauge->setColour(juce::TextEditor::backgroundColourId, juce::Colour(30, 30, 30));
        gauge->setColour(juce::TextEditor::outlineColourId, juce::Colour(45, 133, 194));
        gauge->setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour(45, 133, 194));
        gauge->setColour(juce::TextEditor::highlightColourId, juce::Colour(137, 87, 110));

        gauge->setTextHeight(0.2f);

        gauge->setRightClickCallback([this, parameterID = sliderComponent._id]()
                                     { handleRightClick(parameterID); });
    }

    // Add slider attachment
    _sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, sliderComponent._id, *gauge));
}

void LeikkausAudioProcessorEditor::createToggleButton(ToggleButtonComponent &toggleButtonComponent)
{
    // Create and set toggle image button
    toggleButtonComponent.setComponent(std::make_unique<ImageToggle>());

    // Retrieve the toggle image button
    auto imageToggle = dynamic_cast<ImageToggle *>(toggleButtonComponent.getComponent());
    if (imageToggle != nullptr)
    {
        addAndMakeVisible(imageToggle);
        imageToggle->setTooltip(toggleButtonComponent._toolTip);

        // Look and feel settings here
        setupToggleLookAndFeel(*imageToggle, toggleButtonComponent._lookAndFeelID);

        imageToggle->setRightClickCallback([this, parameterID = toggleButtonComponent._id]()
                                           { handleRightClick(parameterID); });
    }

    // Add toggle button attachment
    _toggleButtonAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, toggleButtonComponent._id, *imageToggle));
}

void LeikkausAudioProcessorEditor::setupToggleLookAndFeel(ImageToggle &imageToggle, int lookAndFeelID)
{
    juce::Image toggleOnImage;
    juce::Image toggleOffImage;

    switch (lookAndFeelID)
    {
    case 0:
        toggleOnImage = juce::ImageCache::getFromMemory(BinaryData::Compensation_ON_png, BinaryData::Compensation_ON_pngSize);
        toggleOffImage = juce::ImageCache::getFromMemory(BinaryData::Compensation_OFF_png, BinaryData::Compensation_OFF_pngSize);
        break;
    case 1:
        toggleOnImage = juce::ImageCache::getFromMemory(BinaryData::Oversampling_ON_png, BinaryData::Oversampling_ON_pngSize);
        toggleOffImage = juce::ImageCache::getFromMemory(BinaryData::Oversampling_OFF_png, BinaryData::Oversampling_OFF_pngSize);
        break;
    case 2:
        toggleOnImage = juce::ImageCache::getFromMemory(BinaryData::Delta_ON_png, BinaryData::Delta_ON_pngSize);
        toggleOffImage = juce::ImageCache::getFromMemory(BinaryData::Delta_OFF_png, BinaryData::Delta_OFF_pngSize);
        break;

    default:
        // Handle default case or throw an exception if necessary
        break;
    }

    imageToggle.setImages(toggleOnImage, toggleOffImage);
}

void LeikkausAudioProcessorEditor::handleRightClick(juce::String parameterID)
{
    auto parameter = audioProcessor._treeState.getParameter(parameterID);
    if (parameter != nullptr)
    {
        auto hostContext = getHostContext();
        if (hostContext != nullptr)
        {
            auto contextMenu = hostContext->getContextMenuForParameter(parameter);
            if (contextMenu != nullptr)
            {
                // This is a hack to make the context menu appear in the right place on MAC
                // TODO: Fix the HiDPI JUCE bug that is causing this
                // contextMenu->showNativeMenu(getMouseXYRelative() * 2);

                // So this only works properly on Windows
                contextMenu->showNativeMenu(getMouseXYRelative());
            }
        }
    }
}