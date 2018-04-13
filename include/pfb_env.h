/*
 * pfb_env.h
 *
 *  Created on: 2017/04/12
 *      Author: RyzeVia
 */

#ifndef INCLUDE_PFB_ENV_H_
#define INCLUDE_PFB_ENV_H_


#include "libpfb.h"
#include "utilmacros.h"

GLOBAL int n_opened GLOBAL_VAL(0);
GLOBAL int master GLOBAL_VAL(0);
GLOBAL char boxplace[PFB_MAXBXNAME] GLOBAL_VAL("");
GLOBAL char nmbuf[PFB_MAXBXPATH] GLOBAL_VAL("");

#endif /* INCLUDE_PFB_ENV_H_ */
