#include "Card.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char const RANK_PIPS[] = "23456789TJQKA" ;
char const SUIT_PIPS[] = "cdhs" ; 
bool Card_rankIsValid (int rank){
    return 0 <= rank && rank < RANK_COUNT;
}

bool Card_suitIsValid (int suit){
    return 0 <= suit && suit < SUIT_COUNT;
}

Card Card_make (int rank, int suit){
    assert(Card_rankIsValid(rank));
    assert(Card_suitIsValid(suit));
    return (Card){.rank = rank, .suit = suit} ;
}

bool Card_isPaired (Card card1, Card card2){
    return card1.rank == card2.rank;
}

bool Card_isSuited (Card card1, Card card2){
    
    return card1.suit == card2.suit;
}

bool Card_equals (Card card1, Card card2){
    return Card_isPaired(card1, card2) && Card_isSuited(card1, card2);
}

int Card_rankFromPip (char rankPip){
    char *p = strchr(RANK_PIPS, rankPip);
    if (p == NULL){
        return -1;
    }
    return p - RANK_PIPS;
}

int Card_suitFromPip (char suitPip){
    char *p = strchr(SUIT_PIPS, suitPip);
    if (p == NULL){
        return -1;
    }
    return p - SUIT_PIPS;
}

Card Card_makeFromPip (char const pip[]){
    assert(strlen(pip) == 2);
    int rank = Card_rankFromPip(pip[0]);
    int suit = Card_suitFromPip(pip[1]);
    assert(rank != -1 && suit != -1);
    return Card_make(rank, suit);   
}

char Card_rankPip (Card card){
    return RANK_PIPS[card.rank];
}

char Card_suitPip (Card card){
    return SUIT_PIPS[card.suit];
}

bool Card_pipEquals (Card card, char const pip[]){
    return card.rank == Card_rankFromPip(pip[0]) 
    && card.suit == Card_suitFromPip(pip[1]);
}

void Card_printPip (Card card, FILE * file){
    fprintf(file, "%c%c", Card_rankPip(card), Card_suitPip(card));
}

int Card_compareByRankOnly (Card card1, Card card2){
    return card1.rank - card2.rank;
}

int Card_compareBySuitOnly (Card card1, Card card2){
    return card1.suit - card2.suit;
}

int Card_compareByRankFirst (Card card1, Card card2){
    int rankDiff = Card_compareByRankOnly(card1, card2);
    if (rankDiff != 0){
        return rankDiff;
    }
    return Card_compareBySuitOnly(card1, card2);
}

int Card_compareBySuitFirst (Card card1, Card card2){
    int suitDiff = Card_compareBySuitOnly(card1, card2);
    if (suitDiff != 0){
        return suitDiff;
    }
    return Card_compareByRankOnly(card1, card2);
}

int Card_compareArrayByRankOnly (Card const cards1[], Card const cards2[], int n){
    for (int i = 0; i < n; i++){
        int rankDiff = Card_compareByRankOnly(cards1[i], cards2[i]);
        if (rankDiff != 0){
            return rankDiff;
        }
    }
    return 0;
}

bool Card_isRegularConnector (Card hiCard, Card loCard){
    return hiCard.rank  == loCard.rank + 1;
}

bool Card_isRegularSuitedConnector (Card hiCard, Card loCard){
    return hiCard.suit == loCard.suit ;
}

bool Card_isAce (Card card){
    return card.rank == 12;
}

bool Card_isDeuce (Card card){
    return card.rank == 0;
}

bool Card_isAceDeuceConnector (Card hiCard, Card loCard){
    return Card_isAce(hiCard) && Card_isDeuce(loCard);
}

bool Card_isAceDeuceSuitedConnector (Card hiCard, Card loCard){
    return Card_isAceDeuceConnector(hiCard, loCard) && 
    Card_isRegularSuitedConnector(hiCard, loCard);
}