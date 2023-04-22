#ifndef _RC_H_
#define _RC_H_

typedef int RC;

#define RC_SUCCESS      0
#define RC_FAIL         -1

#define SUCCESS(code) ((RC)(code) >= (RC)0)

#endif
