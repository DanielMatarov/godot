#include "sfont_loader.h"
#include "MidiStream.h"



ResourceFormatLoaderSfont::ResourceFormatLoaderSfont(){
	test = NULL;

}

ResourceFormatLoaderSfont::~ResourceFormatLoaderSfont()
{
	test = 1;
}

RES ResourceFormatLoaderSfont::load(const String &p_path, const String &p_original_path, Error *r_error) {
	MidiStream *base = memnew(MidiStream);
	if (r_error)
		*r_error = OK;
	base->set_filename(p_path);
	return Ref<MidiStream>(base);
}

void ResourceFormatLoaderSfont::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("sf2");
}

String ResourceFormatLoaderSfont::get_resource_type(const String &p_path) const {

	if (p_path.get_extension().to_lower() == "sf2")
		return "MidiStream";
	return "MidiStream";
}

bool ResourceFormatLoaderSfont::handles_type(const String &p_type) const {
	return (p_type == "MidiStream");
}


