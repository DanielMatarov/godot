#ifndef MIDISTREAM_H
#define MIDISTREAM_H
#include "tsf.h"
#include "tml.h"
#include "reference.h"
#include "resource.h"
#include "servers/audio/audio_stream.h" 


class MidiStream : public AudioStream {
	GDCLASS(MidiStream, AudioStream)
	OBJ_SAVE_TYPE(AudioStream)

	friend class MidiStreamPlayback;
	uint64_t pos;
	int sample_rate;
	float gain;
	int preset;
	char* sf_filename;
	tsf* tsf_pointer;
	double midi_pb_time;
public:
	tml_message* midi_pointer;
	MidiStream();
	void reset();
	void set_position(uint64_t pos);
	void set_preset(int pr);
	void set_filename(const String&filename);
	void midi_load_filename(const String&filename);
	void midi_file_reading(uint8_t *b, int s);
	void note_on(int n,float v);
	virtual Ref<AudioStreamPlayback> instance_playback();
    
	void buffer_function(float* b, int s);
	virtual String get_stream_name() const;
	virtual float get_length() const { return 0; }
	

protected:
	static void _bind_methods();
};

#endif 
