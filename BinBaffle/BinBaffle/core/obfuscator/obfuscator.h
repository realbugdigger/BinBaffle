#pragma once

#include "../pe/pe.h"
//#include "../util/types.h"

namespace obfuscator {
	func_parser::Instance<Img> func_parser_ = {};

	template <pe::raw_image_t Img>
	void obfuscate(const Img* image);

	template <pe::raw_image_t Img>
	void setup(const Img* image);
}