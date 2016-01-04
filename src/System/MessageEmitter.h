#ifndef _System_MessageEmitter_H
#define _System_MessageEmitter_H

#include <boost/signal.hpp>
#include <set>
#include <DesignPattern/StaticMember.h>

namespace System
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Message emitter.  
	/// 
	/// \param MessageType The type of the transmitted message.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class MessageType>
	class MessageEmitter
	{
	private:
		/// all instances of emitters that have been created
		static DesignPattern::StaticMember<::std::set<MessageEmitter*> > s_instances ;

		/// We use boost signals library to handle message passing.
		boost::signal1<void, MessageType> m_signal ;

	public:

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns all alive instances of emitters 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static const ::std::set<MessageEmitter*> & getInstances()
		{
			return *s_instances.getInstance() ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		MessageEmitter()
		{
			s_instances.getInstance()->insert(this) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		~MessageEmitter()
		{
			s_instances.getInstance()->erase(this) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Subscription to messages emitter by this message emitter.
		/// 
		/// \param callback A callback function that is called when a message is emitted.
		/// \return A boost connection object that can be used to cancel the subscription.
		/// 		
		/// \remarks This method is public but you should subscribe with a MessageListener.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		boost::signals::connection connect(boost::function1<void, MessageType> const & callback)
		{
			return m_signal.connect(callback) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Sends a message to all subscribers.
		/// 
		/// \param value The emitted message
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void send(MessageType const & value)
		{
			m_signal(value) ;
		}
	};

	template <class MessageType>
	DesignPattern::StaticMember<::std::set<MessageEmitter<MessageType> *> > MessageEmitter<MessageType>::s_instances ;
}

#endif