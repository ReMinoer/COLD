#ifndef _DesignPattern_StaticMember_H
#define _DesignPattern_StaticMember_H

namespace DesignPattern
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Class used to avoid problems with initialization order of static members
	/// 	   in user defined classes. 
	/// 	   
	/// 	   Whenever you want to create a static member of type Type, replace your
	/// 	   declaration with a declaration similar to 
	/// 	   static StaticMember<Type> myStaticMember. The unique intance associated
	/// 	   to your static member is created when needed, ensuring that all initializations
	/// 	   will be acheived in the correct order.
	/// 
	/// \warning class Type must have a default constructor.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Type>
	class StaticMember
	{
	private:
		/// The instance
		Type * m_instance ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		StaticMember()
			: m_instance(NULL)
		{}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		~StaticMember()
		{
			if(m_instance!=NULL)
			{
				delete m_instance ;
			}
			m_instance = NULL ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief This method returns the associated instance. 
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Type * getInstance()
		{
			if(m_instance==NULL)
			{
				m_instance = new Type ;
			}
			return m_instance ;
		}
	};
}

#endif