#include "stdafx.h"
#include "SoundWrap.h"
#include <iostream>

using namespace std;

namespace SoundWrapper
{
	SoundWrap* SoundWrap::Init(std::string resource_absolute_path, int channels)
	{
		int result; 
		SoundWrap *ref;
		ref = new SoundWrap();

		result = ref->InitSoundSystem(resource_absolute_path, channels);

		if (result < 0)
			return nullptr;

		return ref;
	}

	int SoundWrap::InitSoundSystem(std::string resource_absolute_path, int channels)
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&m_FMODSystem);
		if (result != FMOD_OK)
		{
			return -1;
		}

		m_FMODSystem->init(channels, FMOD_INIT_NORMAL, 0);
		
		if (result != FMOD_OK)
		{
			return -1;
		}

		m_Channels = new FMOD::Channel*[channels];
		m_AvailableChannels = channels;
		return 0;
	}

	int SoundWrap::Load(std::string resource_absolute_path)
	{
		if (m_FMODSystem == nullptr)
			return -1;

		return LoadAudio(resource_absolute_path, false);
	}

	int SoundWrap::LoadStreaming(std::string resource_absolute_path)
	{
		if (m_FMODSystem == nullptr)
			return -1;

		return LoadAudio(resource_absolute_path, true);
	}

	int SoundWrap::Play(int resource_ID,int channel)
	{
		if (m_FMODSystem == nullptr)
			return -1;

		return PlayAudio(resource_ID,channel,false);
	}

	int SoundWrap::PlayLoop(int resource_ID, int channel)
	{
		if (m_FMODSystem == nullptr)
			return -1;

		return PlayAudio(resource_ID, channel, true);
	}

	int SoundWrap::Close()
	{
		FMOD_RESULT result;
		result = m_FMODSystem->release();

		if (result != FMOD_OK)
		{
			return -1;
		}

		return 0;
	}

	void SoundWrap::Info()
	{
		if (m_FMODSystem == nullptr)
			return ;

		unsigned int      version;
		FMOD_RESULT result;
		result = m_FMODSystem->getVersion(&version);
		cout << "FMOD lib version "<< version <<", header version "<< FMOD_VERSION;
	}

	int SoundWrap::AddResource(FMOD::Sound ** sound)
	{
		if (m_FMODSystem == nullptr)
			return -1;

		m_Resources[m_ResourceIndex] = *sound;
		m_ResourceIndex++;
		return m_ResourceIndex - 1;
	}

	int SoundWrap::PlayAudio(int resource_ID, int channel, bool loop)
	{
		if (m_FMODSystem == nullptr)
			return -1;

		FMOD::Sound* sound;
		FMOD::Channel* ch;

		FMOD_RESULT result;

		sound = m_Resources[resource_ID];
		if (!loop) {
			sound->setMode(FMOD_LOOP_OFF);
		}
		else {
			sound->setMode(FMOD_LOOP_NORMAL);
		}

		ch = m_Channels[channel];
		int play_channel = m_ChannelsMap[resource_ID];

		if (play_channel > 0)
		{
			bool playing;
			result = ch->isPlaying(&playing);
			ch->setPaused(false);
		}
		else
		{
			result = m_FMODSystem->playSound(sound, 0, false, &ch);

			if (result != FMOD_OK)
			{
				return -1;
			}

			m_Channels[channel] = ch;
			m_ChannelsMap[resource_ID] = channel;
		}

		return 0;
	}

	int SoundWrap::LoadAudio(std::string resource_absolute_path, bool stream)
	{
		if (m_FMODSystem == nullptr)
			return -1;

		FMOD::Sound *sound;
		FMOD_RESULT result;

		if (!stream)
			result = m_FMODSystem->createSound(resource_absolute_path.c_str(), FMOD_2D, 0, &sound);
		else 
			result = m_FMODSystem->createSound(resource_absolute_path.c_str(), FMOD_CREATESTREAM, 0, &sound);

		if (result != FMOD_OK)
		{
			return -1;
		}

		return AddResource(&sound);
	}

	int SoundWrap::Pause(int resource_ID)
	{
		FMOD::Sound* sound;
		FMOD::Channel* channel;
		int ch;
		FMOD_RESULT result;

		sound = m_Resources[resource_ID];
		ch = m_ChannelsMap[resource_ID];
		channel = m_Channels[ch];
		result = channel->setPaused(true);

		if (result != FMOD_OK)
		{
			return -1;
		}

		return 0;
	}
	
	int SoundWrap::Stop(int resource_ID)
	{

		FMOD::Sound* sound;
		FMOD::Channel* channel;
		int ch;
		FMOD_RESULT result;

		sound = m_Resources[resource_ID];
		ch = m_ChannelsMap[resource_ID];
		channel = m_Channels[ch];
		result = channel->stop();

		if (result != FMOD_OK)
		{
			return -1;
		}

		m_ChannelsMap[resource_ID] = 0;

		return 0;
	}

	int SoundWrap::SetPan(int resource_ID, float pan)
	{
		FMOD::Sound* sound;
		FMOD::Channel* channel;
		int ch;
		FMOD_RESULT result;

		sound = m_Resources[resource_ID];
		ch = m_ChannelsMap[resource_ID];
		channel = m_Channels[ch];
		result = channel->setPan(pan);

		if (result != FMOD_OK)
		{
			return -1;
		}

		return 0;
	}

	int SoundWrap::SetVolume(int resource_ID, float volume)
	{
		FMOD::Sound* sound;
		FMOD::Channel* channel;
		int ch;
		FMOD_RESULT result;

		sound = m_Resources[resource_ID];
		ch = m_ChannelsMap[resource_ID];
		channel = m_Channels[ch];
		result = channel->setVolume(volume);

		if (result != FMOD_OK)
		{
			return -1;
		}

		return 0;
	}
}