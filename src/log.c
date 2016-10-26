/*
 * log.c
 *
 *  Created on: Oct 9, 2016
 *      Author: TheUnnamedNewbie
 */


#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdint.h>
#include <inttypes.h>
#include "asm_func.h"
#include "log.h"
#include "performance_counters.h"
/*
 * TODO:
 * Should be able to add timestaps using the performance.h files. Will have to look into this
 * TODO:
 * Can speed this up with less consecutive printf statements and using just one.
 */




LogLevel logCurrentLevel = DEBUG; //Current LEVEL
LogLevel logDefaultLevel = DEBUG; //DEFAULT LEVEL

int isLogOn = 1;

int Log(LogSubSystem sys, LogLevel level, char *msg);
int LogWithNum(LogSubSystem sys, LogLevel level, char *msg, int number);
int LogWithNumH(LogSubSystem sys, LogLevel level, char *msg, int number);
void LogGlobalOf();
void LogGLobalOn();
LogLevel SetLogLevelDefault();
LogLevel SetLogLevel(LogLevel level);
const char* LogLevelToString(LogLevel level);
const char* LogSubSystemToString(LogSubSystem sys);

/*
 * Log an error. TODO: THIS IS NOT DONE YET
 * maybe add time or smthin
 *
 *
 * AUTH JOREN VAES
 *
 * Returns 0 if logs are turned off
 * Returns -1 if logs are turned on, but the logCurrentLevel is higher than the log's level.
 *
 *
 *
 */
int Log(LogSubSystem sys, LogLevel level, char *msg){
	int succes = 0;
	if(isLogOn){
		succes = -1;
		if(level >= logCurrentLevel){
			succes = 1;
			xil_printf("\r\n");
			xil_printf("%08d", get_cycle_counter());
			xil_printf(" - ");
			xil_printf(LogLevelToString(level));
			xil_printf(" - ");
			xil_printf(LogSubSystemToString(sys));
			xil_printf(" - ");
			xil_printf(msg);
		}
		//TODO: THINGS!
	}
	return succes;	 //Just in case, for some oddball reason, the calling function wants to know this.
}

/*
 * This doesn't seem to work yet
 *
 * AUTH JOREN VAES
 *
 */
int LogWithNum(LogSubSystem sys, LogLevel level, char *msg, int number){
	int succes;
	succes = Log(sys, level, msg);
	if(succes == 1){
		xil_printf("%i", number);
	}
	return succes;
}

int LogWithNumH(LogSubSystem sys, LogLevel level, char *msg, int number){
	int succes;
	succes = Log(sys, level, msg);
	if(succes == 1){
		xil_printf("%x", number);
	}
	return succes;
}


/*
 * Turn Logs on
 *
 * AUTH JOREN VAES
 *
 */
void LogGlobalOf(){
	isLogOn = 0;
}

/*
 * Turn Logs on
 * Allowes all logs with loglevel > loglevel to be logged
 *
 * AUTH JOREN VAES
 */
void LogGLobalOn(){
	isLogOn = 1;
}



/*
 * Set the Log level to system default.
 */
LogLevel SetLogLevelDefault(){
	xil_printf("\r\n");
	xil_printf("%08d", get_cycle_counter());
	xil_printf(" - ");
	xil_printf("INFO - LOGGING - Setting log level to default (");
	xil_printf(LogLevelToString(logDefaultLevel));
	xil_printf(")");
	logCurrentLevel = logDefaultLevel;
	return logCurrentLevel;
}


/*
 * Set the loglevel.
 *
 * AUTH JOREN VAES
 *
 *
 */
LogLevel SetLogLevel(LogLevel level){
	xil_printf("\r\n");
	xil_printf("%08d", get_cycle_counter());
	xil_printf(" - ");
	xil_printf("INFO - LOGGING - Changing log level from ");
	xil_printf(LogLevelToString(logCurrentLevel));
	xil_printf(" to ");
	xil_printf(LogLevelToString(level));
	logCurrentLevel = level;
	return logCurrentLevel; //You know, for good measure.
}


/*
 * Function to print the logLevel as a string
 *
 * AUTH JOREN VAES
 *
 */
const char* LogLevelToString(LogLevel level){
	switch(level){
		case INFO: return "INFO"; break;
		case MESSAGE: return "MESSAGE"; break;
		case DEBUG: return "DEBUG"; break;
		case ERROR: return "ERROR"; break;
		case CRITICAL: return "CRITICAL"; break;
		default: LogWithNum(LOGGING, CRITICAL, "NONLEGAL LOGLEVEL AT LogLevelToSTring", (int)level);
				  return "NONLEGAL LEVEL";
				  break;
	}
}



/*
 * Print subsystem as string
 *
 * AUTH JOREN VAES
 *
 */
const char* LogSubSystemToString(LogSubSystem sys){
	switch(sys){
		case MAIN: return "MAIN"; break;
		case MP_ARITHMATIC: return "MP_ARITHMATIC"; break;
		case LOGGING: return "LOGGING"; break;
		case BLANK: return "BLANK"; break;
		case PERFORMANCE: return "PERFORMANCE"; break;
		case MONTGOMMERY: return "MONTGOMMERY"; break;
		default: LogWithNum(LOGGING, CRITICAL, "NONLEGAL LOGSUBSYSTEM AT LogSubSystemToSTring", (int)sys);
				  return "NONLEGAL SUBSYSTEM";
				  break;
	}
}









