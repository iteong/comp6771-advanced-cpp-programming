#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <sstream>

class MyException : public std::runtime_error
{
public:
    MyException(const std::string& str) : std::runtime_error(str){ };
};

// -------------------------------------------------------------------------------
// library to store objects of type T and descriptions of type U
// -------------------------------------------------------------------------------

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

private:

    // --------------------------------------------------------------------------
	// private inner class to hold objects of type T in the library.
    // --------------------------------------------------------------------------
	class ItemContainer
    {
	public:

		// constructor for creating a new ItemContainer to store an item
		ItemContainer(const T& item);

		const T& getItem() const;
		void addRelated(const ItemContainer& to, const U& desc);
		std::shared_ptr<T> getItemPtr() const;
		void printRelated();

	private:

        // --------------------------------------------------------------------------
		// private inner class to hold information about related works.
        // --------------------------------------------------------------------------
		class RelatedWork
        {
		public:
			RelatedWork(const ItemContainer& link, const U& desc);
			void printItemAndDescription();
		private:
			// private data members of RelatedWork
			U relatedWorkDescription_;

            //-------------------
            // Q7 Use weak_ptr
//			std::shared_ptr<T> relatedWorkLink_;

			std::weak_ptr<T> relatedWorkLink_;

            //-------------------

		};

		// private data members of ItemContainer
		std::shared_ptr<T> itemPtr_;
		std::vector<RelatedWork> relatedWorks_;
	};

	// private data member of Library Class
	std::vector<ItemContainer> items_;
};

// -------------------------------------------------------------------------------
// Implementation of Library
// -------------------------------------------------------------------------------

// method to add a new item to the library.
template <typename T, typename U>
void Library<T,U>::add(const T& item)
{

    //-------------------------
    // Q9 - Don't add duplicate

    // Check if the item exits
    if (inLibrary(item))
    {
        std::stringstream ss;
        ss << "Item \"" << item << "\" already exists in library";
        throw std::invalid_argument(ss.str());
//        throw MyException(ss.str());
    }

    //-------------------------

	ItemContainer newItem{item};
	items_.push_back(newItem);

}

// method to add a related works to an existing item
template <typename T, typename U>
void Library<T,U>::addRelated(const T& from, const T& to, const U& desc)
{
    // find from itemContainer.
    auto fromIC = std::find_if(items_.begin(), items_.end(),
                               [&from] (const ItemContainer& ic)
                               {
                                   return from == ic.getItem();
                               });
    // find to
    auto toIC = std::find_if(items_.begin(), items_.end(),
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
    // Tute: Q6
	// TODO: remove the item from the library

    //-------------------

    // First need to find the item
    auto toRemove = std::find_if(items_.begin(), items_.end(),
                                 [&item] (const ItemContainer& ic)
                                 {
                                     return item == ic.getItem();
                                 });

    if (toRemove != items_.end())
        items_.erase(toRemove);

    //-------------------

	return items_.size();
}

// method to print the related works for a given item.
template <typename T, typename U>
void Library<T,U>::printRelated(const T& from)
{
	// find from itemContainer.
	auto fromIC = std::find_if(items_.begin(), items_.end(),
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
	auto ic = std::find_if(items_.begin(), items_.end(),
                           [&item] (const ItemContainer& ic)
                           {
                               return item == ic.getItem();
                           });
	if (ic == items_.end()) return false;
	return true;
}

// -------------------------------------------------------------------------------
// Implementation of Library::ItemContainer
// -------------------------------------------------------------------------------

template <typename T, typename U>
Library<T,U>::ItemContainer::ItemContainer(const T& item) :
    itemPtr_{std::make_shared<T>(item)} {}

template <typename T, typename U>
const T& Library<T,U>::ItemContainer::getItem() const
{
    return *itemPtr_;
}

template <typename T, typename U>
std::shared_ptr<T> Library<T,U>::ItemContainer::getItemPtr() const
{
    return itemPtr_;
}


// method to add a related works object to the item container.
template <typename T, typename U>
void Library<T,U>::ItemContainer::addRelated(const ItemContainer& to, const U& desc)
{
	RelatedWork rw{to,desc};
	relatedWorks_.push_back(rw);
}

// method to print each related item in a container.
template <typename T, typename U>
void Library<T,U>::ItemContainer::printRelated()
{
	for (auto related : relatedWorks_)
    {
		related.printItemAndDescription();
	}
}

// -------------------------------------------------------------------------------
// Implementation of Library::ItemContainer::RelatedWork
// -------------------------------------------------------------------------------

// constructor for a related works object
template <typename T, typename U>
Library<T,U>::ItemContainer::RelatedWork::RelatedWork(const ItemContainer& link, const U& desc) :
    relatedWorkDescription_{desc}
{
    //-------------------
    // Q7 Note: this still works when we change the type from shared_ptr to weak_ptr
    //-------------------
	relatedWorkLink_ = link.getItemPtr();
}

// method to print the item and description of a related work.
template <typename T, typename U>
void Library<T,U>::ItemContainer::RelatedWork::printItemAndDescription()
{
    //-------------------
    // Q7: Needs to be modified to turn the weak_ptr into a shared_ptr

// 	std::cout << *(relatedWorkLink_) << " - " << relatedWorkDescription_ << std::endl;

    auto sp = relatedWorkLink_.lock();
    if (sp != nullptr)
        std::cout << *sp << " - " << relatedWorkDescription_ << std::endl;

    //-------------------
}

