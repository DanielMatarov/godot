#ifndef SFONT_H
#define SFONT_H

#include "core/variant.h"
#include "reference.h"
#include "variant_parser.h"
#include "io/json.h"
#include "dictionary.h"

class Sfont : public Resource {
	GDCLASS(Sfont, Resource);

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("toString"), &Sfont::toString);
	}
private:
	Dictionary dict;
public:
	Error set_file(const String &p_path) {
		Error error_file;
		FileAccess *file = FileAccess::open(p_path, FileAccess::READ, &error_file);

		String buf = String("");
		while (!file->eof_reached()) {
			buf += file->get_line();
		}
		String err_string;
		int err_line;
		JSON cmd;
		Variant ret;
		Error err = cmd.parse(buf, ret, err_string, err_line);
		dict = Dictionary(ret);
		file->close();
		return OK;
	}
	String toString() const {
		return String(*this);
	}

	operator String() const {
		JSON a;
		return a.print(dict);
	}
	Sfont() {};
	~Sfont() {};
};


#endif 
