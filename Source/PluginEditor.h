/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HardClippingAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    HardClippingAudioProcessorEditor (HardClippingAudioProcessor&);
    ~HardClippingAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HardClippingAudioProcessor& processor;

	int sliderNumber = 3;
	int sliderHeight = 60;
	int sliderWidth = 20;

	Slider coefficientSlider;
	Slider decayRateSlider;
	Slider gateSlider;

	void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HardClippingAudioProcessorEditor)
};
