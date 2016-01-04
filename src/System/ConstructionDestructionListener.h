#ifndef _System_ConstructionDestructionListener_H
#define _System_ConstructionDestructionListener_H

#include <System/ConstructionDestructionEmitter.h>
#include <System/CallbackMessageListener.h>

namespace System
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief A listener class activating methods on construction  and deletion messages
	/// 	   for a given object's type.
	/// 	   \li A System::ConstructionMessage<Type> activates the onCreateObject method
	/// 	   \li A System::DestructionMessage<Type> activates the onDestroyObject method	   
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Type>
	class ConstructionDestructionListener
	{
	protected:
		/// Message listener for ConstructionMessage<Type> messages
		CallbackMessageListener<ConstructionMessage<Type> > m_constructionListener ;
		/// Message listener for DestructionMessage<Type> messages
		CallbackMessageListener<DestructionMessage<Type> > m_destructionListener ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when a Type instance is created
		/// 
		/// \param msg
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onCreateObject(const ConstructionMessage<Type> & msg) = 0 ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when a Type instance is destroyed
		/// 
		/// \param msg
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onDestroyObject(const DestructionMessage<Type> & msg) = 0 ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor.
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		ConstructionDestructionListener()
			: m_constructionListener(ConstructionDestructionEmitter<Type>::getConstructionEmitter(), this, &ConstructionDestructionListener<Type>::onCreateObject),
			  m_destructionListener(ConstructionDestructionEmitter<Type>::getDestructionEmitter(), this, &ConstructionDestructionListener<Type>::onDestroyObject)
		{}

	};
}

#endif