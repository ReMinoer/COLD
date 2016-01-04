#ifndef _DesignPattern_Singleton_H
#define _DesignPattern_Singleton_H

namespace DesignPattern
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief A Singleton. To create a singleton, you must inherit this class, add
	/// 	   the class Singleton as a firned of the newly created class and create
	/// 	   a private default constructor and a private destructor.
	/// 	 
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Type>
	class Singleton
	{
	private:
		static Type * s_value ;

	public:
		static Type * getInstance()
		{
			if(s_value==NULL)
			{
				s_value = new Type ;
			}
			return s_value ;
		}
	};

	template <class Type>
	Type * Singleton<Type>::s_value = NULL ;
}

#endif