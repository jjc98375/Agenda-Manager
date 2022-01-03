
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 30 //length of agenda and event
#define EMPTY "empty" //string that will indicate the empty agenda

//struct that contains the information about Event
typedef struct EventObj{
    char *name;
    int time;
} EventObj;
typedef EventObj* EventPtr;

//struct that contains the information about Agenda
typedef struct Agenda {
    ListPtr L;
    char name[100];
} Agenda;

/**
 * @brief Compare the two event, specifically its name, to see if those two events are 
 *        equal or not.
 * 
 * @param L The first event that will be compared with second one.
 * @param i The second event that will be compared with first one.
 * @return bool,
 *      Return True, if those two pass-in event has same event name.
 *      Return False, if those two pass-in event has different event name.
 */
bool dataEqual(EventPtr p_e1, EventPtr p_e2) {
    // how do we make compare those two....
    bool a = strcmp(p_e1->name, p_e2->name);
    if( a==0 ) {
        return true;
    } else {
        return false;
    }
}


/**
 * @brief Check if the given Event starting time exist in the Agenda
 * 
 * @param L The List Pointer that indicating the list of events from Agenda.
 * @param p_e2 Event Pointer that will be checked in this function
 * @return bool,
 *      Return True, if there is a matching time
 *      Return False, if there is not a matching time
 */
bool checkTime(ListPtr L, EventPtr p_e2) {
    NodePtr cur = L->head;
    while(cur != NULL) {
        if (((EventPtr)(cur->data))->time == p_e2->time) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}
    
/**
 * @brief This function allows to print the data in well format.
 *        Time will be printed in 0~24 hours format,
 *        then it will print the event title.
 * 
 * @param p_e1 Event Pointer that has to be printed
 * @return void, print the data in clean format.
 */
void dataPrinter(EventPtr p_e1) {
    int time = p_e1->time;
    if(time < 10) {
        printf("0%d:00 ", time);
    } else {
        printf("%d:00 ", time);
    }
    printf("%s\n", p_e1->name);
}

/**
 * @brief This function helps the given data(EventObj) fully freed.
 * 
 * @param p_e1 Event Pointer that has to be free
 * @return void
 */
void freeData(EventPtr p_e1) {
    free(p_e1->name);
    free(p_e1);
}

/**
 * @brief This function basically receive all the infos to create an Event Object
 * 
 * @param event_name Event title 
 * @param time Event starting time
 * @return Returns the address of created Event Object
 */
EventPtr createData(const char* event_name, int time) {
    EventPtr ep = (EventPtr)malloc(sizeof(EventObj)); //event pointer
    ep->name = malloc(strlen(event_name)+1);
    strcpy(ep->name, event_name);
    ep->time = time;
    return ep;
}


/**
 * @brief This function was built in purpose to find the Agenda in existing Agenda array
 * 
 * @param arr Array that contains Agenda 
 * @param agenda Agenda name
 * @return Return the List Pointer that was located from founded agenda
 */
ListPtr findAgenda(Agenda arr[], const char* agenda) {
    for(int i = 0; i < 2; i++) {
        if(strcmp(arr[i].name, agenda) == 0) {
            return arr[i].L;
        }
    }
    return NULL;
}


/**
 * @brief This function allows the List ADT to be sorted in terms of the time. 
 * The List ADT will be in set of LinkedList, where it contains the Event Object.
 * Each Event Object will be sorted by its time.
 * 
 * @param L List Pointer that has the address of List ADT
 * @return void, The List will be sorted using selection sort method.
 */
void sort(ListPtr L){
    NodePtr pos, pos_next;
    EventPtr data_pos, data_pos_next, temp;

    if(L->length == 0 || L->length == 1) {

    } else {
        pos = L->head;
        pos_next = pos->next;                          
        while(pos_next != NULL){
            while(pos_next != NULL){
                data_pos = pos->data;
                data_pos_next = pos_next->data;
                if(data_pos->time > data_pos_next->time){
                    temp = data_pos;                                
                    pos->data = pos_next->data;
                    pos_next->data = temp;
                }
                pos_next = pos_next->next;
            }
            pos = pos->next;
            pos_next = pos->next;
        }
    }
    
}


/***********************************************************************
*                       main task functions                            *
************************************************************************/

// provided for output header formatting

/**
 * @brief Print the whole agenda where it contains all the events inside of it.
 * Basically print the linked list. 
 * 
 * @param L The List Pointer that will be soon printed out.
 * @param agenda_name Agenda name that indicates which agenda is being printed.
 * @return void, This function will eventually 
 */
void PRINT(ListPtr L, char *agenda_name) {
    printf("======== %s ========\n", agenda_name);
    // print the content of the List
    printList(L);
    printf("===== END OF %s =====\n", agenda_name);
}

/**
 * @brief Add the event to an existing Agenda if it's applicable. 
 * Things can throw Error, if the given Agenda are not match,
 * or events already exist or the time duplicates. All events will be
 * appended to the list after the validation.
 * 
 * @param agenda Agenda name that will be checked if the agenda_arr already contains or not.
 * @param event Event name of Event that will be added.
 * @param hour Event time of Event that will be added. 
 * @param agenda_arr Agenda array that contains different Agenda's info.
 * @return void,  
 */
void ADD(const char *agenda, const char* event, int hour, Agenda agenda_arr[]) {
    EventPtr data = createData(event, hour);

    ListPtr L = findAgenda(agenda_arr, agenda);
    if(L) { //if there is a matching agenda exist
        if(findElement(L, data) != -1) {
            printf("ERROR: Already an event with that name\n");
            freeData(data);
        } else if(checkTime(L, data)) {
            printf("ERROR: Already an event at that time\n");
            freeData(data);
        } else {
            appendList(L, data);
        }
    } else { //if there is no agenda matching
        //have to check if there's empty agenda to create this following new agenda
        if(strcmp(agenda_arr[0].name, EMPTY) == 0) {
            strcpy(agenda_arr[0].name, agenda);
            L = newList(&dataEqual, &dataPrinter, &freeData);
            agenda_arr[0].L = L; 
            appendList(L, data);
        } else if (strcmp(agenda_arr[1].name, EMPTY) == 0) {
            strcpy(agenda_arr[1].name, agenda);
            L = newList(&dataEqual, &dataPrinter, &freeData);
            agenda_arr[1].L = L;
            appendList(L, data);
        } else {
            printf("ERROR: Agenda not found\n"); 
            freeData(data);           
        }
    }
}

/**
 * @brief Delete the given event, if it is capable.
 * The event will not be deleted if the pass-in Agenda are exist in Agenda array or 
 * the given event are not founded inside of given Agenda. Instead it will be given with Error message.
 * 
 * @param agenda Agenda name that indicates where user wants the event need to be deleted.
 * @param event Event name of Events that wanted to be delted
 * @param agenda_arr Agenda array that contains different Agenda's info.
 * @return void,  
 */
void DELETE(const char *agenda, const char *event, Agenda agenda_arr[]) {
    EventPtr data = createData(event, -1); //trash hour is -1
    ListPtr L = findAgenda(agenda_arr, agenda); 
    if(L) {
        if(findElement(L, data) != -1) {
            int index = findElement(L, data);
            delElement(L, index);
        } else { //the events are not exist in the following agenda
            puts("ERROR: Event not found");
            freeData(data);
        }
    } else {
        printf("ERROR: Agenda not found\n");
        freeData(data);        
    }

}

/**
 * @brief Swap the time of each given events. There will be two events that will be pass-in.
 * Each events will be first checked if they exist in the given Agenda. If Agenda not founded,
 * or if the event were not founded, it will throw the error message. 
 * 
 * @param agenda Agenda name that will be checked if the agenda_arr already contains or not.
 * @param event The name of First Event that will be compared
 * @param event1 The name of Second event that will be compared
 * @param agenda_arr Agenda array that contains different Agenda's info.
 * @return void,  
 */
void SWAP(const char *agenda, const char *event, const char *event1, Agenda agenda_arr[]) {
    EventPtr data = createData(event, -1); //trash hour is -1
    EventPtr data1 = createData(event1, -1);
    ListPtr L = findAgenda(agenda_arr, agenda); 

    if(L) {
        if(findElement(L, data) != -1 && findElement(L, data1) != -1) {
            int index = findElement(L, data);
            int index1 = findElement(L, data1);
            EventPtr d = getElement(L, index); 
            EventPtr d1 = getElement(L, index1);
            int temptime = d->time;
            d->time = d1->time;
            d1->time = temptime;
        } else { //the events are not exist in the following agenda
            puts("ERROR: Event not found");
        }
    } else {
        printf("ERROR: Agenda not found\n");    
    }

    freeData(data);
    freeData(data1);
}

/**
 * @brief Merge function that enables one agenda assimilated to other agenda. 
 * In order to assimilate the agenda, both agenda has to be contained inside of given agenda array.
 * If there's conflict in time or event, agendas will not be merge.
 * 
 * @param agenda First agenda name that will receive all the data from the other agenda.
 * @param agenda1 Second agenda name that will give away their data to other agenda.
 * @param agenda_arr Agenda array that contains different Agenda's info.
 * @return void,  
 */
void MERGE(const char *agenda, const char *agenda1, Agenda agenda_arr[]) {
   
    if(strcmp(agenda, agenda1) == 0) {
        puts("ERROR: Cannot merge same agenda");
    } else {
        ListPtr L = findAgenda(agenda_arr, agenda); 
        ListPtr L1 = findAgenda(agenda_arr, agenda1);
        if(L != NULL && L1 != NULL) {
            
            int key;
            if(strcmp(agenda_arr[0].name, agenda) == 0) {
                key = 1;
                L = agenda_arr[0].L;
                L1 = agenda_arr[1].L;
            } else {
                key = 0;
                L = agenda_arr[1].L;
                L1 = agenda_arr[0].L;        
            }        

            NodePtr cur = L1->head;
            bool hasConflict = false;
            while(cur != NULL) {
                EventPtr cur_data = cur->data;
                if (findElement(L, cur_data) != -1 || checkTime(L, cur_data)) {
                    hasConflict = true;
                } 
                cur = cur->next;
            }
            if(hasConflict) {
                puts("ERROR: Cannot merge: Conflict found.");
            } else {
                L->length = L->length + L1->length;
                cur = L->head;
                while(cur->next != NULL) {
                    cur = cur->next;
                }
                cur->next = L1->head;
                L1->head = NULL;
                L1 = NULL;
                agenda_arr[key].L = L1;
                strcpy(agenda_arr[key].name, EMPTY);
            }
        } else {
            puts("ERROR: Agenda not found");
        }
    }

    

}


/***********************************************************************
*                     END OF main task functions                       *
************************************************************************/



int main(int argc, char **argv) {

    //initiate the agenda array
    Agenda agenda_arr[2];
    Agenda a, b;
    a.L = NULL;
    strcpy(a.name, EMPTY);
    b.L = NULL;
    strcpy(b.name, EMPTY);
    agenda_arr[0] = a;
    agenda_arr[1] = b;

    char command[10];
    while(scanf("%s", command) != EOF) {
        

        char agenda[LENGTH];
        char event[LENGTH];
        char agenda1[LENGTH];
        char event1[LENGTH];
        int hour;

        switch (command[0]) 
        {
        case 'A':
            while(getchar() != '\"');
            scanf("%[^\"]s", agenda);
            getchar();
            while(getchar() != '\"');
            scanf("%[^\"]s", event);
            getchar();
            scanf("%d", &hour);

            ADD(agenda, event, hour, agenda_arr);

            break;
        case 'D':
            while(getchar() != '\"');
            scanf("%[^\"]s", agenda);
            getchar();
            while(getchar() != '\"');
            scanf("%[^\"]s", event);
            getchar();

            DELETE(agenda, event, agenda_arr);

            break;
        case 'S':
            while(getchar() != '\"');
            scanf("%[^\"]s", agenda);
            getchar();
            while(getchar() != '\"');
            scanf("%[^\"]s", event);
            getchar();
            while(getchar() != '\"');
            scanf("%[^\"]s", event1);
            getchar();

            SWAP(agenda, event, event1, agenda_arr);

            break;
        case 'P':
            while(getchar() != '\"');
            scanf("%[^\"]s", agenda);
            getchar();

            ListPtr L = findAgenda(agenda_arr, agenda);
            if(L) {
                sort(L);
                PRINT(L, agenda);
            } else {
                printf("ERROR: Agenda not found\n");
            }
            break;
        case 'M':
            while(getchar() != '\"');
            scanf("%[^\"]s", agenda);
            getchar();
            while(getchar() != '\"');
            scanf("%[^\"]s", agenda1);
            getchar();
            MERGE(agenda, agenda1, agenda_arr);
            break;
        }

    }

    //After the task is done, free the lists from each Agenda.
    for(int i = 0; i < 2; i++) {
        if(agenda_arr[i].L != NULL) {
            freeList(&agenda_arr[i].L, true);
        }
    }

 
}
