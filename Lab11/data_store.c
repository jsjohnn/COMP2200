#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user.h"
#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    if (users_or_null == NULL) {
        return NULL;
    }

    user_t** tmp_pp = users_or_null;
    user_t* tmp_p;

    while (*users_or_null != NULL) {
        if ((*users_or_null)->id == id) {
            tmp_p = *users_or_null;
            users_or_null = tmp_pp;
            return tmp_p;
        }
        users_or_null++;
    }

    users_or_null = tmp_pp;

    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    if (users_or_null == NULL) {
        return NULL;
    }

    user_t** tmp_pp = users_or_null;
    user_t* tmp_p;

    while (*users_or_null != NULL) {
        if (strncmp((*users_or_null)->username, username, LENGTH) == 0) {
            tmp_p = *users_or_null;
            users_or_null = tmp_pp;
            return tmp_p;
        }
        users_or_null++;
    }

    users_or_null = tmp_pp;    

    return NULL;
}

bool update_email(user_t** users_or_null, size_t id, const char* email)
{
    if (users_or_null == NULL) {
        return false;
    }
    
    char oldemail[LENGTH];

#if defined(RELEASE)

    while (*users_or_null != NULL) {
        if ((*users_or_null)->id == id) {
            char old_domain[LENGTH] = { 0, };
            char new_domain[LENGTH] = { 0, };

            char old_address[LENGTH] = { 0, };
            char new_address[LENGTH] = { 0, };

            size_t old_domain_len;
            size_t new_domain_len;


            strcpy(oldemail, (*users_or_null)->email);
            char* oldemail_p = oldemail;
    
            size_t i = 0;
            while (*oldemail_p != '@') {
                old_domain[i++] = *oldemail_p;
                oldemail_p++;
            }
            old_domain_len = i;

            i = 0;
            while (*oldemail_p != '\0') {
                old_address[i++] = *oldemail_p;
                oldemail_p++;

            }

            if (old_domain_len == 1) {
                old_domain[0] = '*';
            } else if (old_domain_len == 2) {
                old_domain[1] = '*';
            } else {
                for (size_t k = 1; k < old_domain_len - 1; ++k) {
                    old_domain[k] = '*';
                }
            }
            old_domain[old_domain_len] = '\0';


            i = 0;

            const char* email_tmp_p = email;

            while (*email != '@') {
                new_domain[i++] = *email;
                email++;
            }
            new_domain_len = i;

            i = 0;
            while (*email != '\0') {
                new_address[i++] = *email;
                email++;

            }

            email = email_tmp_p;

            //char* tmp_p = new_domain;

            if (new_domain_len == 1) {
                new_domain[0] = '*';
            } else if (new_domain_len == 2) {
                new_domain[1] = '*';
            } else {
                for (size_t j = 1; j < new_domain_len - 1; ++j) {
                    new_domain[j] = '*';
                }
            }
            new_domain[new_domain_len] = '\0';

            strcpy((*users_or_null)->email, email);

            FILE* stream;
            stream = fopen("log.txt", "ab");

            fprintf(stream, "TRACE: User %d updated email from \"%s%s\" to \"%s%s\"\n", id, old_domain, old_address, new_domain, new_address);

            fclose(stream);

            return true;

        }
        
        users_or_null++;
    }

#else
    user_t** tmp_pp = users_or_null;

    while (*users_or_null != NULL) {
        if ((*users_or_null)->id == id) {
            FILE* stream;

            stream = fopen("log.txt", "ab");

            strcpy(oldemail, (*users_or_null)->email);

            strcpy((*users_or_null)->email, email);
            users_or_null = tmp_pp;

            fprintf(stream, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", id, oldemail, email);

            fclose(stream);

            return true;
        }

        users_or_null++;

    }

#endif

    return false;
}

bool update_password(user_t** users_or_null, size_t id, const char* password)
{
    if (users_or_null == NULL) {
        return false;
    }

#if defined(RELEASE)

    user_t** tmp_pp = users_or_null;

    while (*users_or_null != NULL) {
        if ((*users_or_null)->id == id) {
            char old_pw[LENGTH];
            strcpy(old_pw, (*users_or_null)->password);
            strcpy((*users_or_null)->password, password);

            size_t old_pw_count = strlen(old_pw);
            size_t new_pw_count = strlen(password);

            char old_pw_log[LENGTH] = { 0, };
            char new_pw_log[LENGTH] = { 0, };


            if (old_pw_count == 1) {
                old_pw_log[0] = '*';
            } else if (old_pw_count == 2) {
                strcpy(old_pw_log, old_pw);
                old_pw_log[1] = '*';
            } else {
                strcpy(old_pw_log, old_pw);

                for (size_t i = 1; i < old_pw_count - 1; ++i) {
                    old_pw_log[i] = '*';
                }

            }

            if (new_pw_count == 1) {
                new_pw_log[0] = '*';
            } else if (new_pw_count == 2) {
                strcpy(new_pw_log, password);
                new_pw_log[1] = '*';
            } else {
                strcpy(new_pw_log, password);

                for (size_t i = 1; i < new_pw_count - 1; ++i) {
                    new_pw_log[i] = '*';
                }

            }

            FILE* stream;
            stream = fopen("log.txt", "ab");
            fprintf(stream, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", id, old_pw_log, new_pw_log);

            fclose(stream);

            users_or_null = tmp_pp;

            return true;

        }
        users_or_null++;

    }

#else

    user_t** tmp_pp = users_or_null;

    while (*users_or_null != NULL) {
        if ((*users_or_null)->id == id) {
            char old_pw[LENGTH];
            strcpy(old_pw, (*users_or_null)->password);
            strcpy((*users_or_null)->password, password);

            FILE* stream;
            stream = fopen("log.txt", "ab");
            fprintf(stream, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", id, old_pw, password);
           
            fclose(stream);
            users_or_null = tmp_pp;

            return true;
        }
        ++users_or_null;
    }

#endif

    
    return false;
}



