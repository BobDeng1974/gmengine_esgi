#include "Component.h"

using namespace Engine;

Component::Component() 
{
	m_state = ComponentState::INIT;
}

Component::~Component() 
{
	
}

void Component::setActive(bool status) 
{
	if (m_state == ComponentState::PENDING_REMOVE) {
		return;
	}

	m_state = (status) ? ComponentState::ENABLED : ComponentState::DISABLED;

	if (ComponentState::ENABLED)
		onEnable();
	else if (ComponentState::DISABLED)
		onDisable();
}

ComponentState Component::getState()
{
	return m_state;
}

GameObject* Component::gameObject()
{
	return m_gameObject;
}

void Component::setGameObject(GameObject* object) {
	m_gameObject = object;
}