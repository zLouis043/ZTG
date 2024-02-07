#ifndef ZFLAGS_H_
#define ZFLAGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>  
#include <string.h>  
#include <stdint.h>

typedef union{
    bool as_bool;
    char * as_str;
    char as_char;
    uint64_t as_uint64;
    size_t as_size;
}ZF_Val;

typedef enum {
    F_BOOL,
    F_STRING,
    F_CHAR,
    F_UINT64,
    F_SIZE,
    F_COUNT
}ZF_Type;

typedef struct {

    const char * name;
    const char * description;

    ZF_Val in_val;
    ZF_Val def_val;

    ZF_Type type;

}zFlag;

#ifndef FLAGS_CAP
#define FLAGS_CAP 256
#endif

typedef struct {

    zFlag flags[FLAGS_CAP];
    size_t flags_count;

    int argc;
    char **argv;

}ZF_Context;

static ZF_Context g_zflag_context;

static char * zflag_shift_args(int * argc, char *** argv);
zFlag * zflag_new(ZF_Type type, const char* name, const char * description);
bool * zflag_bool(const char* name, const char * description, bool default_value);
char ** zflag_str(const char* name, const char * description, char * default_value);
char * zflag_char(const char* name, const char * description, char  default_value);
uint64_t * zflag_uint64(const char* name, const char * description, uint64_t  default_value);
size_t * zflag_size(const char* name, const char * description, uint64_t  default_value);
bool zflag_parse(int argc, char **argv);
void zflag_print_flags(FILE * _Stream);

#define zflag_type(f_type, v_type) zFlag * flag = zflag_new(f_type, name, description);\
                                    flag->def_val.v_type = default_value;\
                                    flag->in_val.v_type = default_value;\
                                    return &flag->in_val.v_type;\

#endif // ZFLAG_H_

#ifdef ZFLAGS_IMPLEMENTATION 

static char * zflag_shift_args(int * argc, char *** argv){

    assert(*argc > 0);
    char * result = **argv;
    *argc -= 1;
    *argv += 1;
    return result;

}

zFlag * zflag_new(ZF_Type type, const char* name, const char * description){
    
    ZF_Context *c = &g_zflag_context;

    assert(c->flags_count < FLAGS_CAP);
    zFlag * flag = &c->flags[c->flags_count++];  
    memset(flag, 0, sizeof(zFlag*)); 
    flag->type = type;
    flag->name = name;
    flag->description = description;
    return flag; 

}

bool * zflag_bool(const char* name, const char * description, bool default_value){

    zflag_type(F_BOOL, as_bool);

}

char ** zflag_str(const char* name, const char * description, char * default_value){

    zflag_type(F_STRING, as_str);

}

char * zflag_char(const char* name, const char * description, char  default_value){

    zflag_type(F_CHAR, as_char);

}

uint64_t * zflag_uint64(const char* name, const char * description, uint64_t default_value){

    zflag_type(F_UINT64, as_uint64);

}

size_t * zflag_size(const char* name, const char * description, uint64_t  default_value){

    zflag_type(F_SIZE, as_size);

}

bool zflag_parse(int argc, char **argv){

    ZF_Context *c = &g_zflag_context;

    zflag_shift_args(&argc, &argv);

    while(argc > 0){
        char * flag = zflag_shift_args(&argc, &argv);

        if(*flag != '-'){
            c->argc = argc + 1;
            c->argv = argv - 1;
            return true;
        }

        if (strcmp(flag, "--") == 0) {
            c->argc = argc;
            c->argv = argv;
            return true;
        }

        flag += 1;

        bool found = false;

        for(size_t i = 0; i < c->flags_count; i++){

            if(strncmp(c->flags[i].name, flag, strlen(c->flags[i].name)) == 0){
                switch (c->flags[i].type) {
                    case F_BOOL: {

                        if(strcmp(argv[0], "true") == 0 || strcmp(argv[0], "false") == 0){

                            char * arg = zflag_shift_args(&argc, &argv);

                            c->flags[i].in_val.as_bool = (strcmp(arg, "true") == 0) ? true : false;

                        }else {

                            c->flags[i].in_val.as_bool = true;

                        }

                    }break;
                    case F_STRING: {
                        
                        if(argc == 0){
                            fprintf(stderr, "[ERROR] no value specified for flag '%s'\n", flag);
                            return false;
                        }

                        char* arg = zflag_shift_args(&argc, &argv);

                        c->flags[i].in_val.as_str = arg;
                    }break;
                    case F_CHAR: {
                        if(argc == 0){
                            fprintf(stderr, "[ERROR] no value specified for flag '%s'\n", flag);
                            return false;
                        }

                        char * arg = zflag_shift_args(&argc, &argv);

                        c->flags[i].in_val.as_char = *arg;
                    }break;
                    case F_UINT64: {

                        if(argc == 0){
                            fprintf(stderr, "[ERROR] no value specified for flag '%s'\n", flag);
                            return false;
                        }

                        char* arg = zflag_shift_args(&argc, &argv);
                        
                        char *endptr;
                        unsigned long long int result = strtoull(arg, &endptr, 10);

                        if (result == ULLONG_MAX && errno == ERANGE) {
                            fprintf(stderr, "[ERROR] integer overflow : '%s'\n", flag);
                            return false;
                        } 

                        c->flags[i].in_val.as_uint64 = result;
                    }break;
                    case F_SIZE: {

                        if(argc == 0){
                            fprintf(stderr, "[ERROR] no value specified for flag '%s'\n", flag);
                            return false;
                        }

                        char* arg = zflag_shift_args(&argc, &argv);
                        
                        char *endptr;
                        unsigned long long int result = strtoull(arg, &endptr, 10);

                        if (strcmp(endptr, "K") == 0) {
                            result *= 1024;
                        } else if (strcmp(endptr, "M") == 0) {
                            result *= 1024*1024;
                        } else if (strcmp(endptr, "G") == 0) {
                            result *= 1024*1024*1024;
                        } else if (strcmp(endptr, "") != 0) {
                            fprintf(stderr, "[ERROR] wrong suffix used for size '%s'\n", endptr);
                            return false;
                        }

                        if(*(endptr + 1) != '\0'){
                            fprintf(stderr, "[ERROR] invalid number '%s'\n", flag);
                            return false;
                        }

                        if (result == ULLONG_MAX && errno == ERANGE) {
                            fprintf(stderr, "[ERROR] integer overflow : '%s'\n", flag);
                            return false;
                        }   

                        c->flags[i].in_val.as_size = result;
                    }break;
                    default:{
                        assert(0 && "unreachable");
                        exit(EXIT_FAILURE);
                    }
                }
                found = true;
            }
        }

        if (!found) {
            fprintf(stderr, "[ERROR] unknown flag:  '%s'\n", flag);
            return false;
        }

    }

    c->argc = argc;
    c->argv = argv;
    return true;
}

void zflag_print_flags(FILE* _Stream){

    ZF_Context *c = &g_zflag_context;

    fprintf(_Stream, "[INFO] Flags: \n");

    for (size_t i = 0; i < c->flags_count; ++i) {

        zFlag *flag = &c->flags[i];

        switch (c->flags[i].type) {
            case F_BOOL:{
                fprintf(_Stream, "[INFO]    Name: -%s <(optional) true | false>\n", flag->name);
                fprintf(_Stream, "[INFO]        Description: %s\n", flag->description);
                fprintf(_Stream, "[INFO]        Default: %s\n", flag->def_val.as_bool ? "true" : "false");
            }break;
            case F_STRING:{
                fprintf(_Stream, "[INFO]    Name: -%s <string>\n", flag->name);
                fprintf(_Stream, "[INFO]        Description: %s\n", flag->description);
                if (flag->def_val.as_str) {
                    fprintf(_Stream, "[INFO]        Default: \"%s\"\n", flag->def_val.as_str);
                }else {
                    fprintf(_Stream, "[INFO]        Default: (null)\n");
                }
            }break;
            case F_CHAR:{
                fprintf(_Stream, "[INFO]    Name: -%s <char>\n", flag->name);
                fprintf(_Stream, "[INFO]        Description: %s\n", flag->description);
                fprintf(_Stream, "[INFO]        Default: '%c'\n", flag->def_val.as_char);
            }break;
            case F_UINT64:{
                fprintf(_Stream, "[INFO]    Name: -%s <uint64_t number>\n", flag->name);
                fprintf(_Stream, "[INFO]        Description: %s\n", flag->description);
                fprintf(_Stream, "[INFO]        Default: %d\n", flag->def_val.as_uint64);
            }break;
            case F_SIZE:{
                fprintf(_Stream, "[INFO]    Name: -%s <uint64_t number[K | M | G]>\n", flag->name);
                fprintf(_Stream, "[INFO]        Description: %s\n", flag->description);
                fprintf(_Stream, "[INFO]        Default: %zu\n", flag->def_val.as_size);
            }break;
            default:{
                assert(0 && "unreachable");
                exit(EXIT_FAILURE);
            }break;
        }

    }   
}



#endif // ZFLAGS_IMPLEMENTATION