#ifndef _INPUTSYSTEM_HPP_
#define _INPUTSYSTEM_HPP_

#include <Engine/Export.hpp>
#include <SDL.h>
#include <functional> //< std::function
#include <unordered_map> //< std::unordered_map est plus efficace que std::map pour une association clé/valeur

enum class MouseButton
{
	Left,
	Right,
	Middle,
	X1,
	X2
};

class GE2DX_ENGINE_API InputSystem
{
public:
	InputSystem() = default;
	InputSystem(const InputSystem&) = delete;
	InputSystem(InputSystem&&) = delete;
	~InputSystem() = default;

	// Appuyer sur la touche "keyCode" déclenchera "action"
	void BindKeyPressed(SDL_KeyCode keyCode, std::string action);

	// Appuyer sur le bouton "button" déclenchera "action"
	void BindMouseButtonPressed(MouseButton button, std::string action);

	// Appuyer sur le bouton "button" du contrôleur (manette) déclenchera "action"
	void BindControllerButton(SDL_GameControllerButton button, std::string action);

	// Réinitialise toutes les associations clavier/souris vers des actions
	void ClearBindings();

	// Gère l'événement de la SDL et déclenche les actions associées, s'il y en a
	void HandleEvent(const SDL_Event & event);

	// Lorsque l'action "action" se déclenche, on appellera "func"
	void OnAction(std::string action, std::function<void()> func);

	InputSystem& operator=(const InputSystem&) = delete;
	InputSystem& operator=(InputSystem&&) = delete;

	static InputSystem& Instance();

private:
	void TriggerAction(const std::string & action);

	std::unordered_map<int /*mouseButton*/, std::string /*action*/> m_mouseButtonToAction;
	std::unordered_map<SDL_GameControllerButton /*controllerButton*/, std::string /*action*/> m_controllerButtonToAction;
	std::unordered_map<SDL_Keycode /*key*/, std::string /*action*/> m_keyToAction;
	std::unordered_map<std::string /*action*/, std::function<void()>> m_actionToFunc;
};

#endif // !_INPUTSYSTEM_HPP_