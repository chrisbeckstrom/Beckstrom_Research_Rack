#include "BR.hpp"

// based on Befaco's "Mixer" module

struct Mixer : Module {
	enum ParamIds {
		CH1_PARAM,
		CH2_PARAM,
		CH3_PARAM,
		CH4_PARAM,
		CH5_PARAM,
		CH6_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		IN4_INPUT,
		IN5_INPUT,
		IN6_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		OUT_POS_LIGHT,
		OUT_NEG_LIGHT,
		NUM_LIGHTS
	};

	Mixer() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
};


void Mixer::step() {
	// each input is weighted to half the level of the previous one
	// not sure if that's actually how real r/2r's work but it sounds pretty close
	float in1 = inputs[IN1_INPUT].value * 0.5;
	float in2 = inputs[IN2_INPUT].value * 0.25;
	float in3 = inputs[IN3_INPUT].value * 0.125;
	float in4 = inputs[IN4_INPUT].value * 0.0625; 
	float in5 = inputs[IN5_INPUT].value * 0.03125; 
	float in6 = inputs[IN6_INPUT].value * 0.015625; 

	float out = in1 + in2 + in3 + in4 + in5 + in6;
	outputs[OUT1_OUTPUT].value = out;
	outputs[OUT2_OUTPUT].value = -out;
	lights[OUT_POS_LIGHT].setBrightnessSmooth(out / 5.0);
	lights[OUT_NEG_LIGHT].setBrightnessSmooth(-out / 5.0);
}


MixerWidget::MixerWidget() {
	Mixer *module = new Mixer();
	setModule(module);
	box.size = Vec(15*5, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/r2r.svg")));
		addChild(panel);
	}

	addChild(createScrew<Knurlie>(Vec(15, 0)));
	addChild(createScrew<Knurlie>(Vec(15, 365)));

	//addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 32), module, Mixer::CH1_PARAM, 0.0, 1.0, 0.0));
	//addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 85), module, Mixer::CH2_PARAM, 0.0, 1.0, 0.0));
	//addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 137), module, Mixer::CH3_PARAM, 0.0, 1.0, 0.0));
	//addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 190), module, Mixer::CH4_PARAM, 0.0, 1.0, 0.0));


	// input ports
	addInput(createInput<PJ301MPort>(Vec(7, 60), module, Mixer::IN1_INPUT));
	addInput(createInput<PJ301MPort>(Vec(7, 100), module, Mixer::IN2_INPUT));
	addInput(createInput<PJ301MPort>(Vec(7, 140), module, Mixer::IN3_INPUT));
	addInput(createInput<PJ301MPort>(Vec(7, 180), module, Mixer::IN4_INPUT));
	addInput(createInput<PJ301MPort>(Vec(7, 220), module, Mixer::IN5_INPUT));
	addInput(createInput<PJ301MPort>(Vec(7, 260), module, Mixer::IN6_INPUT));


	// output ports
	addOutput(createOutput<PJ301MPort>(Vec(7, 320), module, Mixer::OUT1_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(43, 320), module, Mixer::OUT2_OUTPUT));

	addChild(createLight<MediumLight<GreenRedLight>>(Vec(32.7, 300), module, Mixer::OUT_POS_LIGHT));
}
