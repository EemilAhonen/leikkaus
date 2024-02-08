/*
  ==============================================================================

    CeilingVisualizer.cpp
    Created: 8 Feb 2024 2:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "CeilingVisualiser.h"

//==============================================================================

void CeilingVisualiser::paint(juce::Graphics &g)
{
  // Get the height of the component
  float height = static_cast<float>(getHeight());

  // Define ceiling min and max Y-coordinates
  float ceilingZero = 150.0f / 1800.0f * height;
  float ceilingNeg24 = 0.75f * height;

  // Define line width
  float lineWidth = 0.005f * height;

  // Map the _ceiling value to a scaled Y-axis range
  float scaledY = juce::jmap(_ceiling, -24.0f, 0.0f, ceilingNeg24, ceilingZero);

  g.setColour(juce::Colours::white);

  // Create a path for the graph
  juce::Path path;
  path.startNewSubPath(0, height);
  path.lineTo(getWidth() / 4, scaledY);
  path.lineTo(getWidth(), scaledY);

  g.strokePath(path, juce::PathStrokeType(lineWidth));
}