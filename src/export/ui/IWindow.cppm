module lira.ui.IWindow;
import lira.ui.IWindow;

import std.memory;
import lira.ui.IEventReceiver;

namespace lira::ui
{
	void IWindow::RegisterEventReceiver(const std::shared_ptr<IEventReceiver>& r)
	{
		m_eventReceiver = r;
	}
}