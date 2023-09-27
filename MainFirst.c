#include <stdio.h>
#include <regex.h>
#include <locale.h>
#include "Pokemon.h"
char *strip_copy(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if(p) {
        char *p2 = p;
        while(*s != '\0') {
            if(*s != '\t' && *s != '\n' && *s != '\r') {
                *p2++ = *s++;
            } else {
                ++s;
            }
        }
        *p2 = '\0';
    }
    return p;
}
int main(int argc,char *argv[]) {
    int numOfTypes = atoi(argv[1]); // NOLINT(cert-err34-c)
    int numOfPokes = atoi(argv[2]); // NOLINT(cert-err34-c)
    char* file_path = argv[3];
    FILE *file_ptr = fopen(argv[3],"r");
    if(!file_ptr){
        printf("file unreachable");
        return 1;
    }
    char *curr_line;
    size_t bufsize = 300;
    size_t characters;
    curr_line = (char *)malloc(bufsize * sizeof(char));
    if(curr_line == NULL){
        printf("memory to buffer couldnt allocated");
        return 1;
    }
    int line_index = 0;

    char* type_name;
    char* type_source;
    char* list_type;
    char* type_in_list;
    char curr_line_for_types[300];
    Type* source_type_ptr;
    regex_t    pokemon_regex;
    if (regcomp(&pokemon_regex, "Pokemons", 0) != 0){
        printf("Regex couldn't compile");
        return 1;
    }
    int pokemon_flag = 0;
    Type* newType;
    char* copied_curr_line;
    while ((getline(&curr_line,&bufsize,file_ptr) != -1)){
        curr_line[strcspn(curr_line, "\r\n\t")] = 0;
        line_index++;
       if (line_index == 1){continue;}
       if(line_index == 2) { //    buffer[strcspn(buffer, "\r\n")] = 0;
           strcpy(curr_line_for_types, curr_line);
           for  (type_name = strtok(curr_line_for_types, ",");
           type_name != NULL;
           type_name =strtok(NULL, ",")) {
               if ((newType = CreateType(type_name)) == NULL) {
                   printf("Type could not be allocated");
                   return 1;
               } else {
                   PrintType(newType);
                   printf("%s\n",GetTypeArr()[newType->index]->typeName);
               }
           }
           continue;
       }
       if(line_index > 2 && regexec(&pokemon_regex, curr_line, 0, NULL, 0) != 0 && pokemon_flag == 0){
            type_source = strtok(curr_line," ");
                                                if((GetTypeByName(type_source)) == NULL){ printf("no type found"); return 1;}
           list_type = strtok(NULL, ":");
           printf("%s\n", list_type);
           for (type_in_list =strtok(NULL, ","); type_in_list != NULL; type_in_list = strtok(NULL,",")){
               if(strcmp(list_type, "effective-against-me") == 0){
                  if(add_effec_me(*GetTypeByName(type_source), *GetTypeByName(type_in_list)) == failure){
                      printf("add_effec_me failed!");
                      return 1;
                  }
                   PrintType(GetTypeByName(type_source));
               }
               else if(strcmp(list_type, "effective-against-other") == 0){
                 if (add_effec_other(*GetTypeByName(type_source), *GetTypeByName(type_in_list)) == failure){
                     printf("add_effec_other failed!");
                     return 1;
                 }
                   PrintType(GetTypeByName(type_source));
               }

           }
           PrintType(GetTypeByName(type_source));
           continue;
       }
       pokemon_flag = 1;


   }
    return 0;
}

//
//        regex_t    preg;
//        char       *string = "a simple string";
//        char       *pattern = ".*(Pokemons).*";
//        int        rc;
//
//        if ((rc = regcomp(&preg, pattern, REG_EXTENDED)) != 0) {
//            printf("regcomp() failed, returning nonzero (%d)", rc);
//            exit(1);
//        }


//
//    int input(char *s,int length);
//        char *buffer;
//        size_t bufsize = 50;
//        size_t characters;
//
//        buffer = (char *)malloc(bufsize * sizeof(char));
//        if( buffer == NULL)
//        {
//            perror("Unable to allocate buffer");
//            exit(1);
//        }
//
//        printf("Type something: ");
//        characters = getline(&buffer,&bufsize,stdin);
//        printf("%zu characters were read.\n",characters);
//        printf("You typed: '%s'\n",buffer);
//
//        return(0);
//    }
//    Bio* b1 = CreateBio(1,1,1);
//    printf("b1 attack is %d, weight is %f, and height is %f\n", b1->attack, b1->weight, b1 ->height);
//    Type* t1 = CreateType("Electric");
//    add_effec_me(*t1,*t1);
//    add_effec_other(*t1, *t1);
//    printf("%s\n",t1->effective_against_me[0]->typeName);
//    printf("%s\n",t1->effective_against_others[0]->typeName);
//    Pok* pok1 = CreatePok("Picachu","MousePokemon",(float)1.278,(float)1.278,3,t1 );
//    PrintPok(pok1);
//    PrintType(t1);


