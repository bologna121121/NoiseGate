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
    setSize (300, 300);

	coefficientSlider.setSliderStyle(Slider::LinearBarVertical);
	coefficientSlider.setRange(0.0, 1.0, 0.001);
	coefficientSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	coefficientSlider.setPopupDisplayEnabled(true, false, this);
	coefficientSlider.setValue(0.5);

	addAndMakeVisible(&coefficientSlider);

	decayRateSlider.setSliderStyle(Slider::LinearBarVertical);
	decayRateSlider.setRange(0.0001, 0.5, 0.001);
	decayRateSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	decayRateSlider.setPopupDisplayEnabled(true, false, this);
	decayRateSlider.setValue(0.0001);

	addAndMakeVisible(&decayRateSlider);

	gateSlider.setSliderStyle(Slider::LinearBarVertical);
	gateSlider.setRange(0.0, 0.001, 0.00001);
	gateSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	gateSlider.setPopupDisplayEnabled(true, false, this);
	gateSlider.setValue(0.0);

	addAndMakeVisible(&gateSlider);

	coefficientSlider.addListener(this);
	decayRateSlider.addListener(this);
	gateSlider.addListener(this);

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
	//g.drawFittedText("Distortion Plugin", 0, 0, getWidth(), 30, Justification::centred, 1);
	g.drawFittedText("Coefficient", (int)((getWidth() - 60.0) / 4.0 - 15.0), getHeight() - 30, 50, 30, Justification::centred, 1);
	g.drawFittedText("Decay", (int)(getWidth() / 2.0 - 25.0), getHeight() - 30, 50, 30, Justification::centred, 1);
	g.drawFittedText("Gate", (int)(3.0 * (getWidth() - 60.0) / 4.0 + 25.0), getHeight() - 30, 50, 30, Justification::centred, 1);
}

void HardClippingAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	coefficientSlider.setBounds((int)((getWidth() - 60.0) / 4.0), 60, 20, getHeight() - 90);
	decayRateSlider.setBounds((int)(2.0 * (getWidth() - 60.0) / 4.0 + 20.0), 60, 20, getHeight() - 90);
	gateSlider.setBounds((int)(3.0 * (getWidth() - 60.0) / 4.0 + 40.0), 60, 20, getHeight() - 90);
}


void HardClippingAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	processor.coefficientLevel = coefficientSlider.getValue();
	processor.decayRate = decayRateSlider.getValue();
	processor.gateThreshold = gateSlider.getValue();
}
