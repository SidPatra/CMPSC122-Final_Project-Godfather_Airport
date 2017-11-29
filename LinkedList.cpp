// Name:		LinkedList
// Author:		Donavan Keen
// Purpose:		This class holds a List of integers to create a dynamic
//				array.
// Limitations:	This class only can only store integer values.
class LinkedList
{
public:
	// Name:		LinkedList::LinkedList()
	// Purpose:		This function acts as a constructor for the LinkedList class.
	//				it creates the first node.
	// Inputs:		None
	// Outputs:		None
	LinkedList::LinkedList()
	{
		first = nullptr;
		last = nullptr;
	}

	// Name:		LinkedList::~LinkedList()
	// Purpose:		This function frees the memory of the
	//				list to make sure there are no memory leaks
	// Inputs:		None
	// Outputs:		None
	LinkedList::~LinkedList()
	{
		Node* current = first;
		Node* next;

		for (int i = 0; i < sizeNum - 1; i++)
		{
			next = current->next;
			delete(current);
			current = next;
		}
		if (last != nullptr)
		{
			delete(last);
		}
		sizeNum = 0;
	}

	// Name:		LinkedList::addElementFront(int x)
	// Purpose:		This function adds an element to the front of the LinkedList
	// Inputs:		integer, value to be added
	// Outputs:		None
	void LinkedList::addElementFront(int x)
	{
		if (first == nullptr)
		{
			first = new Node(x, nullptr, nullptr);
			last = first;
		}
		else
		{
			Node* tmpPtr = first;
			first = new Node(x, nullptr, tmpPtr);	// Adding the element to the front

			tmpPtr->prev = first;		//assigning pointing second node prev to first node
		}
		sizeNum++;
	}

	// Name:		LinkedList::addElementBack(int x)
	// Purpose:		This function adds an element to the bacl of the LinkedList
	// Inputs:		integer, value to be added
	// Outputs:		None
	void LinkedList::addElementBack(int x)
	{
		if (first == nullptr)
		{
			first = new Node(x, nullptr, nullptr);
			last = first;
		}
		else
		{
			Node* tmpPtr = last;
			last = new Node(x, tmpPtr, nullptr);	// Adding the element to the front

			tmpPtr->next = last;		//assigning pointing second node prev to first node
		}
		sizeNum++;
	}

	// Name:		LinkedList::insertElement(int location, int x)
	// Purpose:		This function adds an element to the front of the LinkedList
	// Inputs:		int location, the index to insert at, int x, the value to be inserted
	// Outputs:		None
	void LinkedList::insertElement(int location, int x)
	{
		// If the insert location is larger than any index in the 
		// list, we can just add the element to the back of the list.
		// This also works in the case that there are no elements
		// in the list.
		if (location >= sizeNum)
		{
			this->addElementBack(x);
		}
		else if (location == 0)
		{
			this->addElementFront(x);
		}
		else
		{
			Node* currentPtr = first;

			for (int i = 0; i <= location; i++)
			{
				if (i == location)
				{
					Node* tmpPtr = currentPtr;
					Node* prevPtr = tmpPtr->prev;

					currentPtr = new Node(x, prevPtr, tmpPtr);	// Create new element at index

					tmpPtr->prev = currentPtr;				// Reassign next node's prev
					(currentPtr->prev)->next = currentPtr;	// Reassign prev node's next

					sizeNum++;
				}
				else
				{
					currentPtr = currentPtr->next;
				}
			}
		}
	}

	// Name:		LinkedList::deleteElement(int x)
	// Purpose:		This function deletes an element with the value passed to it
	// Inputs:		integer, id to be deleted
	// Outputs:		None
	// Limitations:	This function only deletes the first value found to match the input
	void LinkedList::deleteElement(int x)
	{
		bool deleted = false;
		Node* currentPtr = first;
		int i = 0;

		if (first == nullptr)
		{
			// This block just ensures we don't try to dereference a nullptr.
			// It is here as protection, from here, we check if the value was
			// deleted and print that the value was not found and not deleted.
		}
		else if (first->id == x)
		{
			this->removeFront();
			deleted = true;

		}
		else if (last->id == x)
		{
			this->removeBack();
			deleted = true;
		}
		else
		{
			while (!deleted && i < sizeNum - 1)
			{
				if (currentPtr->id == x)
				{

					(currentPtr->prev)->next = currentPtr->next;
					(currentPtr->prev)->prev = currentPtr->prev;

					delete(currentPtr);

					currentPtr = nullptr;
					deleted = true;
					sizeNum--;
				}
				else
				{
					currentPtr = currentPtr->next;
				}
				i++;
			}
		}
	}

	// Name:		LinkedList::removeFront()
	// Purpose:		This function deletes the element at the front of the LinkedList
	// Inputs:		None
	// Outputs:		None
	void LinkedList::removeFront()
	{
		if (sizeNum == 0)
		{
			cout << endl << "The List is Empty." << endl;
		}
		else if (sizeNum == 1)
		{
			// Special case where there is only one node in the list
			delete(first);
			first = nullptr;
			last = nullptr;
			sizeNum--;
		}
		else
		{
			Node* tmpPtr = first->next;
			delete(first);
			first = tmpPtr;
			tmpPtr->prev = nullptr;
			sizeNum--;
		}
	}

	// Name:		LinkedList::removeBack()
	// Purpose:		This function deletes the element at the back of the LinkedList
	// Inputs:		None
	// Outputs:		None
	void LinkedList::removeBack()
	{
		if (sizeNum == 0)
		{
			cout << endl << "The List is Empty." << endl;
		}
		else if (sizeNum == 1)
		{
			// Special case where there is only one node in the list
			delete(first);
			first = nullptr;
			last = nullptr;
			sizeNum--;
		}
		else
		{
			Node* tmpPtr = last->prev;
			delete(last);
			last = tmpPtr;
			tmpPtr->next = nullptr;
			sizeNum--;
		}
	}

	// Name:		LinkedList::getFirst()
	// Purpose:		This function returns a pointer to the first node
	//				of the LinkedList
	// Inputs:		None
	// Outputs:		Pointer to first node in the list
	Node* LinkedList::getFirst()
	{
		return first;
	}

	// Name:		LinkedList::getLast()
	// Purpose:		This function returns a pointer to the last node
	//				of the LinkedList
	// Inputs:		None
	// Outputs:		Pointer to last node in the list
	Node* LinkedList::getLast()
	{
		return last;
	}


	// Name:		LinkedList::getSize()
	// Purpose:		This function returns the size of the LinkedList
	// Inputs:		None
	// Outputs:		int, sizeNum
	int LinkedList::getSize()
	{
		return sizeNum;
	}

private:
	struct Node
	{
		int id;			// id number to keep track of plane (used for deletion specifically)
		int action;		// 0 for departing, 1 for landing
		int refueling;	// 0 for not refueling, 1-9 for time left while refueling
		int people;		// Number of people onboard
		float cargo;	// Value of cargo onboard
		int waitTime;	// Time plane has spent waiting
		int fuelCap;	// Fuel capacity of the plane (The initial fuel of the plane)
		Node* next;
		Node* prev;

		// Name:	LinkedList::Node:Node( Node* p, Node* n)
		// Purpose:	Initializes values for the Node
		// Inputs:	Node* p = prev, Node* n = next
		// Outputs:	None
		Node( Node* p, Node* n)
		{
			next = n;
			prev = p;
		}
	};
	Node* first;
	Node* last;
	int sizeNum = 0;
};
