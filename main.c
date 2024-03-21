//Jehad Hamayel
//1200348
//sec: 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define numChar 40
#define numOfTopics 20
#define numOfCharInLine 200
typedef struct Courses* courPtr;//Define a new variable type name
struct Courses //Define a new type of Courses data
{
    char courseName[numChar];
    char courseCode[numChar];
    char department[numChar];
    char topics [numOfTopics][numChar];
    courPtr Left;//A reference to where the data is stored in memory, represented in the AVL tree, on the Left of the father
    courPtr Right;//A reference to where the data is stored in memory, represented in the AVL tree, on the Right of the father
    int Height;
    int creditHours;
    int numOftopics ;

};
typedef struct Courses* AVLCoursesT;//Define a new variable type name
//functions prototype
int isInteger(char []);
AVLCoursesT insert (AVLCoursesT, courPtr);//The function is to add a node in the AVL Tree on the left or right to root according to the Code Courses
void lexicographicOrder(AVLCoursesT);//Fenction prints the data in alphabetical order
AVLCoursesT readCoursFile (courPtr);//Function to read from course data file and restore private root in AVL tree
AVLCoursesT find( char[], AVLCoursesT ); //Function searches for a specific node according to Code Courses and returns a pointer on the node
AVLCoursesT insertNewCourse (AVLCoursesT );//Function add the courses node and take the data from the user and call the insert to add it and restore the root of the AVL Tree
AVLCoursesT findAndUpdate(char[], AVLCoursesT ); //Function finds a specific node according to the Code Course and asks the user if he wants to modify the data of the course and restore the root of the AVL Tree
void lexicographicSameDep(AVLCoursesT,char[]);//Function finds the nodes according to the department to which the courses belong and prints them in alphabetical order
void listAllTopics(AVLCoursesT );//Function prints all the topics of a particular course according to the Code Course
AVLCoursesT minValueNode(AVLCoursesT );//Function returns the last lowest we like in alphabetical order in the AVL Tree from the right of the tree
AVLCoursesT deleteNode(AVLCoursesT, char []); //A function that deletes a specific node in the AVL Tree according to the Course Code and returns the modified tree
AVLCoursesT deleteAllSpecificLetter(AVLCoursesT T,char specificLetter[]);//A function that deletes all the specific nodes in the AVL Tree according to the first letter in the course code and returns the modified tree.
AVLCoursesT deleteAlldepartment(AVLCoursesT T,char []);//The function deletes all the specific nodes in the AVL Tree according to the name of the department and returns the modified tree
int getBalance(AVLCoursesT );//Function checks the equilibrium of a specific node
//This functions prints all the data of the AVL Tree in a special file
void saveAllWords (courPtr );
void printFile(FILE *,courPtr );
//
int MAX (int, int ); //This function is based on which one is the largest and returns it
int getHeight (AVLCoursesT );//This function returns the height of a specific node
AVLCoursesT singleRotateLeft(AVLCoursesT) ;//This function does a single Rotate Left and returns the root of the modified Tree
AVLCoursesT singleRotateRight(AVLCoursesT) ;//This function does a single Rotate Right and returns the root of the modified Tree
AVLCoursesT doubleRotateLeft(AVLCoursesT) ;//This function does a double Rotate Left and returns the root of the modified Tree
AVLCoursesT doubleRotateRight(AVLCoursesT) ;//This function does a double Rotate Right and returns the root of the modified Tree
int deleted ;//Variable to see if the node has been deleted or not for print sentences
//Global variables for different functions
int print =0;
int foundDep =0;
int moreThanOneChar = 0;
////////////////////////////////////////////////////////////////////////////

int main(){
    printf("-------------------------------------<<<<<<Welcome to my project>>>>>>-------------------------------------\n\n");
    char opch[10];
    int True=1,readedFile=0;//Defining variables of type integer Variable to see if it has been read or not and also to exit the program
    courPtr rootAvlC=NULL;//A variable of type Node marked NULL
    while(True) //Create a loop that displays options for operations and call functions.
    {
        printf("Enter the number of the option that you want:\n\n");
        printf("1. Read the file courses.txt file and create the tree.\n");
        printf("2. Insert a new course from the user with all its associated data.\n");
        printf("3. Find a course and support updating of its information.\n");
        printf("4. List courses in lexicographic order with their associated information (credit hours, IDs, and topics). \n");
        printf("5. List all topics associated with a given course.\n");
        printf("6. List all courses in lexicographic order that belong to the same department.\n");
        printf("7. Delete a course.\n");
        printf("8. Delete all courses that start with a specific letter.\n");
        printf("9. Delete all courses belong to a given department.\n");
        printf("10. Save all words in file offered_courses.txt.\n");
        printf("11. exit.\n\n");
        printf("Choose an option:");

        fflush(stdin);//In order not to take Inter as a character
        gets(opch);
        if(isInteger(opch)) //Check if the entry is a number
        {
            int op=atoi(opch);
            printf("\n-------------------------------------------------------------\n\n");
            switch(op)
            {
            case 1:
                if(!readedFile) //Check if it is read or not
                {
                    rootAvlC  = readCoursFile (rootAvlC);//call read Cours File function.
                    printf("-------------------------------------------------------------\n\n");
                    readedFile=1;//File has been read
                }
                else
                {
                    printf("The file has already been read\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 2:rootAvlC=  insertNewCourse (rootAvlC );//Calling the insert New Course function
                break;
            case 3:
                if(rootAvlC!=NULL) //Check if there is Courses or Not
                {
                    printf("\nEnter Course Code that you want to find and update:");
                    char code[15];
                    scanf("%s",code);
                    findAndUpdate(code, rootAvlC);//Calling the  find And Update function
                }
                else
                {
                    printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 4:
                if(rootAvlC!=NULL) //Check if there is Courses or Not
                {

                        printf("Course Name                    Credit Hours   Course Code          Department           Topics\n\n");
                        lexicographicOrder(rootAvlC );//Calling the lexicographic Order function
                        printf("\n");
                }
                else
                {
                     printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 5:
                if(rootAvlC!=NULL) //Check if there is Courses or Not
                {
                    listAllTopics(rootAvlC );//Calling the list All Topics function
                }
                else
                {
                    printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 6:
                if(rootAvlC!=NULL) //Check if there is Courses or Not
                {

                    printf("Enter the Department to List all courses that belong to it : ");
                    char dep[30];
                    fflush(stdin);//In order not to take Inter as a character
                    gets(dep);
                    foundDep =0;
                    lexicographicSameDep(rootAvlC,dep);//Calling the  lexicographic Same Department function
                    if(foundDep==0)
                        printf("\nThere is no course in this Department\n");

                    printf("\n");
                }
                else
                {
                   printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }

                break;
            case 7:
               if(rootAvlC!=NULL) //Check if there is Courses or Not
                {
                    printf("Enter the Course Code to Delete it : ");
                    char courseCode[30];
                    fflush(stdin);//In order not to take Inter as a character
                    gets(courseCode);
                    deleted=0;
                    rootAvlC=deleteNode(rootAvlC, courseCode);//Calling the  delete Node function
                    if(deleted&&!moreThanOneChar)//Check if it is deleted or not
                        printf("\nThe course has been deleted\n\n");
                    else
                        printf("\nThe course has not deleted Not Found\n\n");
                }
                else
                {
                    printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 8:
                if(rootAvlC!=NULL) //Check if there is Courses or Not
                {
                    printf("Enter the specificLetter to Delete the Course : ");
                    char specificLetter[2];
                    fflush(stdin);//In order not to take Inter as a character
                    gets(specificLetter);
                    deleted=0;
                    moreThanOneChar=0;
                    rootAvlC=deleteAllSpecificLetter(rootAvlC,specificLetter); //Calling the delete All node that have first Specific Letter function
                   if(moreThanOneChar ==1)
                        printf("\nYou have to Enter One Character\n");
                    if(deleted)//Check if it is deleted or not
                        printf("\nThe course has been deleted\n\n");
                    else
                        printf("\nThe course has not deleted Not Found\n\n");
                }
                else
                {
                    printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 9:
              if(rootAvlC!=NULL) //Check if there is Courses or Not
                {
                    printf("Enter the department to Delete all courses belong to it : ");
                    char department[30];
                    fflush(stdin);//In order not to take Inter as a character
                    gets(department);
                    deleted=0;
                    rootAvlC=deleteAlldepartment(rootAvlC, department); //Calling the delete All node that have the same department name function
                    if(deleted)//Check if it is deleted or not
                        printf("\nThe course has been deleted\n\n");
                    else
                        printf("\nThe course has not deleted Not Found\n\n");
                }
                else
                {
                    printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 10:
                if(rootAvlC!=NULL) //Check if there is Courses or Not
                {
                    saveAllWords (rootAvlC);//Calling the save All Words function
                    printf("The data has been printed on the file\n\n");
                    printf("-------------------------------------------------------------\n\n");

                }
                else
                {
                    printf("There are no courses insert or read File\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 11:
                    printf("-------------------------------------<<<<<<Thank You, Goodbey>>>>>>-------------------------------------\n\n");
                    return 0;
                break;
            default :
                printf("Choose a correct number\n\n");
                printf("-------------------------------------------------------------\n\n");
            }
        }
        else
        {
            printf("\nPlease Choose a correct number\n\n");
            printf("-------------------------------------------------------------\n\n");
        }

    }

}

////////////////////////////////////////////////////////////////////////////

int isInteger(char word[]){ //Method to check if he was trafficked or not
    int index ;
    for(index=0; index<strlen(word); index++)
    {
        if(!isdigit(word[index]))
            return 0;
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT readCoursFile (courPtr rootAvlC){ //function definition.
    FILE *in;//Define file
    char inf[numOfCharInLine],*token;
    int isEmpty=1,index2,index;
    in = fopen("courses.txt","r");//Make the file in read
    if(in!=NULL) //Check if the file exists
    {
       while(fgets(inf,numOfCharInLine,in)!=NULL) //while loop for reading from file
        {
            if(!print){
                printf("The data that was in the file:\n\n");
                printf("Course Name                    Credit Hours   Course Code          Department           Topics\n\n");
                print=1;
            }
            courPtr ctemp = (courPtr)malloc(sizeof(struct Courses));
            ctemp->Left = NULL;
            ctemp->Right=NULL;
            token = strtok(inf,":");//String up to :
            strcpy(ctemp->courseName,token);//Copy the string and place it in the required variable
            token = strtok(NULL,"#");//String up to #
            ctemp->creditHours=atoi(token);////Converting a String to an Intger
            token = strtok(NULL,"#");//String up to #
            strcpy(ctemp->courseCode,token);//Copy the string and place it in the required variable
            token = strtok(NULL,"/");//String up to /
            strcpy(ctemp->department,token);//Copy the string and place it in the required variable
            token = strtok(NULL,",\n");//String up to /and \n
            index = 0;
            while(token != NULL) //Loop for storing topics
            {
                strcpy(ctemp->topics[index],token);//Copy the string and place it in the required variable
                index++;
                token = strtok(NULL,",\n");//String up to /and \n
            }
            ctemp->numOftopics = index;
            ctemp->Height=0;
            //print what has been read
            printf("%-30s %-12d   %-20s %-20s/",ctemp->courseName,ctemp->creditHours,ctemp->courseCode,ctemp->department);
            //Print what has been read from the topics
            for(index2=0; index2<(ctemp->numOftopics-1); index2++)
            {

                printf("%s,",ctemp->topics[index2]);
            }
            printf("%s\n",ctemp->topics[index2]);

            rootAvlC=insert (rootAvlC, ctemp);
            isEmpty=0;

        }
        if(isEmpty) //Check if the file is empty or not
        {
            printf("\n-------------------------------------------------------------\n\n");
            printf("The File is empty\n\n");

        }
       else{
        printf("\n-------------------------------------------------------------\n\n");
        printf("The file has been read successfully\n\n");}
        fclose(in);//close file
    }
    else
        printf("File not found\n\n");
    fclose(in); //close file
    return rootAvlC;
}

////////////////////////////////////////////////////////////////////////////

int MAX (int x, int y){ //function definition.
    //Method to find out which number is bigger
    if(x>y)
        return x;
    else
        return y;
}

////////////////////////////////////////////////////////////////////////////

int getHeight (AVLCoursesT t){ //function definition.
    //Method to find out the height of the node
    if(t==NULL)
        return -1;
    else
        return t->Height;
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT singleRotateLeft(AVLCoursesT x){  //function definition.
    //Method for making single Rotate Left
    AVLCoursesT y;
    y         = x->Right;
    x->Right  = y->Left;
    y->Left   = x;
    //Adjusting the Height of the Nodes
    x->Height = 1 + MAX(getHeight(x->Left), getHeight(x->Right));
    y->Height = 1 + MAX(getHeight(x), getHeight(y->Right));

    return y;
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT singleRotateRight(AVLCoursesT y){  //function definition.
    //Method for making single Rotate Right
    AVLCoursesT x;
    x        = y->Left;
    y->Left  = x->Right;
    x->Right = y;
    //Adjusting the Height of the Nodes
    y->Height = 1 + MAX(getHeight(y->Right), getHeight(y->Left));
    x->Height = 1 + MAX(getHeight(y), getHeight(x->Left));

    return x;
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT doubleRotateLeft(AVLCoursesT K3){  //function definition.
    //Method for making double Rotate Left
    K3->Left  = singleRotateLeft(K3->Left);
    return singleRotateRight(K3);
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT doubleRotateRight(AVLCoursesT K3){  //function definition.

    //Method for making double Rotate Right
    K3->Right  = singleRotateRight(K3->Right);
    return singleRotateLeft(K3);
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT insert (AVLCoursesT t, courPtr temp){ //function definition.
    if(t==NULL) //Check if the node reached NULL in order to add new node
    {
        //Create a node and copy the temp to it
        t=(courPtr)malloc(sizeof (struct Courses));
        strcpy(t->courseName,temp->courseName);
        t->creditHours=temp->creditHours;
        strcpy(t->courseCode,temp->courseCode);
        strcpy(t->department,temp->department);
        int index ;
        for(index =0; index<temp->numOftopics; index++)
        {
            strcpy(t->topics[index],temp->topics[index]);
        }
        t->numOftopics=temp->numOftopics;
        t->Height=0;
        t->Left= t->Right=NULL;
    }
    else if(strcasecmp(temp->courseCode,t->courseCode)<0)  //Check on Course Code to go left
    {
        t->Left=insert(t->Left,temp);
        if(getHeight(t->Left) - getHeight(t->Right) >= 2) //Check the balance if there is a defect that is treated
        {
            if(strcasecmp(temp->courseCode, t->Left->courseCode)<0)
                t=singleRotateRight(t);
            else
                t=doubleRotateLeft(t);
        }
    }
    else if(strcasecmp(temp->courseCode, t->courseCode)>0) //Check on Course Code to go right
    {
        t->Right = insert(t->Right, temp);
        if(getHeight(t->Right) - getHeight(t->Left) >= 2) //Check the balance if there is a defect that is treated
        {
            if(strcasecmp(temp->courseCode, t->Right->courseCode)>0)
                t=singleRotateLeft(t);
            else
                t=doubleRotateRight(t);
        }
    }

    t->Height = 1 + MAX(getHeight(t->Right), getHeight(t->Left));
    return t;
}

////////////////////////////////////////////////////////////////////////////

void lexicographicOrder(AVLCoursesT t){ //function definition.
//Print in alphabetical order
    if(t!= NULL)
    {
        lexicographicOrder(t->Left);
        printf("%-30s %-12d   %-20s %-20s/",t->courseName,t->creditHours,t->courseCode,t->department);
        int index;
        for(index =0; index<(t->numOftopics-1); index++)
        {

            printf("%s,",t->topics[index]);
        }
        printf("%s\n\n",t->topics[index]);
        lexicographicOrder(t->Right);
    }
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT insertNewCourse (AVLCoursesT t){ //function definition.
    //Create a node
    courPtr ctemp = (courPtr)malloc(sizeof(struct Courses));
    ctemp->Left = NULL;
    ctemp->Right=NULL;
    //Ask the user to enter the course information
    printf("Enter Course Name:");
    fflush(stdin);
    gets(ctemp->courseName);
    /*if(ctemp->courseName[0]='\0');
    {
    printf("Please Enter Course Name:");
    fflush(stdin);
    gets(ctemp->courseName);
    }*/
    printf("Enter CreditHours:");
    char word[15];
    fflush(stdin);
    gets(word);
    while(!isInteger(word))
    {
        printf("Please Enter valid number:");
        fflush(stdin);
        gets(word);
    }
    ctemp->creditHours= atoi(word);
    printf("Enter CourseCode:");
    char code[15];
    fflush(stdin);
    gets(code);
    if(find(code,t)!=NULL) //Check if the course exists or not before
    {
        printf("\nthe CourseCode already exist\n\n");
        return NULL;
    }
    strcpy(ctemp->courseCode,code);
    printf("Enter Department Name:");
    fflush(stdin);
    gets(ctemp->department);
    char d[15] ;
    printf("Enter topic if you want to stop enter -1:");
    fflush(stdin);
    gets(d);
    int index =0;
    while(strcmp(d,"-1")==0){
            printf("Enter topic if you want to stop enter -1 you have to Enter at least one topic:");
            fflush(stdin);
            gets(d);
    }
    while(strcmp(d,"-1")!=0)
    {

        strcpy(ctemp->topics[index],d);
        index ++;
        printf("Enter topic if you want to stop enter -1:");
        fflush(stdin);
        gets(d);
    }
    ctemp->numOftopics=index;
    printf("\nThe Course has added successfully \n\n");
    return insert (t, ctemp);


}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT find( char x[], AVLCoursesT t){  //function definition.
    //Method to search for a specific course according to the course code
    if ( t == NULL)
        return NULL;
    if ( strcasecmp(x, t->courseCode)<0) //greater than x move to right
        return ( find (x, t->Left));
    else //Less than x move to left
        if ( strcasecmp(x, t->courseCode) >0)
            return ( find ( x, t->Right));
        else
            return t;
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT findAndUpdate(char x[], AVLCoursesT t){  //function definition.
    //Method in order to search for a specific course according to the course code, then present it to the user and allow him to modify the information about the course
    AVLCoursesT co= find(x,t);
    if(co!=NULL)
    {
        printf("\n%-30s %-12d   %-20s %-20s/",co->courseName,co->creditHours,co->courseCode,co->department);
        int index;
        for(index =0; index<(co->numOftopics-1); index++)
        {

            printf("%s,",co->topics[index]);
        }
        printf("%s\n\n",co->topics[index]);
        //Offer to the user and allow him to modify the information about the course
        printf("Do you want to Update Data:(Choose 1 if you want and 0 or any character if you don't)\n1:Yes\n0:No \nYour Choice:");
        char choice [4];
        scanf("%s",choice);
        if(strcmp(choice,"1")==0)
        {
            printf("Enter Course Name that you want to update:");
            scanf("%s",co->courseName);
            printf("Enter CreditHours that you want to update:");
            char word[15];
            scanf("%s",word);
            while(!isInteger(word))
            {
                printf("Please Enter valid number:");
                scanf("%s",word);
            }
            co->creditHours= atoi(word);
            printf("Enter Department Name:");
            scanf("%s",co->department);
            char d[15] ;
            int i;
            for(i=0; i<numOfTopics; i++)
            {
                strcpy(co->topics[i],"");
            }
            printf("Enter topic if you want to stop enter -1 :");
            scanf("%s",d);
            int index =0;
            while(strcmp(d,"-1")==0){
            printf("Enter topic if you want to stop enter -1 you have to Enter at least one topic:");
            fflush(stdin);
            gets(d);
            }
            while(strcmp(d,"-1")!=0)
            {
                strcpy(co->topics[index],d);
                index ++;
                printf("Enter topic if you want to stop enter -1 :");
                scanf("%s",d);
            }
            co->numOftopics=index;
            printf("\nAn update has been made to the data\n\n");
        }
        else
            printf("\nOK\n\n");

    }
    else
    {
        printf("\nthe Course Not exist\n\n");
    }
    return t;
}

////////////////////////////////////////////////////////////////////////////

void listAllTopics(AVLCoursesT t){ //function definition.
    //Method for printing all the topics of the course
    printf("Enter Course Code that you want to list all topics of it:");
    char code[15];
    scanf("%s",code);
    AVLCoursesT co= find(code,t);
    if(co==NULL)
    {
        printf("the Course Not exist\n\n");
    }
    else
    {
        printf("\n%-30s:%20s-> ",co->courseName,co->courseCode);
        int index;
        for(index =0; index<(co->numOftopics-1); index++)
        {

            printf("%s,",co->topics[index]);
        }
        printf("%s\n\n",co->topics[index]);
    }
}

////////////////////////////////////////////////////////////////////////////

void lexicographicSameDep(AVLCoursesT AvlT,char x[]){ //function definition.
//Method for printing the course information in alphabetical order according to the joint department
    if(AvlT!= NULL)
    {
        lexicographicSameDep(AvlT->Left,x);

        if(strcasecmp(AvlT->department,x)==0)
        {
            foundDep=1;
            printf("\n%-30s %-12d   %-20s %-20s/",AvlT->courseName,AvlT->creditHours,AvlT->courseCode,AvlT->department);
            int index;
            for(index =0; index<(AvlT->numOftopics-1); index++)
            {

                printf("%s,",AvlT->topics[index]);
            }
            printf("%s\n",AvlT->topics[index]);

        }
        lexicographicSameDep(AvlT->Right,x);
    }
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT deleteNode(AVLCoursesT root, char courseCode[]){ //function definition.

    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the courseCode to be deleted is smaller than the
    // root's courseCode, then it lies in left subtree
    if ( strcasecmp(courseCode, root->courseCode)<0 )
        root->Left = deleteNode(root->Left, courseCode);

    // If the courseCode to be deleted is greater than the
    // root's courseCode, then it lies in right subtree
    else if( strcasecmp(courseCode, root->courseCode)>0 )
            root->Right = deleteNode(root->Right, courseCode);

    // if courseCode is same as root's courseCode, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->Left == NULL) || (root->Right == NULL) )
        {
            AVLCoursesT temp = root->Left ? root->Left :root->Right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
            deleted=1;

        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AVLCoursesT temp = minValueNode(root->Right);


            // Copy the inorder successor's data to this node
            strcpy(root->courseName,temp->courseName);
            root->creditHours=temp->creditHours;
            strcpy(root->courseCode,temp->courseCode);
            strcpy(root->department,temp->department);
            int i;
            for(i=0; i<numOfTopics; i++)
            {
                strcpy(root->topics[i],"");
            }
            int index ;
            for(index =0; index<temp->numOftopics; index++)
            {
                strcpy(root->topics[index],temp->topics[index]);
            }
            root->numOftopics=temp->numOftopics;

            // Delete the inorder successor
            root->Right = deleteNode(root->Right, temp->courseCode);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->Height = 1 + MAX(getHeight(root->Left),getHeight(root->Right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->Left) >= 0)
        return singleRotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->Left) < 0)
    {
        root->Left = singleRotateLeft(root->Left);
        return singleRotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->Right) <= 0)
        return singleRotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->Right) > 0)
    {
        root->Right = singleRotateRight(root->Right);
        return singleRotateLeft(root);
    }

    return root;
}

////////////////////////////////////////////////////////////////////////////

int getBalance(AVLCoursesT N){ //function definition.
    //Balance check for node
    if (N == NULL)
        return 0;
    return getHeight(N->Left) - getHeight(N->Right);
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT minValueNode(AVLCoursesT node){ //function definition.
    AVLCoursesT current = node;

    /* loop down to find the leftmost leaf */
    while (current->Left != NULL)
        current = current->Left;

    return current;
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT deleteAllSpecificLetter(AVLCoursesT T,char specificLetter[]){ //function definition.
    //DeleteAll courses that start with a specific letter
    if ( T == NULL)
        return NULL;
    T->Left=deleteAllSpecificLetter(T->Left,specificLetter);
    T->Right=deleteAllSpecificLetter(T->Right,specificLetter);
    char firstChatOfCode[2];
    firstChatOfCode[0]=T->courseCode[0];
    firstChatOfCode[1]='\0';
    int count=0;
    while(specificLetter[count]!='\0'){
        count++;
    }
    if(count==1){
    if(strcasecmp(firstChatOfCode,specificLetter)==0)
        T  =deleteNode(T, T->courseCode);
        }
        else
            moreThanOneChar=1;

    return T;
}

////////////////////////////////////////////////////////////////////////////

AVLCoursesT deleteAlldepartment(AVLCoursesT T,char department[]){ //function definition.
//Delete all courses belong to a given department.
    if ( T == NULL)
        return NULL;
    T->Left=deleteAlldepartment(T->Left,department);
    T->Right=deleteAlldepartment(T->Right,department);

    if(strcasecmp(T->department,department)==0)
        T  =deleteNode(T, T->courseCode);
    return T;
}

////////////////////////////////////////////////////////////////////////////

void saveAllWords (courPtr rootAvlC){ //function definition.
    //Method for writing to a file for the data
    FILE * out;
    out = fopen("offered_courses.txt","w");
    printFile(out,rootAvlC);
    fclose(out);
}

////////////////////////////////////////////////////////////////////////////

void printFile(FILE * out,courPtr rootAvlC){ //function definition.
    //print on file
    if(rootAvlC==NULL)
        return ;
    printFile(out,rootAvlC->Left);
    fprintf(out,"%s:%d#%s#%s/",rootAvlC->courseName,rootAvlC->creditHours,rootAvlC->courseCode,rootAvlC->department);
    int index;
    for(index =0; index<(rootAvlC->numOftopics-1); index++)
    {
        fprintf(out,"%s,",rootAvlC->topics[index]);
    }
    fprintf(out,"%s\n",rootAvlC->topics[index]);

    printFile(out,rootAvlC->Right);
}

