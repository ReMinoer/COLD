#ifndef _System_CallbackMessageListener_H
#define _System_CallbackMessageListener_H

#include <System/MessageListener.h>
#include <boost/bind.hpp>

namespace System
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Listener class that triggers a user provided method / function when a message is received.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class MessageType>
	class CallbackMessageListener : public MessageListener<MessageType>
	{
	protected:
		/// Callback function that is triggered when the message is received
		::boost::function1<void, MessageType> m_callback ;
		/// True if the callback function has been provided by the user.
		bool m_isInitalized ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor with no callback function (differed initialization). 
		/// 	   A use of this listener is not permitted until a callback function
		/// 	   is provided.
		/// 
		/// \param emitter The message emitter
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		CallbackMessageListener(MessageEmitter<MessageType> * emitter)
			: MessageListener<MessageType>::MessageListener(emitter), m_isInitalized(false)
		{}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor
		/// 
		/// \param emitter The message emitter
		/// \param callback The callback function that must be called when a message is triggered
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		CallbackMessageListener(MessageEmitter<MessageType> * emitter, const ::boost::function1<void, MessageType> & callback)
			: MessageListener<MessageType>::MessageListener(emitter), m_callback(callback), m_isInitalized(true)
		{}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor
		/// 
		/// \param emitter The message emitter
		/// \param instance A pointer to an instance on which the method methodPtr will be called
		/// \param  methodPtr The method that must be called when a message is received
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		template <class ClassType>
		CallbackMessageListener(MessageEmitter<MessageType> * emitter, ClassType * instance, void (ClassType::*methodPtr)(const MessageType &) )
			: MessageListener<MessageType>::MessageListener(emitter), m_callback(::boost::bind(methodPtr, instance, _1)), m_isInitalized(true)
		{}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Sets the callback function
		/// 
		/// \param callback The new callback function
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void setCallback(const ::boost::function1<void, MessageType> & callback)
		{
			m_callback = callback ;
			m_isInitalized = true ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Sets the callback function
		/// 
		/// \param instance A pointer to an instance on which the method methodPtr will be called
		/// \param  methodPtr The method that must be called when a message is received
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		template <class ClassType>
		void setCallback(ClassType * instance, void (ClassType::*methodPtr)(const MessageType &))
		{
			m_callback = ::boost::bind(methodPtr, instance, _1) ;
			m_isInitalized = true ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Method that is called when a message is received. It calls the callback function
		/// 	   with the received message.
		/// 
		/// \param msg The message
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onMessage(const MessageType & msg)
		{
			assert(m_isInitalized) ;
			m_callback(msg) ;
		}
	};
}

#endif