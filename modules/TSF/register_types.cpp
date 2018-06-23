
#include "register_types.h"
#include "class_db.h"
#include "MidiStream.h"
#include "MidiStreamPlayback.h"
#include "sfont_loader.h"

ResourceFormatLoaderSfont *my_sfont_loader = NULL;

void register_TSF_types() {
		
        my_sfont_loader = memnew(ResourceFormatLoaderSfont);
		ResourceLoader::add_resource_format_loader(my_sfont_loader);
		ClassDB::register_class<MidiStream>();
        ClassDB::register_class<MidiStreamPlayback>();
}

void unregister_TSF_types() {
	memdelete(my_sfont_loader);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
