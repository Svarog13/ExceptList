#include<iostream>
#include<string>

class ListException : public std::exception
{
private:
	std::string message;
public:
	ListException(const std::string & msg) : message (msg){}
	const char* what()const noexcept override
	{
		return message.c_str();
	}
};
class Node
{
public:
    int data;
    Node* next;
    Node* prev;

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList
{
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    bool IsEmpty() const
    {
        return head == nullptr;
    }

    void Append(int val)
    {
        Node* newNode = new Node(val);
        if (IsEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    int RemoveTail()
    {
        if (IsEmpty())
        {
            throw ListException("Cannot remove from an empty list.");
        }

        Node* lastNode = tail;
        int data = lastNode->data;

        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = lastNode->prev;
            tail->next = nullptr;
        }
        delete lastNode;
        return data;
    }

    void Clear()
    {
        while (!IsEmpty())
        {
            RemoveTail();
        }
    }

    void Print()const
    {
        Node* current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
	~DoublyLinkedList()
	{
		Clear();
	}
	
};

int main()
{
    DoublyLinkedList list;
    try
    {
        list.Append(10);
        list.Append(20);
        list.Append(30);
        list.Print();

        int removedValue = list.RemoveTail();
        std::cout << "Removed value: " << removedValue << std::endl;
        list.Print();

        list.Clear();
        list.Print(); 
    }
    catch (const ListException& ex)
    {
        std::cerr << "List Error: " << ex.what() << std::endl;
    }

    return 0;
}