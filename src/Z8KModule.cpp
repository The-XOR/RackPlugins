#include "../include/Z8K.hpp"
#include <sstream>

int Z8K::paths[Z8KPATHS][16] = {
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
    {0,1,2,3,4,5,6,7,15,14,13,12,11,10,9,8},
    {0,8,1,9,2,10,3,11,4,12,5,13,6,14,7,15},
    {8,0,1,9,10,2,3,11,12,4,5,13,14,6,7,15},
    {0,1,2,3,4,5,6,7,15,8,9,10,11,12,13,14},
    {8,0,9,1,10,2,11,3,12,4,13,5,14,6,15,7},
    {0,7,1,6,2,5,3,4,8,15,9,14,10,13,11,12},
    {0,4,8,12,13,14,15,11,7,3,2,1,5,9,10,6},
    {3,2,7,1,6,11,0,5,10,15,4,9,14,8,13,12},
    {0,4,1,5,2,6,3,7,11,15,8,12,9,13,10,14},
    {0,7,9,14,1,6,10,13,8,15,2,5,11,12,3,4},
    {0,7,3,4,9,14,10,13,1,6,11,12,2,5,8,15},
	{0,3,1,2,4,7,5,6,8,11,9,10,12,15,13,14},
	{1,0,2,3,5,4,6,7,9,8,10,11,13,12,14,15}, 
	{2,0,1,3,6,4,5,7,10,8,9,11,14,12,13,15}, 
	{0,2,1,3,4,6,5,7,8,10,9,11,12,14,13,15}, 
	{1,2,0,3,5,6,4,7,9,10,8,11,13,14,12,15}, 
	{2,1,0,3,6,5,4,7,10,9,8,11,14,13,12,15}, 
	{3,1,2,0,7,5,6,4,11,9,10,8,15,13,14,12}, 
	{1,3,2,0,5,7,6,4,9,11,10,8,13,15,14,12}, 
	{2,3,1,0,6,7,5,4,10,11,9,8,14,15,13,12}, 
	{3,2,1,0,7,6,5,4,11,10,9,8,15,14,13,12}, 
	{1,2,3,0,5,6,7,4,9,10,11,8,13,14,15,12}, 
	{2,1,3,0,6,5,7,4,10,9,11,8,14,13,15,12}, 
	{3,0,2,1,7,4,6,5,11,8,10,9,15,12,14,13}, 
	{0,3,2,1,4,7,6,5,8,11,10,9,12,15,14,13}, 
	{2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13}, 
	{3,2,0,1,7,6,4,5,11,10,8,9,15,14,12,13}, 
	{0,2,3,1,4,6,7,5,8,10,11,9,12,14,15,13}, 
	{2,0,3,1,6,4,7,5,10,8,11,9,14,12,15,13}, 
	{3,0,1,2,7,4,5,6,11,8,9,10,15,12,13,14}, 
	{0,3,1,2,4,7,5,6,8,11,9,10,12,15,13,14}, 
	{1,3,0,2,5,7,4,6,9,11,8,10,13,15,12,14}, 
	{3,1,0,2,7,5,4,6,11,9,8,10,15,13,12,14}, 
	{0,1,3,2,4,5,7,6,8,9,11,10,12,13,15,14}, 
	{1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14},
	{13,12,14,15, 1,0,2,3, 9,8,10,11, 5,4,6,7 }, 
	{14,12,13,15, 2,0,1,3, 10,8,9,11, 6,4,5,7 }, 
	{12,14,13,15, 0,2,1,3, 8,10,9,11, 4,6,5,7 }, 
	{13,14,12,15, 1,2,0,3, 9,10,8,11, 5,6,4,7 }, 
	{14,13,12,15, 2,1,0,3, 10,9,8,11, 6,5,4,7 }, 
	{15,13,14,12, 3,1,2,0, 11,9,10,8, 7,5,6,4 }, 
	{13,15,14,12, 1,3,2,0, 9,11,10,8, 5,7,6,4 }, 
	{14,15,13,12, 2,3,1,0, 10,11,9,8, 6,7,5,4 }, 
	{15,14,13,12, 3,2,1,0, 11,10,9,8, 7,6,5,4 }, 
	{13,14,15,12, 1,2,3,0, 9,10,11,8, 5,6,7,4 }, 
	{14,13,15,12, 2,1,3,0, 10,9,11,8, 6,5,7,4 }, 
	{15,12,14,13, 3,0,2,1, 11,8,10,9, 7,4,6,5 }, 
	{12,15,14,13, 0,3,2,1, 8,11,10,9, 4,7,6,5 }, 
	{14,15,12,13, 2,3,0,1, 10,11,8,9, 6,7,4,5 }, 
	{15,14,12,13, 3,2,0,1, 11,10,8,9, 7,6,4,5 }, 
	{12,14,15,13, 0,2,3,1, 8,10,11,9, 4,6,7,5 }, 
	{14,12,15,13, 2,0,3,1, 10,8,11,9, 6,4,7,5 }, 
	{15,12,13,14, 3,0,1,2, 11,8,9,10, 7,4,5,6 }, 
	{12,15,13,14, 0,3,1,2, 8,11,9,10, 4,7,5,6 }, 
	{13,15,12,14, 1,3,0,2, 9,11,8,10, 5,7,4,6 }, 
	{15,13,12,14, 3,1,0,2, 11,9,8,10, 7,5,4,6 }, 
	{12,13,15,14, 0,1,3,2, 8,9,11,10, 4,5,7,6 }, 
	{13,12,15,14, 1,0,3,2, 9,8,11,10, 5,4,7,6 },
	{9,8,10,11, 13,12,14,15, 1,0,2,3, 5,4,6,7 }, 
	{10,8,9,11, 14,12,13,15, 2,0,1,3, 6,4,5,7 }, 
	{8,10,9,11, 12,14,13,15, 0,2,1,3, 4,6,5,7 }, 
	{9,10,8,11, 13,14,12,15, 1,2,0,3, 5,6,4,7 }, 
	{10,9,8,11, 14,13,12,15, 2,1,0,3, 6,5,4,7 }, 
	{11,9,10,8, 15,13,14,12, 3,1,2,0, 7,5,6,4 }, 
	{9,11,10,8, 13,15,14,12, 1,3,2,0, 5,7,6,4 }, 
	{10,11,9,8, 14,15,13,12, 2,3,1,0, 6,7,5,4 }, 
	{11,10,9,8, 15,14,13,12, 3,2,1,0, 7,6,5,4 }, 
	{9,10,11,8, 13,14,15,12, 1,2,3,0, 5,6,7,4 }, 
	{10,9,11,8, 14,13,15,12, 2,1,3,0, 6,5,7,4 }, 
	{11,8,10,9, 15,12,14,13, 3,0,2,1, 7,4,6,5 }, 
	{8,11,10,9, 12,15,14,13, 0,3,2,1, 4,7,6,5 }, 
	{10,11,8,9, 14,15,12,13, 2,3,0,1, 6,7,4,5 }, 
	{11,10,8,9, 15,14,12,13, 3,2,0,1, 7,6,4,5 }, 
	{8,10,11,9, 12,14,15,13, 0,2,3,1, 4,6,7,5 }, 
	{10,8,11,9, 14,12,15,13, 2,0,3,1, 6,4,7,5 }, 
	{11,8,9,10, 15,12,13,14, 3,0,1,2, 7,4,5,6 }, 
	{8,11,9,10, 12,15,13,14, 0,3,1,2, 4,7,5,6 }, 
	{9,11,8,10, 13,15,12,14, 1,3,0,2, 5,7,4,6 }, 
	{11,9,8,10, 15,13,12,14, 3,1,0,2, 7,5,4,6 }, 
	{8,9,11,10, 12,13,15,14, 0,1,3,2, 4,5,7,6 }, 
	{9,8,11,10, 13,12,15,14, 1,0,3,2, 5,4,7,6 },
	{5,4,6,7,9,8,10,11, 13,12,14,15, 1,0,2,3, }, 
	{6,4,5,7,10,8,9,11, 14,12,13,15, 2,0,1,3,  }, 
	{4,6,5,7,8,10,9,11, 12,14,13,15, 0,2,1,3,  }, 
	{5,6,4,7,9,10,8,11, 13,14,12,15, 1,2,0,3,  }, 
	{6,5,4,7,10,9,8,11, 14,13,12,15, 2,1,0,3,  }, 
	{7,5,6,4,11,9,10,8, 15,13,14,12, 3,1,2,0,  }, 
	{5,7,6,4,9,11,10,8, 13,15,14,12, 1,3,2,0,  }, 
	{6,7,5,4,10,11,9,8, 14,15,13,12, 2,3,1,0,  }, 
	{7,6,5,4,11,10,9,8, 15,14,13,12, 3,2,1,0,  }, 
	{5,6,7,4,9,10,11,8, 13,14,15,12, 1,2,3,0,  }, 
	{6,5,7,4,10,9,11,8, 14,13,15,12, 2,1,3,0,  }, 
	{7,4,6,5,11,8,10,9, 15,12,14,13, 3,0,2,1,  }, 
	{4,7,6,5,8,11,10,9, 12,15,14,13, 0,3,2,1,  }, 
	{6,7,4,5,10,11,8,9, 14,15,12,13, 2,3,0,1,  }, 
	{7,6,4,5,11,10,8,9, 15,14,12,13, 3,2,0,1,  }, 
	{4,6,7,5,8,10,11,9, 12,14,15,13, 0,2,3,1,  }, 
	{6,4,7,5,10,8,11,9, 14,12,15,13, 2,0,3,1,  },
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15} // il # 100 e' random
	
};

void Z8K::on_loaded()
{
	load();
	cvs.Init(pWidget);
}

void Z8K::load()
{
	// sequencer 1-4
	for(int k = 0; k < 4; k++)
	{
		int base = VOLTAGE_1 + 4 * k;
		std::vector<int> steps = {base, base + 1, base + 2, base + 3};
		seq[SEQ_1 + k].Init(RESET_1 + k, DIR_1 + k, DIRSW_1+k, CLOCK_1 + k, CV_1 + k, &lights[LED_ROW], params, steps);
	}
	// sequencer A-D
	for(int k = 0; k < 4; k++)
	{
		std::vector<int> steps = {k, k + 4, k + 8, k + 12};
		seq[SEQ_A + k].Init(RESET_A + k, DIR_A + k, DIRSW_A+k, CLOCK_A + k, CV_A + k, &lights[LED_COL], params, steps);
	}
	// horiz
	std::vector<int> steps_h = {0,1,2,3,7,6,5,4,8,9,10,11,15,14,13,12};
	seq[SEQ_HORIZ].Init(RESET_HORIZ, DIR_HORIZ, DIRSW_HORZ, CLOCK_HORIZ, CV_HORIZ, &lights[LED_HORIZ], params, steps_h);
	//vert
	std::vector<int> steps_v = {0,4,8,12,13,9,5,1,2,6,10,14,15,11,7,3};
	seq[SEQ_VERT].Init(RESET_VERT, DIR_VERT, DIRSW_VERT, CLOCK_VERT, CV_VERT, &lights[LED_VERT], params, steps_v);
	//path
	seq[SEQ_PATH].Init(RESET_PATH, DIR_PATH, DIRSW_PATH, CLOCK_PATH, CV_PATH, &lights[LED_PATH], params, getPath());

	reset();
}

void Z8K::reset()
{
	for(int k = 0; k < NUM_Z8SEQUENCERS; k++)
		seq[k].Reset();
}

void Z8K::QuantizePitch()
{
	for(int k = 0; k < 16; k++)
		params[VOLTAGE_1 + k].value = pWidget->quantizePitch(VOLTAGE_1 + k, params[VOLTAGE_1 + k].value, cvs);
}

void Z8K::process_keys()
{
	if(pWidget != NULL)
	{
		if(btninc.process(params[PTN_INC].value))
		{
			if((APP->window->getMods() & RACK_MOD_MASK) == GLFW_MOD_CONTROL)
				basePtn+=10;
			else
				basePtn++;
		} else if(btndec.process(params[PTN_DEC].value))
		{
			if((APP->window->getMods() & RACK_MOD_MASK) == GLFW_MOD_CONTROL)
				basePtn-=10;
			else
				basePtn--;
		}
		basePtn=clamp(basePtn, 0,  Z8KPATHS-1);

		float v = rescale(inputs[PATH_SELECT].getNormalVoltage(0.0), 0,LVL_MAX, 0, Z8KPATHS-1);
		int n = clamp(int(v+ basePtn), 0,  Z8KPATHS-1);
		
		if (curPtn != n)
		{
			curPtn = n;
			seq[SEQ_PATH].SetSequence(params, &lights[LED_PATH], getPath(), curPtn==99); 
		}
	}
}

void Z8K::process(const ProcessArgs &args)
{
	process_keys();
	int activeSteps[16];
	for(int k = 0; k < 16; k++)
		activeSteps[k] = LVL_OFF;
	if (masterReset.process(params[M_RESET].value) || masterResetIn.process(inputs[MASTERRESET].getVoltage()))
	{
		reset();
	} else
	{
		if (randomizeTrigger.process(inputs[RANDOMIZE].getVoltage()))
			pWidget->std_randomize(VOLTAGE_1, VOLTAGE_1 + 16);

		float rec_smp;
		int rec_step;
		if(cvs.IsRecAvailable(&rec_smp, &rec_step))
		{
			pWidget->SetValue(Z8K::VOLTAGE_1 + rec_step, rec_smp);
		}

		float expander_out = 0;
		uint8_t *p = (uint8_t *)&expander_out;
		*(p+3) = EXPPORT_Z8K;
		for(int k = 0; k < NUM_Z8SEQUENCERS; k++)
		{
			int stp = seq[k].Step(this);
			activeSteps[stp]++;
			switch(k)
			{
				case Z8K::SEQ_1 + 0:
					*(p + 0) |= stp;
					break;

				case Z8K::SEQ_1 + 1:
					*(p + 0) |= (stp-4) << 2;
					break;

				case Z8K::SEQ_1 + 2:
					*(p + 0) |= (stp - 8) << 4;
					break;

				case Z8K::SEQ_1 + 3:
					*(p + 0) |= (stp - 12) << 6;
					break;

				case Z8K::SEQ_A + 0:
					*(p + 1) |= (stp/4);
					break;

				case Z8K::SEQ_A + 1:
					*(p + 1) |= ((stp - 1) / 4) << 2;
					break;

				case Z8K::SEQ_A + 2:
					*(p + 1) |= ((stp - 2) / 4) << 4;
					break;

				case Z8K::SEQ_A + 3:
					*(p + 1) |= ((stp - 3) / 4) << 6;
					break;

				case Z8K::SEQ_HORIZ:
					*(p + 2) |= stp;
					break;

				case Z8K::SEQ_VERT:
					*(p + 2) |= stp << 4;
					break;

				case Z8K::SEQ_PATH:
					*(p + 3) |= stp;
					break;
			}
		}

		outputs[EXP_PORT].setVoltage(expander_out);
		for (int k = 0; k < 16; k++)
			outputs[ACTIVE_STEP + k].setVoltage( activeSteps[k]);
	}

}

Menu *Z8KWidget::addContextMenu(Menu *menu)
{
	menu->addChild(new SeqMenuItem<Z8KWidget>("Randomize Pitch", this, RANDOMIZE_PITCH));
	menu->addChild(new SeqMenuItem<Z8KWidget>("Pitch Quantization", this, QUANTIZE_PITCH));
	return menu;
}

void Z8KWidget::onMenu(int action)
{
	switch (action)
	{
		case RANDOMIZE_PITCH: std_randomize(Z8K::VOLTAGE_1, Z8K::VOLTAGE_1 + 16); break;
		case QUANTIZE_PITCH: ((Z8K *)module)->QuantizePitch(); break;
	}
}

Z8KWidget::Z8KWidget(Z8K *module) : SequencerWidget()
{
	if(module != NULL)
		module->setWidget(this);

	CREATE_PANEL(module, this, 40, "res/modules/Z8KModule.svg");

	float dist_h = 22.225;
	float dist_v = -18.697;

	for(int k = 0; k < 4; k++)
	{
		addInput(createInput<PJ301YPort>(Vec(mm2px(5.738), yncscape(82.210+k*dist_v,8.255)), module, Z8K::RESET_1 + k));
		addInput(createInput<PJ301BPort>(Vec(mm2px(16.544), yncscape(82.210+k*dist_v,8.255)), module, Z8K::DIR_1 + k));
		addInput(createInput<PJ301RPort>(Vec(mm2px(34.758), yncscape(82.210+k*dist_v,8.255)), module, Z8K::CLOCK_1 + k));
		addParam(createParam<TL1105Sw>(Vec(mm2px(26.387), yncscape(83.035+k*dist_v, 6.607)), module, Z8K::DIRSW_1+k));		
	}

	for(int k = 0; k < 4; k++)
	{
		addInput(createInput<PJ301YPort>(Vec(mm2px(57.460+k*dist_h), yncscape(115.442,8.255)), module, Z8K::RESET_A + k));
		addInput(createInput<PJ301BPort>(Vec(mm2px(57.460+k*dist_h), yncscape(105.695,8.255)), module, Z8K::DIR_A + k));
		addInput(createInput<PJ301RPort>(Vec(mm2px(57.460+k*dist_h), yncscape(95.948,8.255)), module, Z8K::CLOCK_A + k));
		addParam(createParam<TL1105Sw>(Vec(mm2px(66.809+k*dist_h), yncscape(106.520, 6.607)), module, Z8K::DIRSW_A+k));		
	}

	float x = 165.034;
	addInput(createInput<portYSmall>( Vec(mm2px(x), yncscape(114.587,5.885)), module, Z8K::RESET_VERT ));
	addInput(createInput<portSmall>( Vec(mm2px(x), yncscape(107.179,5.885)), module, Z8K::DIR_VERT));
	addInput(createInput<portRSmall>( Vec(mm2px(x), yncscape(99.770,5.885)), module, Z8K::CLOCK_VERT ));
	addOutput(createOutput<portGSmall>(Vec(mm2px(x), yncscape(92.362,5.885)), module, Z8K::CV_VERT) );
	addParam(createParam<TL1105Sw>(Vec(mm2px(178.677), yncscape(106.818, 6.607)), module, Z8K::DIRSW_VERT));

	addInput(createInput<portYSmall>  (Vec(mm2px(x), yncscape(77.545, 5.885)), module, Z8K::RESET_HORIZ));
	addInput(createInput<portSmall>  (Vec(mm2px(x), yncscape(70.137, 5.885)), module, Z8K::DIR_HORIZ ));
	addInput(createInput<portRSmall>  (Vec(mm2px(x), yncscape(62.729, 5.885)), module, Z8K::CLOCK_HORIZ));
	addOutput(createOutput<portGSmall>(Vec(mm2px(x), yncscape(55.320, 5.885)), module, Z8K::CV_HORIZ));
	addParam(createParam<TL1105Sw>(Vec(mm2px(178.677), yncscape(69.776, 6.607)), module, Z8K::DIRSW_HORZ));

	addInput(createInput<portYSmall>  (Vec(mm2px(x), yncscape(40.317, 5.885)), module, Z8K::RESET_PATH));
	addInput(createInput<portSmall>  (Vec(mm2px(x), yncscape(32.909, 5.885)), module, Z8K::DIR_PATH ));
	addInput(createInput<portRSmall>  (Vec(mm2px(x), yncscape(25.500, 5.885)), module, Z8K::CLOCK_PATH));
	addOutput(createOutput<portGSmall>(Vec(mm2px(x), yncscape(18.092, 5.885)), module, Z8K::CV_PATH));
	addParam(createParam<TL1105Sw>(Vec(mm2px(178.677), yncscape(32.548, 6.607)), module, Z8K::DIRSW_PATH));

	addParam(createParam<UPSWITCH>(Vec(mm2px(165.721), yncscape(12.899, 4.627)), module, Z8K::PTN_INC));
	addParam(createParam<DNSWITCH>(Vec(mm2px(165.721), yncscape(8.307, 4.627)), module, Z8K::PTN_DEC));
	addChild(new Z8K7Segm(module != NULL ? module : NULL, 172.366, 8.836));
	addInput(createInput<portSmall> (Vec(mm2px(184.021), yncscape(9.718, 5.885)), module, Z8K::PATH_SELECT));

	addInput(createInput<PJ301BPort>(Vec(mm2px(33.774), yncscape(115.442, 8.255)), module, Z8K::RANDOMIZE));
	addInput(createInput<PJ301YPort> (Vec(mm2px(17.012), yncscape(115.442, 8.255)), module, Z8K::MASTERRESET));

	addOutput(createOutput<PJ301EXP>(Vec(mm2px(145.809), yncscape(2.685, 8.255)), module, Z8K::EXP_PORT));

	for(int r = 0; r < 4; r++)
	{
		for(int c = 0; c < 4; c++)
		{
			int n = c + r * 4;
			ParamWidget *pctrl = createParam<Davies1900hFixRedKnob>(Vec(mm2px(56.825 + dist_h * c), yncscape(81.575 + dist_v * r, 9.525)), module, Z8K::VOLTAGE_1 + n);
			addParam(pctrl);

			addChild(createLight<TinyLight<RedLight>>(Vec(mm2px(62.129 + dist_h * c), yncscape(78.633 + dist_v * r, 1.088)), module, Z8K::LED_ROW + n));
			addChild(createLight<TinyLight<GreenLight>>(Vec(mm2px(63.626 + dist_h * c), yncscape(80.129 + dist_v * r, 1.088)), module, Z8K::LED_COL + n));
			addChild(createLight<TinyLight<YellowLight>>(Vec(mm2px(64.951 + dist_h * c), yncscape(81.455 + dist_v * r, 1.088)), module, Z8K::LED_VERT + n));
			addChild(createLight<TinyLight<BlueLight>>(Vec(mm2px(66.277 + dist_h * c), yncscape(82.781 + dist_v * r, 1.088)), module, Z8K::LED_HORIZ + n));
			addChild(createLight<TinyLight<WhiteLight>>(Vec(mm2px(67.603 + dist_h * c), yncscape(84.107 + dist_v * r, 1.088)), module, Z8K::LED_PATH + n));

			if(r == 3)
				addOutput(createOutput<PJ301GPort>(Vec(mm2px(57.460 + dist_h * c), yncscape(2.685, 8.255)), module, Z8K::CV_A + c));

			addOutput(createOutput<portWSmall>(Vec(mm2px(64.995 + dist_h * c), yncscape(75.690 + dist_v * r, 5.885)), module, Z8K::ACTIVE_STEP + n));
		}
		addOutput(createOutput<PJ301GPort>(Vec(mm2px(145.809), yncscape(82.210 + r * dist_v, 8.255)), module, Z8K::CV_1 + r));
	}

	addChild(createParam<BefacoPushBig>(Vec(mm2px(5.366), yncscape(115.070, 9.001)), module, Z8K::M_RESET));

	if(module != NULL)
		module->cvs.Create(this, 191.814, 3.048f, Z8K::NUM_INPUTS - cvStrip::CVSTRIP_INPUTS, Z8K::NUM_PARAMS - cvStrip::CVSTRIP_PARAMS, 16);
}

int z8kSequencer::Step(Z8K *pModule)
{
	if(resetTrigger.process(pModule->inputs[pReset].getVoltage()))
	{
		Reset();
	} else if(clockTrigger.process(pModule->inputs[pClock].getVoltage()))
	{
		if(random)
			curStep = int(random::uniform() * numSteps);
		else
		{
			if(getModulableSwitch(pModule, pDirSwitch, pDirection))
			{
				if(--curStep < 0)
					curStep = numSteps - 1;
			} else
			{
				if(++curStep >= numSteps)
					curStep = 0;
			}
		}
		if(pModule->outputs[pOutput].isConnected())
			pModule->outputs[pOutput].setVoltage(pModule->cvs.TransposeableValue(sequence[curStep]->value));
		for(int k = 0; k < numSteps; k++)
			leds[k]->value = k == curStep ? LED_ON : LED_OFF;
	}
	return chain[curStep];
}

void Z8K7Segm::draw(const DrawArgs &args) 
{
	// Background
	NVGcolor backgroundColor = nvgRGB(0x20, 0x20, 0x20);
	NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
	nvgBeginPath(args.vg);
	nvgRoundedRect(args.vg, 0.0, 0.0, box.size.x, box.size.y, 4.0);
	nvgFillColor(args.vg, backgroundColor);
	nvgFill(args.vg);
	nvgStrokeWidth(args.vg, 1.0);
	nvgStrokeColor(args.vg, borderColor);
	nvgStroke(args.vg);
	// text
	nvgFontSize(args.vg, 18);
	nvgFontFaceId(args.vg, font->handle);
	nvgTextLetterSpacing(args.vg, 2.5);

	Vec textPos = Vec(2, 18);
	NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
	nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
	nvgText(args.vg, textPos.x, textPos.y, "~~", NULL);

	textColor = nvgRGB(0xda, 0xe9, 0x29);
	nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
	nvgText(args.vg, textPos.x, textPos.y, "\\\\", NULL);

	if(p8 != NULL)
	{
		char n[20];
		int ptn = p8->patternNumber()+1;
		if (ptn < 100)
			sprintf(n, "%2i", ptn);
		else
			sprintf(n, "??");
		textColor = nvgRGB(0xff, 0x00, 0x00);
		nvgFillColor(args.vg, textColor);
		nvgText(args.vg, textPos.x, textPos.y, n, NULL);
	}
}
