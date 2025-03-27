#include "Card.h"
#include "Deck.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
static int Random_intBetween(int left, int right){
    return rand() % (right + 1 - left);
  }
bool Deck_isFull  (Deck const * deck){
    return deck->length == DECK_CAPACITY;
}

bool Deck_isEmpty (Deck const * deck){
    return deck->length == 0;
}

void Deck_appendCard (Deck * deck, Card card){
    assert(!Deck_isFull(deck));
    deck->cards[deck->length] = card;
    deck->length++;
}

Card Deck_popCard(Deck * deck){
    deck->length--;
    return deck->cards[deck->length];
}

void Deck_initEmpty (Deck * deck){
    deck->length = 0;
}

void Deck_initComplete (Deck * deck){
    Deck_initEmpty(deck);
    for (int suit = SUIT_COUNT - 1; suit >= 0; suit--){
        for (int rank = RANK_COUNT - 1; rank >= 0; rank--){
            Card card = Card_make(rank, suit);
            Deck_appendCard(deck, card);
        }
    }
}


bool Deck_pipsEqual    (Deck const * deck, char const pips[]){
    if (Deck_isEmpty(deck)){
        return strlen(pips) == 0;
    }
    if (strlen(pips) != 3 * deck->length - 1){
        return false;
    }
    for (int i = 0; i < deck->length; i++){
        if(!
            (Card_rankPip(deck->cards[i]) == pips[3 * i] &&
            Card_suitPip(deck->cards[i]) == pips[3 * i + 1])
        ){
            return false;
        }

    }
    return true;
}

void Deck_appendPips   (Deck * deck, char const pips []){
    int length = strlen(pips);
    assert(length % 3 == 2 || length == 0);
    for (int i = 0; i < strlen(pips); i += 3){
        int rank = Card_rankFromPip(pips[i]);
        int suit = Card_suitFromPip(pips[i + 1]);
        Deck_appendCard(deck, Card_make(rank, suit));
    }
}

void Deck_initFromPips (Deck * deck, char const pips []){
    Deck_initEmpty(deck);
    Deck_appendPips(deck, pips);
}

void Deck_printPips (Deck const * deck, FILE * file){
    for(int i = 0; i < deck->length; i++){
        if(i != 0){
            fprintf(file, " ");
        }
        Card_printPip(deck->cards[i], file);
    }
}

bool Deck_indexIsValid (Deck const * deck, int index){
    return index >= 0 && index < deck->length;
}


bool Deck_rangeIsValid (Deck const * deck, int start, int length){
    return start >= 0 && start + length <= deck->length;
}

void Deck_swapCardsAt (Deck * deck, int index1, int index2){
    assert(Deck_indexIsValid(deck, index1) && Deck_indexIsValid(deck, index2));
    Card temp = deck->cards[index1];
    deck->cards[index1] = deck->cards[index2];
    deck->cards[index2] = temp;
}

void Deck_shuffle(Deck * deck){
    for(int k = 0; k < deck->length; k++){
        int index = Random_intBetween(k, deck->length - 1);
        Deck_swapCardsAt(deck, k, index);
    }
}

