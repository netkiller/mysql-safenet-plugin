my_bool safenet_encrypt_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *safenet_encrypt(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void safenet_encrypt_deinit(UDF_INIT *initid);

my_bool safenet_decrypt_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *safenet_decrypt(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void safenet_decrypt_deinit(UDF_INIT *initid);

my_bool safenet_config_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *safenet_config(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void safenet_config_deinit(UDF_INIT *initid);
