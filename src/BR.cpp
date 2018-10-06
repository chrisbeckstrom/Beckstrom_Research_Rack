#include "BR.hpp"
#include "BR_components.hpp"


Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	p->addModel(modelMixer);
	p->addModel(modelHFO);
	p->addModel(modelInverter);
	p->addModel(modelVCMixer);
}
