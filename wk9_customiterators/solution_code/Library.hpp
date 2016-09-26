#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>

//-----------------------------------------------------------------------------------
// LibraryItemIterator class declaration
//-----------------------------------------------------------------------------------

template <typename T>
class LibraryItemIterator
{
public:
    typedef std::ptrdiff_t                     difference_type;

    // TODO - Q8. What iterator category tag?
    typedef std::forward_iterator_tag          iterator_category;

    typedef T                                  value_type;
    typedef T*                                 pointer;
    typedef T&                                 reference;

    reference operator*() const;        // TODO Q14
    pointer operator->() const;         // TODO Q18

    LibraryItemIterator& operator++();  // TODO Q13

// Should also add postfix increment operator
//    LibraryItemIterator operator++(int);

    // TODO Q15
    bool operator==(const LibraryItemIterator& other) const;
    bool operator!=(const LibraryItemIterator& other) const;

    // TODO Q10
    LibraryItemIterator(std::shared_ptr<std::list<std::shared_ptr<T> > > v = nullptr);
private:
  std::shared_ptr<std::list<std::shared_ptr<T> > > sortedPointers;
};

//-----------------------------------------------------------------------------------
// LibraryItemIterator definitions
//-----------------------------------------------------------------------------------

// TODO Q14
template<typename T>
typename LibraryItemIterator<T>::reference LibraryItemIterator<T>::operator*() const
{
    return *(sortedPointers->front());
}

// TODO Q18
template<typename T>
typename LibraryItemIterator<T>::pointer LibraryItemIterator<T>::operator->() const
{
    return &(operator*());
}

// TODO Q15
template<typename T>
bool LibraryItemIterator<T>::operator==(const LibraryItemIterator& other) const
{
//    return sortedPointers == other.sortedPointers;

    if (sortedPointers == other.sortedPointers) return true;
    if (sortedPointers == nullptr || other.sortedPointers == nullptr) return false;

    return (*sortedPointers == *other.sortedPointers);
}

// TODO Q15
template<typename T>
bool LibraryItemIterator<T>::operator!=(const LibraryItemIterator& other) const
{
    return !operator==(other);
}

// TODO Q10
template<typename T>
LibraryItemIterator<T>::LibraryItemIterator(std::shared_ptr<std::list<std::shared_ptr<T> > > v) :
                                            sortedPointers{v} {}

// TODO Q13
template <typename T>
LibraryItemIterator<T>& LibraryItemIterator<T>::operator++()
{
    sortedPointers->pop_front();
    if (sortedPointers->size() == 0) sortedPointers = nullptr;
    return *this;
}


//-----------------------------------------------------------------------------------
// library to store objects of type T and descriptions of type U
//-----------------------------------------------------------------------------------

template <typename T, typename U>
class Library
{
public:
	// mutators to change the contents of the library
	void add(const T& item);
	unsigned int remove(const T& item);
	void addRelated(const T& from, const T& to, const U& desc);
	void printRelated(const T& from);
	bool inLibrary(const T& item);

	LibraryItemIterator<T> begin();
	LibraryItemIterator<T> end();

    // Note: should also have const versions of begin() and
    // end(). Will need a new LibraryItemConstIterator<T>.  So
    // something like:
    //
    // LibraryItemConstIterator<T> begin() const;
    // LibraryItemConstIterator<T> end() const;
    //
    // Since C++11 should also have cbegin(), cend().
private:

    //-------------------------------------------------------------------------------
	// private inner class to hold objects of type T in the library.
    //-------------------------------------------------------------------------------
	class ItemContainer
    {
	public:

		// constructor for creating a new ItemContainer to store an item
		ItemContainer(const T& item) : itemPtr{std::make_shared<T>(item)} {}

		const T& getItem() const { return *itemPtr; }
		void addRelated(const ItemContainer& to, const U& desc);
		std::shared_ptr<T> getItemPtr() const { return itemPtr; }
		void printRelated();

	private:

        //-------------------------------------------------------------------------------
		// private inner class to hold information about related works.
        //-------------------------------------------------------------------------------
		class RelatedWork
        {
		public:
			RelatedWork(const ItemContainer& link, const U& desc);
			void printItemAndDescription();
		private:
			// private data members of RelatedWork
			U relatedWorkDescription;
			std::shared_ptr<T> relatedWorkLink;
		};


		// private data members of ItemContainer
		std::shared_ptr<T> itemPtr;
		std::vector<RelatedWork> relatedWorks;
	};

	// private data member of Library Class
	std::vector<ItemContainer> items;
};

//-----------------------------------------------------------------------------------
// Library member functions
//-----------------------------------------------------------------------------------

// method to add a new item to the library.
template <typename T, typename U>
void Library<T,U>::add(const T& item)
{
	ItemContainer newItem{item};
	items.push_back(newItem);
}

// method to add a related works to an existing item
template <typename T, typename U>
void Library<T,U>::addRelated(const T& from, const T& to, const U& desc)
{
    // find from itemContainer.
    auto fromIC = std::find_if(items.begin(), items.end(),
                               [&from] (const ItemContainer& ic)
                               {
                                   return from == ic.getItem();
                               });
    // find to
    auto toIC = std::find_if(items.begin(), items.end(),
                             [&to] (const ItemContainer& ic)
                             {
                                 return to == ic.getItem();
                             });
    // add desc
    fromIC->addRelated(*toIC,desc);
}

// method to remove an item from the library.
template <typename T, typename U>
unsigned int Library<T,U>::remove(const T& item)
{
	
	
	
	return items.size();
}

// method to print the related works for a given item.
template <typename T, typename U>
void Library<T,U>::printRelated(const T& from)
{
	// find from itemContainer.
	auto fromIC = std::find_if(items.begin(), items.end(),
                               [&from] (const ItemContainer& ic)
                               {
                                   return from == ic.getItem();
                               });
	fromIC->printRelated();
}

// method to check if an item is already in the library
template <typename T, typename U>
bool Library<T,U>::inLibrary(const T& item)
{
	auto ic = std::find_if(items.begin(), items.end(),
                           [&item] (const ItemContainer& ic)
                           {
                               return item == ic.getItem();
                           });
	if (ic == items.end()) return false;
	return true;
}


//-----------------------------------------------------------------------------------
// TODO - Q11 - Create begin() and end() member functions

// iterator begin
template <typename T, typename U>
LibraryItemIterator<T> Library<T,U>::begin()
{
	auto sortedListPtr = std::make_shared<std::list<std::shared_ptr<T> > >();
	for (auto it : items) {
		sortedListPtr->push_back(it.getItemPtr());
	}
	return LibraryItemIterator<T>(sortedListPtr);
}


template <typename T, typename U>
LibraryItemIterator<T> Library<T,U>::end()
{
    return LibraryItemIterator<T>();
}

//-----------------------------------------------------------------------------------
// Library::ItemContainer member functions
//-----------------------------------------------------------------------------------

// method to add a related works object to the item container.
template <typename T, typename U>
void Library<T,U>::ItemContainer::addRelated(const ItemContainer& to, const U& desc)
{
	RelatedWork rw{to,desc};
	relatedWorks.push_back(rw);
}

// method to print each related item in a container.
template <typename T, typename U>
void Library<T,U>::ItemContainer::printRelated()
{
	for (auto related : relatedWorks)
    {
		related.printItemAndDescription();
	}
}

//-----------------------------------------------------------------------------------
// Library::ItemContainer::RelatedWork member functions
//-----------------------------------------------------------------------------------

// constructor for a related works object
template <typename T, typename U>
Library<T,U>::ItemContainer::RelatedWork::RelatedWork(const ItemContainer& link, const U& desc) :
    relatedWorkDescription{desc}
{
	relatedWorkLink = link.getItemPtr();
}

// method to print the item and description of a related work.
template <typename T, typename U>
void Library<T,U>::ItemContainer::RelatedWork::printItemAndDescription()
{
	std::cout << *(relatedWorkLink) << " - " << relatedWorkDescription << std::endl;
}
