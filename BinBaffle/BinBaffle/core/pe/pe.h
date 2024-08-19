#pragma once

#include <Windows.h>
#include <string>

#include "../../external/zasm/base/mode.hpp"
#include "../../external/linux_pe/nt/image.hpp"

#include "../util/types.h"

namespace pe {
	/// Concept for raw images from linux-pe, could also probably check for `win::image_t`
	template <typename Ty> concept raw_image_t = types::is_any_of_v<Ty, win::image_x86_t, win::image_x64_t>;

	class PE_Image {

	};

	bool ReadPeFile(std::string& file, PBYTE* pPe, size_t* sPe);
	void ParsePe(PBYTE pPE);

	template <raw_image_t Img>
	bool isValid(Img* image);

	template <raw_image_t Img>
	bool isX64(const Img* image);
}