#ifndef MIDIFILEREADER_H
#define	MIDIFILEREADER_H

#include "MidiStream.h"
#include "reference.h"
#include "resource.h"


class MidiFileReader : public Resource {
	GDCLASS(MidiFileReader, Resource)
	OBJ_SAVE_TYPE(Resource)
	RES_BASE_EXTENSION("midistr")
	String file;
	
	double midi_pb_time;
	void *data;
	uint32_t data_len;
	void clear_data();
public:
	MidiFileReader();
	tml_message* pointer;
	void set_data(const PoolVector<uint8_t> &p_data);
	PoolVector<uint8_t> get_data() const;

protected:
	void _bind_methods();
};

#endif
