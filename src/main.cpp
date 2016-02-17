#include "LCSS.h"

using namespace std;

extern "C" {
	PHPCPP_EXPORT void* get_module() {
		static Php::Extension extension(LCSS_EXTNAME, LCSS_EXTVERSION);
		Php::Class<LCSS> lcss("LCSS");
		lcss.method("__construct", &LCSS::__construct);
		lcss.method("findSimilarity", &LCSS::findSimilarity,{
			Php::ByRef("trajectory1Lat", Php::Type::Array, true),
			Php::ByRef("trajectory1Lng", Php::Type::Array, true),
			Php::ByRef("trajectory2Lat", Php::Type::Array, true),
			Php::ByRef("trajectory2Lng", Php::Type::Array, true)
		});
		// lcss.method('findSimilarity', &LCSS::findSimilarity);
		extension.add(move(lcss));
		return extension;
	}
}
