#include "tsf.h"
#include "reference.h"
#include "resource.h"
#include "servers/audio/audio_stream.h"
#include "MidiStream.h"
#define TSF_IMPLEMENTATION


MidiStream::MidiStream()

	: stereo(true), sample_rate(44100), 
