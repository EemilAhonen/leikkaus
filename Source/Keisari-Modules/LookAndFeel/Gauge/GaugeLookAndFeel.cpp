/*
  ==============================================================================

    GaugeLookAndFeel.cpp
    Created: 5 Feb 2024 10:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "GaugeLookAndFeel.h"

//==============================================================================

/**
 * @brief Overrides the SliderLayout to center text inside the Gauge.
 *
 * Given a juce::Slider reference, calculates and returns the SliderLayout to ensure
 * the associated Gauge's text is centered. It adjusts the textBoxBounds and maintains
 * the original sliderBounds.
 *
 * @param slider A reference to the juce::Slider associated with the Gauge.
 * @return The SliderLayout with updated textBoxBounds for centered text.
 */
juce::Slider::SliderLayout GaugeLookAndFeel::getSliderLayout(juce::Slider &slider)
{
  auto localBounds = slider.getLocalBounds().toFloat();
  juce::Slider::SliderLayout layout;
  auto textBounds = localBounds.withSizeKeepingCentre(localBounds.getWidth(),
                                                      localBounds.getHeight() * _textHeight);
  layout.textBoxBounds = textBounds.toNearestInt();
  layout.sliderBounds = slider.getLocalBounds();
  return layout;
}

/**
 * @brief Creates and configures a TextLabel and TextEditor for the Gauge.
 *
 * Creates a GaugeLabel with a specified font size and sets various properties
 * such as editability, justification, and colors. Returns a pointer to the created label.
 *
 * @param slider A reference to the juce::Slider associated with the Gauge.
 * @return A pointer to the created GaugeLabel.
 */
juce::Label *GaugeLookAndFeel::createSliderTextBox(juce::Slider &slider)
{
  // Dynamically allocate memory for gaugeLabel
  auto *gaugeLabel = new GaugeLabel();

  gaugeLabel->setEditable(false, false, true);
  gaugeLabel->setJustificationType(juce::Justification::centred);
  gaugeLabel->setColour(juce::TextEditor::backgroundColourId, slider.findColour(juce::TextEditor::backgroundColourId));
  gaugeLabel->setColour(juce::TextEditor::outlineColourId, slider.findColour(juce::TextEditor::outlineColourId));
  gaugeLabel->setColour(juce::TextEditor::focusedOutlineColourId, slider.findColour(juce::TextEditor::focusedOutlineColourId));
  gaugeLabel->setColour(juce::TextEditor::highlightColourId, slider.findColour(juce::TextEditor::highlightColourId));
  gaugeLabel->setInterceptsMouseClicks(false, false);
  return gaugeLabel;
}

/**
 * @brief Draws the Gauge with a filled circle based on slider position.
 *
 * Given graphics context and dimensions, draws the Gauge with a filled
 * circle representing the slider position. The fill color is specified by _fillColor.
 *
 * @param g The graphics context to draw on.
 * @param x The x-coordinate of the slider.
 * @param y The y-coordinate of the slider.
 * @param width The width of the slider.
 * @param height The height of the slider.
 * @param sliderPosition The position of the slider.
 * @param rotaryStartAngle The start angle of the rotary slider.
 * @param rotaryEndAngle The end angle of the rotary slider.
 * @param slider A reference to the juce::Slider associated with the Gauge.
 */
void GaugeLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider)
{
  auto bounds = juce::Rectangle<int>(x, y, width, height);

  // Define circle colors
  juce::Colour fillColour = slider.findColour(juce::Slider::rotarySliderFillColourId);
  juce::Colour outerCircle = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
  juce::Colour innerCircle = slider.findColour(juce::Slider::trackColourId);

  // Draw the outer circle
  g.setColour(outerCircle);
  g.fillEllipse(x, y, width, height);

  // Set the inner circle size and gradient
  juce::ColourGradient innerGradient = juce::ColourGradient(innerCircle, bounds.getCentreX(), bounds.getCentreY(), juce::Colours::black, width * innerCircleSize, height * innerCircleSize, true);
  innerGradient.addColour(shadowWeakness, innerCircle);

  // Draw the inner circle
  g.setGradientFill(innerGradient);
  g.fillEllipse(x + (width * (1.0f - innerCircleSize) * 0.5f), y + (height * (1.0f - innerCircleSize) * 0.5f), width * innerCircleSize, height * innerCircleSize);

  // Calculate the vertical position to fill the circle based on the slider position.
  float fillY = height * (1.0f - sliderPosition);

  // Create a circular clipping path to restrict drawing within the specified circle.
  juce::Path clippingCircle;
  clippingCircle.addEllipse(x, y, width, height);
  g.reduceClipRegion(clippingCircle);

  // Fill the rectangle within the circular boundary with the specified color.
  g.setColour(fillColour);
  g.fillRect(static_cast<int>(x), static_cast<int>(fillY), static_cast<int>(width), static_cast<int>(height));

  innerGradient.multiplyOpacity(centerOpacity);
  g.setGradientFill(innerGradient);
  g.fillEllipse(x + (width * (1.0f - innerCircleSize) * 0.5f), y + (height * (1.0f - innerCircleSize) * 0.5f), width * innerCircleSize, height * innerCircleSize);

  // Set arrows based on hovering and clicking state
  if (_hovering)
  {
    // Define arrow characteristics
    float arrowWidth = width * 0.1f;
    float opacityModifier = _mouseDown ? 0.5f : 0.25f;
    float fullOpacityModifier = opacityModifier * 2;

    // Calculate arrow color based on slider position and opacity modifiers
    juce::Colour arrowColor = juce::Colour(static_cast<juce::uint8>(255), 255, 255, sliderPosition == 1.0f ? opacityModifier : fullOpacityModifier);

    // Draw top arrow
    g.setColour(arrowColor);
    drawArrow(g, bounds.getCentreX(), bounds.getCentreY(), arrowWidth, height, true);

    // Draw bottom arrow
    g.setColour(arrowColor.withAlpha(sliderPosition == 0.0f ? opacityModifier : fullOpacityModifier));
    drawArrow(g, bounds.getCentreX(), bounds.getCentreY(), arrowWidth, height, false);
  }
}

void GaugeLookAndFeel::drawArrow(juce::Graphics &g, float x, float y, float width, float height, bool flip)
{
  // Set arrow direction based on 'flip'
  float arrowDirection = flip ? -1.0f : 1.0f;

  float arrowY = 0.2125f * height * arrowDirection;
  float thickness = 0.025f * height;

  // Create arrow path
  juce::Path arrow;
  arrow.startNewSubPath(x - width / 2, y + arrowY);
  arrow.lineTo(x, y + arrowY + arrowDirection * (height * 0.05f));
  arrow.lineTo(x + width / 2, y + arrowY);

  // Stroke the arrow path
  g.strokePath(arrow, juce::PathStrokeType(juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded)));
}