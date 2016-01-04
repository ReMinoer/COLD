#ifndef _System_ConstructionDestructionEmitter_H
#define _System_ConstructionDestructionEmitter_H

#include <System/MessageEmitter.h>
#include <System/ConstructionMessage.h>
#include <System/DestructionMessage.h>
#include <DesignPattern/StaticMember.h>

namespace System
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Message emitter that sends messages to notifiy constructions and destructions
	/// 	   of instances of type Type that inherits from it. Emitters are singletons that
	/// 	   ensure that messages will be correctly handled.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Type>
	class ConstructionDestructionEmitter
	{
	private:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief No instance of this class needs to be constructed.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		ConstructionDestructionEmitter() {}

	protected:
		/// Emitter of construction messages
		static DesignPattern::StaticMember<System::MessageEmitter<ConstructionMessage<Type> > > m_constructionEmitter ;
		/// Emitter of destruction messages
		static DesignPattern::StaticMember<System::MessageEmitter<DestructionMessage<Type> > > m_destructionEmitter ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the construction message emitter
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static System::MessageEmitter<ConstructionMessage<Type> > * getConstructionEmitter()
		{
			return m_constructionEmitter.getInstance() ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the destruction message emitter
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static System::MessageEmitter<DestructionMessage<Type> > * getDestructionEmitter()
		{
			return m_destructionEmitter.getInstance() ;
			//return &m_destructionEmitter ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static void ConstructionDestructionEmitter::sendConstruction(Type & object)
		///
		/// \brief	Sends a construction message for the given object.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	24/11/2011
		///
		/// \param	object	The object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static void sendConstruction(Type & object)
		{
			getConstructionEmitter()->send(System::ConstructionMessage<Type>(object)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static void ConstructionDestructionEmitter::sendDestruction(Type & object)
		///
		/// \brief	Sends a destruction for the given object.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	24/11/2011
		///
		/// \param	object	The object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static void sendDestruction(Type & object)
		{
			getDestructionEmitter()->send(System::DestructionMessage<Type>(object)) ;
		}
	};

	template <class Type>
	DesignPattern::StaticMember<System::MessageEmitter<ConstructionMessage<Type> > > ConstructionDestructionEmitter<Type>::m_constructionEmitter ;

	template <class Type>
	DesignPattern::StaticMember<System::MessageEmitter<DestructionMessage<Type> > > ConstructionDestructionEmitter<Type>::m_destructionEmitter ;

}

#endif