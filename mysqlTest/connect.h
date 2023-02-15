#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H

#define token_count 30
#define _CRT_SECURE_NO_WARNINGS

#include </usr/include/mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cheaderfile
extern "C" {
#endif
#ifndef BUILD_MY_DLL
#define SHARED_LIB __declspec(dllexport)
#else
#define SHARED_LIB __declspec(dllexport)
#endif
#ifdef _GNUC_
#define NORETERN _attribute_ ((_noreturn_))
    /* 함수 전방 선언 */
    extern char *read_json_file(char *filename, int *readsize);
    extern void parseJSON(char *doc, int size, JSON *json);
    extern void freeJSON(JSON *json);
    extern char *get_tokens(int token_select_num);
    extern int return_main(MYSQL conn, MYSQL *connection);

    /* 비멤버 생성자 전방 선언 */
#endif

typedef enum _token_type token_type;
typedef struct _token token;
typedef struct _json JSON;

extern char *read_json_file(char *filename, int *readsize);
extern void parseJSON(char *doc, int size, JSON *json);
extern void freeJSON(JSON *json);
extern char *get_tokens(int token_select_num);
extern int return_main(MYSQL conn, MYSQL *connection);

typedef enum _token_type {
    token_db_host,
    token_db_user,
    token_db_pass,
    token_db_name,
} token_type;

typedef struct _token {
    token_type type;
    union {
        char    *string;
    };
    bool isArray;
} token;

typedef struct _json {
    token tokens[token_count];
} JSON;

char *read_json_file(char *filename, int *readsize) {
    int size;
    char *buffer;

    FILE *fp = fopen(filename, "rb");
    if(fp == NULL)
        return NULL;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);

    if(fread(buffer, size, 1, fp) < 1) {
        *readsize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }
    *readsize = size;
    fclose(fp);
    return buffer;
}

void parseJSON(char *doc, int size, JSON *json) {
    int tokenIndex = 0;
    int pos = 0;

    if(doc[pos] != '{')
        return;

    pos++;
    while(pos<size) {
        switch(doc[pos]) {
            case '"' : {
                char *begin = doc+pos+1;
                char *end = strchr(begin, '"');
                if(end==NULL) break;

                int stringLength = end-begin;
                json->tokens[tokenIndex].type = token_db_host;
                json->tokens[tokenIndex].string = malloc(stringLength+1);

                memset(json->tokens[tokenIndex].string,0,stringLength+1);
                memcpy(json->tokens[tokenIndex].string, begin, stringLength);
                
                tokenIndex++;
                pos = pos+stringLength+1;
            }
            break;
        }
        pos++;
    }
}

void freeJSON(JSON *json) {
    for(int i=0; i<token_count; i++) {
        if(json->tokens[i].type==token_db_host)
        free(json->tokens[i].string);
    }
}

char *test(char *c) {
    char d = sizeof(c);
    char *e = c;

    asm ("mov %[e], %[d]"
    : [d] "=rm" (d)
    : [e] "rm" (*e));
    
    return e;
}

char *get_tokens(int token_select_num) {
    int size;

    char *doc = read_json_file("connect.json", &size);
    if(doc==NULL) 
        return 0;

    JSON json = {0, };
    parseJSON(doc, size, &json);

    for(int i=1; i<10; i+=2) {
        if(token_select_num == token_db_host) {
            return (test(json.tokens[1].string));
        } else if(token_select_num == token_db_user) {
            return (test(json.tokens[3].string));
        } else if(token_select_num == token_db_pass) {
            return (test(json.tokens[5].string));
        } else if(token_select_num == token_db_name) {
            return (test(json.tokens[7].string));
        }
    }
}
#ifdef __cplusplus
}
#endif //__cplusplus
#endif
