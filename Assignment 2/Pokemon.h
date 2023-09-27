//
// Created by ise on 12/4/21.
//

#ifndef POKEMON_H
#define POKEMON_H
/*
 * Pokemon.h
 *
 *  Created on: Dec 3, 2021
 *      Author: ise
 */
#include "Defs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Type_t{
    char* typeName;
    int numOfPoke;
    int me_counter ;
    int other_counter ;
    struct Type_t** effective_against_me;
    struct Type_t** effective_against_others;
    int index;

}Type;

typedef struct Bio_t{
    float height;
    float weight;
    int attack;
}Bio;

typedef struct Pok_t{
    char* name ;
    char* species;
    struct Type_t* mytype;
    struct Bio_t* myBio;
    int index;

}Pok;

Pok* CreatePok(char* name, char* species, float height, float weight, int attack, Type* type);
Type* CreateType(char* typeName);
Bio* CreateBio(float height, float weight, int attack);
status add_effec_me(Type source, Type added );
status add_effec_other(Type source, Type added);
status delete_effec_me(Type source, char* removed);
status delete_effec_others(Type source, char* removed);
status PrintPok(Pok* pokemon);
status PrintType(Type* type);
//char *TypesArr[];
Type* GetTypeByName(char* type_name);
Type** GetTypeArr();
#endif
