#ifndef MACROS_H
#define MACROS_H

#define FALSE 0
#define TRUE !FALSE

#define BETWEEN(min,max,value) ((value <= max && value >= min) ? TRUE : FALSE)

/* Markers */
#define MARKER_BORDER       '*'

/* Keyboard Controls */
#define KEY_LEFT    'a'
#define KEY_RIGHT   'd'
#define KEY_UP      'w'
#define KEY_DOWN    's'

#endif