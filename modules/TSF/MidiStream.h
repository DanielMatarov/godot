#define TSF_IMPLEMENTATION
#include "tsf.h"
#include "reference.h"
#include "resource.h"
#include "servers/audio/audio_stream.h" 


class MidiStream : public AudioStream {
	GDCLASS(MidiStream, AudioStream);
private:
	friend class AudioStreamPlaybackMidiStream;
	uint64_t pos;
	bool stereo;
	int sample_rate;
	int samples;
	short* buffer;
	int flag_mixing;
public:
	tsf * f;
	char* sf_filename;
	float gain;
	int note;
	int vel;
	int index;
};
