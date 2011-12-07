#include <iostream>
#include <string>
using namespace std;

struct sLLnode {
	int n;
	struct sLLnode* next;
};	

sLLnode* addSorted(int n, sLLnode* &list) {
	if (list == 0)
	{
		sLLnode* newList = new sLLnode;
		newList->n = n;
		newList->next = 0;
		list = newList;
		return newList;
	} else if (list->n > n){
		sLLnode* newList = new sLLnode;
		newList->n = n;
		newList->next = list;
		list = newList;
		return list;
	} else {
		sLLnode* current = list;
		while (current->next != 0 && n >= current->next->n)
			current = current->next;
		if (n != current->n) {
			// n should be greater than current->n
			sLLnode* newNode = new sLLnode;
			newNode->n = n;
			newNode->next = current->next;
			current->next = newNode;
			return current;
		}
	}
}

bool contains(int n, sLLnode* &list) {
	sLLnode *current = list;
	while (current != 0) {
		if (current->n == n) 
			return true;
		current = current->next;
	}
	return false;
}

sLLnode* unionWith(sLLnode* &a, sLLnode* &b) {
	sLLnode *current = b;
	while (current != 0) {
		addSorted(current->n, a);
		current = current->next;
	}
	return a;
}

sLLnode* removeSorted(int n, sLLnode* &list) {
	sLLnode *current = list;
	sLLnode *prev = 0;
	while (current != 0 && n > current->n) {
		prev = current;
		current = current->next;
	}
	if (current != 0) { 
		if (prev != 0) {
			prev->next = current->next;
		} else {
			list = current->next;
		}
	}
	

}

sLLnode* intersectWith(sLLnode* &a, sLLnode* &b) {
	sLLnode* current = a;
	while (current != 0) {
		if (!(contains(current->n, b))) {
			removeSorted(current->n, a);
		}
		current = current->next;
	}
}

int main() {
	sLLnode* list = 0;
	addSorted(5, list);
	cout << "Contains 5 ? " << contains(5, list) << endl;
	addSorted(3, list);
	addSorted(4, list);
	addSorted(6, list);
	cout << "Contains 4 ? " << contains(4, list) << endl;
	addSorted(4, list);
	cout << "Contains 8 ? " << contains(8, list) << endl;
	sLLnode* listB = 0;
	addSorted(8, listB);
	addSorted(1337, listB);
	addSorted(42, listB);
	addSorted(4, listB);
	
	unionWith(list, listB);
	cout << "Contains 8 ? " << contains(8, list) << endl;
	removeSorted(8, listB);
	removeSorted(1337, listB);
	removeSorted(4, listB);
	intersectWith(list, listB);
	cout << "Contains 8 ? " << contains(8, list) << endl;
	
	
	while (list != 0) {
		cout << list->n << " ";
		list = list->next;
	}
cout << endl << "listb" << endl;	
	while (listB != 0) {
		cout << listB->n << " ";
		listB = listB->next;
	}
	
}


