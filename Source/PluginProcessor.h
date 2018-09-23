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

	float coefficientLevel = 1.0;
	float clippingLevel = 0.1;
	float gateThreshold = 0.0;

	double currentSamplingRate;
	int currentBufferIndexCH0 = 0;
	int currentBufferIndexCH1 = 0;
	double gateMultiplierCH0 = 0.0;
	double gateMultiplierCH1 = 0.0;
	double attackRate = 0.02;
	double decayRate = 0.02;
	std::vector<float> averagingBufferCH0 = std::vector<float>(700, 0.0);
	std::vector<float> averagingBufferCH1 = std::vector<float>(700, 0.0);

	std::vector<int> currentBufferIndex{ 0,0 };
	std::vector<double> gateMultiplier{ 0,0 };
	std::vector<std::vector<float>> averagingBuffer = std::vector<std::vector<float>>(2, std::vector<float>(700, 0.0));


private:
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HardClippingAudioProcessor)
};