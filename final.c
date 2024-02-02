#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char song[100];
    struct node *next;
    struct node *prev;
};

struct node *top, *temp, *top1;

//into file
void tofile(char a[])
{
    FILE *f1;
    f1 = fopen("playlist.txt", "a");
    fprintf(f1, "%s\n", a);
    fclose(f1);
}

void add_node(struct node *first)
{
    char a[100];
    while (first->next != NULL)
    {
        first = first->next;
    }
    first->next = (struct node *)malloc(sizeof(struct node));
    first->next->prev = first;
    first = first->next;
    printf("\n\a\a\a\aEnter Song name-  ");
    scanf("%s", a);
    strcpy(first->song, a);
    tofile(a);
    first->next = NULL;
}

void add_node_file(struct node *first, char *a)
{
    while (first->next != NULL)
    {
        first = first->next;
    }

    // Allocate memory for the new node
    first->next = (struct node *)malloc(sizeof(struct node));
    struct node *newNode = first->next;

    // Set prev pointer to the last node in the list
    newNode->prev = first;

    // Move to the newly added node
    first = newNode;

    strcpy(first->song, a);
    first->next = NULL;
}

void delete_node(char a[])
{
    FILE *f1, *f2;
    char line[100];
    int x = 0;
    f1 = fopen("playlist.txt", "r");
    f2 = fopen("temp.txt", "w");
    while (fgets(line, sizeof(line), f1) != NULL)
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        if (strcmp(a, line) != 0)
            fprintf(f2, "%s\n", line);
        else if (strcmp(a, line) == 0)
            x = 1;
    }
    fclose(f1);
    fclose(f2);
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    if (x == 0)
    {
        printf("There is no song with the name you entered.\n");
    }
    else
    {
        printf("Song has been deleted.\n");
    }
}

//prints entire playlist
void printlist(struct node *first)
{
    printf("\nPlaylist Name- ");
    while (first->next != NULL)
    {
        printf("%s\n", first->song);
        first = first->next;
    }
    printf("%s\n", first->song);
}

void count_nodes(struct node *first)
{
    int i = 0;
    while (first->next != NULL)
    {
        first = first->next;
        i++;
    }

    printf("\nTotal songs-  %d\n", i);
}

void search1(struct node *first)
{
    char song[100];
    printf("\n\a\a\a\aEnter song To be Searched- ");
    scanf("%s", song);
    int flag = 0;

    while (first != NULL)
    {
        if (strcmp(first->song, song) == 0)
        {
            printf("\n\a\a\a\a#Song Found\n");
            flag++;
            break;
        }
        else
        {
            first = first->next;
        }
    }
    if (flag == 0)
    {
        printf("\n\a\a\a\a#Song Not found\n");
    }
}

void create()
{
    top = NULL;
}

void push(char data[])
{
    if (top == NULL)
    {
        top = (struct node *)malloc(sizeof(struct node));
        top->next = NULL;
        strcpy(top->song, data);
    }
    else if (strcmp(top->song, data) != 0)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        temp->next = top;
        strcpy(temp->song, data);
        top = temp;
    }
}

//recently played songs
void display()
{
    top1 = top;
    if (top1 == NULL)
    {
        printf("\n\a\a\a\a=>NO recently played tracks.\n");
        return;
    }
    printf("\n\a\a\a\a#Recently played tracks-\n");
    while (top1 != NULL)
    {
        printf("%s", top1->song);
        printf("\n");
        top1 = top1->next;
    }
}

void play(struct node *first)
{
    char song[100];
    printlist(first);
    printf("\n\a\a\a\aChoose song you wish to play- ");
    scanf("%s", song);
    int flag = 0;

    while (first != NULL)
    {
        if (strcmp(first->song, song) == 0)
        {
            printf("\n\a\a\a\a=>Now Playing......%s\n", song);
            flag++;
            push(song);
            break;
        }
        else
        {
            first = first->next;
        }
    }
    if (flag == 0)
    {
        printf("\n\a\a\a\a#Song Not found\n");
    }
}

void recent()
{
    display();
}

void topelement()
{
    top1 = top;
    if (top1 == NULL)
    {
        printf("\n\a\a\a\a#NO last played tracks.\n");
        return;
    }
    printf("\n=>Last Played Song - %s\n", top->song);
}

// Comparison function for qsort
int compareSongs(const void *a, const void *b)
{
    return strcmp(((struct node *)a)->song, ((struct node *)b)->song);
}

void sort(struct node *start)
{
    // Count the number of nodes
    int count = 0;
    struct node *temp = start;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    // Convert linked list to array
    struct node *arr = (struct node *)malloc(count * sizeof(struct node));
    temp = start;
    for (int i = 0; i < count; i++)
    {
        strcpy(arr[i].song, temp->song);
        temp = temp->next;
    }

    // Use qsort to sort the array
    qsort(arr, count, sizeof(struct node), compareSongs);

    // Copy the sorted array back to the linked list
    temp = start;
    for (int i = 0; i < count; i++)
    {
        strcpy(temp->song, arr[i].song);
        temp = temp->next;
    }

    // Free the allocated memory for the array
    free(arr);
}

void addplaylist(struct node *start)
{
    FILE *f1;
    char line[100];
    f1 = fopen("playlist.txt", "r");
    while (fgets(line, sizeof(line), f1) != NULL)
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        add_node_file(start, line);
    }
    printf("Playlist Added\n");
    fclose(f1);
}

void del_search(struct node *start)
{
    char song[100];
    printlist(start);
    printf("\n\a\a\a\aChoose song you wish to delete- ");
    scanf("%s", song);
    int flag = 0;
    while (start != NULL)
    {
        if (strcmp(start->song, song) == 0)
        {
            printf("\n\a\a\a\a#Song Found\n");
            struct node *temp;
            temp = (struct node *)malloc(sizeof(struct node));
            temp = start;
            delete_node(temp->song);
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
            flag++;
            break;
        }
        else
        {
            start = start->next;
        }
    }
    if (flag == 0)
    {
        printf("\n\a\a\a\a#Song Not found\n");
    }
}

int main()
{
    system("color 03");
    int choice;
    struct node *start, *hold;
    start = (struct node *)malloc(sizeof(struct node));
    printf("\t\t\t\a\a\a\a*WELCOME*\n");
    printf("\n**please use '_' for space.\n");
    printf("\n\n\a\a\a\aEnter your playlist name-  ");
    fgets(start->song, sizeof(start->song), stdin);
    start->song[strcspn(start->song, "\n")] = 0; // Remove newline character
    start->next = NULL;
    hold = start;
    create();

    do
    {
        printf("\n1.Add  New Song\n2.Delete Song\n3.Display Entered Playlist\n4.Total Songs\n5.Search Song\n6.Play Song\n7.Recently Played List\n8.Last Played\n9. Sorted playlist\n10.Add From File\n11.Exit\n");
        printf("\n\a\a\a\aEnter your choice- ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_node(start);
            break;
        case 2:
            del_search(start);
            break;
        case 3:
            printlist(start);
            break;
        case 4:
            count_nodes(hold);
            break;
        case 5:
            search1(start);
            break;
        case 6:
            play(start);
            break;
        case 7:
            recent();
            break;
        case 8:
            topelement();
            break;
        case 9:
            sort(start->next);
            printlist(start);
            break;
        case 10:
            addplaylist(start);
            break;
        case 11:
            exit(0);
        default:
            printf("\n Invalid Input \n");
        }
    } while (choice != 11);

    return 0;
}