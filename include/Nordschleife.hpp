#include "common.hpp"
#include <functional>

using namespace rack;
extern Plugin *pluginInstance;
#define NORDSTEPS	64
#define NORDCARS	4
#define NORDPATHS	12

#include "../include/nsElements.hpp"

struct NordschleifeField
{
	std::string label;
	int minValue;
	int maxValue;
	std::function<void(int)> setter;
	std::function<int(void)> getter;
	std::vector<std::string> values;
	int pos_x;
	int pos_y;
	int display_offset;
	bool bigField;

	void set(int x, int y, const char *lbl, std::vector<std::string> strngs, std::function<int(void)> gtr, std::function<void(int)> str, bool big = false)
	{
		set(x,y, lbl, 0, (int)strngs.size()-1, gtr, str, 0, big);
		values = strngs;
	}

	void set(int x, int y, const char *lbl, int mi, int ma, std::function<int(void)> gtr, std::function<void(int)> str, int dispoff = 0, bool big = false)
	{
		pos_x=x;
		pos_y=y;
		label = lbl;
		minValue=mi;
		maxValue=ma;
		getter=gtr;
		setter=str;
		display_offset = dispoff;
		bigField = big;
	}

	void inc()
	{
		int value = getter();
		if(++value > maxValue)
			value = minValue;
		setter(value);
	}

	void dec()
	{
		int value = getter();
		if(--value < minValue)
			value = maxValue;
		setter(value);
	}

	std::string getText()
	{
		if(values.empty())
		{
			char n[20];
			sprintf(n, "%i", display_offset+getter());
			return n;
		}
		
		return values[getter()];
	}
};

struct nordDisplay;
struct NordschleifeWidget : SequencerWidget
{
	enum MENUACTIONS
	{
		RANDOMIZE_PITCH = 0x01,
		RANDOMIZE_MODE = 0x02,
		RANDOMIZE_PROBABILITY = 0x04,
		RANDOMIZE_REPETITIONS = 0x08,
		RANDOMIZE_DIRECTION = 0x10,
		RANDOMIZE_PATH = 0x20,
		RANDOMIZE_ONCRASH = 0x40,
		RANDOMIZE_LAQUALUNQUE = 0x80,
		QUANTIZE_PITCH
	};

	struct RandomizeSubItemItem : MenuItem
	{
		RandomizeSubItemItem(Module *m, const char *title, int action);

		int randomizeDest;
		Nordschleife *md;
		void onAction(const event::Action &e) override;
	};

	struct RandomizeItem : ui::MenuItem
	{
		public:
		RandomizeItem(Module *m)
		{
			md = m;
			text = "Force the hand of chance";
			rightText = RIGHT_ARROW;
		};
		Menu *createChildMenu() override
		{
			Menu *sub_menu = new Menu;
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Pitch", RANDOMIZE_PITCH));
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Mode", RANDOMIZE_MODE ));
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Probability", RANDOMIZE_PROBABILITY ));
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Repetition", RANDOMIZE_REPETITIONS ));
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Direction", RANDOMIZE_DIRECTION ));
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Path", RANDOMIZE_PATH ));
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Collision", RANDOMIZE_ONCRASH ));
			sub_menu->addChild(new RandomizeSubItemItem(md, "Ov Power", RANDOMIZE_LAQUALUNQUE));
			return sub_menu;
		}
		private:
		Module *md;
	};

	void onHoverKey(const event::HoverKey &e) override;

	NordschleifeWidget(Nordschleife *module);
	void createStep(Nordschleife *module, int index);
	void createCar(Nordschleife *module, int index);
	void createDataEntry(Nordschleife *module);
	void onMenu(int action);
	Menu *addContextMenu(Menu *menu) override;
};

struct Nordschleife : Module
{
	enum ParamIds
	{
		VOLTAGE_1,
		STEPSELECT_1 = VOLTAGE_1 + NORDSTEPS,
		CAR_SELECT = STEPSELECT_1 + NORDSTEPS,
		DATAENTRY_MODE = CAR_SELECT + NORDCARS,
		DATAENTRY_UP,
		DATAENTRY_DOWN,
		DATAENTRY_LEFT,
		DATAENTRY_RIGHT,
		M_RESET,
		RANGE,
		NUM_PARAMS = RANGE + cvStrip::CVSTRIP_PARAMS
	};
	enum InputIds
	{
		CAR_RESET,
		CAR_CLOCK = CAR_RESET + NORDCARS,
		RANDOMIZONE = CAR_CLOCK + NORDCARS,
		MRESET_IN,
		RANGE_IN,
		NUM_INPUTS = RANGE_IN + cvStrip::CVSTRIP_INPUTS
	};
	enum OutputIds
	{
		OUT_A,
		OUT_B = OUT_A + NORDSTEPS,
		CAR_CV = OUT_B + NORDSTEPS,
		CAR_GATE = CAR_CV + NORDCARS,
		CAR_LAP = CAR_GATE + NORDCARS,
		NUM_OUTPUTS = CAR_LAP + NORDCARS
	};
	enum LightIds
	{
		LOTUS_LED,
		BRABHAM_LED = LOTUS_LED + NORDSTEPS,
		FERRARI_LED = BRABHAM_LED + NORDSTEPS,
		HESKETH_LED = FERRARI_LED + NORDSTEPS,
		LAP_LED = HESKETH_LED + NORDSTEPS,
		NUM_LIGHTS = LAP_LED + NORDCARS
	};

	Nordschleife() : Module()
	{
		display = NULL;
		pWidget = NULL;
		theRandomizer = 0;
		init_tables();
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		cvs.configure(this, NUM_PARAMS - cvStrip::CVSTRIP_PARAMS);

		for(int k = 0; k < NORDCARS; k++)
			cars[k].Init(this, k);

		for(int k = 0; k < NORDSTEPS; k++)
			steps[k].Init(k);
	}

	void process(const ProcessArgs &args) override;

	cvStrip cvs;
	int theRandomizer;
	NordschleifeField nsFields[NORDFIELDS];
	NordschleifeCar cars[NORDCARS];
	NordschleifeStep steps[NORDSTEPS];
	int rotation[4][NORDSTEPS]; // 0 90 180 270
	int selectedCar = 0;
	int selectedStep = 0;
	static int paths[NORDPATHS][64];
	static std::vector<std::string> pathNames;
	static std::vector<std::string> carNames;

	TransparentWidget *createDisplay(Vec pos);

	void QuantizePitch();
	void setWidget(NordschleifeWidget *pwdg) { pWidget = pwdg; }
	inline void setCar(int n)
	{
		selectedCar = n;
		for(int k = 0; k < NORDCARS; k++)
			params[CAR_SELECT + k].setValue(k == selectedCar);
	}

	inline void toggleDataEntryMode()
	{
		params[DATAENTRY_MODE].setValue(params[DATAENTRY_MODE].getValue() == 0);
	}
	inline bool moveByStep() { return params[DATAENTRY_MODE].getValue() == 0; }
	inline void setKey(int code) { key = code; }
	void randrandrand(int action);

	protected:
	void dataFromJson(json_t *root) override
	{
		Module::dataFromJson(root);
		json_t *rndJson = json_object_get(root, "theRandomizer");
		if(rndJson)
			theRandomizer = json_integer_value(rndJson);
		for(int k = 0; k < NORDCARS; k++)
			cars[k].dataFromJson(root);
		
		for(int k = 0; k < NORDSTEPS; k++)
			steps[k].dataFromJson(root, std::to_string(k));

		on_loaded();
	}
	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();
		json_t *rndJson = json_integer(theRandomizer);
		json_object_set_new(rootJ, "theRandomizer", rndJson);
		for(int k = 0; k < NORDCARS; k++)
			cars[k].dataToJson(rootJ);
		
		for(int k = 0; k < NORDSTEPS; k++)
			steps[k].dataToJson(rootJ, std::to_string(k));
		return rootJ;
	}

	private:
	void car_select();
	void step_select();
	inline void setStep(int n)
	{
		selectedStep = n;
		for(int k = 0; k < NORDSTEPS; k++)
			params[STEPSELECT_1 + k].setValue(k == selectedStep);
	}
	void init_tables();
	void randrandrand();
	void on_loaded();
	void load();
	void data_entry();
	void declareFields();

	virtual void onReset() override
	{
		for(int k = 0; k < NORDCARS; k++)
		{
			cars[k].init();
		}
		for(int k = 0; k < NORDSTEPS; k++)
			steps[k].init();
		reset();
	}

	void reset() 
	{
		setCar(0);
		setStep(0);
		lazyCheck = 0;
		for(int k = 0; k < NORDCARS; k++)
			cars[k].reset();
		for(int k = 0; k < NORDSTEPS; k++)
			steps[k].reset();
	}

	inline bool consumeKey(int code)
	{
		if(key == code)
		{
			key = 0;
			return true;
		}
		return false;
	}

	dsp::SchmittTrigger carSelectTrigger[NORDCARS];
	dsp::SchmittTrigger stepSelectTrigger[NORDSTEPS];
	dsp::SchmittTrigger rndTrigger;
	dsp::SchmittTrigger leftKey;
	dsp::SchmittTrigger rightKey;
	dsp::SchmittTrigger upKey;
	dsp::SchmittTrigger downKey;
	int lazyCheck = 0;
	int key = 0;
	NordschleifeWidget *pWidget;
	nordDisplay *display;
	dsp::SchmittTrigger masterReset;
};
