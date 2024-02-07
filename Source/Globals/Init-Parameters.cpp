/*
  ==============================================================================

    Initialize-Parameters.cpp
    Created: 7 Feb 2024 7:00:00pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "Parameters.h"
#include "Globals.h"

//==============================================================================

void Parameters::initParameters()
{
  // Add your parameters here
  addSliderParameter(inputID, inputName, inputToolTip, -24.0f, 24.0f, 0.0f, 0.1f, 1, 250, 1200, 400, 400, 0);
  addSliderParameter(outputID, outputName, outputToolTip, -24.0f, 24.0f, 0.0f, 0.1f, 1, 1825, 1200, 400, 400, 0);
  addSliderParameter(ceilingID, ceilingName, ceilingToolTip, -24.0f, 0.0f, 0.0f, 0.1f, 1, 775, 1200, 400, 400, 0);
  addSliderParameter(kneeID, kneeName, kneeToolTip, 0.0f, 100.0f, 0.0f, 0.1f, -1, 1300, 1200, 400, 400, 0);
  addSliderParameter(mixID, mixName, mixToolTip, 0.0f, 100.0f, 100.0f, 0.1f, -1, 2350, 1200, 400, 400, 0);

  addToggleButtonParameter(compensationID, compensationName, compensationToolTip, 562, 1753, 300, 100, 0, false);
  addToggleButtonParameter(oversamplingID, oversamplingName, oversamplingToolTip, 1350, 1753, 300, 100, 1, false);
  addToggleButtonParameter(deltaID, deltaName, deltaToolTip, 2137, 1753, 300, 100, 2, false);
}