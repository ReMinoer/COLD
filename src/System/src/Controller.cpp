#include <stdafx.h>

#include <System/Controller.h>
#include <iostream>

namespace System
{


	void Controller::handleConstructed()
	{
		::std::copy(m_constructedBuffer.begin(), m_constructedBuffer.end(), ::std::back_inserter(m_objects)) ;
		m_constructedBuffer.erase(m_constructedBuffer.begin(), m_constructedBuffer.end()) ;
	}

	void Controller::handleDestroyed()
	{
		unsigned int cpt=0 ; 
		while(cpt<m_objects.size())
		{
			ActiveObject * current = m_objects[cpt] ;
			::std::set<ActiveObject*>::iterator location=m_destroyedBuffer.find(current) ;
			if(location!=m_destroyedBuffer.end())
			{
				m_objects[cpt] = m_objects.back() ;
				m_objects.pop_back() ;
				m_destroyedBuffer.erase(location) ;
			}
			else
			{
				++cpt ;
			}
		}
		m_destroyedBuffer.clear() ;
	}

	void Controller::handleObjectLifeAndDeath()
	{
		handleConstructed() ;
		handleDestroyed() ;
	}

	void Controller::onCreateObject( const ConstructionMessage<ActiveObject> & msg )
	{
		m_constructedBuffer.push_back(&msg.m_object) ;
	}

	void Controller::onDestroyObject( const DestructionMessage<ActiveObject> & msg )
	{
		m_destroyedBuffer.insert(&msg.m_object) ;
	}

	Controller::Controller() 
	{

	}

	void Controller::update( Config::Real const & dt )
	{
		handleObjectLifeAndDeath() ;
		for(std::vector<ActiveObject*>::const_iterator it=m_objects.begin(), end=m_objects.end() ; it!=end ; ++it)
		{
			ActiveObject * current = *it ;
			// If the object has not been destroyed and is active, we call the update method
			if(m_destroyedBuffer.find(current)==m_destroyedBuffer.end() && current->isActive())
			{
				current->update(dt) ;
			}
		}
	}
}