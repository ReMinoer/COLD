#ifndef _System_DestructionMessage_H
#define _System_DestructionMessage_H

namespace System
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Message sent when an instance is destroyed
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Type>
	class DestructionMessage
	{
	public:
		/// Reference to the destroyed object
		Type & m_object ;

		DestructionMessage(Type & object)
			: m_object(object)
		{}
	};
}

#endif