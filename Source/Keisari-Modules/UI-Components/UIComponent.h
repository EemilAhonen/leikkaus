/*
  ==============================================================================

    UIComponent.h
    Created: 7 Feb 2024 2:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================

class UIComponent
{
public:
    virtual ~UIComponent() = default;

    virtual void setBounds(float ratio = 1.0f)
    {
        _component.get()->setBounds(_x * ratio, _y * ratio, _width * ratio, _height * ratio);
    }

    void setComponent(std::unique_ptr<juce::Component> newComponent)
    {
        _component = std::move(newComponent);
    }

    juce::Component *getComponent() { return _component.get(); }

public:
    const juce::String _id;
    const juce::String _name;
    const juce::String _toolTip;

    const int _x;
    const int _y;
    const int _width;
    const int _height;

    const int _lookAndFeelID;

protected:
    UIComponent(const juce::String id, const juce::String name, const juce::String toolTip, const int x, const int y, const int width, const int height, int lookAndFeelID)
        : _id(id), _name(name), _toolTip(toolTip), _x(x), _y(y), _width(width), _height(height), _lookAndFeelID(lookAndFeelID)
    {
    }

    std::unique_ptr<juce::Component> _component;
};