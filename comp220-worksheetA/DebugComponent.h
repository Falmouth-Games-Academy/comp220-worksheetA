#pragma once

struct DebugComponent
{
	const char* name;
	const char* info;

	void Init(const char* _name, const char* _info)
	{
		name = _name;
		info = _info;
	}
};

// typeid(coordinator->GetComponentType<WindowComponent>()).name