#pragma once
#include <vector>
#include <string>
#include <fmod.hpp>
#include <map>

namespace SoundWrapper
{

	class SoundWrap {
	private:
		bool m_InitDone;
		int m_AvailableChannels;
		int m_ResourceIndex = 0;
		FMOD::System* m_FMODSystem = NULL;
		std::string m_ResourceAbsolutePath;
		std::map<int, FMOD::Sound*> m_Resources;
		std::map<int, int> m_ChannelsMap;
		FMOD::Channel** m_Channels;

	public:
		static SoundWrap* Init(std::string resource_absolute_path, int channels);
		
		int InitSoundSystem(std::string resource_absolute_path, int channels);

		int Load(std::string resource_absolute_path);
		int LoadStreaming(std::string resource_absolute_path);

		int Play(int resource_ID, int channel);
		int PlayLoop(int resource_ID, int channel);
		int Pause(int resource_ID);
		int Stop(int resource_ID);
		
		int SetPan(int resource_ID, float pan);
		int SetVolume(int resource_ID, float volume);

		int Close();

		void Info();
	private:
		int AddResource(FMOD::Sound **sound);
		int PlayAudio(int resource_ID, int channel, bool loop);
		int LoadAudio(std::string resource_absolute_path, bool stream);

	};
}