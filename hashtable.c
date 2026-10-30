#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
//separate chaining
typedef struct Node {
	int key, value;
	struct Node *next;
}Node;

Node *chainTable[SIZE] = {NULL};

//open addressing
typedef struct {
	int key, value, status;
}Entry;
 Entry openTable[SIZE];
 
 //hash function
 int hashFunction(int key) {
 	return key % SIZE;
 }
 
 //initialize open table
 void initializeOpenTable() {
 	int i;
 	for(i=0; i<SIZE; i++)
 	openTable[i].status = 0;
 } 
 
 //insert using chaining
void insertChaining(int key, int value) {
	int index = hashFunction(key);
	Node *newNode = (Node *)malloc(sizeof(Node));
	if(newNode == NULL) {
		printf("Memory allocation failed!\n");
		return;
	}
	newNode -> key = key;
	newNode -> value = value;
	newNode -> next = chainTable[index];
	chainTable[index] = newNode;
	printf("Key inserted using Separate Chaining at index %d.\n",index);
}

//search using chaining
int searchChaining(int key) {
	int index = hashFunction(key);
	Node *temp = chainTable[index];
	while (temp != NULL) {
		if (temp -> key == key){
			printf("Key found!\nKey: %d\nValue: %d\n", temp -> key, temp -> value);
			return 1;
		}
		temp = temp -> next;
	}
	return 0;
}

//delete using chaining
int deleteChaining(int key) {
	int index = hashFunction(key);
	Node *temp = chainTable[index];
	Node *prev = NULL;
	while(temp != NULL) {
		if(temp -> key == key) {
			if(prev == NULL)
				chainTable[index] = temp -> next;
			else
				prev -> next = temp -> next;
			free(temp);
			printf("Key deleted successfully.\n");
			return 1;
		}
		prev = temp;
		temp = temp->next;
	}
	return 0;
}

//insert using open addressing, linear probing
int insertOpenAddressing(int key, int value, int startIndex) {
	int index, i;
	for(i=0; i<SIZE; i++) {
		index = (startIndex + i) % SIZE;
		if (openTable[index].status != 1) {
			openTable[index].key = key;
			openTable[index].value = value;
			openTable[index].status = 1;
			printf("Key inserted using Open Addressing at index %d.\n", index);
			return 1;
		}
	}
	printf("Hash Table is full!\n");
	return 0;
}

//search using open addressing
int searchOpenAddressing(int key) {
	int startIndex = hashFunction(key);
	int index, i;
	for (i=0; i<SIZE; i++) {
		index = (startIndex + i) % SIZE;
		if (openTable[index].status == 0)
			return 0;
		if (openTable[index].status == 1 && openTable[index].key == key) {
			printf("Key found!\nKey : %d\nValue : %d\n", openTable[index].key, openTable[index].value);
			return 1;
		}
	}
	return 0;
}

//delete using open addressing
int deleteOpenAddressing(int key) {
	int startIndex = hashFunction(key);
	int index, i;
	for(i=0; i<SIZE; i++) {
		index = (startIndex+i) % SIZE;	
		if(openTable[index].status == 0)
			return 0;
		if(openTable[index].status == 1 && openTable[index].key == key) {
			openTable[index].status = 2;
			printf("Key deleted successfully.\n");
			return 1;
		}
	}
	return 0;
}

//insert operation
void insert()
{
    int key, value;
    int index;
    int choice;
    printf("\nEnter key: ");
    scanf("%d", &key);
    printf("Enter value: ");
    scanf("%d", &value);
    index = hashFunction(key);
    printf("Hash index = %d\n", index);
    if (openTable[index].status == 0 && chainTable[index] == NULL)
    {
        openTable[index].key = key;
        openTable[index].value = value;
        openTable[index].status = 1;
        printf("Key inserted at index %d.\n", index);
        return;
    }
    printf("\nCollision occurred at index %d!\n", index);
    printf("Choose collision resolution technique:\n");
    printf("1. Separate Chaining\n2. Open Addressing\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        insertChaining(key, value);
    }
    else if (choice == 2)
    {
        insertOpenAddressing(key, value, index);
    }
    else
    {
        printf("Invalid choice!\n");
    }
}

//search operation
void search()
{
    int key;
    printf("\nEnter key to search: ");
    scanf("%d", &key);
    if (searchOpenAddressing(key))
        return;
    if (searchChaining(key))
        return;
    printf("Key not found.\n");
}

//delete operation
void deleteKey()
{
    int key;
    printf("\nEnter key to delete: ");
    scanf("%d", &key);
    if (deleteOpenAddressing(key))
        return;
    if (deleteChaining(key))
        return;
    printf("Key not found.\n");
}
 
 //main function
int main()
{
    int choice;
    initializeOpenTable();
    printf("HASH TABLE\n");
    printf("1. Insert\n2. Search\n3. Delete\n4. Exit\n");
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                insert();
                break;
            case 2:
                search();
                break;
            case 3:
                deleteKey();
                break;
            case 4:
                printf("Program terminated.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}