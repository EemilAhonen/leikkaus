/*
  ==============================================================================

    Pro-State.cpp
    Created: 27 Jan 2024 8:09:01pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"

//==============================================================================

/**
 * @brief Saves the AudioProcessor's internal state into a memory block.
 *
 * The host invokes this method to request the processor to save its internal state.
 * It is responsible for copying relevant information into the provided memory block.
 * The saved state can later be restored using setStateInformation().
 *
 * @param destData A reference to the memory block where the state information will be stored.
 */
void LeikkausAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
  _treeState.state.appendChild(_valueTree, nullptr);
  juce::MemoryOutputStream stream(destData, false);
  _treeState.state.writeToStream(stream);
}

/**
 * @brief Restores the processor's state from a previously saved memory block.
 *
 * This method is responsible for restoring the processor's state from a memory block
 * that was previously created using the getStateInformation() method. It should be
 * implemented to reconstruct the internal state based on the provided data.
 *
 * @param data A pointer to the memory block containing the saved state information.
 * @param sizeInBytes The size of the memory block in bytes.
 */
void LeikkausAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
  // You should use this method to restore your parameters from this memory block,
  // whose contents will have been created by the getStateInformation() call.
  juce::ValueTree tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
  _valueTree = tree.getChildWithName("Variables");

  // Note: This check is a temporary measure and may be removed in the future.
  // Altering the structure of the ValueTree can render existing saved states incompatible.
  if (tree.isValid())
  {
    _treeState.state = tree;

    // Extract the "width" and "height" properties from the "Variables" node.
    _width = _valueTree.getProperty("width");
    _height = _valueTree.getProperty("height");

    // Update parameter values
    parameterChanged(juce::String(), 0.0f);
  }
}
