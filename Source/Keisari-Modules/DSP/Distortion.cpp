/*
  ==============================================================================

    Distortion.cpp
    Created: 4 Feb 2024 8:37:05pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "Distortion.h"

//==============================================================================

/**
 * Clips the input sample with a smooth transition (ratio) around the specified ceiling.
 *
 * @param sample The input sample to be clipped.
 * @param ceiling The threshold for positive and negative clipping.
 * @param ratio The factor determining the smoothness of the transition.
 * @return The clipped value with a smooth transition.
 *
 * @note This implementation is optimized for ARM processors. For X86 architectures, consider using
 * fabs for conditionals for better performance.
 */
float clipWithRatio(const float sample, const float ceiling, const float ratio)
{
  if (sample > ceiling)
  {
    // Clip above the threshold with 'ratio' for a gradual transition.
    return ceiling + (sample - ceiling) * ratio;
  }
  else if (sample < -ceiling)
  {
    // Clip below the threshold with 'ratio' for a gradual transition.
    return -(ceiling + (-sample - ceiling) * ratio);
  }
  // No clipping needed
  return sample;
}