#ifndef GS2D_FM_AUDIO_CONTEXT_H_
#define GS2D_FM_AUDIO_CONTEXT_H_

#include "../../Audio.h"
#include "../../Platform/FileLogger.h"

#include "fmod.hpp"

namespace gs2d {

bool FMOD_ERRCHECK_fn(FMOD_RESULT result, const char *file, int line, Platform::FileLogger& logger);
#define FMOD_ERRCHECK(_result, _logger) FMOD_ERRCHECK_fn(_result, __FILE__, __LINE__, _logger)

class FMAudioContext : public Audio
{
	static FMOD::System* m_system;

	float m_globalVolume;

	bool CreateAudioDevice(boost::any data);
	Platform::FileLogger m_logger;

	boost::weak_ptr<FMAudioContext> weak_this;

	FMAudioContext();

public:
	~FMAudioContext();

	static boost::shared_ptr<FMAudioContext> Create(boost::any data);

	static bool IsStreamable(const Audio::SAMPLE_TYPE type);

	static void CommonInit(Platform::FileLogger& logger);

	AudioSamplePtr LoadSampleFromFile(
		const str_type::string& fileName,
		const Platform::FileManagerPtr& fileManager,
		const Audio::SAMPLE_TYPE type = Audio::UNKNOWN_TYPE);

	AudioSamplePtr LoadSampleFromFileInMemory(
		void *pBuffer,
		const unsigned int bufferLength,
		const Audio::SAMPLE_TYPE type = Audio::UNKNOWN_TYPE);

	boost::any GetAudioContext();

	void SetGlobalVolume(const float volume);
	float GetGlobalVolume() const;

	void Update();
};

typedef boost::shared_ptr<FMAudioContext> FMAudioContextPtr;
typedef boost::shared_ptr<FMAudioContext> FMAudioContextWeakPtr;

} // namespace gs2d

#endif
