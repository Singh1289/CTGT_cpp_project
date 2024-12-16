/*
    Program to build a playlist manager that supports adding, removing, modifying, searching, playing and listing songs. Each song has a title and an artist. Use dynamic memory to handle the list of songs. Playlist manager should record the frequency of playing and keep the list of songs sorted based on the recorded frequency.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char title[100];
    char artist[100];
    int played;
} Song;

typedef struct Playlist {
    Song *data;
    struct Playlist *next;
} Playlist;

// Function prototypes
Song *createSong();
void addSong(Playlist **playlist);
void removeSong(Playlist **playlist);
void modifySong(Playlist *playlist);
void searchSong(Playlist *playlist);
void playSong(Playlist *playlist);
void listSongs(Playlist *playlist);
void sortPlaylist(Playlist **playlist);
void freePlaylist(Playlist *playlist);

int main() {
    Playlist *playlist = NULL;
    int choice;

    do {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|  ~ Playlist Manager ~   |");
        printf("\n|1: Add Song              |");
        printf("\n|2: Remove Song           |");
        printf("\n|3: Play Song             |");
        printf("\n|4: View Playlist         |");
        printf("\n|5: Sort Playlist         |");
        printf("\n|6: Search Song           |");
        printf("\n|7: Exit                  |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nChoose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addSong(&playlist);
                break;
            case 2:
                removeSong(&playlist);
                break;
            case 3:
                playSong(playlist);
                break;
            case 4:
                listSongs(playlist);
                break;
            case 5:
                sortPlaylist(&playlist);
                listSongs(playlist);
                break;
            case 6:
                searchSong(playlist);
                break;
            case 7:
                printf("\n~~~~ T H A N K  Y O U ~~~~~\n");
                freePlaylist(playlist);
                break;
            default:
                printf("\n~~~~ Please choose a valid option ~~~~\n");
        }
    } while (choice != 7);

    return 0;
}

Song *createSong() {
    Song *song = (Song *)malloc(sizeof(Song));
    if (!song) {
        printf("Memory allocation error.\n");
        return NULL;
    }

    printf("\nEnter song title: ");
    fgets(song->title, 100, stdin);
    song->title[strcspn(song->title, "\n")] = '\0';

    printf("Enter artist: ");
    fgets(song->artist, 100, stdin);
    song->artist[strcspn(song->artist, "\n")] = '\0';

    song->played = 0;
    return song;
}

void addSong(Playlist **playlist) {
    Playlist *newNode = (Playlist *)malloc(sizeof(Playlist));
    if (!newNode) {
        printf("Memory allocation error.\n");
        return;
    }

    newNode->data = createSong();
    newNode->next = NULL;

    if (*playlist == NULL) {
        *playlist = newNode;
    } else {
        Playlist *temp = *playlist;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("\nSong added successfully!\n");
}

void removeSong(Playlist **playlist) {
    if (*playlist == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    printf("\nEnter song title to remove: ");
    char title[100];
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = '\0';

    Playlist *current = *playlist, *previous = NULL;

    while (current != NULL && strcmp(current->data->title, title) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\nSong not found.\n");
        return;
    }

    if (previous == NULL)
        *playlist = current->next;
    else
        previous->next = current->next;

    free(current->data);
    free(current);
    printf("\nSong removed successfully.\n");
}

void playSong(Playlist *playlist) {
    if (playlist == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    printf("\nEnter song title to play: ");
    char title[100];
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = '\0';

    Playlist *iter = playlist;
    while (iter != NULL) {
        if (strcmp(iter->data->title, title) == 0) {
            printf("\nPlaying '%s' by '%s'\n", iter->data->title, iter->data->artist);
            iter->data->played++;
            return;
        }
        iter = iter->next;
    }

    printf("\nSong not found.\n");
}

void searchSong(Playlist *playlist) {
    if (playlist == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    printf("\nEnter song title to search: ");
    char title[100];
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = '\0';

    Playlist *iter = playlist;
    while (iter != NULL) {
        if (strcmp(iter->data->title, title) == 0) {
            printf("\nSong found:\nTitle: %s\nArtist: %s\nPlayed: %d times\n", iter->data->title, iter->data->artist, iter->data->played);
            return;
        }
        iter = iter->next;
    }

    printf("\nSong not found.\n");
}

void listSongs(Playlist *playlist) {
    if (playlist == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    printf("\nPlaylist:\nTitle              Artist            Played\n");
    printf("-------------------------------------------------\n");
    Playlist *iter = playlist;
    while (iter != NULL) {
        printf("%-18s %-16s %d\n", iter->data->title, iter->data->artist, iter->data->played);
        iter = iter->next;
    }
}

void sortPlaylist(Playlist **playlist) {
    if (*playlist == NULL || (*playlist)->next == NULL)
        return;

    Playlist *sorted = NULL;

    while (*playlist != NULL) {
        Playlist *maxPrev = NULL;
        Playlist *maxNode = *playlist;
        Playlist *prev = *playlist;
        Playlist *current = (*playlist)->next;

        while (current != NULL) {
            if (current->data->played < maxNode->data->played) {
                maxPrev = prev;
                maxNode = current;
            }
            prev = current;
            current = current->next;
        }

        if (maxPrev != NULL)
            maxPrev->next = maxNode->next;
        else
            *playlist = maxNode->next;

        maxNode->next = sorted;
        sorted = maxNode;
    }

    *playlist = sorted;
}

void freePlaylist(Playlist *playlist) {
    while (playlist != NULL) {
        Playlist *temp = playlist;
        playlist = playlist->next;
        free(temp->data);
        free(temp);
    }
}
