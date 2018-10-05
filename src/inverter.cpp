#include "BR.hpp"

// based on Befaco's "Mixer" module
// uses some stuff from ML modules too  


struct Inverter: Module {
	enum ParamIds {
		CH1_PARAM,
		CH2_PARAM,
		CH3_PARAM,
		CH4_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		IN4_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		OUT_POS_LIGHT,
		OUT_NEG_LIGHT,
		OUT_LIGHT1,
		OUT_LIGHT2,
		OUT_LIGHT3,
		OUT_LIGHT4,
		NUM_LIGHTS
	};

	Inverter() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
};


void Inverter::step() {
	// each input is weighted to half the level of the previous one
	// not sure if that's _actually_ how real r2rs work, but it sounds pretty close
	float in1 = inputs[IN1_INPUT].value * 1;
	float in2 = inputs[IN2_INPUT].value * 1;
	float in3 = inputs[IN3_INPUT].value * 1;
	float in4 = inputs[IN4_INPUT].value * 1; 

	float out1 = in1;
	float out2 = in2;
	float out3 = in3;
	float out4 = in4;

	outputs[OUT1_OUTPUT].value = -out1;
	outputs[OUT2_OUTPUT].value = -out2;
	outputs[OUT3_OUTPUT].value = -out3;
	outputs[OUT4_OUTPUT].value = -out4;

	// lights
	lights[OUT_LIGHT1].setBrightnessSmooth(-out1 / 5.0);
	lights[OUT_LIGHT2].setBrightnessSmooth(-out2 / 5.0);
	lights[OUT_LIGHT3].setBrightnessSmooth(-out3 / 5.0);
	lights[OUT_LIGHT4].setBrightnessSmooth(-out4 / 5.0);

}


struct MixerWidget : ModuleWidget {
	MixerWidget(Inverter*module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/inverter.svg")));

		addChild(Widget::create<MLScrew>(Vec(15, 0)));
		addChild(Widget::create<MLScrew>(Vec(15, 365)));

		// WHERE WE'RE GOING, WE DON'T NEED KNOBS!
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 32), module, Mixer::CH1_PARAM, 0.0, 1.0, 0.0));
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 85), module, Mixer::CH2_PARAM, 0.0, 1.0, 0.0));
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 137), module, Mixer::CH3_PARAM, 0.0, 1.0, 0.0));
		//addParam(ParamWidget::create<Davies1900hWhiteKnob>(Vec(19, 190), module, Mixer::CH4_PARAM, 0.0, 1.0, 0.0));

		// input ports
		addInput(Port::create<MLPort>(Vec(2, 60), Port::INPUT, module, Inverter::IN1_INPUT));
		addInput(Port::create<MLPort>(Vec(2, 150), Port::INPUT, module, Inverter::IN2_INPUT));
		addInput(Port::create<MLPort>(Vec(2, 240), Port::INPUT, module, Inverter::IN3_INPUT));
		addInput(Port::create<MLPort>(Vec(2, 330), Port::INPUT, module, Inverter::IN4_INPUT));


		// output ports
		addOutput(Port::create<MLPort>(Vec(30, 60), Port::OUTPUT, module, Inverter::OUT1_OUTPUT));
		addOutput(Port::create<MLPort>(Vec(30, 150), Port::OUTPUT, module, Inverter::OUT2_OUTPUT));
		addOutput(Port::create<MLPort>(Vec(30, 240), Port::OUTPUT, module, Inverter::OUT3_OUTPUT));
		addOutput(Port::create<MLPort>(Vec(30, 330), Port::OUTPUT, module, Inverter::OUT4_OUTPUT));

		// lights
		//addChild(ModuleLightWidget::create<MediumLight<GreenRedLight>>(Vec(80, 60), module, Inverter::OUT_LIGHT1));
		//addChild(ModuleLightWidget::create<MediumLight<GreenRedLight>>(Vec(80, 100), module, Inverter::OUT_LIGHT2));
		//addChild(ModuleLightWidget::create<MediumLight<GreenRedLight>>(Vec(80, 140), module, Inverter::OUT_LIGHT3));
		//addChild(ModuleLightWidget::create<MediumLight<GreenRedLight>>(Vec(80, 180), module, Inverter::OUT_LIGHT4));
	}
};


Model *modelInverter= Model::create<Inverter, MixerWidget>("Beckstrom Research", "Analog Inverter", "Analog Inverter", MIXER_TAG);
