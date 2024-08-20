#include "obfuscator.h"

namespace obfuscator {
	template <pe::raw_image_t Img>
	void obfuscate(const Img* image) {
		setup();
	}

    template <pe::raw_image_t Img>
	void setup(const Img* image) {
        
        func_parser_.collect_functions();

        // Add functions from config, that we should protecc
        //
        auto analysis_progress = util::Progress("obfuscator: setting up functions", config_.size());
        for (auto& configuration : config_) {
            add_function(configuration);
            analysis_progress.step();
        }

        // Enable transforms from global config
        //
        auto& scheduler = TransformScheduler::get();
        for (auto& [tag, _] : config_.global_transforms_config()) {
            scheduler.enable_transform(tag);
        }
	}
}