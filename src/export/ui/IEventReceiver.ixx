export module lira.ui.IEventReceiver;

import lira.ui.KeyCodes;
import lira.ui.IWindow;

import std.memory;
export namespace lira::ui
{
	class IEventReceiver
	{
	public:
		IEventReceiver(IWindow* window)
		{
			//TODO: i know this is wrong 
			//TODO: custom shared pointer
			window->RegisterEventReceiver(std::shared_ptr<IEventReceiver>(this));
		}
		void OnKeyPress(KeyCode key, KeyState state) 
		{
			OnKeyPressImpl(key, state);
		}
		void OnMouseMove(double mouseX, double mouseY) 
		{
			OnMouseMoveImpl(mouseX, mouseY);
		}
		void OnMouseButtonClick(MouseButton button, KeyState state)
		{
			OnMouseButtonClickImpl(button, state);
		}

	protected:
		virtual void OnKeyPressImpl(KeyCode key, KeyState state)
		{

		}
		virtual void OnMouseMoveImpl(double mouseX, double mouseY)
		{

		}
		virtual void OnMouseButtonClickImpl(MouseButton button, KeyState state)
		{

		}

		
	};
}