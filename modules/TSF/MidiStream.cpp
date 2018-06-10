#define TSF_IMPLEMENTATION
#define TML_IMPLEMENTATION
#include "servers/audio/audio_stream.h"
#include "MidiStream.h"
#include "MidiStreamPlayback.h"
#include "tml.h"

tml_message* midi_pointer;

MidiStream::MidiStream(){
	sample_rate=44100;
	tsf_pointer = NULL;
	gain = 0;
}


Ref<AudioStreamPlayback> MidiStream::instance_playback() {
	Ref<MidiStreamPlayback> talking_tree;
	talking_tree.instance();
	talking_tree->base = Ref<MidiStream>(this);
	return talking_tree;
}

void MidiStream::set_position(uint64_t p) {
	pos = p;
}

void MidiStream::set_filename(const String&filename) {
	tsf_pointer = tsf_load_filename(filename.utf8().get_data());
	if (tsf_pointer){
		tsf_set_output(tsf_pointer, TSF_STEREO_INTERLEAVED, sample_rate, gain);
	}
	else{
		printf("error loading file");
	}
	
}

void MidiStream::buffer_function(float* b, int s){
	if (tsf_pointer == NULL) {
		return;
	}
	else{
		tsf_render_float(tsf_pointer, b, s, 0);
	}
	
}


void MidiStream::note_on(int n, float v)
{
	tsf_note_on(tsf_pointer, preset, n, v);
}

void MidiStream::reset() {
	set_position(0);
}

void MidiStream::set_preset(int pr)
{
	preset = pr;
}


void MidiStream::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_filename", "filename"), &MidiStream::set_filename);
	ClassDB::bind_method(D_METHOD("set_midi_filename", "filename"), &MidiStream::midi_load_filename);
	ClassDB::bind_method(D_METHOD("get_stream_name"), &MidiStream::get_stream_name);
	ClassDB::bind_method(D_METHOD("note_on", "note", "velocity"), &MidiStream::note_on);
	ClassDB::bind_method(D_METHOD("set_preset","preset"), &MidiStream::set_preset);
}


String MidiStream::get_stream_name() const {
	return "MidiStream";
}


void MidiStream::midi_load_filename(const String&filename)
{
	midi_pointer = tml_load_filename(filename.utf8().get_data());
}

void MidiStream::midi_file_reading(float* b, int s) {

	int sampleBlock, sampleCount = (s / (2 * sizeof(float)));
	for (sampleBlock = TSF_RENDER_EFFECTSAMPLEBLOCK; sampleCount; sampleCount -= sampleBlock, b += (sampleBlock * (2 * sizeof(float)))) {

		if (sampleBlock > sampleCount) sampleBlock = sampleCount;

		for (midi_pb_time += sampleBlock * (1000.0 / 44100.0); midi_pointer && midi_pb_time >= midi_pointer->time; midi_pointer = midi_pointer->next)
		{
			switch (midi_pointer->type)
			{
				case TML_NOTE_ON:
					tsf_channel_note_on(tsf_pointer, midi_pointer->channel, midi_pointer->key, midi_pointer->velocity / 127.0f);
					break;
				case TML_NOTE_OFF:
					tsf_channel_note_off(tsf_pointer, midi_pointer->channel, midi_pointer->key);
					break;
				case TML_PITCH_BEND:
					tsf_channel_set_pitchwheel(tsf_pointer, midi_pointer->channel, midi_pointer->pitch_bend);
					break;
				case TML_CONTROL_CHANGE:
					tsf_channel_midi_control(tsf_pointer, midi_pointer->channel, midi_pointer->control, midi_pointer->control_value);
					break;
			}
		}
		tsf_set_output(tsf_pointer, TSF_STEREO_INTERLEAVED, sample_rate, gain);
		buffer_function(b, sampleBlock);
	}

}
