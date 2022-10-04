#include "..\include\InputSystem.hpp"

std::shared_ptr<InputSystem> InputSystem::instance = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

std::shared_ptr<InputSystem> InputSystem::Instance()
{
	if (instance == nullptr)
	{
		instance = std::make_shared<InputSystem>();
	}

	return instance;
}

void InputSystem::BindKeyPressed(int _key, const std::string& _name)
{
	std::map<std::string, std::shared_ptr<SEvent>>::iterator it;

	it = actions.find(_name);

	if (it == actions.end())
	{
		std::shared_ptr<SEvent> un = std::make_shared<SEvent>();
		un->name = _name;
		un->keyButton = _key;

		actions[_name] = un;
	}
	else
	{
		actions[_name]->keyButton = _key;
	}
}

void InputSystem::BindMouseButton(int _mouseButton, const std::string& _name)
{
	std::map<std::string, std::shared_ptr<SEvent>>::iterator it;

	it = actions.find(_name);

	if (it == actions.end())
	{
		std::shared_ptr<SEvent> un = std::make_shared<SEvent>();
		un->name = _name;
		un->mouseButton = _mouseButton;

		actions[_name] = un;
	}
	else
	{
		actions[_name]->mouseButton = _mouseButton;
	}
}

void InputSystem::OnAction(const std::string& _name, std::function<void()> _func)
{
	std::map<std::string, std::shared_ptr<SEvent>>::iterator it;

	it = actions.find(_name);

	if (it != actions.end())
	{
		actions[_name]->action = _func;
	}
}
