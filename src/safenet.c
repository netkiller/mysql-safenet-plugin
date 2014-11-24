/*
Homepage: http://netkiller.github.io/
Author: netkiller<netkiller@msn.com>
*/

#include <mysql.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "safenet.h"

#define SAFENET_URL "http://localhost/safe/interface" 
#define SAFENET_KEY "Web01-key" 

char *safe_url;
char *safe_key;


void get_safenet_env(){
    if (getenv("SAFENET_URL")){
	safe_url = getenv("SAFENET_URL");
    }else{
	safe_url = SAFENET_URL;
    }
    if (getenv("SAFENET_KEY")){
	safe_key = getenv("SAFENET_KEY");
    }else{
	safe_key = SAFENET_KEY;
    }
}

/* CURL FUNCTION BEGIN*/
struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

char * safenet(char *url, char *mode, char *key, char *in )
{ 
    CURL *curl;
    CURLcode res;
    char *fields;
    char *data;

//  curl_global_init(CURL_GLOBAL_ALL);
 
    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) {
        struct string s;
        init_string(&s); 
        
        asprintf(&fields, "mode=%s&keyname=%s&input=%s", mode, key, in);    
    
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "safenet/1.0 by netkiller <netkiller@msn.com>");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);
     
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));
     
        asprintf(&data, "%s", s.ptr);
        //printf("Encrypt: %s\n", data);
    
        free(s.ptr);
        /* always cleanup */ 
        curl_easy_cleanup(curl);
    }
    else{
	strcpy(data,"");
    }

    return data;
  //curl_global_cleanup();
}
/* CURL FUNCTION END*/

/* ------------------------ safenet encrypt ----------------------------- */

my_bool safenet_encrypt_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{

  if (args->arg_count != 1)
  {
    strncpy(message,
            "two arguments must be supplied: safenet_encrypt('<data>').",
            MYSQL_ERRMSG_SIZE);
    return 1;
  }
  get_safenet_env(); 
  args->arg_type[0]= STRING_RESULT;

  return 0;
}

char *safenet_encrypt(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

    char *data;
    data = safenet(safe_url, "encrypt", safe_key, args->args[0]);
    *length = strlen(data);
    return ((char *)data);

}

void safenet_encrypt_deinit(UDF_INIT *initid)
{
  return;
}

/* ------------------------ safenet decrypt ----------------------------- */

my_bool safenet_decrypt_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{

  if (args->arg_count != 1)
  {
    strncpy(message,
            "two arguments must be supplied: safenet_decrypt('<data>').",
            MYSQL_ERRMSG_SIZE);
    return 1;
  }

  get_safenet_env();
  args->arg_type[0]= STRING_RESULT;

  return 0;
}

char *safenet_decrypt(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

    char *data;
    if(strlen(args->args[0]) != 512){
        data = args->args[0];
    }else{
        data = safenet(safe_url, "decrypt", safe_key, args->args[0]);
    }
    *length = strlen(data);
    return ((char *)data);

}

void safenet_decrypt_deinit(UDF_INIT *initid)
{
  return;
}

/* ------------------------ safenet config ----------------------------- */

my_bool safenet_config_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{

    get_safenet_env();
    return 0;
}

char *safenet_config(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

  char *config;
  asprintf(&config, "SAFENET_URL=%s, SAFENET_KEY=%s", safe_url, safe_key);
  *length = strlen(config);
  return ((char *)config);
}

void safenet_config_deinit(UDF_INIT *initid)
{
   return;
}
