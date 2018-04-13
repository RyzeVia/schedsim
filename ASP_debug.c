/*
 * ASP_debug.c
 *
 *  Created on: 2014/10/16
 *      Author: RyzeVia
 */
#include "utilaspect.h"

void ASP_pre_procedure(const char* funcname, const char* tag){
	ASP_PRINT_EACH_TAG("EXTERNAL", "EEN:");
	ASP_PRINT_EACH_TAG("INTERNAL", "IEN:");
}

void ASP_post_procedure(const char* funcname, const char* tag){
	ASP_PRINT_EACH_TAG("EXTERNAL", "EEX:");
	ASP_PRINT_EACH_TAG("INTERNAL", "IEX:");
}
