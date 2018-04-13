/*
 * PFB_init.c
 *
 *  Created on: 2017/04/11
 *      Author: RyzeVia
 */
//DEBUG FLAG//
#define DISPLAY_ERROR_LOCATION
#define


#define GLOBAL_DEFINITION
#include "libpfb.h"


void PFB_Init(char* name, int ismaster){
	char* dir = CFR_getvalue("COMMDIR", PFB_DEFBXNAME);
	int rv;
	static int initialized = 0;
	PFBI_LOGEN();

	if(initialized != 0){
		ERROR_LOCF("Multiple PFB_Init() call");
		ERROR_EXIT();
	}

	n_opened = 0;
	master = ismaster;
	rv = snprintf(boxplace, PFB_MAXBXNAME, "%s/%s", dir, name);
	if((rv >= PFB_MAXBXNAME) | (rv < 0)){
		ERROR_LOCF("Application Name is too long or Other reasons");
		ERROR_LOCF("Hint: The length of PFB_Init() argument + shared storage path ");
		ERROR_LOCF("      must be smaller than %s byte.", PFB_MAXBXNAME);
		ERROR_EXIT();
	}

	rv = mkdir(boxplace, S_IRWXU);
	// 重複作成はエラー無視により対応する

	initialized = 1;
	PFBI_LOGEX();

}

PFB_hdl* PFB_Open(long int id, long int mailsize){
	PFB_hdl* hdl;
	int rv;

	PFBI_LOGEN();

	MALLOC(PFB_hdl, hdl, sizeof(PFB_hdl));
	hdl->mailsize = mailsize;
	hdl->id = id;
	rv = snpritf(hdl->boxname, PFB_MAXBXPATH, "%s/%d", boxplace, n_opened);
	if((rv >= PFB_MAXBXPATH | (rv < 0))){
		ERROR_LOCF("The number of box exceed limitation or Other reasons");
		ERROR_LOCF("Hint: #box must be smaller than %d-digit number", PFB_MAXBXNAME_PLACE);
		ERROR_EXIT();
	}
	if(0 > (hdl->fd = open(hdl->boxname, O_RDWR| O_CREAT, S_IRWXU))){
		PERROR_LOC("open");
		ERROR_LOCF("Hint: The directory %s may not be there.", boxplace);
		ERROR_EXIT();
	}

	PFBI_LOGEX();

	return hdl;
}

void PFB_Close(PFB_hdl* hdl){
	PFBI_LOGEN();

	if(0 > (close(hdl->fd))){
		PEEROR_LOC("close");
		ERROR_EXIT();
	}
	if(0 > (free(hdl))){
		PERROR_LOC("free");
		ERROR_EXIT();
	}

	PFBI_LOGEX();
}

void PFB_Finalize(){
	char cmd[PFB_MAXRDELCMD];

	PFBI_LOGEN();

	if(master == 1){
//		printf(stderr, "Please delete directory : %s\n", boxplace);
		sprintf(cmd, PFB_RDELCMD, boxplace);
		system(cmd);
	}
	PFBI_LOGEX();
}

int PFB_Set(PFB_hdl* hdl, int destid, void* value){
	int tot = 0, wc = 0;
	int len = hdl->mailsize;

	PFBI_LOGEN();
	lseek(hdl->fd, destid*hdl->mailsize, SEEK_SET);

	while(len){
		do {
			wc = write(hdl->fd, value, len);
		}while (wc < 0 && errno == EINTR);

		if(wc < 0){
			tot = -1;
			break;
		}

		tot += wc;
		value = ((const char*)value)+wc;
		len -= wc;
	}

	fsync(hdl->fd);

	PFBI_LOGEX();
	return tot;
}

int PFB_Get(PFB_hdl* hdl, int destid, void* value){
	int tot = 0, wc = 0;
	int len = hdl->mailsize;

	PFBI_LOGEN();
	lseek(hdl->fd, destid*hdl->mailsize, SEEK_SET);
	fsync(hdl->fd);

	while(len > 0){
		do{
			wc = read(hdl->fd, value, len);
		}while(wc < 0 && errno == EINTR);

		if(wc < 0){
			tot = -1;
			break;
		}

		if (wc == 0) break;

		tot += wc;
		value = ((const char*)value)+wc;
		len -= wc;
	}

	PFBI_LOGEX();
	return tot;
}






