#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <stdbool.h>

user_t* get_user_by_id_or_null(user_t**, size_t);
user_t* get_user_by_username_or_null(user_t**, const char*);
bool update_email(user_t** users_or_null, size_t id, const char* email);
bool update_password(user_t** users_or_null, size_t id, const char* password);

#endif /* DATA_STORE_H */
