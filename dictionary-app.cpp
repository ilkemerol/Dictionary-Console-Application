#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
	void *dataPtr;
	int count;
	int ID;
	struct node *link;
}NODE;
typedef struct{
	int countlist;
	NODE *head;
	NODE *rear;
	int (*compare)(void* argu1, void* argu2); 
}LIST;
int list(void *first,void *second){
	int result;
	result=strcmp((char*)first,(char*)second);
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////
LIST* createList(int (*compare) (void* argu1, void* argu2)){
	LIST* list;
	list = (LIST*)malloc(sizeof (LIST));
	if (list){
	    list->head    = NULL;
	    list->rear    = NULL;
	    list->countlist   = 0;
	    list->compare = compare;
	}
	return list;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool _search (LIST*  pList, NODE** pPre,NODE** pLoc,  void*  pArgu){
#define COMPARE \
	( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )
#define COMPARE_LAST \
	((* pList->compare) (pArgu, pList->rear->dataPtr))
	int result; 
	*pPre  = NULL;
	*pLoc  = pList->head;
	if (pList->countlist == 0){
	    return false;
	}
	if(COMPARE_LAST > 0){
	    *pPre = pList->rear;
	    *pLoc = NULL;
	    return false;
	}
	while ( (result = COMPARE) > 0 ){
	    *pPre = *pLoc;
	    *pLoc = (*pLoc)->link;
	}
	if (result == 0){
	   return true;
	}
	else{
	   return false;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
static bool _insert (LIST* pList, NODE* pPre, void* dataInPtr){
	NODE* pNew;
	if (!(pNew = (NODE*) malloc(sizeof(NODE))))
	   return false;

	pNew->dataPtr  = dataInPtr;
	pNew->link      = NULL;
	pNew->count = 1;

	if (pPre == NULL){
	    pNew->link       = pList->head;
	    pList->head      = pNew;
	    if (pList->countlist == 0)
	       pList->rear = pNew;
	   }
	   
	else{
	    pNew->link  = pPre->link;
	    pPre->link  = pNew;
	    if (pNew->link     == NULL)
	         pList->rear   =  pNew;
	   }

	(pList->countlist)++;
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
int addNode (LIST* pList,char* dataInPtr){
	bool found;
	bool success;
	NODE* pPre;
	NODE* pLoc;
	found = _search (pList, &pPre, &pLoc, dataInPtr);
	if (found){
		pLoc->count++;
	}
	if(!found){
		success = _insert (pList, pPre, dataInPtr);
		if(!success){
			return -1;
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
int MYsearch (LIST* pList,char* dataInPtr){
	bool found;
	NODE* pPre;
	NODE* pLoc;
	found=_search (pList, &pPre, &pLoc, dataInPtr);
	if(found){
		return 1;
	}
	if(!found){
		return 0;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
int MYdelete(LIST* pList,char* dataInPtr){
	bool found;
	NODE* temp;
	NODE* pPre;
	NODE* pLoc;
	found=_search (pList, &pPre, &pLoc, dataInPtr);
	if(found){
		if(pPre==NULL){
			temp=pList->head;
			pList->head=pList->head->link;
			pList->countlist--;
			free(temp);
		}
		else if(pLoc->link==NULL){
				temp=pList->rear;
				pPre=pList->head;
				while(pPre->link!=pList->rear){
					pPre=pPre->link;
				}
				free(temp);
				pPre->link=NULL;
				pList->rear=pPre;
				pList->countlist--;
			}
			else{
				temp=pLoc;
				pPre->link=pLoc->link;
				free(temp);
				pList->countlist--;
			}
	return 1;
	if(!found){
		printf("ERROR:WORD ÝS NOT FOUND!\n");
		return 0;
	}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
void give_ID(LIST *pList){
	NODE *travel;
	travel = (NODE*) malloc(sizeof(NODE));
	travel=pList->head;
	int ident=1;
	while(travel->link!=NULL){
		travel->ID=ident;
		ident++;
		travel=travel->link;
	}
	if(travel->link==NULL){
		travel->ID=ident;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
FILE *mytext;
char textname[50];
printf("Enter a file name:");
scanf("%s",textname);
mytext=fopen(textname,"r");
while(mytext==NULL){
	printf("ERROR:THE FILE DOES NOT EXIST!\n");
	printf("Enter a new file name:");
	scanf("%s",textname);
	mytext=fopen(textname,"r");
}
LIST *basiclist,*dictionary;
char *word;
char *token;
basiclist=createList(&list);
dictionary=createList(&list);
while(!feof(mytext)){
	word=(char*)malloc(sizeof(char)*50);
	fscanf(mytext,"%s",word);
	strlwr(word);
	token=strtok(word,".,?!'$[]/\(%)={}+^#<>&-_*:;\"1234567890");
	while(token!=NULL){
		addNode(basiclist,token);
		addNode(dictionary,token);
		token=strtok(NULL,".,?!'$[]/\(%)={}+^#<>&-_*:;\"1234567890");
	}
}
give_ID(dictionary);
int i=0;
while(i!=8){
	printf("------Standart Functions------\n");
	printf("1-Insert Function\n");
	printf("2-Delete Function\n");
	printf("3-Search Function\n");
	printf("---------Text Fuctions---------\n");
	printf("4-Count and Word Text.\n");
	printf("5-Dictionary or ID Text.\n");
	printf("6-Convert from Normal Text to Numeratic Text.\n");
	printf("7-Convert from Numeratic Text to Letter Text.\n");
	printf("8-Exit\n");
	printf("------------NOTICE------------\n");
	printf("If you want to convert from Numeratic Text to Letter Text,\n");
	printf("First you must press 6.\n");
	scanf("%d",&i);
	if(i==1){
		char *insert1;
		insert1=(char*)malloc(sizeof(char)*50);
		printf("Enter a word:");
		scanf("%s",insert1);
		strlwr(insert1);
		addNode(basiclist,insert1);
		addNode(dictionary,insert1);
		give_ID(dictionary);
		printf("Insert Operation Successful.\n");
		printf("\n");
		printf("\n");
		printf("\n");
	}
	if(i==2){
		int result;
		char *insert2;
		insert2=(char*)malloc(sizeof(char)*50);
		printf("Enter a word:");
		scanf("%s",insert2);
		strlwr(insert2);
		result=MYdelete(basiclist,insert2);
		if(result==1){
			printf("Delete Operation Successful.\n");
			printf("\n");
			printf("\n");
			printf("\n");
		}
		else{
			printf("ERROR:DELETE OPERATION UNSUCCESSFUL.\n");
			printf("\n");
			printf("\n");
			printf("\n");
		}
	}
	if(i==3){
		int result;
		char *insert3;
		insert3=(char*)malloc(sizeof(char)*50);
		printf("Enter a word:");
		scanf("%s",insert3);
		strlwr(insert3);
		result=MYsearch(basiclist,insert3);
		if(result==1){
			printf("Word is Founded.\n");
			printf("\n");
			printf("\n");
			printf("\n");
		}
		else{
			printf("ERROR:WORD IS NOT FOUNDED.\n");
			printf("\n");
			printf("\n");
			printf("\n");
		}
	}
	if(i==4){
		FILE* writePtr;
		NODE *travel;
		travel=basiclist->head;
		if((writePtr=fopen("Count and Word.txt","w"))==NULL){
			printf("ERROR:FILE COULD NOT BE OPENED.\n");
			printf("\n");
		}
		else{
			while(travel!=NULL){
				fprintf(writePtr,"COUNT: %d---",travel->count);
				fprintf(writePtr,"WORD: %s\n",travel->dataPtr);
				travel=travel->link;
			}
			fflush(writePtr);
		}
		printf("Created Count&Word Text.\n");
		printf("\n");
		printf("\n");
		printf("\n");
	}
	if(i==5){
		FILE* writePtrD;
		NODE* travel;
		travel=dictionary->head;
		if((writePtrD=fopen("ID and Word.txt","w"))==NULL){
			printf("ERROR:FILE COULD NOT BE OPENED.\n");
			printf("\n");
		}
		else{
			while(travel!=NULL){
				fprintf(writePtrD,"ID: %d---",travel->ID);
				fprintf(writePtrD,"WORD: %s\n",travel->dataPtr);
				travel=travel->link;
			}
			fflush(writePtrD);
		}
		printf("Created ID&Word Text.\n");
		printf("\n");
		printf("\n");
		printf("\n");
	}
	if(i==6){
		FILE *mytext;
		mytext=fopen(textname,"r");
		bool found;
		NODE* pPre;
		NODE* pLoc;
		char* word;
		char* token;
		FILE* write;
		if((write=fopen("Numeratic Text.txt","w"))==NULL){
			printf("ERROR:FILE COULD NOT BE OPENED.\n");
			printf("\n");
		}
		while(!feof(mytext)){
			word=(char*)malloc(sizeof(char)*5000);
			fgets(word,5000,mytext);
			strlwr(word);
			token=strtok(word," .,?!\n'$[]/\(%)={}+^#<>&-_*:;\"1234567890");
			while(token!=NULL){
				found=_search (dictionary, &pPre, &pLoc, token);
				if(found){
					fprintf(write,"%d ",pLoc->ID);
				}
				fflush(write);
				token=strtok(NULL," .,?!\n'$[]/\(%)={}+^#<>&-_*:;\"1234567890");
			}
			fprintf(write,"\n");
		}
		printf("Converted from Normal Text to Numeratic Text.\n");
		printf("\n");
		printf("\n");
		printf("\n");
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i==7){
		FILE* mytextnumber;
		mytextnumber=fopen("Numeratic Text.txt","r");
		if(mytextnumber == NULL){
			printf("Numeratic Text Does Not Exist.!\n");
			printf("Please First Press 6 And Then Press 7.\n");
			printf("\n");
			printf("\n");
			printf("\n");
		}
		else{
		char* word;
		char* token;
		int number;
		FILE* writenumber;
		writenumber=fopen("Letter Text.txt","w");
		while(!feof(mytextnumber)){
			word=(char*)malloc(sizeof(char)*5000);
			fgets(word,5000,mytextnumber);
			token=strtok(word," ");
			while(token != NULL){
				number = atoi(token);
				NODE* travel;
				travel=dictionary->head;
				while(travel != NULL){
					if(travel->ID == number){
						fprintf(writenumber,"%s ",travel->dataPtr);
						travel=travel->link;
					}
					else{
						travel = travel->link;
						}
				}
				token = strtok(NULL," ");
			}
			fprintf(writenumber,"\n");
		}
		fflush(writenumber);
		printf("Converted from Numeratic Text to Letter Text.\n");
		printf("\n");
		printf("\n");
		printf("\n");
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i==8){
		printf("PROGRAM SHUT DOWN.\n");
		printf("\n");
		printf("\n");
		printf("\n");
	}
}
	system("pause");
	return 0;
}

