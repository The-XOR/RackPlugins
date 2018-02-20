#include "common.hpp"
#ifdef OSC_ENABLE
#include "../digitalExt/osc/oscCommunicator.hpp"
#include "../digitalExt/osc/oscControl.hpp"
#include "../digitalExt/osc/oscDriver.hpp"

void oscControl::Draw(OSCDriver *drv, bool force)
{
	if((force || m_dirty))
	{
		drv->sendMsg(m_address.c_str(), getValue());
	}
	m_dirty = false;
	m_lastDrawnValue = getValue();
}

void oscControl::ChangeFromGUI(OSCDriver *drv)  // gui updated: the new value is already in the binded parameter
{
	m_dirty = true;
	Draw(drv);
}

#endif //OSC
