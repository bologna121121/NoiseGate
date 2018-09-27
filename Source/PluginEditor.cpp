/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HardClippingAudioProcessorEditor::HardClippingAudioProcessorEditor (HardClippingAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (100 * sliderCount, 300);
	setResizable(true, true);
	AudioProcessorEditor::setResizeLimits(100, 100, 1800, 1000);

	for (int i = 0; i < sliderCount; i++)
	{
		sliders[i].setSliderStyle(Slider::LinearBarVertical);
		sliders[i].setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		sliders[i].setPopupDisplayEnabled(true, false, this);
		addAndMakeVisible(&sliders[i]);
		sliders[i].addListener(this);

		switch (i)
		{
			case thresholdSlider:
				sliders[thresholdSlider].setRange(0.0, 0.00001, 0.00000001);
				sliders[thresholdSlider].setValue(0.0);

				break;
			case attackSlider:
				sliders[attackSlider].setRange(1, 100, 1);
				sliders[attackSlider].setValue(50);
				sliders[attackSlider].setTextValueSuffix("ms");
				break;
			case decaySlider:
				sliders[decaySlider].setRange(1, 100, 1);
				sliders[decaySlider].setValue(50);
				sliders[decaySlider].setTextValueSuffix("ms");
				break;
			case holdSlider:
				sliders[holdSlider].setRange(1, 1000, 1);
				sliders[holdSlider].setValue(500);
				sliders[holdSlider].setTextValueSuffix("ms");
				break;
		}
	}


}

HardClippingAudioProcessorEditor::~HardClippingAudioProcessorEditor()
{
}

//==============================================================================
void HardClippingAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);

	for (int i = 0; i < sliderCount; i++)
	{
		g.drawFittedText(sliderLabels[i], (int)(((i + 1) * gapWidth + (i + 0.5) * sliderWidth - (gapWidth + sliderWidth) / 2 + sliderAreaCornerX) * getWidth()),
						(int)((sliderHeight + sliderVerticalMargin + sliderAreaCornerY) * getHeight()),
						(int)(sliderLabelWidth * getWidth()), (int)(sliderLabelHeight * getHeight()),
						Justification::centred, 1);
	}
}

void HardClippingAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	for (int i = 0; i < sliderCount; i++)
	{
		sliders[i].setBounds((int)(((i + 1) * gapWidth + i * sliderWidth + sliderAreaCornerX) * getWidth()), (int)((sliderVerticalMargin + sliderAreaCornerY) * getHeight()),
			(int)(sliderWidth * getWidth()), (int)(sliderHeight * getHeight()));
	}
}


void HardClippingAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	processor.gateThreshold = sliders[thresholdSlider].getValue();
	processor.attackTime = sliders[attackSlider].getValue() * 0.001;
	processor.decayTime = sliders[decaySlider].getValue() * 0.001;
	processor.holdTime = sliders[holdSlider].getValue() * 0.001;
}
