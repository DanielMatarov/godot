
#include "MidiStreamPlayback.h"
#include "MidiStream.h"
#include "math/math_funcs.h"
#include "print_string.h"



MidiStreamPlayback::MidiStreamPlayback()
		: active(false) {
		AudioServer::get_singleton()->lock();
		pcm_buffer = AudioServer::get_singleton()->audio_data_alloc(PCM_BUFFER_SIZE*sizeof(float)*2);
		zeromem(pcm_buffer, PCM_BUFFER_SIZE);
		AudioServer::get_singleton()->unlock();
	}

MidiStreamPlayback::~MidiStreamPlayback() {
	if (pcm_buffer) {
		AudioServer::get_singleton()->audio_data_free(pcm_buffer);
		pcm_buffer = NULL;
	}
}

void MidiStreamPlayback::stop() {
	active = false;
	base->reset();
}

void MidiStreamPlayback::start(float p_from_pos) {
	seek(p_from_pos);
	active = true;
}

void MidiStreamPlayback::seek(float p_time) {
	float max = get_length();
	if (p_time < 0) {
		p_time = 0;
	}
	base->set_position(uint64_t(p_time * base->sample_rate) << MIX_FRAC_BITS);
}

void MidiStreamPlayback::mix(AudioFrame *p_buffer, float p_rate, int p_frames) {
	ERR_FAIL_COND(!active);
	if (!active) {
		return;
	}
	float *buf = (float *)pcm_buffer;
	base->buffer_function(buf, MAX(PCM_BUFFER_SIZE, p_frames));

	for (int i = 0, j = 0; i < p_frames; i++) {
		p_buffer[i] = AudioFrame(buf[i / 2 + 0], buf[i / 2 + 1]);
	}
}

int MidiStreamPlayback::get_loop_count() const {
	return 0;
}

float MidiStreamPlayback::get_playback_position() const {
	return 0.0;
}

float MidiStreamPlayback::get_length() const {
	return 0.0;
}

bool MidiStreamPlayback::is_playing() const {
	return active;
}
