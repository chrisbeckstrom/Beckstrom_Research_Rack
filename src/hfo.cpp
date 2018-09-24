#include "BR.hpp"
// based on Template plugin
// uses some stuff from ML Modules too


struct MyModule : Module {
	enum ParamIds {
		PITCH_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		PITCH_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SINE_OUTPUT,
		NUM_OUTPUTS
	};
	// let's get rid of lights
	//enum LightIds {
	//	BLINK_LIGHT,
	//	NUM_LIGHTS
	//};

	float phase = 0.0;
	//float blinkPhase = 0.0;

	MyModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};


void MyModule::step() {
	// Implement a simple sine oscillator
	float deltaTime = engineGetSampleTime();

	// Compute the frequency from the pitch parameter and input
	float pitch = params[PITCH_PARAM].value;
	// CB addition: multiply by a number
	// original:
	//pitch += inputs[PITCH_INPUT].value;
	// new:
	pitch += inputs[PITCH_INPUT*1.910].value;
	pitch = clamp(pitch, -6.0f, 6.0f);
	// The default pitch is C4
	float freq = 261.626f * powf(2.0f, pitch);

	// Accumulate the phase
	phase += freq * deltaTime;
	if (phase >= 1.0f)
		phase -= 1.0f;

	// Compute the sine output
	float sine = sinf(2.0f * M_PI * phase);
	outputs[SINE_OUTPUT].value = 5.0f * sine;

	// Blink light at 1Hz
	//blinkPhase += deltaTime;
	//if (blinkPhase >= 1.0f)
	//	blinkPhase -= 1.0f;
	//lights[BLINK_LIGHT].value = (blinkPhase < 0.5f) ? 1.0f : 0.0f;
}


struct MyModuleWidget : ModuleWidget {
	MyModuleWidget(MyModule *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/CBhfo.svg")));

		addChild(Widget::create<MLScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<MLScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<MLScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(Widget::create<MLScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(28, 87), module, MyModule::PITCH_PARAM, -9.0, 9.0, 0.0));

		addInput(Port::create<MLPort>(Vec(33, 186), Port::INPUT, module, MyModule::PITCH_INPUT));

		addOutput(Port::create<MLPort>(Vec(33, 275), Port::OUTPUT, module, MyModule::SINE_OUTPUT));

		//addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(41, 59), module, MyModule::BLINK_LIGHT));
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelMyModule = Model::create<MyModule, MyModuleWidget>("Beckstrom Research", "HFO", "High Frequency Oscillator", OSCILLATOR_TAG);
