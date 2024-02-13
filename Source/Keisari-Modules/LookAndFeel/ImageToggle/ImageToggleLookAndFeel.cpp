/*
  ==============================================================================

    ImageToggleLookAndFeel.cpp
    Created: 7 Feb 2024 1:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "ImageToggleLookAndFeel.h"

//==============================================================================

void ImageToggleLookAndFeel::drawTickBox(juce::Graphics &g, juce::Component &toggle, float x, float y, float width, float height, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
  // Obtain the height of the local bounds of the toggle component.
  float boundsHeight = toggle.getLocalBounds().getHeight();

  // Determine which image to draw based on the 'ticked' condition.
  // If 'ticked' is true, use the '_onImage'; otherwise, use the '_offImage'.
  auto &imageToDraw = ticked ? _onImage : _offImage;

  // Check if the selected image is valid (not null) before attempting to draw.
  // If the image is valid, calculate a scaling transformation based on the
  // ratio of 'boundsHeight' to the height of the selected image. Then, draw
  // the transformed image on the graphics context 'g'.
  if (!imageToDraw.isNull())
  {
    auto transform = juce::AffineTransform::scale(boundsHeight / imageToDraw.getHeight());
    g.drawImageTransformed(imageToDraw, transform, false);
  }
}