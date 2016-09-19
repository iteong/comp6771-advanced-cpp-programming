#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

// library to store objects of type T and descriptions of type U
// if too many variations, will slow down the compiling
template <typename T, typename U> // typename types can be books or movies, or audio CDs for T (multiple versions by compiler)
class Library {
	
public:
	// mutators to change the contents of the library
	void add(const T& item);
	unsigned int remove(const T& item);
	void addRelated(const T& from, const T& to, const U& desc);
	void printRelated(const T& from);
	bool inLibrary(const T& item);
	
private:

	// private inner class to hold objects of type T in the library. 
	class ItemContainer {
	public:
		
		// constructor for creating a new ItemContainer to store an item
		ItemContainer(const T& item) : itemPtr{std::make_shared<T>(item)} {}
		
		const T& getItem() const { return *itemPtr; }
		void addRelated(const ItemContainer& to, const U& desc);
		std::shared_ptr<T> getItemPtr() const { return itemPtr; }
		void printRelated();
	
	private:
		
		// private inner class to hold information about related works.
		class RelatedWork { // inner inner class (inside ItemContainer inside Library
		public:
			RelatedWork(const ItemContainer& link, const U& desc);
			void printItemAndDescription();
		private:
			// private data members of RelatedWork
			U relatedWorkDescription;
			std::weak_ptr<T> relatedWorkLink_; // converted to weak pointer from shared pointer
		};
	
	
		// private data members of ItemContainer
		std::shared_ptr<T> itemPtr;
		std::vector<RelatedWork> relatedWorks;
	};
	
	// private data member of Library Class
	std::vector<ItemContainer> items;
};

// method to add a new item to the library.
template <typename T, typename U>
void Library<T,U>::add(const T& item) {
	// check to prevent duplicates
	// use InLibrary to find if it's already inside library
	if (inLibrary(item)) { // add try catch in main to catch exception without terminating program
		// without throw still works, but better if throw exception
		auto ss = std::stringstream{}; // use stream object to stream strings into it and put into throw
		ss << "Error: the item \"" << item << "\" is already in the library";
		throw std::invalid_argument{ss.str()};
	}

	ItemContainer newItem{item};
	items.push_back(newItem);
}

// method to add a related works to an existing item
template <typename T, typename U>
void Library<T,U>::addRelated(const T& from, const T& to, const U& desc) {
		// find from itemContainer. 
		auto fromIC = std::find_if(items.begin(), items.end(), [&from] (const ItemContainer& ic) {
			return from == ic.getItem();
		});
		// find to
		auto toIC = std::find_if(items.begin(), items.end(), [&to] (const ItemContainer& ic) {
			return to == ic.getItem();
		});
		// add desc
		fromIC->addRelated(*toIC,desc);
}

// method to remove an item from the library. 
template <typename T, typename U>
unsigned int Library<T,U>::remove(const T& item) {
	// TODO: remove the item from the library
	auto to_remove = std::find_if(items_.cbegin(), items_.cend(), // and UnararyPredicate (function that returns true/false that only takes in one argument)
		[&item](const ItemContainer& ic){ return item == ic.getItem(); }); // if item we want to find equals to ic, then pass the iterator

if (to_remove != items_.cend()) { items_.erase(to_remove); }// if it is not at the last element (meaning it found the item it wants to find)

return items.size();
}

// method to print the related works for a given item. 
template <typename T, typename U>
void Library<T,U>::printRelated(const T& from) {
	// find from itemContainer. 
	auto fromIC = std::find_if(items.begin(), items.end(), [&from] (const ItemContainer& ic) {
		return from == ic.getItem();
	});
	fromIC->printRelated();
}

// method to check if an item is already in the library
template <typename T, typename U>
bool Library<T,U>::inLibrary(const T& item) {
	auto ic = std::find_if(items.begin(), items.end(), [&item] (const ItemContainer& ic) {
		return item == ic.getItem();
	});
	if (ic == items.end()) return false;
	return true;
}

// method to add a related works object to the item container. 
template <typename T, typename U>
void Library<T,U>::ItemContainer::addRelated(const ItemContainer& to, const U& desc) {
	RelatedWork rw{to,desc};
	relatedWorks.push_back(rw);
}

// method to print each related item in a container. 
template <typename T, typename U>
void Library<T,U>::ItemContainer::printRelated() {
	for (auto related : relatedWorks) {
		related.printItemAndDescription();
	}
}

// constructor for a related works object 
template <typename T, typename U>
Library<T,U>::ItemContainer::RelatedWork::RelatedWork(const ItemContainer& link, const U& desc) : relatedWorkDescription{desc} {
	relatedWorkLink = link.getItemPtr();
}

// method to print the item and description of a related work. 
template <typename T, typename U>
void Library<T,U>::ItemContainer::RelatedWork::printItemAndDescription() {
	auto sp = relatedWorkLink_.lock(); // lock gets the shared pointer from weak pointer, and print out *sp if it is not nullptr
	if (sp != nullptr) {
		std::cout << *sp << " - " << relatedWorkDescription << std::endl;
	}
	
}
