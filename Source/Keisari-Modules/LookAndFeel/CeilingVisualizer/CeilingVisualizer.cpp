/*
  ==============================================================================

    CeilingVisualizer.cpp
    Created: 8 Feb 2024 2:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "CeilingVisualizer.h"

//==============================================================================

void CeilingVisualizer::paint(juce::Graphics &g)
{
  // Get the height of the component
  float height = static_cast<float>(getHeight());

  // Define ceiling min and max Y-coordinates
  float ceilingZero = 150.0f / 1800.0f * height;
  float ceilingNeg24 = 0.75f * height;

  // Define line width
  float lineWidth = 0.005f * height;

  // Map the _ceiling value to a scaled X and Y-axis range
  float scaledY = juce::jmap(_ceiling, -24.0f, 0.0f, ceilingNeg24, ceilingZero);
  float scaledX = juce::jmap(_ceiling, -33.0f, 3.0f, 0.0f, getWidth() / 2.0f);

  g.setColour(juce::Colours::white);

  // Create a path for the graph
  juce::Path path;
  path.startNewSubPath(0, height);
  path.lineTo(scaledX, scaledY);

  // TODO: Technically this isn't correct (when the y-coordinate goes below 0),
  // but visually it is the same as the correct solution.
  // It's just making a big triangle and drawing out of bounds.
  // Someone with actual trigonometry knowledge should fix this.

  // Calculate the base of the triangle (This is correct)
  float baseWidth = getWidth() - scaledX;

  // Calculate the angle and radians of the triangle (This is correct)
  float angleDegrees = 50.0f * _ratio;
  float angleRadians = angleDegrees * (juce::MathConstants<float>::pi / 180.0f);

  // Calculate the visualizer end Y-coordinate (This is not correct)
  float endY = scaledY - baseWidth * std::tan(angleRadians);

  // Calculate the visualizer end X-coordinate (This is not correct)
  float endX = getWidth();

  // Draw the visualizer end point
  path.lineTo(getWidth(), endY);

  g.strokePath(path, juce::PathStrokeType(lineWidth));
}
