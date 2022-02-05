#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "receipter.h"

#define ITEM_LENGTH (300)
#define DELIM (1)

static char s_temp[300] = {0, };
static double s_prices[10];
static s_item_number = 0;
static double s_tip = 0.0;
static char s_message[75] = "";
static size_t s_i = 0;

int add_item(const char* name, double price)
{
    size_t count = 0;

    if (s_item_number >= 10) {  
        return FALSE;
    }
    
    if (name == NULL || strlen(name) < 1) {
        return FALSE;
    }

    while (*name != '\0') {
        s_temp[s_i] = *name;
        ++count;

        ++s_i;
        ++name;

        if (count == 25) {
            break;
        }
    
    }
    s_temp[s_i++] = DELIM;

    s_prices[s_item_number++] = price;

    return TRUE;
}

void set_tip(double tip)
{
    s_tip = tip;
}

void set_message(const char* message)
{
    size_t i;
    
    for (i = 0; i < 75; ++i) {
        if (*message == '\0') {
            break;
        }
        s_message[i] = *message++;
    }

    s_message[i] = '\0';

    i = 0;
    
}

int print_receipt(const char* filename, time_t timestamp)
{
    static int s_order_num = 0;

    char* token;

    const char* RESTAURANT_NAME = "Charles' Seafood";
    const char* SUBTOTAL = "Subtotal";
    const char* TIP = "Tip";
    const char* TAX = "Tax";
    const char* TOTAL = "Total";
    const char* TAX_NUM = "Tax#-51234";

    const double D_TAX = 0.05;

    const char* BAR = "----------";
    const char* DUP_BAR = "==========";
    const double* LOC_PRICES = s_prices;
    const char* LOC_MESSAGE = s_message;
    
    size_t i;
    double d_subtotal = 0.0;

    struct tm tm = *gmtime(&timestamp);

    FILE* stream;

    if (s_i == 0) {
        s_tip = 0;

        if (s_message[0] != 0) { 
            for (i = 0; i < 75; ++i) {
                s_message[i] = 0;
            }
        }

        return FALSE;
    }

    stream = fopen(filename, "w");

    if (!stream) {
        perror("error while opening");
        return FALSE;
    }

    fprintf(stream, "%s", RESTAURANT_NAME);
    fputc('\n', stream);

    for (i = 0; i < 5; ++i) {
        fprintf(stream, "%s", BAR);
    }

    fputc('\n', stream);
    
    /* UNIX TIME */
    fprintf(stream, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    for (i = 0; i < 26; ++i) {
        putc(' ', stream);
    }

    fprintf(stream, "%05d", s_order_num);
    fputc('\n', stream);

    for (i = 0; i < 5; ++i) {
        fprintf(stream, "%s", BAR);
    }

    fputc('\n', stream);

    token = strtok(s_temp, "\1");
    while (token != NULL) {
        fprintf(stream, "%33s", token);
        fprintf(stream, "%17.2f", *LOC_PRICES);

        d_subtotal += *LOC_PRICES;
        LOC_PRICES++;

        fputc('\n', stream);

        token = strtok(NULL, "\1");
    }
    
    fputc('\n', stream);

    fprintf(stream, "%33s", SUBTOTAL);
    fprintf(stream, "%17.2f", d_subtotal);
    fputc('\n', stream);

    if (s_tip != 0) {
        fprintf(stream, "%33s", TIP);
        fprintf(stream, "%17.2f", s_tip);
        fputc('\n', stream);
    }

    fprintf(stream, "%33s", TAX);
    fprintf(stream, "%17.2f", d_subtotal * D_TAX);
    fputc('\n', stream);

    fprintf(stream, "%33s", TOTAL);
    fprintf(stream, "%17.2f", d_subtotal + (d_subtotal * D_TAX) + s_tip);

    fputc('\n', stream);

    if (*LOC_MESSAGE != '\0') {
        fputc('\n', stream);
    }

    i = 0;
    while (*LOC_MESSAGE != '\0') {
        fprintf(stream, "%c", *LOC_MESSAGE);
        
        ++i;
        if (i == 50) {
            fputc('\n', stream);
            i = 0;
        }

        ++LOC_MESSAGE;

    }

    fputc('\n', stream);

    for (i = 0; i < 5; ++i) {
        fprintf(stream, "%s", DUP_BAR);
    }

    fputc('\n', stream);

    fprintf(stream, "%50s", TAX_NUM);

    fclose(stream);

    /* static variable initialize */

    for (i = 0; i < ITEM_LENGTH; ++i) {
        s_temp[i] = 0;
    }

    for (i = 0; i < 10; ++i) {
        s_prices[i] = 0;
    }

    s_tip = 0.0;
    
    for (i = 0; i < 75; ++i) {
        s_message[i] = 0;
    }

    s_item_number = 0;
    s_i = 0;
    

    s_order_num++;
    
    return TRUE;
}
