#ifndef _System_ConstructionMessage_H
#define _System_ConstructionMessage_H

namespace System
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Message sent when an instance is constructed
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Type>
	class ConstructionMessage
	{
	public:
		/// Reference to the constructed object
		Type & m_object ;

		ConstructionMessage(Type & object)
			: m_object(object)
		{}
	} ;
}

#endif