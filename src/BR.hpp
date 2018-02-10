#include "rack.hpp"

// in template, this file is called "Template.hpp"


using namespace rack;


extern Plugin *plugin;

struct Knurlie : SVGScrew {
	Knurlie() {
		sw->svg = SVG::load(assetPlugin(plugin, "res/Knurlie.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

////////////////////
// module widgets
////////////////////

struct MyModuleWidget : ModuleWidget {
	MyModuleWidget();
};

// copied from Befaco
struct MixerWidget : ModuleWidget {
	MixerWidget();
};
