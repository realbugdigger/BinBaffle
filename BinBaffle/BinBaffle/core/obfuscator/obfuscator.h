#pragma once

#include "../pe/pe.h"
//#include "../util/types.h"

namespace obfuscator {
	template <pe::raw_image_t Img>
	void binbaffle(const Img* image);
	
	template <pe::raw_image_t Img>
	void obfuscate(const Img* image);

	template <pe::raw_image_t Img>
	void setup(const Img* image);
	
	// check this out
	template <pe::raw_image_t Img>
	void save(const Img* image);
}