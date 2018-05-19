#include "tsf.h"

#include "servers/audio/audio_stream.h"
#include "MidiStream.h"
#define TSF_IMPLEMENTATION


MidiStream::MidiStream(){
	sample_rate=44100;
	note = 50;
	vel = 50;
	sf_filename = "florestan-subset.sf2";
}


Ref<AudioStreamPlayback> MidiStream::instance_playback() {
	Ref<MidiStreamPlayback> talking_tree;
	talking_tree.instance();
	talking_tree->base = Ref<MidiStream>(this);
	return talking_tree;
}

void MidiStream::set_filename(char* filename) {
	filename = sf_filename;
	tsf_load_filename(filename);

}

void MidiStream::buffer_function(float* b){
	 b = buffer;
}

void MidiStream::set_output(enum TSFOutputMode outputmode, int samplerate, float global_gain_db) {
	samplerate = sample_rate;
	global_gain_db = gain;
	tsf_set_output(TSFpointer, TSF_STEREO_INTERLEAVED, sample_rate, gain);
}

void MidiStream::note_on(int n, int v)
{
	n = note;
	v = vel;
	tsf_note_on(TSFpointer, 0, n, v);
}


