/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HardClippingAudioProcessor::HardClippingAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

HardClippingAudioProcessor::~HardClippingAudioProcessor()
{
}

//==============================================================================
const String HardClippingAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HardClippingAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HardClippingAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HardClippingAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HardClippingAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HardClippingAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HardClippingAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HardClippingAudioProcessor::setCurrentProgram (int index)
{
}

const String HardClippingAudioProcessor::getProgramName (int index)
{
    return {};
}

void HardClippingAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HardClippingAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	currentSamplingRate = sampleRate;
}

void HardClippingAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HardClippingAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HardClippingAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
	
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		float* const bufferToFill = buffer.getWritePointer(channel);
		float current;
		double averagedValue;
		
		for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			current = bufferToFill[sample];
			averagingBuffer[channel][ currentBufferIndex[channel] ] = current * channel;
			currentBufferIndex[channel] += 1;

			if (currentBufferIndex[channel] == averagingBuffer[channel].size())
			{
				currentBufferIndex[channel] = 0;
			}
			averagedValue = std::accumulate(averagingBuffer[channel].begin(), averagingBuffer[channel].end(), 0.0) / (double)(averagingBuffer[channel].size());
			if ((averagedValue > gateThreshold) && (gateMultiplier[channel] < 1.0))
			{
				gateMultiplier[channel] += attackRate;
				if (gateMultiplier[channel] > 1.0) gateMultiplier[channel] = 1.0;
			}
			if ((averagedValue < gateThreshold) && (gateMultiplier[channel] > 0.0))
			{
				gateMultiplier[channel] -= decayRate;
				if (gateMultiplier[channel] < 0.0) gateMultiplier[channel] = 0.0;
			}
			bufferToFill[sample] = current * gateMultiplier[channel];
			/*
			switch (channel)
			{
				case 0:
				{
					averagingBufferCH0[currentBufferIndexCH0] = current * current;
					currentBufferIndexCH0 += 1;
					if (currentBufferIndexCH0 == averagingBufferCH0.size())
					{
						currentBufferIndexCH0 = 0;
					}
					averagedValue = std::accumulate(averagingBufferCH0.begin(), averagingBufferCH0.end(), 0.0) / (double)(averagingBufferCH0.size());
					if ((averagedValue > gateThreshold) && (gateMultiplierCH0 < 1.0))
					{
						gateMultiplierCH0 += attackRate;
						if (gateMultiplierCH0 > 1.0) gateMultiplierCH0 = 1.0;
					}
					if (((averagedValue < gateThreshold) && (gateMultiplierCH0 > 0.0)))
					{
						gateMultiplierCH0 -= decayRate;
						if (gateMultiplierCH0 < 0.0) gateMultiplierCH0 = 0.0;
					}
					bufferToFill[sample] = current * gateMultiplierCH0;
					break;
				}
				case 1:
				{
					averagingBufferCH1[currentBufferIndexCH1] = current * current;
					currentBufferIndexCH1 += 1;
					if (currentBufferIndexCH1 == averagingBufferCH1.size())
					{
						currentBufferIndexCH1 = 0;
					}
					averagedValue = std::accumulate(averagingBufferCH1.begin(), averagingBufferCH1.end(), 0.0) / (double)(averagingBufferCH1.size());
					if ((averagedValue > gateThreshold) && (gateMultiplierCH1 < 1.0))
					{
						gateMultiplierCH1 += attackRate;
						if (gateMultiplierCH1 > 1.0) gateMultiplierCH1 = 1.0;
					}
					if ((averagedValue < gateThreshold / 4.0) && (gateMultiplierCH1 > 0.0))
					{
						gateMultiplierCH1 -= decayRate;
						if (gateMultiplierCH1 < 0.0) gateMultiplierCH1 = 0.0;
					}

					bufferToFill[sample] = current * gateMultiplierCH1;
					break;
				}
			}*/
		}
	}
}

//==============================================================================
bool HardClippingAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HardClippingAudioProcessor::createEditor()
{
    return new HardClippingAudioProcessorEditor (*this);
}

//==============================================================================
void HardClippingAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HardClippingAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HardClippingAudioProcessor();
}
