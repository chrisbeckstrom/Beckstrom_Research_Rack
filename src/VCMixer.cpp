#include "BR.hpp"
// based on the Fundamental "VCMixer" module


struct VCMixer : Module {
	enum ParamIds {
		MIX_LVL_PARAM,
		ENUMS(LVL_PARAM, 16),
		NUM_PARAMS
	};
	enum InputIds {
		MIX_CV_INPUT,
		//ENUMS(CH_INPUT, 4),
		CH_INPUT1,
		CH_INPUT2,
		CH_INPUT3,
		CH_INPUT4,
		ENUMS(CV_INPUT, 16),
		NUM_INPUTS
	};
	enum OutputIds {
		MIX_OUTPUT,
		ENUMS(CH_OUTPUT, 4),
		NUM_OUTPUTS
	};

	VCMixer() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}

	void step() override {
		float mix = 0.f;


		// signal inputs
		float in1 = inputs[CH_INPUT1].value;
		float in2 = inputs[CH_INPUT2].value;
		float in3 = inputs[CH_INPUT3].value;
		float in4 = inputs[CH_INPUT4].value;

		float cv1a = inputs[CV_INPUT1].value;

		// cv inputs
		CH_OUTPUT1 = in1 * LVL_PARAM1;


		for (int i = 0; i < 4; i++) {
			float ch = inputs[CH_INPUT + i].value;
			ch *= powf(params[LVL_PARAM + i].value, 2.f);

			if (inputs[CV_INPUT + i].active)
				ch *= clamp(inputs[CV_INPUT + i].value / 10.f, 0.f, 1.f);
			outputs[CH_OUTPUT + i].value = ch;
			mix += ch;
		}
		mix *= params[MIX_LVL_PARAM].value;

		if (inputs[MIX_CV_INPUT].active)
			mix *= clamp(inputs[MIX_CV_INPUT].value / 10.f, 0.f, 1.f);
		outputs[MIX_OUTPUT].value = mix;
	}
};


struct VCMixerWidget : ModuleWidget {
	VCMixerWidget(VCMixer *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/VCMixer.svg")));


		// screws
		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// large black knob - master output
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(19.049999, 21.161154)), module, VCMixer::MIX_LVL_PARAM, 0.0, 2.0, 1.0));
		

		// 4 columns of cv inputs
		// first column:  3.2935
		// second: 15.2934
		// third: 27.29346
		// fourth: 39.29341
		//
		// 5 rows total
		// first row: ?
		// second row: ?
		// third row: 78.5316 
		// bottom (outputs): 44.33145

		// KNOBS
		// knobs vertical location is input port location -2
		// first row
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(13.899343, 42.33149)), module, VCMixer::LVL_PARAM + 0, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(25.899282, 42.331486)), module, VCMixer::LVL_PARAM + 1, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(38.09965, 42.331486)), module, VCMixer::LVL_PARAM + 2, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(49.2112, 42.331486)), module, VCMixer::LVL_PARAM + 3, 0.0, 1.0, 1.0));

		//second row
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(13.899343, 54.531639)), module, VCMixer::LVL_PARAM + 0, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(25.899282, 54.531639)), module, VCMixer::LVL_PARAM + 1, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(38.09965, 54.531639)), module, VCMixer::LVL_PARAM + 2, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(49.2112, 54.531639)), module, VCMixer::LVL_PARAM + 3, 0.0, 1.0, 1.0));

		//third row
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(13.899343, 66.531639 )), module, VCMixer::LVL_PARAM + 0, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(25.899282, 66.531639 )), module, VCMixer::LVL_PARAM + 1, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(38.09965, 66.531639 )), module, VCMixer::LVL_PARAM + 2, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(49.2112, 66.531639 )), module, VCMixer::LVL_PARAM + 3, 0.0, 1.0, 1.0));

		//fourth row
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(13.899343, 78.531639 )), module, VCMixer::LVL_PARAM + 0, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(25.899282, 78.531639)), module, VCMixer::LVL_PARAM + 1, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(38.09965, 78.531639)), module, VCMixer::LVL_PARAM + 2, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(49.2112, 78.531639)), module, VCMixer::LVL_PARAM + 3, 0.0, 1.0, 1.0));
		//
		//
		// Use old interleaved order for backward compatibility with <0.6
		///// PORTS
		// master mix cv input
		addInput(Port::create<PJ301MPort>(mm2px(Vec(3.2935331, 23.404598)), Port::INPUT, module, VCMixer::MIX_CV_INPUT));

		// signal inputs
		addInput(Port::create<MLPort>(mm2px(Vec(3.2935, 44.33149)), Port::INPUT, module, VCMixer::CH_INPUT + 0));
		addInput(Port::create<MLPort>(mm2px(Vec(3.2935, 56.531639)), Port::INPUT, module, VCMixer::CH_INPUT + 1));
		addInput(Port::create<MLPort>(mm2px(Vec(3.2935, 68.531639)), Port::INPUT, module, VCMixer::CH_INPUT + 2));
		addInput(Port::create<MLPort>(mm2px(Vec(3.2935, 80.531639)), Port::INPUT, module, VCMixer::CH_INPUT + 3));

		// modulation (CV) inputs
		//
		// first row
		addInput(Port::create<PJ301MPort>(mm2px(Vec(61, 44.33149)), Port::INPUT, module, VCMixer::CV_INPUT + 1));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(73, 44.33149)), Port::INPUT, module, VCMixer::CV_INPUT + 2));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(85, 44.33149)), Port::INPUT, module, VCMixer::CV_INPUT + 3));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(97, 44.33149)), Port::INPUT, module, VCMixer::CV_INPUT + 4));

		// outputs
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(39.293411, 23.4046)), Port::OUTPUT, module, VCMixer::MIX_OUTPUT));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(3.2935331, 108.53153)), Port::OUTPUT, module, VCMixer::CH_OUTPUT + 0));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(15.29348, 108.53153)), Port::OUTPUT, module, VCMixer::CH_OUTPUT + 1));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(27.293465, 108.53153)), Port::OUTPUT, module, VCMixer::CH_OUTPUT + 2));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(39.293411, 108.53153)), Port::OUTPUT, module, VCMixer::CH_OUTPUT + 3));
	}
};


Model *modelVCMixer = Model::create<VCMixer, VCMixerWidget>("Beckstrom Research", "Matrix Mixer", "Mixer", MIXER_TAG, AMPLIFIER_TAG);
