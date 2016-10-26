/*
 * log.h
 *
 *  Created on: Oct 9, 2016
 *      Author: TheUnnamedNewbie
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

typedef enum {
	INFO,			//IF YOU EDIT THIS
	MESSAGE,		//FOR THE LOVE OF GOD
	DEBUG,			//AND ALL THAT IS HOLY
	ERROR,			//ALSO EDDIT THE
	CRITICAL,		//LogLevelToString FUNCTION
} LogLevel;		//THANKYOU

typedef enum {
	MAIN,			//IF YOU EDIT THIS
	MP_ARITHMATIC,	//ALSO EDIT
	LOGGING,		//THE FUNCTION
	BLANK,			//LogSubSystemToString
	PERFORMANCE,
	MONTGOMMERY,
} LogSubSystem;	//THANKYOU


int Log(LogSubSystem sys, LogLevel level, char *msg);
int LogWithNum(LogSubSystem sys, LogLevel level, char *msg, int number);

int LogWithNumH(LogSubSystem sys, LogLevel level, char *msg, int number);
void LogGlobalOf();
void LogGLobalOn();
LogLevel SetLogLevelDefault();
LogLevel SetLogLevel(LogLevel level);

#endif /* SRC_LOG_H_ */
