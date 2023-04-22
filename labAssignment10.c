#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 26

struct Trie {
    bool end;
    int count;
    struct Trie* trie[SIZE];
};

void insert(struct Trie** ppTrie, char* word) {
    if (ppTrie == NULL || word == NULL) {
        return;
    }

    struct Trie* pNode = *ppTrie;
    if (pNode == NULL) {
        pNode = (struct Trie*)malloc(sizeof(struct Trie));
        pNode->end = false;
        pNode->count = 0;
        for (int i = 0; i < SIZE; i++) {
            pNode->trie[i] = NULL;
        }
        *ppTrie = pNode;
    }

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pNode->trie[index] == NULL) {
            pNode->trie[index] = (struct Trie*)malloc(sizeof(struct Trie));
            pNode->trie[index]->end = false;
            pNode->trie[index]->count = 0;
            for (int j = 0; j < SIZE; j++) {
                pNode->trie[index]->trie[j] = NULL;
            }
        }
        pNode = pNode->trie[index];
    }

    pNode->end = true;
    pNode->count++;
}

int numberOfOccurrences(struct Trie* pTrie, char* word) {
    if (pTrie == NULL || word == NULL) {
        return 0;
    }

    struct Trie* pNode = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pNode->trie[index] == NULL) {
            return 0;
        }
        pNode = pNode->trie[index];
    }

    if (pNode->end) {
        return pNode->count;
    } else {
        return 0;
    }
}

struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }

    for (int i = 0; i < SIZE; i++) {
        if (pTrie->trie[i] != NULL) {
            pTrie->trie[i] = deallocateTrie(pTrie->trie[i]);
        }
    }

    free(pTrie);
    return NULL;
}

int main(void) {
    // Read the number of words in the dictionary.
    int numWords;
    scanf("%d", &numWords);
    getchar();

    // Parse line by line and insert each word into the Trie.
    char buffer[101];
    struct Trie* pTrie = NULL;
    for (int i = 0; i < numWords; i++) {
        fgets(buffer, 101, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        insert(&pTrie, buffer);
    }

    // Print the number of occurrences of each word in the dictionary.
    char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    // Deallocate the Trie.
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL) {
        printf("There is an error in this program\n");
    }

    return 0;
}