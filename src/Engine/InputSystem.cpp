#include <Engine/InputSystem.hpp>

void InputSystem::BindKeyPressed(SDL_KeyCode keyCode, std::string action)
{
	m_keyToAction[keyCode] = std::move(action);
}

void InputSystem::BindMouseButtonPressed(MouseButton button, std::string action)
{
	// Plutôt que de traduire depuis notre enum vers les defines de la SDL à chaque événement
	// on peut le faire une seule fois au binding (plus efficace)
	int mouseButton;
	switch (button)
	{
	case MouseButton::Left:   mouseButton = SDL_BUTTON_LEFT;   break;
	case MouseButton::Right:  mouseButton = SDL_BUTTON_RIGHT;  break;
	case MouseButton::Middle: mouseButton = SDL_BUTTON_MIDDLE; break;
	case MouseButton::X1:     mouseButton = SDL_BUTTON_X1;     break;
	case MouseButton::X2:     mouseButton = SDL_BUTTON_X2;     break;
	default:
		return; //< ne devrait pas arriver
	}

	m_mouseButtonToAction[mouseButton] = std::move(action);
}

void InputSystem::BindControllerButton(SDL_GameControllerButton button, std::string action)
{
	m_controllerButtonToAction[button] = std::move(action);
}

void InputSystem::ClearBindings()
{
	m_controllerButtonToAction.clear();
	m_mouseButtonToAction.clear();
	m_keyToAction.clear();
}

void InputSystem::HandleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_CONTROLLERBUTTONDOWN:
	{
		auto it = m_controllerButtonToAction.find(static_cast<SDL_GameControllerButton>(event.cbutton.button));
		if (it != m_controllerButtonToAction.end())
			TriggerAction(it->second);

		break;
	}

	case SDL_KEYDOWN:
	{
		auto it = m_keyToAction.find(event.key.keysym.sym);
		if (it != m_keyToAction.end())
			TriggerAction(it->second);

		break;
	}

	case SDL_MOUSEBUTTONDOWN:
	{
		auto it = m_mouseButtonToAction.find(event.button.button);
		if (it != m_mouseButtonToAction.end())
			TriggerAction(it->second);

		break;
	}
	}
}

void InputSystem::OnAction(std::string action, std::function<void()> func)
{
	m_actionToFunc[std::move(action)] = std::move(func);
}

InputSystem& InputSystem::Instance()
{
	static InputSystem InputSystem;
	return InputSystem;
}

void InputSystem::TriggerAction(const std::string& action)
{
	auto it = m_actionToFunc.find(action);
	if (it != m_actionToFunc.end())
	{
		std::function<void()>& func = it->second;
		func();
	}
}