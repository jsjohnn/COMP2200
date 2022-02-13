#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "character_deserializer.h"

#define LENGTH (1024)

int get_character(const char* filename, character_v3_t* out_character)
{
    size_t comma = 0;
    size_t colon = 0;
    size_t bar = 0;
    size_t x = 0;

    /* size_t buf_size = 0; */
    size_t count = 0;

    int num;

    version_t version;

    char buffer[LENGTH] = "";
    char buffer2[LENGTH] = "";
    char buffer3[LENGTH] = "";
    char buffer4[LENGTH] = "";
    char buffer5[LENGTH] = "";
    char buffer6[LENGTH] = "";
    char* dummy = NULL;


    char* buffer_p;

    char* token;
    /* char* token2; */

    char player_name[64] = "player_";
    char v2_name[64] = "";
    char* tmp_player_name;

    /* for compare */
    const char* lvl = "lvl";
    const char* intel = "intel";
    const char* str = "str";
    const char* dex = "dex";
    const char* def = "def";
    const char* id = "id";
    const char* hp = "hp";
    const char* mp = "mp";

    /* v2 added */
    const char* name = "name";
    const char* level = "level";
    const char* strength = "strength";
    const char* dexterity = "dexterity";
    const char* intelligence = "intelligence";
    const char* armour = "armour";
    const char* evasion = "evasion";
    const char* magic_resistance = "magic_resistance";
    const char* health = "health";
    const char* mana = "mana";

    /* v3 added*/
    const char* fire_res = "fire_res";
    const char* cold_res = "cold_res";
    const char* lightning_res = "lightning_res";
    const char* minion_count = "minion_count";
    const char* leadership = "leadership";
    const char* defence = "defence";

    char* minion_att[4];
    

    char att1[16] = "";
    char att2[16] = "";
    char att3[16] = "";
    char att4[16] = "";

    size_t i = 0;
    

    FILE* file = fopen(filename, "rb");

    if (!file) {
        fprintf(stderr, "error while opening: %s", filename);
        return -1;
    }
    
    fgets(buffer, LENGTH, file);

    buffer_p = buffer;

    while (*buffer_p != '\0') {
        if (',' == *buffer_p) {
            ++comma;
        } else if (':' == *buffer_p) {
            ++colon;
            break;
        } else if ('|' == *buffer_p) {
            ++bar;
            break;
        }

        ++buffer_p;
    }

    if (bar != 0) {
        version = VERSION_3;
        goto version3_start;
    } else if (colon != 0) {
        version = VERSION_1;
        goto version1_start;
    } else {
        version = VERSION_2;
        goto version2_start;
    }

version1_start:
    
    out_character->minion_count = 0;

    token = strtok(buffer, ":");

    while (token != NULL) {

        if (strcmp(token, lvl) == 0) {
            token = strtok(NULL, ",");
            sscanf(token, "%d", &num);
            out_character->level = num;
            if (num == 0) {
                out_character->leadership = num;
            } else {
                out_character->leadership = num / 10;
            }
        } else if (strcmp(token, intel) == 0) {
            token = strtok(NULL, ",");
            sscanf(token, "%d", &num);
            out_character->intelligence = num;
        } else if (strcmp(token, str) == 0) {
            token = strtok(NULL, ",");
            sscanf(token, "%d", &num);
            out_character->strength = num;
        } else if (strcmp(token, dex) == 0) {
            token = strtok(NULL, ",");
            sscanf(token, "%d", &num);

            out_character->dexterity = num;
                
            out_character->evasion = num / 2;
                
        } else if (strcmp(token, def) == 0) {
            token = strtok(NULL, ",");
            sscanf(token, "%d", &num);
            out_character->armour = num;
                
            out_character->elemental_resistance.fire = ((num / 4) / 3);
            out_character->elemental_resistance.cold = ((num / 4) / 3);
            out_character->elemental_resistance.lightning = ((num / 4) / 3);

        } else if (strcmp(token, id) == 0) {
            token = strtok(NULL, ",");
            strcat(player_name, token);
            tmp_player_name = player_name;

            while (*tmp_player_name != '\0') {
                out_character->name[x++] = *tmp_player_name;
                if (x == 50) {
                    out_character->name[x] = '\0';
                    break;
                }

                tmp_player_name++;
            }

            out_character->name[x] = '\0';

        } else if (strcmp(token, hp) == 0) {
            token = strtok(NULL, ",");
            sscanf(token, "%d", &num);
            out_character->health = num;

        } else if (strcmp(token, mp) == 0) {
            token = strtok(NULL, ",");
            sscanf(token, "%d", &num);
            out_character->mana = num;

        }

        token = strtok(NULL, ":");
    }

    fclose(file);

    return version;

version2_start:

    out_character->minion_count = 0;
        
    fgets(buffer2, LENGTH, file);
    buffer_p = buffer2;

    /* buf_size = strlen(buffer_p); */
        
    token = strtok(buffer, ",\r");

    while (token != NULL) {

        /*  name set */
        if (strcmp(token, name) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                }

                count++;
                buffer_p++;
            }

            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%s", v2_name);

            while (v2_name[x] != ' ') {
                out_character->name[x] = v2_name[x];
                ++x;
                if (x == 50) {
                    out_character->name[x] = '\0';
                    break;
                }
            }

            buffer_p = buffer_p + count + 1;                
            count = 0;
        } else if (strcmp(token, level) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                }

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->level = num;
            out_character->leadership = num / 10;

            buffer_p = buffer_p + count + 1;                
            count = 0;
        } else if (strcmp(token, strength) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->strength = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, dexterity) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->dexterity = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, intelligence) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->intelligence = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, armour) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->armour = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, evasion) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->evasion = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, magic_resistance) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                }

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            num /= 3;

            out_character->elemental_resistance.fire = num;
            out_character->elemental_resistance.cold = num;
            out_character->elemental_resistance.lightning = num;
            
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, health) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                }

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->health = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, mana) == 0) {
                
            while (*buffer_p != '\0') {

                if (*buffer_p == ',') {
                    break;
                }

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->mana = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        }
      
        token = strtok(NULL, ",\r");
    }        

    fclose(file);

    return version;

version3_start:

    fgets(buffer2, LENGTH, file);
    buffer_p = buffer2;

    token = strtok(buffer, " |\r");

    while (token != NULL) {

        if (strcmp(token, name) == 0) {
                
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                }

                count++;
                buffer_p++;
            }

            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%s", v2_name);

            while (v2_name[x] != ' ') {
                out_character->name[x] = v2_name[x];
                ++x;
                if (x == 50) {
                    out_character->name[x] = '\0';
                    break;
                }
            }

            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, level) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->level = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, health) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->health = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, mana) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->mana = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, strength) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->strength = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, dexterity) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->dexterity = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, intelligence) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->intelligence = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, armour) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->armour = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, evasion) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->evasion = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, fire_res) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->elemental_resistance.fire = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, cold_res) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->elemental_resistance.cold = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, lightning_res) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->elemental_resistance.lightning = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, leadership) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->leadership = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        } else if (strcmp(token, minion_count) == 0) {
            while (*buffer_p != '\0') {

                if (*buffer_p == '|') {
                    break;
                } 

                count++;
                buffer_p++;
            }
            *buffer_p = ' ';
            buffer_p -= count;

            sscanf(buffer_p, "%d", &num);

            out_character->minion_count = num;
                
            buffer_p = buffer_p + count + 1;                
            count = 0;

        }

        token = strtok(NULL, " |\r");

    }

    if (out_character->minion_count == 0) {
        goto VERSION3_END;
    }


    /* minion count가 0이 아닌 경우 */
    
    dummy = fgets(buffer3, LENGTH, file);

    if (dummy == NULL) {
        goto VERSION3_END;
    }  
    
    /* att1 */
    token = strtok(buffer3, " |\r");
    strcpy(att1, token);
    minion_att[0] = att1;

    /* att2 */
    token = strtok(NULL, " |\r");

    if (token == NULL) {
        goto MINION_ATT_SETTING;
    }
    strcpy(att2, token);
    minion_att[1] = att2;


    /* att3 */
    token = strtok(NULL, " |\r");
    if (token == NULL) {
        goto MINION_ATT_SETTING;
    }
    strcpy(att3, token);
    minion_att[2] = att3;

    /* att4 */
    token = strtok(NULL, " |\r");
    if (token == NULL) {
        goto MINION_ATT_SETTING;
    }
    strcpy(att4, token);
    minion_att[3] = att4;

MINION_ATT_SETTING:

    dummy = NULL;
    dummy = fgets(buffer4, LENGTH, file);

    if (dummy == NULL) {
        goto VERSION3_END;
    }

    token = strtok(buffer4, " |\r");

    /* printf("%d\n", *(token + 9)); */

    i = 0;
    x = 0;
    num = 0;

    while (token != NULL) {
        if (strcmp(minion_att[i], name) == 0) {
            buffer_p = token;
            
                
            while (*buffer_p != '\0') {
                out_character->minions[0].name[x] = *buffer_p;

                

                ++x;
                ++buffer_p;

                if (x == 50) {
                    out_character->minions[0].name[x] = '\0';
                    break;
                }
            }
            if (x != 50) {
                out_character->minions[0].name[x] = *buffer_p;
            }       

        } else if (strcmp(minion_att[i], health) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[0].health = num;
        } else if (strcmp(minion_att[i], strength) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[0].strength = num;
        } else if (strcmp(minion_att[i], defence) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[0].defence = num;
        } 

        token = strtok(NULL, " |\r");
        ++i;

        if (i == 4) {
            break;
        }

    }

    dummy = NULL;
    dummy = fgets(buffer5, LENGTH, file);

    if (dummy == NULL) {
        goto VERSION3_END;
    }

    token = strtok(buffer5, " |\r");

    i = 0;
    x = 0;
    num = 0;

    while (token != NULL) {
        if (strcmp(minion_att[i], name) == 0) {
            buffer_p = token;
                
            while (*buffer_p != '\0') {
                out_character->minions[1].name[x] = *buffer_p;

                ++x;
                ++buffer_p;

                if (x == 50) {
                    out_character->minions[1].name[x] = '\0';
                    break;
                }
            }
            if (x != 50) {
                out_character->minions[1].name[x] = '\0';
            }

        } else if (strcmp(minion_att[i], health) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[1].health = num;
        } else if (strcmp(minion_att[i], strength) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[1].strength = num;
        } else if (strcmp(minion_att[i], defence) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[1].defence = num;
        } 

        token = strtok(NULL, " |\r");
        ++i;

        if (i == 4) {
            break;
        }

    }

    dummy = NULL;
    dummy = fgets(buffer6, LENGTH, file);

    if (dummy == NULL) {
        goto VERSION3_END;
    }

    token = strtok(buffer6, " |\r");

    i = 0;
    x = 0;
    num = 0;

    while (token != NULL) {
        if (strcmp(minion_att[i], name) == 0) {
            buffer_p = token;
                
            while (*buffer_p != '\0') {
                out_character->minions[2].name[x] = *buffer_p;

                ++x;
                ++buffer_p;

                if (x == 50) {
                    out_character->minions[2].name[x] = '\0';
                    break;
                }
            }
            if (x != 50) {
                out_character->minions[2].name[x] = '\0';  
            }    

        } else if (strcmp(minion_att[i], health) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[2].health = num;
        } else if (strcmp(minion_att[i], strength) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[2].strength = num;
        } else if (strcmp(minion_att[i], defence) == 0) {
            sscanf(token, "%d", &num);
            out_character->minions[2].defence = num;
        } 

        token = strtok(NULL, " |\r");
        ++i;

        if (i == 4) {
            break;
        }

    }

VERSION3_END:
    fclose(file);
    return version;
    
}
