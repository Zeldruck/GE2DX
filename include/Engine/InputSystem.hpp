#ifndef _INPUTSYSTEM_HPP_
#define _INPUTSYSTEM_HPP_

#include <Engine/Export.hpp>
#include <memory>
#include <iostream>
#include <functional>
#include <map>

class SEvent;

class GE2DX_ENGINE_API InputSystem
{
public:
	InputSystem();
	~InputSystem();

	InputSystem(InputSystem&) = delete;
	void operator=(const InputSystem&) = delete;

	static std::shared_ptr<InputSystem> Instance();

	void BindKeyPressed(int, const std::string&);
	void BindMouseButton(int, const std::string&);

	void OnAction(const std::string&, std::function<void()>);

private:
	static std::shared_ptr<InputSystem> instance;

	std::map<std::string, std::shared_ptr<SEvent>> actions;


};

struct SEvent
{
	std::string name;
	int keyButton;
	int mouseButton;

	std::function<void()> action;
};

#endif // !_INPUTSYSTEM_HPP_