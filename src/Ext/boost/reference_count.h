#ifndef _Ext_boost_reference_count_H
#define _Ext_boost_reference_count_H

#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>

namespace Ext
{
	namespace boost
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \class	reference_count
		///
		/// \brief	Class that implements all boost::intrusive_ptr<T> requirements. To use it, you just have
		/// 		to inherit from this class and use the boost:intrusive_ptr to designate your instances.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		class reference_count : public ::boost::noncopyable
		{
		private:
			unsigned int m_refCount ;

		public:

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	:::reference_count()
			///
			/// \brief	Default constructor which initiliazes the reference count to zero.
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			////////////////////////////////////////////////////////////////////////////////////////////////////
			reference_count()
				: m_refCount(0)
			{}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void :::intrusive_ptr_add_ref()
			///
			/// \brief	Increases the number of references.
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void intrusive_ptr_add_ref()
			{
				++m_refCount ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void :::intrusive_ptr_release()
			///
			/// \brief	Decreases the number of references.
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void intrusive_ptr_release()
			{
				--m_refCount ;
				if(m_refCount==0) { delete this ;}
			}

			virtual ~reference_count()
			{}
		};

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline void intrusive_ptr_add_ref(::Ext::boost::reference_count * object)
///
/// \brief	Used by ::boost::intrusive_ptr to incerase the number of references on an object inheriting
/// 		from class ::Ext::boost::reference_count.
///
/// \author	Fabrice Lamarche, university of Rennes 1
/// \param [in,out]	object	If non-null, the object.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void intrusive_ptr_add_ref(::Ext::boost::reference_count * object)
{
	object->intrusive_ptr_add_ref() ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline void intrusive_ptr_release(::Ext::boost::reference_count * object)
///
/// \brief	Used by ::boost::intrusive_ptr to decrease the number of references on an object inheriting
/// 		from class ::Ext::boost::reference_count.
///
/// \author	Fabrice Lamarche, university of Rennes 1
/// \param [in,out]	object	If non-null, the object.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void intrusive_ptr_release(::Ext::boost::reference_count * object)
{
	object->intrusive_ptr_release() ;
}

#endif