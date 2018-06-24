#include "sfont_loader.h"
#include "MidiStream.h"

ResourceFormatLoaderSfont::ResourceFormatLoaderSfont(){


}

ResourceFormatLoaderSfont::~ResourceFormatLoaderSfont()
{}

RES ResourceFormatLoaderSfont::load(const String &p_path, const String &p_original_path, Error *r_error) {
	MidiStream *base = memnew(MidiStream);
	if (r_error)
		*r_error = OK;
	base->set_filename(p_path);
	return Ref<MidiStream>(base);
}

void ResourceFormatLoaderSfont::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("Sfont");
}

String ResourceFormatLoaderSfont::get_resource_type(const String &p_path) const {

	if (p_path.get_extension().to_lower() == "sfont")
		return "sfont";
	return "";
}

bool ResourceFormatLoaderSfont::handles_type(const String &p_type) const {
	return (p_type == "Sfont");
}


