#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Code to implement the functions in List.h

// Constructors-Destructors --------------------------

/**
 * @brief Creates a new list
 * 
 
 * @param dataEqual Function to use to check if 2 pieces of data are equal to each other
 * @param dataPrinter Function to use to print out a piece of data in the list
 * @param freeData Function to use to free data in a node when destroying the list
 * @return List The newly created list.
 */
ListPtr newList(bool (*dataEqual)(void *obj1, void*obj2), void (*dataPrinter)(void *data), void (*freeData)(void *data)) {
    ListPtr lp = (ListPtr)malloc(sizeof(ListObj));
    lp->head = NULL;
    lp->dataEqual = dataEqual;
    lp->dataPrinter = dataPrinter;
    lp->freeData = freeData;
    lp->length = 0;
    return lp;
}
    
/**
 * @brief Frees the space taken up by the list
 * 
 * @param pL       A pointer to the list to deallocate. The pointer should be set to NULL
 * @param freeData If to also free the data contained within the list
 */
void freeList( ListPtr *point_to_L, bool freeData) {
    if(freeData) {
        ListPtr L = (*point_to_L); //needs to free
        if(L != NULL) {
            while(L->head != NULL) {
                NodePtr temp = L->head;
                L->head = L->head->next;
                L->freeData(temp->data);
                free(temp);
            }
        }
        L->head = NULL;
        free(L);
        point_to_L = NULL;
    } else {

    }
}

// Access functions ----------------------------------

/**
 * @brief Gets the length of a list
 * 
 * @param L The list for which the length should be returned.
 * @return int The length of the list, or -1 if error
 */
int length( ListPtr L ) {
    //agenda not found
    if(L == NULL) {
        return -1;
    }
    return L->length;
}

/**
 * @brief Returns the index of the search data in the list
 * 
 * @param L The list to check
 * @param comp The data to search for
 * @return int The index of the data in the list, or -1 if not in list
 */
int findElement( ListPtr L, void *comp ) {
    if(L) {
        NodePtr cur = L->head;
        int index = -1;

        while(cur != NULL) {
            index++;
            if (L->dataEqual(cur->data, comp)) {
                return index;
            }
            cur = cur->next;
        }
        return -1;
    } else {
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Returns the data stored at the index i.
 * 
 * @param i The index to fetch
 * @return void* The data at the index, or NULL if out of range
 */
void *getElement( ListPtr L, int i) {
    if(L) {
        NodePtr cur = L->head;
        while(i > 0) {
            cur = cur->next;
            --i;
        }
        return cur->data;
    } else {
        exit(EXIT_FAILURE);
    }
}


// Manipulation functions ----------------------------

/**
 * @brief Deletes the entry at the specified index and returns the data from the entry.
 * 
 * @param L The list to delete the entry from.
 * @param i The index of the entry to remove
 * @return void* The data that was stored in that entry. Returns NULL if the entry does not exist.
 */
void *delElement( ListPtr L, int i ) {
    if(L) {
        void *var;
        int size = length(L);
        if(size < i+1) {
            return NULL;
        }
        if(i == 0) {
            NodePtr temp = L->head;
            var = temp->data;
            L->head = L->head->next;
            temp->next = NULL;
            // L->freeData(temp->data);
            free(temp);
        } else {
            NodePtr iter = L->head;
            for(int j = 0; j < i-1; j++) {
                iter = iter->next;
            }
            NodePtr temp = iter->next;
            var = temp->data;
            iter->next = temp->next;
            temp->next = NULL;
            // L->freeData(temp->data);
            free(temp);
        }
        L->length--;
        return var;
    } else {
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Appends an entry to the list.
 * 
 * @param L    The list to append to
 * @param data The data to insert into the new entry.
 * @return true  If the append was succesfull
 * @return false If the entry could not be appended
 */
bool appendList( ListPtr L, void *data ) {
    if(L) {
        L->length = L->length + 1;
        NodePtr newNodePointer = (NodePtr)malloc(sizeof(NodeObj));
        newNodePointer->data = data;
        newNodePointer->next = NULL;

        if(L->head == NULL) {
            L->head = newNodePointer;
        } else {
            NodePtr cur = L->head;
            while(cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = newNodePointer; 
        }
    } else {
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Inserts an entry into the list.  
 * 
 * @param L      The list to insert the entry into
 * @param pos    The position into which to insert the entry
 * @param data   The data to insert into the entry
 * @return true  If the insert was succesfull
 * @return false If the insert could not be performed
 */
bool insertElement(ListPtr L, int pos, void *data) {
    if(L) {
        if(pos > L->length) {
            return false;
        }

        NodePtr cur = L->head;

        if(pos == 0) {
            NodePtr newNodePointer = (NodePtr)malloc(sizeof(NodeObj)); 
            //but if we trying to give amount of address for NodeObj, how does program know, whether
            //how much they should give space on heap because the data is undefined. 
            newNodePointer->data = data;
            newNodePointer->next = L->head;
            L->head = newNodePointer;  
            return true;   
        }  else if(pos == (L->length)) {
            appendList(L, data);
            return true;
        }
        
        for(int i = 0; i < pos-1; i++) {
            cur = cur->next;
        }
        NodePtr newNodePointer = (NodePtr)malloc(sizeof(NodeObj));
        newNodePointer->data = data;
        newNodePointer->next = cur->next;
        cur->next = newNodePointer;
        return true;

    }
}


// Other functions ----------------------------
/**
 * @brief Prints the data in the list in the format "%s\n" for each entry
 * 
 * @param L           The list to print
 */
void printList(ListPtr L) {
    if(L) {
        NodePtr cur = L->head;
        while(cur != NULL) {
            L->dataPrinter(cur->data);
            cur = cur->next;
        }
    }
}