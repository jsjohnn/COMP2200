#include <assert.h>
#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(
    const char* const cab_start_location, 
    const size_t cab_length, 
    const char* const cluster_start_locations[], 
    const size_t cluster_lengths[], 
    const size_t cluster_count, 
    size_t* out_longest_safe_area_length)
{
    size_t i;
    size_t overlab_count = 0;
    size_t safe_area_length = 0;
    size_t bool_continous_flag = 0;
     
    const char* temp_longest_address = NULL;
    const char* longest_address = NULL;
    const char* current_location = cab_start_location;
    const char* last_location = current_location + cab_length;

    *out_longest_safe_area_length = 0;
    
    if (cab_length == 0) {
        return NULL;
    }

    for (; current_location < last_location; ++current_location) {
        for (i = 0; i < cluster_count; ++i) {
            if (current_location >= cluster_start_locations[i]
                && current_location < cluster_start_locations[i] + cluster_lengths[i]) {
                ++overlab_count;
            }
        }

        if (overlab_count % 2 == 0) {
            safe_area_length += 1;

            if (bool_continous_flag != 1) {
                temp_longest_address = current_location;
                bool_continous_flag = 1;
            }
        } else {
            if (bool_continous_flag != 0 && safe_area_length >= *out_longest_safe_area_length) {
                *out_longest_safe_area_length = safe_area_length;
                if (temp_longest_address > longest_address) {
                    longest_address = temp_longest_address;
                }
            }
            temp_longest_address = 0;
            safe_area_length = 0;
            bool_continous_flag = 0;
        }
        
        if (current_location == last_location - 1 && bool_continous_flag != 0
            && safe_area_length >= *out_longest_safe_area_length) {
            *out_longest_safe_area_length = safe_area_length;
            if (temp_longest_address > longest_address) {
                longest_address = temp_longest_address;
            }
            break;
        }

        overlab_count = 0;
    }
    
    return longest_address;
}

int get_travel_time(
    const char* const cab_start_location,
    const size_t cab_length,
    const char* const cluster_start_locations[],
    const size_t cluster_lengths[],
    const size_t cluster_count)
{
    size_t i;
    size_t overlab_count = 0;
    size_t safe_area_length = 0;
    size_t unsafe_area_length = 0;

    const char* current_location = cab_start_location;
    const char* last_location = current_location + cab_length;

    for (; current_location < last_location; ++current_location) {
        for (i = 0; i < cluster_count; ++i) {
            if (current_location >= cluster_start_locations[i]
                && current_location < cluster_start_locations[i] + cluster_lengths[i]) {
                ++overlab_count;
            }
        }

        (overlab_count % 2 == 0)? ++safe_area_length : ++unsafe_area_length;
        overlab_count = 0;
    }

    return (int)((safe_area_length / 10.0 + unsafe_area_length / 5.0) + 0.5);
}
