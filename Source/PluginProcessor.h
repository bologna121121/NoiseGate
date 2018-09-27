/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <cstdlib>
#include <cmath>
#include <vector>
#include <numeric> 

//==============================================================================
/**
*/
class HardClippingAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    HardClippingAudioProcessor();
    ~HardClippingAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	double gateThreshold = 0.0;
	double attackTime = 0.01;
	double attackRate = 0.0;
	double decayTime = 0.01;
	double decayRate = 0.0;
	double holdTime = 0.5;
	double currentSampleRate = 0.0;

	double averagingBufferDuration = 0.015;

	std::vector<int> currentBufferIndex{ 0,0 };
	std::vector<double> gateMultiplier{ 0,0 };
	std::vector<double> openTime{ 0.0, 0.0 };
	std::vector<bool> isOpen{ false, false };
	std::vector<std::vector<float>> averagingBuffer = std::vector<std::vector<float>>(2, std::vector<float>(0, 0.0));
	


private:
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HardClippingAudioProcessor)
};