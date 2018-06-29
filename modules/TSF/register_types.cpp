
#include "register_types.h"
#include "class_db.h"
#include "MidiStream.h"
#include "MidiStreamPlayback.h"
#include "sfont_loader.h"



void register_TSF_types() {

#ifdef TOOLS_ENABLED
	Ref<ResourceImporterSfont> sfont_import;
	sfont_import.instance();
		ResourceFormatImporter::get_singleton()->add_importer(sfont_import);
#endif     
		ClassDB::register_class<MidiStream>();
        ClassDB::register_class<MidiStreamPlayback>();
}

void unregister_TSF_types() {
	
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
