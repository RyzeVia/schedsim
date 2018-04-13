/*
 * libpfb.h
 *
 *  Created on: 2017/04/11
 *      Author: RyzeVia
 */

#ifndef INCLUDE_LIBPFB_H_
#define INCLUDE_LIBPFB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utilmacros.h"
#include "utilaspect.h"
#include "libcfr.h"

#define PFB_DEFBXNAME "noname"
#define PFB_MAXBXNAME	(256)
#define PFB_MAXBXNAME_PLACE (3)
#define PFB_MAXBXPATH	(PFB_MAXBXNAME+PFB_MAXBXNAME_PLACE+1)
#define PFB_RDELCMD	"rm -Rf %s"
#define PFB_MAXRDELCMD	(16+PFB_MAXBXNAME)

struct PFB_hdl_ {
	char boxname[PFB_MAXBXPATH];
	long int id;
	long int mailsize;
	int fd;
};
typedef struct PFB_hdl_ PFB_hdl;

/* aspect debug */
#define PFB_LOGEN(interface_mode) \
		do{ \
			ASP_PRE_PROC(__FUNCTION__, __FILE__); \
			ASP_PRE_PROC(__FUNCTION__, interface_mode);\
		}while(0)
#define PFB_LOGEX(interface_mode) \
		do{ \
			ASP_POST_PROC(__FUNCTION__, interface_mode); \
			ASP_POST_PROC(__FUNCTION__, __FILE__); \
		}while(0)
#define PFBE_LOGEN() PFB_LOGEN("EXTERNAL")
#define PFBE_LOGEX() PFB_LOGEX("EXTERNAL")
#define PFBI_LOGEN() PFB_LOGEN("INTERNAL")
#define PFBI_LOGEX() PFB_LOGEX("INTERNAL")


#include "pfb_env.h"

#endif /* INCLUDE_LIBPFB_H_ */
