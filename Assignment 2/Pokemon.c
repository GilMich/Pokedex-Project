//
// Created by ise on 12/4/21.
//

/*
 * Pokemon.c
 *
 *  Created on: Dec 3, 2021
 *      Author: ise
 */
#include "Pokemon.h"
Type** TypeArr = NULL;
int typeArr_length= 0 ;
Type* get_type_from_effec_list(Type* source, char* me_or_other, Type* target){
    if(strcmp(me_or_other,"me") == 0) {
        for (int i = 0; i < source->me_counter; i++) {
            if (strcmp(source->effective_against_me[i]->typeName, target->typeName) == 0) {
                return source->effective_against_me[i];
            }
        }
    }else if(strcmp(me_or_other,"others") == 0){
        for (int i = 0; i < source->me_counter; i++) {
            if (strcmp(source->effective_against_others[i]->typeName, target->typeName) == 0) {
                return source->effective_against_others[i];
            }
        }
    }
    return NULL;
}
Type* CreateType(char* typeName){
    Type* newType = (Type*)malloc(sizeof(Type));
    if(newType == NULL){
        return newType;
    }
    newType->typeName = typeName;
    newType->numOfPoke = 0;
    newType->me_counter = 0;
    newType->other_counter = 0;
    newType->index = typeArr_length ;
    typeArr_length ++;
    TypeArr = (Type**)realloc(TypeArr,typeArr_length * sizeof(Type*));
    TypeArr[newType->index] = newType;
    return newType;
}
status add_effec_me(Type source, Type added ){
    Type* source_ptr;
    Type* added_ptr;
    if((source_ptr = GetTypeByName(source.typeName)) == NULL || (added_ptr = GetTypeByName(added.typeName)) == NULL)
    {return failure;} // one of them don't exist in the database!
    if(get_type_from_effec_list(source_ptr,"me",added_ptr) != NULL){return success;} // already added!

    TypeArr[source.index]->effective_against_me = (Type**)realloc(source_ptr->effective_against_me, (me_counter +1)
    *sizeof(Type*));
    if(source_ptr->effective_against_me == NULL){
        return failure;
    }
    TypeArr[source.index]->effective_against_me[me_counter] = TypeArr[added.index];
    TypeArr[added.index]->me_counter ++;
    return success;
}
status add_effec_other(Type source, Type added){

    if(TypeIndex(TypeArr ,source.typeName) == -1 || TypeIndex(TypeArr ,added.typeName) == -1 ){ //type not exists
        return bad_param;
    }
    if(TypeIndex(source.effective_against_others, added.typeName) != -1){ //already exists
        return success;
    }
    Type* source_ptr = TypeArr[source.index];
    int other_counter = TypeArr[source.index]->other_counter;
    TypeArr[source.index]->effective_against_others = (Type**)realloc(source_ptr->effective_against_others, (other_counter +1)*sizeof(Type*));
    if(source_ptr->effective_against_me == NULL){
        return failure;
    }
    TypeArr[source.index]->effective_against_others[other_counter] = TypeArr[added.index];
    TypeArr[added.index]->other_counter ++;
    return success;
}
status delete_effec_me(Type source, char* removed_name) {
    if (TypeIndex(TypeArr, source.typeName) == -1 ||TypeIndex(TypeArr, removed_name) == -1) { //type does not exists
        return bad_param;
    }
    if (TypeIndex(source.effective_against_me, removed_name) == -1) { // deleted already!
        return failure;
    }
    if (source.me_counter == 0) { //list is empty
        return failure;
    }
    Type *temp_last = source.effective_against_me[source.me_counter - 1];
    TypeArr[source.index]->effective_against_me[TypeIndex(source.effective_against_me, removed_name)] = temp_last;
    TypeArr[source.index]->effective_against_me = (Type **) realloc(TypeArr[source.index]->effective_against_me,
                                                                    (source.me_counter - 1) * sizeof(Type *));
    if (source.me_counter == 1) {
        TypeArr[source.index]->me_counter--;;
        free(TypeArr[source.index]->effective_against_me);
        return success;
    }
    TypeArr[source.index]->me_counter--;
    return success;
}
status delete_effec_others(Type source, char* removed_name){
    if (TypeIndex(TypeArr, source.typeName) == -1 ||TypeIndex(TypeArr, removed_name) == -1) { //type does not exists
        return bad_param;
    }
    if (source.other_counter == 0) { //list is empty
        return failure;
    }
    if (TypeIndex(source.effective_against_others, removed_name) == -1) { // deleted already!
        return failure;
    }
    Type *temp_last = source.effective_against_others[source.me_counter - 1];
    TypeArr[source.index]->effective_against_others[TypeIndex(source.effective_against_others, removed_name)] = temp_last;
    TypeArr[source.index]->effective_against_others = (Type **) realloc(TypeArr[source.index]->effective_against_others,
                                                                    (source.other_counter - 1) * sizeof(Type *));
    if (source.other_counter == 1) {
        TypeArr[source.index]->other_counter--;;
        free(TypeArr[source.index]->effective_against_others);
        return success;
    }
    TypeArr[source.index]->other_counter--;
    return success;
}
Pok** pokArr;
int pokArr_length = 0;
Bio* CreateBio(float height, float weight, int attack){
    Bio * newBio = (Bio*)malloc(sizeof(Bio));
    if(newBio == NULL){
        return newBio;
    }
    newBio->height = height ;
    newBio->weight = weight ;
    newBio->attack = attack ;
    return newBio;
}
status DeleteBio(Bio* bio_ptr) {
    if(bio_ptr == NULL){
        return failure;
    }
    else {
        free( bio_ptr);
        return success;
    }
}
Pok* CreatePok(char* name, char* species, float height, float weight, int attack, Type* type) {
    Bio *newBio = CreateBio(height, weight, attack);
    if(newBio == NULL){
        return NULL;
    }
    Pok* newPok = (Pok *)malloc(sizeof(Pok));
    if(newPok == NULL){
        DeleteBio(newBio);
        free(newPok);
        return NULL;
    }
    newPok->myBio = newBio ;
    newPok->mytype = TypeArr[type->index] ;
    TypeArr[type->index]->numOfPoke += 1 ;
    newPok->name = name ;
    newPok->species = species ;
    newPok->index = pokArr_length;
    Pok** temp_pok_arr = pokArr;
    pokArr_length++;
    temp_pok_arr = realloc(pokArr,pokArr_length*sizeof(Pok*));
    if(temp_pok_arr == NULL){
        DeleteBio(newBio);
        free(newPok);
        return NULL;
    }
    pokArr = temp_pok_arr;
    pokArr[newPok->index] = newPok;
    return newPok ;
}
status PrintPok(Pok* pokemon){
    if(pokemon == NULL){
        return failure;
    }
    printf("%s :\n%s, %s Type.\nHeight: %.2f m    Weight: %.2f    Attack: %d\n\n",pokemon->name, pokemon->species,
           pokemon->mytype->typeName,pokemon->myBio->height, pokemon->myBio->weight,pokemon->myBio->attack );
    return success;
}
char* printEffec(Type* type, int me_or_other) {
    int list_length;
    char* return_string = (char*)malloc(100*sizeof(char));
    char *curr_string;
    char *space = " ,";
    if (me_or_other == 0) {
        list_length = type->me_counter;
    } else {
        list_length = type->other_counter;
    }
    if (me_or_other == 0) {
        for (int i = 0; i < list_length; ++i) {
            curr_string = type->effective_against_me[i]->typeName;
             strcat(return_string, curr_string);
            if (i == list_length - 1) { return return_string; }
            strcat(return_string, space);
        }

    } else {
        for (int i = 0; i < list_length; ++i) {
            curr_string = type->effective_against_others[i]->typeName;
            strcat(return_string, curr_string);
            if (i == list_length - 1) { return return_string; }
            strcat(return_string, space);
        }
    }
    return return_string ;
}
status PrintType(Type* type){
    if(type == NULL){
        return failure;
    }
    char* effec_list;
    printf("Type %s -- %d pokemons\n",type->typeName, type->numOfPoke);
    if(type->me_counter != 0) {
        printf("These types are super-effective against %s:\t", type->typeName);
        effec_list = printEffec(type, 0);
        printf("%s", effec_list);
        free(effec_list);
        if (type->other_counter != 0) {
            printf("\n%s moves are super-effective against:\t", type->typeName);
            effec_list = printEffec(type, 1);
            printf("%s\n\n", effec_list);
            free(effec_list);
            return success;
        }
        else{
          printf("\n\n");
          return success;
        }
    }
    else {
        if(type->other_counter != 0){
            printf("%s moves are super-effective against:\t", type->typeName);
            effec_list = printEffec(type, 1);
            printf("%s\n\n", effec_list);
            free(effec_list);
            return success;
        }
        else{
            printf("\n");
            return success;
        }
    }
}
Type* GetTypeByName(char* type_name){
    for (int i = 0; i < typeArr_length; i++) {
        if(strcmp(TypeArr[i]->typeName, type_name) == 0){
            return TypeArr[i];
        }
    }
    return NULL;
}
Type** GetTypeArr(){
    return TypeArr;
}

