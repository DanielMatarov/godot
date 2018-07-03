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
	RES_BASE_EXTENSION("sf2str")
	String file;
	friend class MidiStreamPlayback;
	uint64_t pos;
	int sample_rate;
	float gain;
	int preset;
	char* sf_filename;
	tsf* tsf_pointer;
	double midi_pb_time;
	void *data;
	uint32_t data_len;
	void clear_data();
public:
	tml_message* midi_pointer;
	MidiStream();
	void reset();
	void set_position(uint64_t pos);
	void set_preset(int pr);
	char* get_preset_name(int pr);
	int get_preset_count();
	void set_filename(const String&filename);
	void set_data(const PoolVector<uint8_t> &p_data);
	PoolVector<uint8_t> get_data() const;
	void midi_load_filename(const String&filename);
	void midi_file_reading(uint8_t *b, int s);
	void note_on(int n,float v);
	void note_off(int n);
	void set_channel_pan(int chn, float pan);
	void set_channel_tuning(int chn, float tun);
	void set_channel_volume(int chn, float vol);
	void set_channel_pitchwheel(int chn, float pw);
	void set_channel_pitchrange(int chn, float pr);
	virtual Ref<AudioStreamPlayback> instance_playback();
    
	void buffer_function(float* b, int s);
	virtual String get_stream_name() const;
	virtual float get_length() const { return 0; }
	void set_file(const String &p_file) { file = p_file; }

	
protected:
	static void _bind_methods();
};

#endif 
