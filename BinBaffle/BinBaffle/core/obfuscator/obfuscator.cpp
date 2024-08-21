#include "obfuscator.h"

namespace obfuscator {
    template <pe::raw_image_t Img>
    void binbaffle(const Img* image) {
        setup();
        obfuscate();
        assemble();
        save();
    }

	template <pe::raw_image_t Img>
	void obfuscate(const Img* image) {
		
	}
    
    template <pe::raw_image_t Img>
	void save(const Img* image) {
        auto new_img = image_->rebuild_pe_image();

        auto out_path = config_.obfuscator_config().binary_path;

        auto filename = out_path.filename();
        const auto file_ext = filename.extension().string();
        const auto filename_no_ext = filename.replace_extension().string();

        const auto new_filename = filename_no_ext + ".protected" + file_ext;

        out_path = out_path.replace_filename(new_filename);
        util::write_file(out_path, new_img.data(), new_img.size());
	}

    template <pe::raw_image_t Img>
	void setup(const Img* image) {
        
        func_parser_.collect_functions();

        // Add functions from config, that we should protect
        auto analysis_progress = util::Progress("obfuscator: setting up functions", config_.size());
        for (auto& configuration : config_) {
            add_function(configuration);
            analysis_progress.step();
        }

        // Enable transforms from global config
        auto& scheduler = TransformScheduler::get();
        for (auto& [tag, _] : config_.global_transforms_config()) {
            scheduler.enable_transform(tag);
        }
	}
}