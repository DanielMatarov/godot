#ifndef SFONT_LOADER_H
#define SFONT_LOADER_H

#include "io/resource_loader.h"

class ResourceFormatLoaderSfont : public ResourceFormatLoader {
public:
	virtual RES load(const String &p_path, const String &p_original_path, Error *r_error);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;

	ResourceFormatLoaderSfont();
	virtual ~ResourceFormatLoaderSfont();
	int test;
	
};

#endif
