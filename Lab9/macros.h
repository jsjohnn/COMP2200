#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
        
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define ABS(x) (((x) >= 0) ? (x) : -(x))

#define RANGE(curr, min, max)              \
    for ((curr) = (min); ((curr) <= (max)); ++(curr))  \
    
#define RANGE_DESC(curr, max, min)         \
    for (((curr) = (max)); ((curr) >= (min)); --(curr))  \

#define SET(ary, start, count, value) \
    do {                              \
        int i = (start);              \
        int end = i + (count);        \
                                      \
        for (; i < end; ++i) {        \
            (ary)[i] = (value);       \
        }                             \
                                      \
    } while(0) \

/* 중괄호가 없는 if / else 문에 복붙 될 때 세미콜론 때문에 빌드 오류가 발생

#define SET(ary, start, count, value) \
{
    int i = (start);
    int end = i + (count);

    for (; i < end; ++i) {
        (ary)[i] = (value);
    }
}

*/

#endif /* MACROS_H */
