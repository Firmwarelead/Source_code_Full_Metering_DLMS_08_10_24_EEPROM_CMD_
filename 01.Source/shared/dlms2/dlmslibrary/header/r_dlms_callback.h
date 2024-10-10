/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_callback.h
* Version      : 1.00
* Description  : DLMS Callback Link Definition
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_CALLBACK_H
#define _R_DLMS_CALLBACK_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/* Indicate how many pointer can be reconige to the list */
#define		CALLBACK_LINK_MAX_LIST_SIZE			(3)

#define		EMPTY_CALLBACK_LINK(link) do {					\
	for (link ## _count = 0;                                \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;      \
         link ## _count++) {		                        \
		link[link ## _count] = NULL;						\
	}														\
	link ## _pos = 0;										\
} while (0);

/* Declare */
#define		DECLARE_CALLBACK_LINK(qualifier, type, name)	qualifier type name[CALLBACK_LINK_MAX_LIST_SIZE]; qualifier uint8_t name ## _pos; qualifier uint8_t name ## _count;

/* Add to the link */
#define		ADD_CALLBACK_LINK(link, callback) do {			            \
	uint8_t found = FALSE;									            \
	for (link ## _count = 0;                                            \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;                  \
         link ## _count++) {		                                    \
		if (link[link ## _count] == callback) {							\
			found = TRUE;												\
			break;														\
		}																\
	}																	\
	if (link ## _pos < CALLBACK_LINK_MAX_LIST_SIZE && found == FALSE) {	\
		link[link ## _pos] = callback;									\
		link ## _pos++;													\
		if (g_dlms_diag_callback_max_usage < link ## _pos) {			\
			g_dlms_diag_callback_max_usage = link ## _pos;				\
		}																\
	}																	\
} while (0);

/* Normal invoker */
#define		INVOKE_CALLBACK_LINK(link) do {					\
	for (link ## _count = 0;                                \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;		\
         link ## _count++) {		                        \
		if (link[link ## _count] != NULL) {				    \
			(*link[link ## _count])();					    \
		}													\
	}														\
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG1(link, arg1) do {		\
	for (link ## _count = 0;                                \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;		\
         link ## _count++) {		                        \
		if (link[link ## _count] != NULL) {				    \
			(*link[link ## _count])(arg1);				    \
		}													\
	}														\
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG2(link, arg1, arg2) do {	\
	for (link ## _count = 0;                                    \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;			\
         link ## _count++) {		                            \
		if (link[link ## _count] != NULL) {				        \
			(*link[link ## _count])(arg1, arg2);			    \
		}													    \
	}														    \
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG3(link, arg1, arg2, arg3) do {	\
	for (link ## _count = 0;                                        \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;				\
         link ## _count++) {		                                \
		if (link[link ## _count] != NULL) {				            \
			(*link[link ## _count])(arg1, arg2, arg3);	            \
		}													        \
	}														        \
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG4(link, arg1, arg2, arg3, arg4) do {	\
	for (link ## _count = 0;                                                \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;						\
         link ## _count++) {		                                        \
		if (link[link ## _count] != NULL) {								    \
			(*link[link ## _count])(arg1, arg2, arg3, arg4);				\
		}																	\
	}																		\
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG5(link, arg1, arg2, arg3, arg4, arg5) do {	\
	for (link ## _count = 0;                                                    \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;							\
         link ## _count++) {		                                            \
		if (link[link ## _count] != NULL) {								        \
			(*link[link ## _count])(arg1, arg2, arg3, arg4, arg5);		        \
		}																	    \
	}																		    \
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG6(link, arg1, arg2, arg3, arg4, arg5, arg6) do {	\
	for (link ## _count = 0;                                                            \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;									\
         link ## _count++) {		                                                    \
		if (link[link ## _count] != NULL) {								                \
			(*link[link ## _count])(arg1, arg2, arg3, arg4, arg5, arg6);	            \
		}																	            \
	}																		            \
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG7(link, arg1, arg2, arg3, arg4, arg5, arg6, arg7) do {	\
	for (link ## _count = 0;                                                                \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;										\
         link ## _count++) {		                                                        \
		if (link[link ## _count] != NULL) {								                    \
			(*link[link ## _count])(arg1, arg2, arg3, arg4, arg5, arg6, arg7);	            \
		}																	                \
	}																		                \
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG8(link, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) do {	\
	for (link ## _count = 0;                                                                        \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;												\
         link ## _count++) {		                                                                \
		if (link[link ## _count] != NULL) {								                            \
			(*link[link ## _count])(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);	            \
		}																	                        \
	}																		                        \
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG9(link, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) do {	\
	for (link ## _count = 0;                                                                            \
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;													\
         link ## _count++) {		                                                                    \
		if (link[link ## _count] != NULL) {								                                \
			(*link[link ## _count])(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);	            \
		}																	                            \
	}																		                            \
} while (0);

#define		INVOKE_CALLBACK_LINK_ARG10(link, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) do {	\
	for (link ## _count = 0;																					\
         link ## _count < CALLBACK_LINK_MAX_LIST_SIZE;															\
         link ## _count++) {																					\
		if (link[link ## _count] != NULL) {																		\
			(*link[link ## _count])(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);				\
		}																										\
	}																											\
} while (0);

/* Fast first invoker */
#define		FAST_INVOKE_CALLBACK_LINK(link) do {			\
	if (link[0] != NULL) {									\
		(*link[0])();										\
	}														\
} while (0);

#define		FAST_INVOKE_CALLBACK_LINK_ARG1(link, arg1) do {		\
	if (link[0] != NULL) {										\
		(*link[0])(arg1);										\
	}															\
} while (0);

#define		FAST_INVOKE_CALLBACK_LINK_ARG2(link, arg1, arg2) do {	\
	if (link[0] != NULL) {										\
		(*link[0])(arg1, arg2);									\
	}															\
} while (0);

#define		FAST_INVOKE_CALLBACK_LINK_ARG3(link, arg1, arg2, arg3) do {	\
	if (link[0] != NULL) {												\
		(*link[0])(arg1, arg2, arg3);									\
	}																	\
} while (0);

#define		FAST_INVOKE_CALLBACK_LINK_ARG4(link, arg1, arg2, arg3, arg4) do {	\
	if (link[0] != NULL) {														\
		(*link[0])(arg1, arg2, arg3, arg4);										\
	}																			\
} while (0);

#define		FAST_INVOKE_CALLBACK_LINK_ARG5(link, arg1, arg2, arg3, arg4, arg5) do {	\
	if (link[0] != NULL) {															\
		(*link[0])(arg1, arg2, arg3, arg4, arg5);									\
	}																				\
} while (0);

#define		FAST_INVOKE_CALLBACK_LINK_ARG6(link, arg1, arg2, arg3, arg4, arg5, arg6) do {	\
	if (link[0] != NULL) {																	\
		(*link[0])(arg1, arg2, arg3, arg4, arg5, arg6);										\
	}																						\
} while (0);

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern uint8_t	g_dlms_diag_callback_max_usage;

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* _R_DLMS_CALLBACK_H */

