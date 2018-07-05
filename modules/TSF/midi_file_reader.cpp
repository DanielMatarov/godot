#define TSF_IMPLEMENTATION
#define TML_IMPLEMENTATION
#include "midi_file_reader.h"
#include "MidiStream.h"


MidiFileReader::MidiFileReader() {
	pointer = NULL;
	
	data = NULL;
	data_len = 0;
}

void MidiFileReader::clear_data() {
	if (data) {
		AudioServer::get_singleton()->audio_data_free(data);
		data = NULL;
		data_len = 0;

	}
}

void MidiFileReader::set_data(const PoolVector<uint8_t> &p_data) {
	clear_data();

	data_len = p_data.size();
	data = AudioServer::get_singleton()->audio_data_alloc(data_len, p_data.read().ptr());

	pointer = tml_load_memory(data, data_len);
}

PoolVector<uint8_t> MidiFileReader::get_data() const {

	PoolVector<uint8_t> vdata;

	if (data_len && data) {
		vdata.resize(data_len);
		{
			PoolVector<uint8_t>::Write w = vdata.write();
			copymem(w.ptr(), data, data_len);
		}

	}

	return vdata;
}
