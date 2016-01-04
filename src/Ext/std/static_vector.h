#ifndef _Rennes1_Ext_std_static_vector_H
#define _Rennes1_Ext_std_static_vector_H

#include <boost/iterator/reverse_iterator.hpp>

namespace Ext
{
	namespace std
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \class	static_vector
		///
		/// \brief	STL compliant vector of elements with fixed maximal size. This vector do not use dynamic 
		///         memory allocation to enhance performances. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	06/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <class Type, unsigned int t_size>
		class static_vector 
		{
		public:
			//! Type of elements. 
			typedef Type value_type ;
			//! Pointer to the element type. 
			typedef Type * pointer ;
			//! Reference to the element type. 
			typedef Type & reference ;
			//! Const reference to the element type. 
			typedef const Type & const_reference ;
			//! Type of the size. 
			typedef unsigned int size_type ;
			//! Iterator on elements. 
			typedef Type * iterator ;
			//! Const iterator on elements. 
			typedef const Type * const_iterator ;
			//! Reverse iterator on elements. 
			typedef ::boost::reverse_iterator<iterator> reverse_iterator ;
			//! Const reverse iterator on elements. 
			typedef ::boost::reverse_iterator<const_iterator> const_reverse_iterator ;

		protected:
			//! Current size of the vector. 
			size_type m_size ;
			//! Elements of the vector. 
			Type m_vector[t_size] ;

			Type * firstElementPointer()
			{
				return (Type*)m_vector ;
			}

			const Type * firstElementPointer() const
			{
				return (Type*)m_vector ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void shiftRight(iterator pos, size_type nb, const_reference value=value_type())
			///
			/// \brief	Shift the table on the right. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	08/12/2009
			///
			/// \param	pos		The first position of shifting. 
			/// \param	nb		The number of shifts. 
			/// \param	value	The value inserted from pos. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void shiftRight(iterator pos, size_type nb, const_reference value=value_type())
			{
				assert(m_size+nb<t_size) ;
				iterator end = firstElementPointer()+m_size-1 ;
				while(end>=pos)
				{
					*(end+nb) = *end ;
					--end ;
				}
				for(iterator it=pos ; it!=pos+nb ; ++it)
				{
					*it=value ;
				}
				m_size+=nb ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void shiftLeft(iterator pos, size_type nb)
			///
			/// \brief	Shift the table on the left. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	08/12/2009
			///
			/// \param	pos	The first position of shifting. 
			/// \param	nb	The number of shifts. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void shiftLeft(iterator pos, size_type nb)
			{
				while(pos+nb<firstElementPointer()+m_size-1)
				{
					*pos = *(pos+nb) ;
					pos++ ;
				}
				for(iterator it=firstElementPointer()+m_size-nb, end=firstElementPointer()+m_size ; it!=end ; ++it)
				{
					*it = value_type() ;
				}
				m_size -= nb ;
			}

		public:

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	static_vector(size_type initialSize=0, Type const & initVal = value_type())
			///
			/// \brief	Constructor. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	initialSize		Initial size of the vector. 
			/// \param [in]	initVal	    Defaut value of elements. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			static_vector(size_type initialSize=0, Type const & initVal = value_type())
				: m_size(initialSize)
			{
				assert(initialSize>=0 && initialSize<=t_size) ;
				for(size_type cpt=0 ; cpt<initialSize ; ++cpt)
				{
					firstElementPointer()[cpt] = initVal ;
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	size_type max_size() const
			///
			/// \brief		Returns the largest possible size of the vector.  
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			size_type max_size() const { return t_size ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reference operator[] (size_type index)
			///
			/// \brief	 Returns the n'th element. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	index	index of the element. 
			///
			/// \return	the n'th element. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			reference operator[] (size_type n) 
			{
				assert(n>=size_type(0) && n<m_size) ;
				return firstElementPointer()[n] ; 
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reference operator[] (size_type index)
			///
			/// \brief	 Returns the n'th element. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	index	index of the element. 
			///
			/// \return	the n'th element. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			const_reference operator[] (size_type n) const
			{
				assert(n>=size_type(0) && n<m_size) ;
				return firstElementPointer()[n] ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reference front()
			///
			/// \brief Returns the first element. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			reference front() { return *begin() ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reference front()
			///
			/// \brief Returns the first element. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			const_reference front() const { return *begin() ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reference back()
			///
			/// \brief	Returns the last element. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			reference back() { return *(begin()+m_size-1) ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reference back()
			///
			/// \brief	Returns the last element. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			const_reference back() const { return *(begin()+m_size-1) ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void push_back(const_reference value)
			///
			/// \brief		Inserts a new element at the end.
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	value	The value to insert. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void push_back(const_reference value)
			{
				assert(m_size<t_size) ;
				if(!(m_size<t_size)) { char * toto = NULL ; *toto = 10 ; }
				firstElementPointer()[m_size] = value ;
				m_size++ ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void pop_back()
			///
			/// \brief		Removes the last element. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void pop_back()
			{
				assert(m_size!=0) ;
				m_size-- ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void insert(iterator pos, const_reference value)
			///
			/// \brief	Inserts value before pos. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	pos		The position. 
			/// \param	value	The value. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void insert(iterator pos, const_reference value)
			{
				assert(m_size<t_size) ;
				shiftRight(pos, 1) ;
				*pos = value ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void insert(iterator pos, size_type n, const_reference value)
			///
			/// \brief	Inserts n copies of value before pos. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	pos		The position. 
			/// \param	n		Number of elements to insert. 
			/// \param	value	The value of inserted elements. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void insert(iterator pos, size_type n, const_reference value)
			{
				shiftRight(pos, n, value) ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void erase(iterator pos)
			///
			/// \brief	Erases the element at position pos. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	pos	The position. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void erase(iterator pos)
			{
				shiftLeft(pos, 1) ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void erase(iterator first, iterator last)
			///
			/// \brief	Erases elements in range [first;last[. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	first	The first element. 
			/// \param	last	The last element. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void erase(iterator first, iterator last)
			{
				shiftLeft(first, size_type(last-first)) ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void clear()
			///
			/// \brief	Clears this object to its blank/initial state. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void clear()
			{
				erase(begin(), end()) ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	bool empty() const
			///
			/// \brief		true if the vector's size is 0. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	true if the vector's size is 0. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			bool empty() const { return m_size==0 ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	size_type size() const
			///
			/// \brief	Returns the size of the vector.  
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			size_type size() const { return m_size ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void reserve(size_type size)
			///
			/// \brief	Reserves space for storing size elements. This method has been added for compatibility
			///         with ::std::vector interface. In this implementation it does nothing. 
			///
			/// \warning The constraint size<t_size should be ensured !
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	08/12/2009
			///
			/// \param	size	The "reserved" size. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void reserve(size_type size)
			{
				assert(size<=t_size) ;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	void resize(size_type n, const_reference value=value_type())
			///
			/// \brief	Resizes the vector. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \param	n		The new size. 
			/// \param	value	The value f inserted elements (if any). 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			void resize(size_type n, const_reference value=value_type())
			{
				if(n>m_size)
				{
					int count=n ;
					while(count>0)
					{
						push_back(value) ;
						--count ;
					}
				}
				else if(n<m_size)
				{
					erase(end()-n, end()) ;
				}
				m_size = n ;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	iterator begin()
			///
			/// \brief	Returns an iterator pointing to the beginning of the vector. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			iterator begin() { return firstElementPointer() ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	iterator end()
			///
			/// \brief		Returns an iterator pointing to the end of the vector. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			iterator end() { return firstElementPointer()+m_size ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	const_iterator begin() const
			///
			/// \brief		Returns a const_iterator pointing to the beginning of the vector.  
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			const_iterator begin() const { return firstElementPointer() ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	const_iterator end() const
			///
			/// \brief	Returns a const_iterator pointing to the end of the vector.  
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	06/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			const_iterator end() const { return firstElementPointer()+m_size ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	const_reverse_iterator rbegin() const
			///
			/// \brief	Returns a reverse iterator pointing to the last element of this object. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	08/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			const_reverse_iterator rbegin() const { return ::boost::reverse_iterator<const_iterator>(firstElementPointer()+(m_size-1)) ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	const_reverse_iterator rend() const
			///
			/// \brief	Returns a reverse iterator pointing to the "reverse" end of this object. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	08/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			const_reverse_iterator rend() const { return ::boost::reverse_iterator<const_iterator>(firstElementPointer()-1) ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reverse_iterator rbegin()
			///
			/// \brief	Returns a reverse iterator pointing to the last element of this object. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	08/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			reverse_iterator rbegin()  { return ::boost::reverse_iterator<iterator>(firstElementPointer()+(m_size)) ; }

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	reverse_iterator rend()
			///
			/// \brief	Returns a reverse iterator to the "reverse" end of this object. 
			///
			/// \author	Fabrice Lamarche, University Of Rennes 1
			/// \date	08/12/2009
			///
			/// \return	. 
			////////////////////////////////////////////////////////////////////////////////////////////////////
			reverse_iterator rend() { return ::boost::reverse_iterator<iterator>(firstElementPointer()) ; }

			int find(Type const & value) const
			{
				for(int cpt=0 ; cpt<(int)m_size ; ++cpt)
				{
					if(m_vector[cpt]==value) { return cpt ; }
				}
				return m_size ;
			}
		};
	}
}

#endif