/*
  ==============================================================================

    Gauge.cpp
    Created: 5 Feb 2024 10:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "Gauge.h"

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
juce::Slider::SliderLayout Gauge::getSliderLayout(juce::Slider &slider)
{
  auto localBounds = slider.getLocalBounds().toFloat();
  juce::Slider::SliderLayout layout;
  auto textBounds = localBounds.withSizeKeepingCentre(localBounds.getWidth(),
                                                      localBounds.getHeight() * 0.25f);
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
juce::Label *Gauge::createSliderTextBox(juce::Slider &)
{
  auto *l = new GaugeLabel(_textSize);

  // TODO: Change this later so that the dial below is interactable
  l->setEditable(false, true, true);
  l->setJustificationType(juce::Justification::centred);
  l->setColour(juce::TextEditor::backgroundColourId, juce::Colour(30, 30, 30));
  l->setColour(juce::TextEditor::outlineColourId, juce::Colour(45, 133, 194));
  l->setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour(45, 133, 194));
  l->setColour(juce::TextEditor::highlightColourId, juce::Colour(137, 87, 110));
  l->setInterceptsMouseClicks(true, true);
  return l;
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
void Gauge::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider)
{
  // Calculate the vertical position to fill the circle based on the slider position.
  float fillY = height * (1.0f - sliderPosition);

  // Create a circular clipping path to restrict drawing within the specified circle.
  juce::Path clipPath;
  clipPath.addEllipse(x, y, width, height);
  g.reduceClipRegion(clipPath);

  // Fill the rectangle within the circular boundary with the specified color.
  g.setColour(_fillColor);
  g.fillRect(static_cast<int>(x), static_cast<int>(fillY), static_cast<int>(width), static_cast<int>(height));

  // Draw arrow image if it's set
  if (!_arrowImage.isNull())
  {
    // Calculate the transformation for the knob image
    auto transform = juce::AffineTransform::scale(static_cast<float>(height) / _arrowImage.getHeight()).translated(x, y);
    g.setColour(juce::Colours::white);
    g.drawImageTransformed(_arrowImage, transform, false);
  }
}
