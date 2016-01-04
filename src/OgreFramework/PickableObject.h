#ifndef _OgreFramework_PickableObject_H
#define _OgreFramework_PickableObject_H

#include <OGRE/OgreNode.h>
#include <DesignPattern/StaticMember.h>
#include <System/MessageEmitter.h>

namespace OgreFramework
{
	class Picking ;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	PickableObject
	///
	/// \brief	Pickable object.
	/// 		
	/// 		This class emits the following messages
	/// 		\li PickableObject::SelectedObjectMessage when an instance of pickable object is selected
	/// 		\li PickableObject::UnselectedObjectMessage when an instance of pickable object is unselected
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	26/11/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class PickableObject
	{
	protected:
		friend class Picking ;
		friend class PickingSelectionBuffer ;

		///< Map between Ogre scene nodes and related instances of pickable objects
		//static DesignPattern::StaticMember<::std::map<Ogre::Node*, PickableObject*> > m_instances ;

		///< Map between Ogre entities and related instances of pickable objects
		static DesignPattern::StaticMember<::std::map<Ogre::Entity*, PickableObject*> > m_pickableInstances ;

		///< The pickable object
		Ogre::Node * m_object ;

		///< true if this object is selected
		bool m_isSelected ;

		///< The entities of the geometry
		::std::vector<Ogre::Entity*> m_entities ;
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	SelectedObjectMessage
		///
		/// \brief	Selected object message.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct SelectedObjectMessage
		{
			PickableObject & m_selected ;

			SelectedObjectMessage(PickableObject & object)
				: m_selected(object)
			{}
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	UnselectedObjectMessage
		///
		/// \brief	Unselected object message.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct UnselectedObjectMessage
		{
			PickableObject & m_unselected ;

			UnselectedObjectMessage(PickableObject & object)
				: m_unselected(object)
			{}	
		};

	private:
		static DesignPattern::StaticMember<System::MessageEmitter<SelectedObjectMessage> > m_selectedEmitter ;
		static DesignPattern::StaticMember<System::MessageEmitter<UnselectedObjectMessage> > m_unselectedEmitter ;
	
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static System::MessageEmitter<SelectedObjectMessage> * PickableObject::getSelectedEmitter()
		///
		/// \brief	Gets the SelectedObjectMessage emitter.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	null if it fails, else the selected emitter.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static System::MessageEmitter<SelectedObjectMessage> * getSelectedEmitter();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static System::MessageEmitter<UnselectedObjectMessage> * PickableObject::getUnselectedEmitter()
		///
		/// \brief	Gets the UnselectedObjectMessage emitter.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	null if it fails, else the unselected emitter.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static System::MessageEmitter<UnselectedObjectMessage> * getUnselectedEmitter();
	
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	PickableObject::PickableObject(Ogre::Node * object);
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param object	the pickable object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		PickableObject(Ogre::Node * object) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual PickableObject::~PickableObject();
		///
		/// \brief	Destructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ~PickableObject() ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void PickableObject::onSelect() = 0;
		///
		/// \brief	Called when the object is selected.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void onSelect();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void PickableObject::onUnselect() = 0;
		///
		/// \brief	Called when the object is unselected.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void onUnselect();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool PickableObject::isSelected() const;
		///
		/// \brief	Query if this object is selected.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	true if selected, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isSelected() const;
	};


}

#endif