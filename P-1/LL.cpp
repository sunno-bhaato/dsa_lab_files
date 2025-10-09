#include <iostream>
#include "LL.h"
using namespace std;

//declare struct for Node
struct Node{ int data; Node* next; };
Node* head;

//constructors
LL::LL(){
	head = nullptr;
}
LL::LL(int element){
	Node* newNode = new Node();
	head = newNode;
	newNode->data = element;
	newNode->next = nullptr;
}
//destructors
LL::~LL(){
	Node* current = head;
	while(current != nullptr){
		Node* next_node = current->next;
		delete current;
		current = next_node;
	}
	head = nullptr;
}

bool LL::isEmpty() const
{
	return head == nullptr;
}

void LL::printList() const{
	Node* cur = head;
	while(cur != nullptr){
		cout<<cur->data<<'\t';
		cur = cur->next;
	}
	cout<<'\n';
}

//insertion at beginning
void LL::insertAtBeginning(int x){
	Node* newNode = new Node();
	newNode->data = x;
	newNode->next = head;
	head = newNode;
}

//insert at end
void LL::insertAtEnd(int x){
	Node* current = head;
	if(current == nullptr){
		Node* newNode = new Node();
		head = newNode;
		newNode->data = x;
		newNode->next = nullptr;
		return;
	}
	
	while(current->next != nullptr){
		current = current->next;
	}

	Node* newNode = new Node();
	current->next = newNode;
	newNode->data = x;
	newNode->next = nullptr;
}

//insert x at given index k
void LL::insertAtIndex(int x, int k){
	if(k==0) LL::insertAtBeginning(x);
	else{
		Node* cur = head;

		for(int i=0;i<k-1;i++){
			if(cur == nullptr){
				cout<<"Index out of range.\n";	return;
			}
			cur = cur->next;
		}
		
		if(cur == nullptr){
			cout<<"Index out of range.\n";	return;
		}
		
		Node* newNode = new Node();
		newNode->data = x;
		newNode->next = cur->next;
		cur->next = newNode;
		
	}
}

//delete from beginning
void LL::delFromBeginning(){
	Node* current = head;
	if(current == nullptr){
		cout<<"No node available to delete.\n";
	}
	else{
		head = head->next;
		delete current;
	}
}

//delete from end
void LL::delFromEnd(){
	Node* current = head;
	if(current == nullptr){
		cout<<"No node available to delete.\n";
	}
	else if(current->next == nullptr){
		head = nullptr;
		delete current;
	}
	else{
		while(current->next->next != nullptr){
			current = current->next;
		}
		
		Node* temp = current->next;
		current->next = nullptr;
		delete temp;
	}
}

//delete from given index
void LL::delFromIndex(int k){
	if(k==0) LL::delFromBeginning();
	else{
		Node* cur = head;
		for(int i=0;i<k-1;i++){
			if(cur == nullptr){
				cout<<"Index out of range.\n";	return;
			}
			cur = cur->next;
		}
		
		if(cur == nullptr || cur->next == nullptr){
			cout<<"Index out of range.\n";	return;
		}
		
		Node* temp = cur->next;
		cur->next = cur->next->next;
		delete temp;
	}
}

//return non-negative index if x is in list, else return -1 
int LL::searchList(int x){
	Node* cur = head;
	int index = 0;
	while(cur != nullptr){
		if(cur->data == x) return index;
		index++;
		cur = cur->next;
	}
	return -1;
}

//delete first occurence of given x
void LL::delElement(int x){
	int index = searchList(x);
	if(index==-1) cout<<"Given element "<<x<<" not found.\n";
	else delFromIndex(index);
}

void LL::sort_asc(){
	// insertion sort implementation

	if(head == nullptr || head->next == nullptr){cout<<"Nothing to sort really.\n";	return;}
	
	Node* cur = head->next;
	Node* prev = head;
	int index = 1;
	while(cur != nullptr){
		if(cur->data >= prev->data){
			index++;
			prev = cur;
			cur = cur->next;
		}
		else{
			int myData = cur->data;
			cur = cur->next;		// crucial step before deletion of current Node, to prevent cur from being a dangling pointer
			LL::delFromIndex(index);
			Node* temp = head;
			for(int i=0;i<index;i++){
				if(myData < temp->data){
					LL::insertAtIndex(myData, i);
					break;
				}
				temp = temp->next;
			}
			index++;	// prev remains unchanged since the Node at prev itself gets shifted by 1 forward
		}
	}
}

LL LL::merge(const LL &b){
	LL merged;
	Node* current = head;
	while(current != nullptr){
		merged.insertAtEnd(current->data);
		current = current->next;
	}
	current = b.head;
	while(current != nullptr){
		merged.insertAtEnd(current->data);
		current = current->next;
	}
	return merged;
}

void LL::reverse(){
	Node* prev = nullptr;
	Node* cur = head;
	Node* temp;
	while(cur != nullptr){
		temp = cur;
		cur = cur->next;
		temp->next = prev;
		prev = temp;
	}
	head = prev;
}

LL::Node* LL::reverse_recursive_help(LL::Node* r) {
	if (r == nullptr || r->next == nullptr)
		return r;
	LL::Node* rest = LL::reverse_recursive_help(r->next);
	r->next->next = r;
	r->next = nullptr;
	return rest;
}

void LL::reverse_recurse(){
	head = LL::reverse_recursive_help(head);
}

LL::Node* LL::getHead() const{
	return head;
}


