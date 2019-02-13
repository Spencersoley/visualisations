#include "Model_AudioInterface.h"
#include "Program.h"

PaStreamParameters defaultParams()
{
	PaStreamParameters params;
	params.channelCount = 2;
	params.device = -1;
	params.hostApiSpecificStreamInfo = nullptr;
	params.sampleFormat = paFloat32;
	params.suggestedLatency = 10.0;
	return params;
}

Model_AudioInterface::Model_AudioInterface(std::shared_ptr<Settings_AudioInterface> & settings, Program * prog)
	: m_settings{ settings }, m_realTime{ new Recorder{} }, p_program{prog}
{
}

Model_AudioInterface::~Model_AudioInterface()
{
}

Buffer Model_AudioInterface::buffer()
{
	Buffer buf{ 512,defaultParams() };
	return buf;
}
