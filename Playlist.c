#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//MACRO for malloc
#define MALLOC(a,type)\
a=(type*)malloc(sizeof(type));\
if(a==NULL)\
{ printf("Insufficient memory\n");\
    exit(0);\
}

//structure for song
typedef struct Song {
    char title[50];
    char artist[50];
    char genre[20];
    struct Song *next;
    struct Song *prev;
} Song;


//structure for playlist
typedef struct {
    Song *head;
    Song *tail;
    Song *current;
} Playlist;

//Add song to playlist
void addSong(Playlist *playlist, char *title, char *artist, char *genre) {
    Song *newSong;
    MALLOC(newSong,Song);
   strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->genre, genre);
    newSong->next = NULL;
    newSong->prev = NULL;

    if(playlist->head==NULL)//if playlist is empty
    {
        playlist->head = newSong;
        playlist->tail = newSong;
        playlist->current = newSong;
    }else{
        playlist->tail->next = newSong;//updating previous song *next
        newSong->prev = playlist->tail;//updating newsong *prev
        playlist->tail = newSong;//updating tail in playlist
    }
}

//Remove song from playlist
Song *removeSong(Playlist *playlist,char *title)
{
    Song *cur,*back,*front;
     if(playlist->head==NULL)//if playlist is empty
     {
         printf("No songs in the playlist.\n");
         return NULL;
     }
     if (strcmp(title, playlist->head->title) == 0)
     {
         printf("song deleted %s \n",playlist->head->title);
         cur=playlist->head;
         playlist->head=playlist->head->next;//update head
         if (playlist->head != NULL)
         {
             playlist->head->prev = NULL;
         } else {
             playlist->tail = NULL;
        }
         free(cur);
         return playlist->head;
     }
         back=NULL;
         cur=playlist->head;
         front=playlist->head->next;
         while(cur!=NULL)
         {
             if (strcmp(title, cur->title) == 0)
                break;
             back=cur;
             cur=cur->next;
             front = cur != NULL ? cur->next : NULL;
         }
         if(cur==NULL)//song not found in list
         {
             printf("song not found\n");
             return playlist->head;
         }
         //successful search
         printf("song deleted %s \n",cur->title);
         back->next=cur->next;//update back song next link
         if (front != NULL)
         {
             front->prev = cur->prev; // update front song prev link
         }
         else
        {
            playlist->tail = back;
        }
         free(cur);
         return playlist->head;

}

//plau song
void playSong(Playlist *playlist)
{
    if (playlist->current == NULL) {
        printf("No songs in the playlist.\n");
        return;
    }
    if(playlist->current!=playlist->head)
    {
        playlist->current=playlist->head;
        printf("Playing: %s by %s\n", playlist->current->title, playlist->current->artist);

    }else
    {
        printf("Playing: %s by %s\n", playlist->current->title, playlist->current->artist);
    }
}

//play next song
void playNextSong(Playlist *playlist) {
    if (playlist->current == NULL) {
        printf("No songs in the playlist.\n");
        return;
    }
    if (playlist->current->next != NULL) {
        playlist->current = playlist->current->next;//next song
    } else {
        playlist->current = playlist->head;//updating current if it is at tail
    }
    printf("Playing: %s by %s\n", playlist->current->title, playlist->current->artist);
}

//play previous song
void playPreviousSong(Playlist *playlist) {
    if (playlist->current == NULL) {
        printf("No songs in the playlist.\n");
        return;
    }
    if (playlist->current->prev != NULL) {
        playlist->current = playlist->current->prev;//prev song
    } else {
        playlist->current = playlist->tail;//updating current if it is at head
    }
    printf("Playing: %s by %s\n", playlist->current->title, playlist->current->artist);
}

//switch songs
void switchToSong(Playlist* playlist,char *title)
{
    if (playlist->head == NULL) {
        printf("No songs in the playlist.\n");
        return;
    }
    Song *cur=playlist->head;
    while(cur!=NULL)
    {
        if (strcmp(title, cur->title) == 0)
            break;
        cur=cur->next;
    }
    if(cur==NULL)
    {
        printf("Song not found");
    }
    playlist->current=cur;
    printf("Playing: %s by %s\n", playlist->current->title, playlist->current->artist);
}

//display all songs
void displayAllSongs(Playlist* playlist)
{
    if(playlist->head==NULL)//if playlist is empty
     {
         printf("No songs in the playlist.\n");
         return;
     }
     Song *cur=playlist->head;
    while(cur!=NULL)
    {
        printf("%s by %s\n", cur->title, cur->artist);
        cur=cur->next;
    }
}

//display songs by genre
void displaySongsByGenre(Playlist *playlist, char *genre)
{
    if(playlist->head==NULL)//if playlist is empty
     {
         printf("No songs in the playlist.\n");
         return;
     }
     int found = 0;
      Song *cur=playlist->head;
    while(cur!=NULL)
    {
       if (strcmp(genre, cur->genre) == 0)
        {
            printf("%s by %s\n", cur->title, cur->artist);
            found = 1;
        }
        cur=cur->next;
    }
    if (!found) {
        printf("No songs found in the genre: %s\n", genre);
    }
}


int main() {
    Playlist playlist = { .head = NULL, .tail = NULL, .current = NULL };
    char title[50], artist[50], genre[20];
    int choice;

    while (1) {
        printf("\n1. Add Song\n2. Play Song\n3. Play Next Song\n4. Play Previous Song\n5. Switch to Song\n6. Remove Song\n7. Display Songs\n8. Display Songs by Genre\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf(" %[^\n]", title);
                printf("Enter artist name: ");
                scanf(" %[^\n]", artist);
                printf("Enter genre: ");
                scanf(" %[^\n]", genre);
                addSong(&playlist, title, artist, genre);
                break;
            case 2:
                playSong(&playlist);
                break;
            case 3:
                playNextSong(&playlist);
                break;
            case 4:
                playPreviousSong(&playlist);
                break;
            case 5:
                printf("Enter song title: ");
                scanf(" %[^\n]", title);
                switchToSong(&playlist, title);
                break;
            case 6:
                printf("Enter song title: ");
                scanf(" %[^\n]", title);
                playlist.head = removeSong(&playlist, title);
                break;
            case 7:
                displayAllSongs(&playlist);
                break;
            case 8:
                printf("Enter genre: ");
                scanf(" %[^\n]", genre);
                displaySongsByGenre(&playlist, genre);
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
