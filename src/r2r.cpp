#include "BR.hpp"

// based on Befaco's "Mixer" module
// uses some stuff from ML modules too  


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
	// not sure if that's _actually_ how real r2rs work, but it sounds pretty close
	float in1 = inputs[IN1_INPUT].value * 0.5;
	float in2 = inputs[IN2_INPUT].value * 0.25;
	float in3 = inputs[IN3_INPUT].value * 0.125;
	float in4 = inputs[IN4_INPUT].value * 0.0625;
	float in5 = inputs[IN5_INPUT].value * 0.0315;
	float in6 = inputs[IN6_INPUT].value * 0.015625;

	// combine everything into one
	float out = in1 + in2 + in3 + in4 + in5 + in6;
	outputs[OUT1_OUTPUT].value = out;
	outputs[OUT2_OUTPUT].value = -out;
	lights[OUT_POS_LIGHT].setBrightnessSmooth(out / 5.0);
	lights[OUT_NEG_LIGHT].setBrightnessSmooth(-out / 5.0);
}


struct MixerWidget : ModuleWidget {
	MixerWidget(Mixer *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/r2r.svg")));

		addChild(Widget::create<MLScrew>(Vec(15, 0)));
		addChild(Widget::create<MLScrew>(Vec(15, 365)));

		// WHERE WE'RE GOING, WE DON'T NEED KNOBS!
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 32), module, Mixer::CH1_PARAM, 0.0, 1.0, 0.0));
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 85), module, Mixer::CH2_PARAM, 0.0, 1.0, 0.0));
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 137), module, Mixer::CH3_PARAM, 0.0, 1.0, 0.0));
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 190), module, Mixer::CH4_PARAM, 0.0, 1.0, 0.0));

		// input ports
		addInput(Port::create<MLPort>(Vec(7, 60), Port::INPUT, module, Mixer::IN1_INPUT));
		addInput(Port::create<MLPort>(Vec(7, 100), Port::INPUT, module, Mixer::IN2_INPUT));
		addInput(Port::create<MLPort>(Vec(7, 140), Port::INPUT, module, Mixer::IN3_INPUT));
		addInput(Port::create<MLPort>(Vec(7, 180), Port::INPUT, module, Mixer::IN4_INPUT));
		addInput(Port::create<MLPort>(Vec(7, 220), Port::INPUT, module, Mixer::IN5_INPUT));
		addInput(Port::create<MLPort>(Vec(7, 260), Port::INPUT, module, Mixer::IN6_INPUT));


		// output ports
		addOutput(Port::create<MLPort>(Vec(7, 320), Port::OUTPUT, module, Mixer::OUT1_OUTPUT));
		addOutput(Port::create<MLPort>(Vec(43, 320), Port::OUTPUT, module, Mixer::OUT2_OUTPUT));

		addChild(ModuleLightWidget::create<MediumLight<GreenRedLight>>(Vec(32.7, 300), module, Mixer::OUT_POS_LIGHT));
	}
};


Model *modelMixer = Model::create<Mixer, MixerWidget>("Beckstrom Research", "R2R Ladder", "R2R Ladder", MIXER_TAG);
