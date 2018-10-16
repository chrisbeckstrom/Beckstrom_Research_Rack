#include "BR.hpp"
// based on Fundamental VCMixer


struct VCMixer : Module {
	enum ParamIds {
		MIX_LVL1_PARAM,
		ENUMS(LVL1_PARAM, 4),
		MIX_LVL2_PARAM,
		ENUMS(LVL2_PARAM, 4),
		MIX_LVL3_PARAM,
		ENUMS(LVL3_PARAM, 4),
		MIX_LVL4_PARAM,
		ENUMS(LVL4_PARAM, 4),
		MIX_LVL5_PARAM,
		ENUMS(LVL5_PARAM, 4),
		NUM_PARAMS
	};
	enum InputIds {
		MIX_CV_INPUT1,
		MIX_CV_INPUT2,
		MIX_CV_INPUT3,
		MIX_CV_INPUT4,
		MIX_CV_INPUT5,
		ENUMS(CH_INPUT, 4),
		ENUMS(CV_INPUT1, 4),
		ENUMS(CV_INPUT2, 4),
		ENUMS(CV_INPUT3, 4),
		ENUMS(CV_INPUT4, 4),
		ENUMS(CV_INPUT5, 4),
		NUM_INPUTS
	};
	enum OutputIds {
		MIX_OUTPUT1,
		MIX_OUTPUT2,
		MIX_OUTPUT3,
		MIX_OUTPUT4,
		MIX_OUTPUT5,
		ENUMS(CH_OUTPUT1, 4),
		ENUMS(CH_OUTPUT2, 4),
		ENUMS(CH_OUTPUT3, 4),
		ENUMS(CH_OUTPUT4, 4),
		ENUMS(CH_OUTPUT5, 4),
		NUM_OUTPUTS
	};

	VCMixer() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}

	void step() override {

		// for the first row 
		float mix1 = 0.f;
		for (int i = 0; i < 4; i++) {
			float ch = inputs[CH_INPUT + i].value;
			ch *= powf(params[LVL1_PARAM + i].value, 2.f);
			if (inputs[CV_INPUT1 + i].active)
				ch *= clamp(inputs[CV_INPUT1 + i].value / 10.f, 0.f, 1.f);
			mix1 += ch;
		}
		mix1 *= params[MIX_LVL1_PARAM].value;
		if (inputs[MIX_CV_INPUT1].active)
			mix1 *= clamp(inputs[MIX_CV_INPUT1].value / 10.f, 0.f, 1.f);
		outputs[MIX_OUTPUT1].value = mix1;
		
		// for the second row 
		float mix2 = 0.f;
		for (int i = 0; i < 4; i++) {
			float ch = inputs[CH_INPUT + i].value;
			ch *= powf(params[LVL2_PARAM + i].value, 2.f);
			if (inputs[CV_INPUT2 + i].active)
				ch *= clamp(inputs[CV_INPUT2 + i].value / 10.f, 0.f, 1.f);
			mix2 += ch;
		}
		mix2 *= params[MIX_LVL2_PARAM].value;
		if (inputs[MIX_CV_INPUT2].active)
			mix2 *= clamp(inputs[MIX_CV_INPUT2].value / 10.f, 0.f, 1.f);
		outputs[MIX_OUTPUT2].value = mix2;

		// for the third row
		float mix3 = 0.f;
		for (int i = 0; i < 4; i++) {
			float ch = inputs[CH_INPUT + i].value;
			ch *= powf(params[LVL3_PARAM + i].value, 2.f);
			if (inputs[CV_INPUT3 + i].active)
				ch *= clamp(inputs[CV_INPUT3 + i].value / 10.f, 0.f, 1.f);
			mix3 += ch;
		}
		mix3 *= params[MIX_LVL3_PARAM].value;
		if (inputs[MIX_CV_INPUT3].active)
			mix3 *= clamp(inputs[MIX_CV_INPUT3].value / 10.f, 0.f, 1.f);
		outputs[MIX_OUTPUT3].value = mix3;

		// for the fourth row
		float mix4 = 0.f;
		for (int i = 0; i < 4; i++) {
			float ch = inputs[CH_INPUT + i].value;
			ch *= powf(params[LVL4_PARAM + i].value, 2.f);
			if (inputs[CV_INPUT4 + i].active)
				ch *= clamp(inputs[CV_INPUT4 + i].value / 10.f, 0.f, 1.f);
			mix4 += ch;
		}
		mix4 *= params[MIX_LVL4_PARAM].value;
		if (inputs[MIX_CV_INPUT4].active)
			mix4 *= clamp(inputs[MIX_CV_INPUT4].value / 10.f, 0.f, 1.f);
		outputs[MIX_OUTPUT4].value = mix4;

		// for the fifth row
		float mix5 = 0.f;
		for (int i = 0; i < 4; i++) {
			float ch = inputs[CH_INPUT + i].value;
			ch *= powf(params[LVL5_PARAM + i].value, 2.f);
			if (inputs[CV_INPUT5 + i].active)
				ch *= clamp(inputs[CV_INPUT5 + i].value / 10.f, 0.f, 1.f);
			mix5 += ch;
		}
		mix5 *= params[MIX_LVL5_PARAM].value;
		if (inputs[MIX_CV_INPUT5].active)
			mix5 *= clamp(inputs[MIX_CV_INPUT5].value / 10.f, 0.f, 1.f);
		outputs[MIX_OUTPUT5].value = mix5;
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

		// input ports - inputs 1 - 4
		addInput(Port::create<PJ301MPort>(mm2px(Vec(5.898988, 10.531639)), Port::INPUT, module, VCMixer::CH_INPUT + 0));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(21.899928, 10.531639)), Port::INPUT, module, VCMixer::CH_INPUT + 1));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(37.982392, 10.531639)), Port::INPUT, module, VCMixer::CH_INPUT + 2));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(53.989882, 10.531639)), Port::INPUT, module, VCMixer::CH_INPUT + 3));


		// mixer - channel 1
		//
		// knobs
		// ///// channel levels
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(5.8993969, 26.33149).plus(Vec(-2, 0))), module, VCMixer::LVL1_PARAM + 0, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(21.899343, 26.331486).plus(Vec(-2, 0))), module, VCMixer::LVL1_PARAM + 1, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(37.899292, 26.331486).plus(Vec(-2, 0))), module, VCMixer::LVL1_PARAM + 2, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(53.90065, 26.331486).plus(Vec(-2, 0))), module, VCMixer::LVL1_PARAM + 3, 0.0, 1.0, 0.0));
		// cv control ports
		addInput(Port::create<PJ301MPort>(mm2px(Vec(69.2935331, 28.331486)), Port::INPUT, module, VCMixer::CV_INPUT1 + 0));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(85.29348, 28.331486)), Port::INPUT, module, VCMixer::CV_INPUT1 + 1));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(101.293465, 28.331486)), Port::INPUT, module, VCMixer::CV_INPUT1 + 2));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(117.293411, 28.331486)), Port::INPUT, module, VCMixer::CV_INPUT1 + 3));
		// output cv input port
		addInput(Port::create<PJ301MPort>(mm2px(Vec(133.2935331, 28.331486)), Port::INPUT, module, VCMixer::MIX_CV_INPUT1));
		// ///// master level  knob
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(149.049999, 26.331486)), module, VCMixer::MIX_LVL1_PARAM, 0.0, 2.0, 1.0));
		// output port
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(165.293411, 28.331486)), Port::OUTPUT, module, VCMixer::MIX_OUTPUT1));


		// mixer - channel 2
		//
		// knobs
		// ///// channel levels
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(5.8993969, 42.33149).plus(Vec(-2, 0))), module, VCMixer::LVL2_PARAM + 0, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(21.899343, 42.331486).plus(Vec(-2, 0))), module, VCMixer::LVL2_PARAM + 1, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(37.899292, 42.331486).plus(Vec(-2, 0))), module, VCMixer::LVL2_PARAM + 2, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(53.90065, 42.331486).plus(Vec(-2, 0))), module, VCMixer::LVL2_PARAM + 3, 0.0, 1.0, 0.0));
		// cv control ports
		addInput(Port::create<PJ301MPort>(mm2px(Vec(69.2935331, 44.331486)), Port::INPUT, module, VCMixer::CV_INPUT2 + 0));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(85.29348, 44.331486)), Port::INPUT, module, VCMixer::CV_INPUT2 + 1));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(101.293465, 44.331486)), Port::INPUT, module, VCMixer::CV_INPUT2 + 2));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(117.293411, 44.331486)), Port::INPUT, module, VCMixer::CV_INPUT2 + 3));
		// output cv input port
		addInput(Port::create<PJ301MPort>(mm2px(Vec(133.2935331, 44.331486)), Port::INPUT, module, VCMixer::MIX_CV_INPUT2));
		// ///// master level  knob
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(149.049999, 42.331486)), module, VCMixer::MIX_LVL2_PARAM, 0.0, 2.0, 1.0));
		// output port
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(165.293411, 44.331486)), Port::OUTPUT, module, VCMixer::MIX_OUTPUT2));

		// mixer - channel 3
		//
		// knobs
		// ///// channel levels
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(5.8993969, 58.33149).plus(Vec(-2, 0))), module, VCMixer::LVL3_PARAM + 0, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(21.899343, 58.331486).plus(Vec(-2, 0))), module, VCMixer::LVL3_PARAM + 1, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(37.899292, 58.331486).plus(Vec(-2, 0))), module, VCMixer::LVL3_PARAM + 2, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(53.90065, 58.331486).plus(Vec(-2, 0))), module, VCMixer::LVL3_PARAM + 3, 0.0, 1.0, 0.0));
		// cv control ports
		addInput(Port::create<PJ301MPort>(mm2px(Vec(69.2935331, 60.331486)), Port::INPUT, module, VCMixer::CV_INPUT3 + 0));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(85.29348, 60.331486)), Port::INPUT, module, VCMixer::CV_INPUT3 + 1));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(101.293465, 60.331486)), Port::INPUT, module, VCMixer::CV_INPUT3 + 2));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(117.293411, 60.331486)), Port::INPUT, module, VCMixer::CV_INPUT3 + 3));
		// output cv input port
		addInput(Port::create<PJ301MPort>(mm2px(Vec(133.2935331, 60.331486)), Port::INPUT, module, VCMixer::MIX_CV_INPUT3));
		// ///// master level  knob
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(149.049999, 58.331486)), module, VCMixer::MIX_LVL3_PARAM, 0.0, 2.0, 1.0));
		// output port
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(165.293411, 60.331486)), Port::OUTPUT, module, VCMixer::MIX_OUTPUT3));

		// mixer - channel 4
		//
		// knobs
		// ///// channel levels
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(5.8993969, 74.33149).plus(Vec(-2, 0))), module, VCMixer::LVL4_PARAM + 0, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(21.899343, 74.331486).plus(Vec(-2, 0))), module, VCMixer::LVL4_PARAM + 1, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(37.899292, 74.331486).plus(Vec(-2, 0))), module, VCMixer::LVL4_PARAM + 2, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(53.90065, 74.331486).plus(Vec(-2, 0))), module, VCMixer::LVL4_PARAM + 3, 0.0, 1.0, 0.0));
		// cv control ports
		addInput(Port::create<PJ301MPort>(mm2px(Vec(69.2935331, 76.331486)), Port::INPUT, module, VCMixer::CV_INPUT4 + 0));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(85.29348, 76.331486)), Port::INPUT, module, VCMixer::CV_INPUT4 + 1));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(101.293465, 76.331486)), Port::INPUT, module, VCMixer::CV_INPUT4 + 2));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(117.293411, 76.331486)), Port::INPUT, module, VCMixer::CV_INPUT4 + 3));
		// output cv input port
		addInput(Port::create<PJ301MPort>(mm2px(Vec(133.2935331, 76.331486)), Port::INPUT, module, VCMixer::MIX_CV_INPUT4));
		// ///// master level  knob
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(149.049999, 74.331486)), module, VCMixer::MIX_LVL4_PARAM, 0.0, 2.0, 1.0));
		// output port
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(165.293411, 76.331486)), Port::OUTPUT, module, VCMixer::MIX_OUTPUT4));

		// mixer - channel 5
		//
		// knobs
		// ///// channel levels
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(5.8993969, 90.33149).plus(Vec(-2, 0))), module, VCMixer::LVL5_PARAM + 0, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(21.899343, 90.331486).plus(Vec(-2, 0))), module, VCMixer::LVL5_PARAM + 1, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(37.899292, 90.331486).plus(Vec(-2, 0))), module, VCMixer::LVL5_PARAM + 2, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(53.90065, 90.331486).plus(Vec(-2, 0))), module, VCMixer::LVL5_PARAM + 3, 0.0, 1.0, 0.0));
		// cv control ports
		addInput(Port::create<PJ301MPort>(mm2px(Vec(69.2935331, 92.331486)), Port::INPUT, module, VCMixer::CV_INPUT5 + 0));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(85.29348, 92.331486)), Port::INPUT, module, VCMixer::CV_INPUT5 + 1));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(101.293465, 92.331486)), Port::INPUT, module, VCMixer::CV_INPUT5 + 2));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(117.293411, 92.331486)), Port::INPUT, module, VCMixer::CV_INPUT5 + 3));
		// output cv input port
		addInput(Port::create<PJ301MPort>(mm2px(Vec(133.2935331, 92.331486)), Port::INPUT, module, VCMixer::MIX_CV_INPUT5));
		// ///// master level  knob
		addParam(ParamWidget::create<RoundLargeBlackKnob>(mm2px(Vec(149.049999, 90.331486)), module, VCMixer::MIX_LVL5_PARAM, 0.0, 2.0, 1.0));
		// output port
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(165.293411, 92.331486)), Port::OUTPUT, module, VCMixer::MIX_OUTPUT5));
	}
};


Model *modelVCMixer = Model::create<VCMixer, VCMixerWidget>("Beckstrom Research", "Matrix Mixer", "Matrix Mixer", MIXER_TAG, AMPLIFIER_TAG);
