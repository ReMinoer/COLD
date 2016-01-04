#ifndef _System_Controller_H
#define _System_Controller_H

#include <System/ActiveObject.h>
#include <System/CallbackMessageListener.h>
#include <System/ConstructionDestructionListener.h>
#include <vector>
#include <set>

namespace System
{

	///////////////////////////////////////////////////////////////////////////////////
	/// \brief A controller class in charge of regularly activating instances of 
	/// 	   ActiveObjects. 
	/// 	   
	/// 	   Usually their should be only one instance of this class
	/// 	   inside your application. However, just in case, it si not a singleton...
	/// 	   Instances of ActiveObject are automatically referenced inside living 
	/// 	   controllers at their creation and automatically unreferenced at their
	/// 	   deletion. 
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class Controller : ConstructionDestructionListener<ActiveObject>
	{
	protected:
		/// All ActiveObject instances 
		std::vector<ActiveObject*> m_objects ;
		/// All active objects that have been constructed during / after the last call to the update method
		std::vector<ActiveObject*> m_constructedBuffer ;
		/// All active objects that have been destroyed during / after the last call to the update method
		std::set<ActiveObject*> m_destroyedBuffer ;

		///// Message listener for ConstructionMessage<ActiveObject> messages
		//CallbackMessageListener<ConstructionMessage<ActiveObject> > m_constructionListener ;
		///// Message listener for DestructionMessage<ActiveObject> messages
		//CallbackMessageListener<DestructionMessage<ActiveObject> > m_destructionListener ;

	private:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Updates data structures given the created objects (internal use)
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void handleConstructed();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Updates data structures given destroyed objects (internal use)
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void handleDestroyed();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Updates datastructures given created and destroyed objects (internal use)
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void handleObjectLifeAndDeath();

	protected:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when an ActiveObject is created
		/// 
		/// \param msg
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onCreateObject(const ConstructionMessage<ActiveObject> & msg);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when and ActiveObject is destroyed
		/// 
		/// \param msg
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onDestroyObject(const DestructionMessage<ActiveObject> & msg);

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor for a controller
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Controller();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Updates all known ActiveObjects.
		/// 
		/// \param dt The time elapsed since last call
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void update(Config::Real const & dt);

	};
}

#endif