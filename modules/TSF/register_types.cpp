
#include "register_types.h"
#include "class_db.h"
#include "MidiStream.h"
#include "MidiStreamPlayback.h"

void register_summator_types() {

        ClassDB::register_class<MidiStream>();
        ClassDB::register_class<MidiStreamPlayback>();
}

void unregister_summator_types() {
   //nothing to do here
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        