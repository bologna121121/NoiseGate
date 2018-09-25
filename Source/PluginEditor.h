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

	enum sliderTypes 
	{
		coefficientSlider = 0,
		decayRateSlider = 1,
		gateSlider = 2
	};

	// Values below are expressed as fractions of the current window width and height

	int sliderCount = 3;
	double sliderAreaCornerX = 0;
	double sliderAreaCornerY = 0;
	double sliderAreaHeight = 1.0;
	double sliderAreaWidth = 1.0;
	double sliderVerticalMargin = 0.1;
	double sliderLabelHeight = 0.1;
	double sliderWidth = 0.066667;
	double sliderHeight = sliderAreaHeight - 2 * sliderVerticalMargin - sliderLabelHeight;
	double gapWidth = (sliderAreaWidth - sliderCount * sliderWidth) / (sliderCount + 1.0);
	double sliderLabelWidth = gapWidth + sliderWidth;
	std::vector<Slider> sliders{3};
	std::vector<String> sliderLabels{3};

	

	void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HardClippingAudioProcessorEditor)
};
