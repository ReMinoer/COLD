#ifndef _System_MessageListener_H
#define _System_MessageListener_H

#include <boost/signal.hpp>

namespace System
{
	template <class MessageType> class MessageEmitter ;

	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Message listener.
	/// 	   
	///  To listen a message, inherit from this class and implement the abstract 
	///  onMessage method. 
	///  
	/// \remarks The method is called as soon as the message is emitted.
	/// 
	/// \param MessageType The type of the transmitted message.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class MessageType>
	class MessageListener
	{
	protected:
		/// The message emitter.
		MessageEmitter<MessageType> * m_emitter ;
		/// Connection to the message emitter. It enables subscription cancellation.
		boost::signals::connection m_connection ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor with subscription to emitter.
		/// 
		/// \param sender The message emitter.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		MessageListener(MessageEmitter<MessageType> * emitter)
			: m_emitter(emitter) 
		{
			m_connection = emitter->connect(boost::bind(&MessageListener<MessageType>::onMessage, this, _1)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor cancelling the subscription to the message emitter.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual ~MessageListener()
		{
			m_connection.disconnect() ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the emitter associated to this message listener.
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		const MessageEmitter<MessageType> * getEmitter() const
		{
			return m_emitter ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Méthode appelée lors de la réception d'un message provenant de l'émetteur.
		/// 
		/// \param msg Le message emis.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onMessage(const MessageType & msg) = 0 ;
	};
}

#endif