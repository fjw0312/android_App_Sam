/*==========================================================================*
 *
 *  FILENAME : err_code.h
 *  CREATOR  : fjw0312                 
 *  VERSION  : V1.00
 *  PURPOSE  : Defines the all error codes 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/

#ifndef __ERR_CODE_H__
#define __ERR_CODE_H__

#ifdef __cplusplus
extern "C" {
#endif

//
// The exit code of ACU main application.
// 
#define SYS_EXIT_BY_USER	0	// killed/stopped by user.
#define SYS_EXIT_BY_SWAP    1	// for swap to other program. 
#define SYS_EXIT_BY_REBOOT_REQ  2	// for the request to reboot system. 
#define SYS_EXIT_BY_ERROR	128
#define SYS_EXIT_BY_INIT	128	// for init error.
#define SYS_EXIT_BY_THREAD	129	// for abnormal threads.
#define SYS_EXIT_BY_SERVICE 130	// for abnormal service
#define SYS_EXIT_BY_FAULT	131 // for fault errors, such as segment fault.


/* 
 * Error code format: 
 * An errorcode, which can be generated by MK_ERR_CODE macro, is a unique 
 * DWORD is the whole system. 
 */

/* To make an error code. Now format is b3b2b1b0. b3 is the module ID, b2 is the 
 * sub-module ID and b1b0 is the error code in the sub-module.
 */
#define MK_ERR_CODE(nMajorModuleID, nMinorModuleID, nErrCodeInMinorModule ) \
	( ((nMajorModuleID)<<24) + ((nMinorModuleID)<<16) +(nErrCodeInMinorModule))

/* 
 * Major module ID definition. ( minor-module ID are defined in major modules
 */
/*
CFG = HLD for ACU Software 每 Config Mgmt Module .doc
DXI = HLD for ACU Software 每 Data Exchange Interface Module .doc
DAT = HLD for ACU Software 每 Data Management Module.doc
DBS = HLD for ACU Software 每 Debug and Service Module.doc
EQP = HLD for ACU Software 每 Equipment Monitoring Module.doc
ESR = HLD for ACU Software 每 ESR Module.doc
CTL = HLD for ACU Software 每 General Controller Module .doc
HAL = HLD for ACU Software 每 HAL for Communication Ports.doc
LCD = HLD for ACU Software 每 LCD Service Module .doc
MSM = HLD for ACU Software 每 Main Module.doc
MSC = HLD for ACU Software 每 Miscellaneous Function Module.doc
PLC = HLD for ACU Software 每 PLC Module.doc
PUB = HLD for ACU Software 每 Public Module.doc
SEC = HLD for ACU Software 每 Security Management Module .doc
SNP = HLD for ACU Software 每 SNMP Service Module .doc
WEB = HLD for ACU Software 每 Web Module.doc
*/
enum MAJOR_MODULE_ENUM
{
	MOD_SYS		= 0,		/* To define the common(SYStem) error code.		*/
	MOD_MSM		= 1,		/* Main System Module							*/
	MOD_EQP		= 2,		/* EQuiPment monitoring module					*/
	MOD_CFG		= 3,		/* ConFiGuration module							*/
	MOD_DXI		= 4,		/* Data eXchange Interface						*/
	MOD_DAT		= 5,		/* DATa management module						*/
	MOD_HAL		= 6,		/* Hardware Abstract Layer modules				*/
	MOD_PUB     = MOD_SYS,	/* PUBlic modules								*/
	MOD_CTL		= 7,		/* general ConTroL module						*/
	MOD_ESR		= 8,		/* Eem Soc-tpe, Rsoc							*/
	MOD_LCD		= 9,		/* LCD interface								*/
	MOD_WEB		= 10,		/* Web interface								*/
	MOD_PLC		= 11,		/* PLC											*/
	MOD_SNP		= 12,		/* SNMP agent									*/
	MOD_SEC		= 13,		/* Security management							*/
	MOD_DBS		= 14,		/* Debug and Maintenance Interface module		*/
	MOD_MSC		= 15,		/* Miscellaneous Function Module				*/
	MOD_SAM		= 16,		/* SAMpler modules(reserved)					*/
	MOD_LOG		= 17,		/* Write running log							*/
	
	MOD_END					/* End now										*/
};


/****************************************************************************
 *Error code definition for system
 */
enum ERR_CODE_SYSTEM_ENUM	/* the error codes for system or public			*/
{
	ERR_OK				= MK_ERR_CODE(0, 0, 0),	/* always 0!				*/
	ERR_NO_MEMORY		= MK_ERR_CODE(0, 0, 1),	/* out of memory			*/
	ERR_INVALID_ARGS	= MK_ERR_CODE(0, 0, 2),	/* error function args		*/
	ERR_TIMEOUT			= MK_ERR_CODE(0, 0, 3),	/* error timeout			*/
	ERR_SYS_FAULT		= MK_ERR_CODE(0, 0, 4),	/* error segment fault		*/
};


enum ERR_CODE_MAIN_MODULE_ENUM
{
	ERR_MAIN_OK			= ERR_OK,
	ERR_LOADING_CONFIG	= MK_ERR_CODE(MOD_MSM, 0, 1),/* load cfg error */
	ERR_CREATING_EQUIPMENT_MANAGER = MK_ERR_CODE(MOD_MSM, 0, 2),
	ERR_CREATING_SERVICE= MK_ERR_CODE(MOD_MSM, 0, 3),
	ERR_INIT_USER_MGR	= MK_ERR_CODE(MOD_MSM, 0, 4),
	ERR_INIT_DATA_MGMT	= MK_ERR_CODE(MOD_MSM, 0, 5),	// hist data interface
	ERR_INIT_DXI		= MK_ERR_CODE(MOD_MSM, 0, 6),	// data exchange interface
	ERR_INIT_TIME_SYNC	= MK_ERR_CODE(MOD_MSM, 0, 7),	// time sync
};

/*==========================================================================*
 * error codes defined in modules											*
 *==========================================================================*/

// public modules
enum MOD_PUB_MODULE_ENUM
{
	MOD_PUB_GENERAL			= 0,		/* general			*/
	MOD_PUB_THREAD			= 1,		/* thread			*/
	MOD_PUB_TIMER			= 2,		/* timer			*/
	MOD_PUB_QUEUE			= 3,		/* Queue			*/
	MOD_PUB_MUTEX			= 4,		/* mutex			*/
};

// error code for public modules
enum ERR_CODE_PUB_MODULE_ENUM
{

	// errors of mutex
	ERR_MUTEX_OK			= ERR_OK,
	ERR_MUTEX_TIMEOUT		= ERR_TIMEOUT,//timeout

	// errors for queue
	ERR_QUEUE_OK			= ERR_OK,
	ERR_QUEUE_FULL			= MK_ERR_CODE(MOD_PUB, MOD_PUB_QUEUE, 1),
	ERR_QUEUE_EMPTY			= MK_ERR_CODE(MOD_PUB, MOD_PUB_QUEUE, 2),

	// errors for timer
	ERR_TIMER_OK			= ERR_OK,
	ERR_TIMER_EXISTS		= MK_ERR_CODE(MOD_PUB, MOD_PUB_TIMER, 1),
	ERR_TIMER_SET_FAIL		= MK_ERR_CODE(MOD_PUB, MOD_PUB_TIMER, 2),
	ERR_TIMER_NOT_FOUND		= MK_ERR_CODE(MOD_PUB, MOD_PUB_TIMER, 3),

	// error code of run thread
	ERR_THREAD_OK			= ERR_OK,
	ERR_THREAD_INVALID_HANDLE=MK_ERR_CODE(MOD_PUB, MOD_PUB_THREAD, 1),
	ERR_THREAD_MSG_EMPTY	= MK_ERR_CODE(MOD_PUB, MOD_PUB_THREAD, 2),
	ERR_THREAD_MSG_FULL		= MK_ERR_CODE(MOD_PUB, MOD_PUB_THREAD, 3),
	ERR_THREAD_INIT_MANAGER = MK_ERR_CODE(MOD_PUB, MOD_PUB_THREAD, 4),
	ERR_THREAD_EXIT_MANAGER = MK_ERR_CODE(MOD_PUB, MOD_PUB_THREAD, 5),

	// eorr code of StopThread.
	ERR_THREAD_STILL_RUNNING= MK_ERR_CODE(MOD_PUB, MOD_PUB_THREAD, 6),
	ERR_THREAD_KILLED       = MK_ERR_CODE(MOD_PUB, MOD_PUB_THREAD, 7),
};


/* error codes for HAL comm port	*/
/* minor modules for HAL comm port	*/
enum MOD_HAL_MINOR_MODULE_ENUM
{
	MOD_HAL_GENERAL			= 0,		/* general			*/
	MOD_HAL_TCPIP			= 1,		/* TCPIP Network	*/
	MOD_HAL_SERIAL			= 2,		/* std serial		*/
	MOD_HAL_DIALLING		= 3,		/* dialling modem	*/
	MOD_HAL_UDP				= 4			/* UDP Network		*/
};

enum ERR_CODE_HAL_COMM_ENUM
{
	/* general errors */
	ERR_COMM_OK				= ERR_OK,
	ERR_COMM_NO_MEMORY		= ERR_NO_MEMORY,
	ERR_COMM_TIMEOUT		= ERR_TIMEOUT,
	ERR_COMM_OPENING_PORT	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 2),
	ERR_COMM_OPENING_PARAM	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 3),
	ERR_COMM_SUPPORT_ACCEPT = MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 4),
	ERR_COMM_MANY_CLIENTS   = MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 5),
	ERR_COMM_ACCEPT_FAILURE = MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 6),
	ERR_COMM_READ_DATA      = MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 7),
	ERR_COMM_WRITE_DATA     = MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 8),
	ERR_COMM_CONNECT_SERVER	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 9 ),
	ERR_COMM_CREATE_SERVER	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 10 ),
	ERR_COMM_PORT_HANDLE	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 11 ),
	ERR_COMM_CTRL_COMMAND	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 12 ),
	ERR_COMM_CTRL_PARAMS	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 13 ),
	ERR_COMM_CTRL_EXECUTION	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 14 ),
	ERR_COMM_BUFFER_SIZE	= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL, 15 ),
	ERR_COMM_CONNECTION_BROKEN=MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL,16 ),
	ERR_COMM_STD_PORT		= MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL,17 ),
	ERR_COMM_LOADING_DRIVER = MK_ERR_CODE(MOD_HAL, MOD_HAL_GENERAL,18 ),

	/* special for TCP/IP and UDP port */

	/* special for dialling serial port */
	ERR_COMM_CTRL_MODEM		= MK_ERR_CODE(MOD_HAL, MOD_HAL_DIALLING, 1),
	ERR_COMM_DIAL_PHONE		= MK_ERR_CODE(MOD_HAL, MOD_HAL_DIALLING, 2),
	ERR_COMM_PHONE_BUSY		= MK_ERR_CODE(MOD_HAL, MOD_HAL_DIALLING, 3),
	ERR_COMM_HANGUP_PHONE	= MK_ERR_CODE(MOD_HAL, MOD_HAL_DIALLING, 4),
	ERR_COMM_NO_CARRIER		= MK_ERR_CODE(MOD_HAL, MOD_HAL_DIALLING, 5),
	ERR_COMM_NO_DIALTONE	= MK_ERR_CODE(MOD_HAL, MOD_HAL_DIALLING, 6),
};


/* err code for CFG module */
enum ERR_CODE_CFG_ENUM
{
	ERR_CFG_OK					= ERR_OK,
	ERR_CFG_NO_MEMORY			= ERR_NO_MEMORY,
	ERR_CFG_FAIL				= MK_ERR_CODE(MOD_CFG, 0, 1),
	ERR_CFG_BADCONFIG			= MK_ERR_CODE(MOD_CFG, 0, 2),
	ERR_CFG_FILE_OPEN			= MK_ERR_CODE(MOD_CFG, 0, 3),
	ERR_CFG_FILE_READ			= MK_ERR_CODE(MOD_CFG, 0, 4),
	ERR_CFG_BADRUNINFO			= MK_ERR_CODE(MOD_CFG, 0, 5),

	/* input param is wrong */
	ERR_CFG_PARAM               = MK_ERR_CODE(MOD_CFG, 0, 6),

	ERR_CFG_RUNINFO_MUTEX_TIMEOUT		= MK_ERR_CODE(MOD_CFG, 0, 7),
};


/* err code for ESR module */
enum MOD_ESR_SUBMODULE_ENUM
{
	MOD_ESR_LINKLAYER_MGMT   = 0,  /* Link-layer Manager sub-module */
	MOD_ESR_FRAME_ANALYSE,		   /* Frame Analyse sub-module      */
	MOD_ESR_STATE_MACHINE,		   /* State Machine sub-module		*/
	MOD_ESR_CMD_HANDLER,	       /* Command Handler sub-module    */
	MOD_ESR_ALARM_HANDLER,		   /* Alarm Handler sub-module      */
	MOD_ESR_SERVICE_PROVIDER,	   /* Service Provider sub-module   */
	MOD_ESR_CONFIG_BUILDER		   /* Config Builder sub-module	    */
};

enum ERR_CODE_ESR_ENUM
{
	ERR_ESR_CMD_OK				= MK_ERR_CODE(MOD_ESR, MOD_ESR_CMD_HANDLER, 1),
	ERR_ESR_CMD_NEXT			= MK_ERR_CODE(MOD_ESR, MOD_ESR_CMD_HANDLER, 2),
	ERR_ESR_CMD_FAIL			= MK_ERR_CODE(MOD_ESR, MOD_ESR_CMD_HANDLER, 3),
};


/* err code for CTL module */
/* minor modules for CTL comm port	*/
enum MOD_CTL_MINOR_MODULE_ENUM
{
	MOD_CTL_GENERAL			= 0,		/* General						*/
	MOD_CTL_MODULE			= 1,		/* GC Function Module Error		*/

	MOD_CTL_INTERFACE		= 2,		/* Interface functions error	*/
	MOD_CTL_LIST			= 3,		/* List error					*/
	MOD_CTL_CFG				= 4,		/* Private Configuration        */
	MOD_CTL_PARAM			= 5,		/* Parameter of function		*/
	MOD_CTL_OTHER			= 10,		/* Others						*/
};

/* err code for CTL module */
enum ERR_CODE_CTL_ENUM
{
	ERR_CTL_OK					= ERR_OK,
	ERR_CTL_NO_MEMORY			= ERR_NO_MEMORY,

	ERR_CTL_BM_STATE			= MK_ERR_CODE(MOD_CTL, MOD_CTL_MODULE, 1),
	ERR_CTL_BM_TESTLOG,
	ERR_CTL_BM_BATT_NUM,
	ERR_CTL_BM_RECT_NUM,

	ERR_CTL_PRI_CFG				= MK_ERR_CODE(MOD_CTL, MOD_CTL_INTERFACE, 1),
	ERR_CTL_GET_MESSAGE,
	ERR_CTL_GET_SAMPLER_NUM,
	ERR_CTL_GET_SAMPLER_LIST,
	ERR_CTL_GET_EQUIP_NUM,
	ERR_CTL_GET_EQUIP_LIST,
	ERR_CTL_GET_VLAUE,
	ERR_CTL_SET_VALUE,
	ERR_CTL_GET_ALARM_NUM,
	ERR_CTL_SIG_TYPE,
	ERR_CTL_TIMER,
	ERR_CTL_DATA_CREATE,
	ERR_CTL_DATA_WRITE,
	ERR_CTL_DATA_CLOSE,

	ERR_CTL_LIST_CREATE			= MK_ERR_CODE(MOD_CTL, MOD_CTL_LIST, 1),
	ERR_CTL_LIST_GET,
	ERR_CTL_LIST_SET,
	ERR_CTL_LIST_INSERT,
	ERR_CTL_LIST_DELETE,
	ERR_CTL_LIST_OTHER,
	
	ERR_CTL_CFG_EQUIP_ID		= MK_ERR_CODE(MOD_CTL, MOD_CTL_CFG, 1),
	ERR_CTL_CFG_GROUP_SIG,
	ERR_CTL_CFG_BATT_SIG,
	ERR_CTL_CFG_RECT_SIG,
	ERR_CTL_CFG_SIG_NAME,
	ERR_CTL_CFG_SIG_ID,
	ERR_CTL_CFG_SIG_TYPE,
	ERR_CTL_CFG_EQUIP_TYPE_ID,
	ERR_CTL_CFG_TEST_PLAN,
	ERR_CTL_CFG_LVD,
	ERR_CTL_CFG_BATT_TYPE_PARAM,
	ERR_CTL_CFG_ENGY_SAV_OUTPUT,
	ERR_CTL_CFG_POWER_SPLIT_INPUT,
	ERR_CTL_CFG_REDUCE_CONSUMPTION_ACT,
	ERR_CTL_CFG_LMT_MAX_POWER_ACT,
	ERR_CTL_CFG_ENGY_SAV_MODE,
	ERR_CTL_CFG_ENGY_SAV_SCHEDULE,
	ERR_CTL_CFG_LOAD_FLIE,
	ERR_CTL_CFG_POINT_NULL,
	ERR_CTL_CFG_BATT_TYPE_NO,
	ERR_CTL_CFG_INTERFACE,

	ERR_CTL_PARAM_EQUIP_TYPE	= MK_ERR_CODE(MOD_CTL, MOD_CTL_PARAM, 1),
	ERR_CTL_PARAM_RT_RATED_CURR,

	ERR_CTL_OTHER				= MK_ERR_CODE(MOD_CTL, 0, 10),
};


/* error codes for DXI module	*/
/* minor for DXI module	*/
enum MOD_DXI_MINOR_MODULE_ENUM
{
	MOD_DXI_DATA			= 0,		/* for data sub module*/
	MOD_DXI_TRAP			= 1,		/* for trap sub module*/
};

enum ERR_CODE_DXI_ENUM
{
	//No error
	ERR_DXI_OK							= ERR_OK,
	//Invalid interface type
	ERR_DXI_INVALID_VARIABLE_TYPE		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 1),
	//Invalid data ID
	ERR_DXI_INVALID_VARIABLE_DATA_ID	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 2),
	//Invalid data sub ID
	ERR_DXI_INVALID_VARIABLE_SUBID		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 3),
	//Wrong buffer length
	ERR_DXI_WRONG_BUFFER_LENGTH			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 4),
	//Invalid length output
	ERR_DXI_INVALID_LENGTH_BUF			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 5),
	//Invalid buffer
	ERR_DXI_INVALID_DATA_BUFFER			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 6),
	//Time out
	ERR_DXI_TIME_OUT					= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 7),
									
	//Invalid equip buffer
	ERR_DXI_INVALID_EQUIP_BUFFER		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 8),
	//Invalid standard equip buffer
	ERR_DXI_INVALID_STD_EQUIP_BUFFER	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 9),
									
	//Invalid standard signal buffer
	ERR_DXI_INVALID_STD_SIGNAL_BUFFER	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 10),	
								
	//Invalid equip ID
	ERR_DXI_INVALID_EQUIP_ID			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 11),
							
	//Control or set failure
	ERR_DXI_CONTROL_OR_SET				= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 12),
								
	//Set data has not change
	ERR_DXI_DATA_NOT_CHANGED			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 13),		
	//Data is not in range
	ERR_DXI_INVALID_DATA_VALUE			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 14),
								
	//Invalid signal value type
	ERR_DXI_INVALID_SIGNAL_VALUE_TYPE	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 15),
									
	//Invalid site name buffer
	ERR_DXI_INVALID_SITE_NAME_BUFFER	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 16),
	//Invalid site lang code buffer
	ERR_DXI_INVALID_SITE_LANG_CODE_BUF	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 17),
	//Invalid site location buffer
//	ERR_DXI_INVALID_SITE_LOCATION_BUF	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 18),
	//Invalid site descrip buffer
//	ERR_DXI_INVALID_SITE_DESCRIP_BUF	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 19),
		
	//Invalid signal name buffer
	ERR_DXI_INVALID_SIGNAL_NAME_BUF		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 20),
	//Invalid signal name type
	ERR_DXI_INVALID_SIGNAL_MODIFY_TYPE	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 21),
								
	//Invalid equip name buffer
	ERR_DXI_INVALID_EQUIP_NAME_BUF		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 22),
	//Invalid equip name type
	ERR_DXI_INVALID_EQUIP_MODIFY_TYPE	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 23),
									
	//Invalid site name buffer
	ERR_DXI_INVALID_SITE_NAME_BUF		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 24),
	//Invalid site name type
	ERR_DXI_INVALID_SITE_MODIFY_TYPE	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 25),
									
	//Infalid signal type
	ERR_DXI_INVALID_SIG_TYPE			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 26),
	//Infalid signal ID
	ERR_DXI_INVALID_SIG_ID				= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 27),
	//Not find expected signal
	ERR_DXI_NOT_FIND_SIGNAL				= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 28),

	//too long length
	ERR_DXI_TOO_LONG_LENGTH				= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 29),

	//Invalid site location buffer
	ERR_DXI_INVALID_SITE_LOCATION_BUF	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 30),
	//Invalid site location type
	ERR_DXI_INVALID_SITE_LOCATION_TYPE	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 31),

	//Invalid site description buffer
	ERR_DXI_INVALID_SITE_DESCRIP_BUF	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 32),
	//Invalid site description type
	ERR_DXI_INVALID_SITE_DESCRIP_TYPE	= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 33),

	ERR_DXI_INVALID_STD_EQUIP_ID		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 34),

	ERR_DXI_INVALID_MODIFY_NAME_BUF		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 35),

	ERR_DXI_MUTEX_WAIT_TIMEOUT			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 36),

	ERR_DXI_LOAD_DEFAULT_CONFIG			= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 37),

	ERR_DXI_GET_ACU_PRODUCT_INFO		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 38),

	ERR_DXI_HARDWARE_SWITCH_STATUS		= MK_ERR_CODE(MOD_DXI, MOD_DXI_DATA, 39),

	//for Product Info support
	ERR_DXI_INVALID_DEVICE_ID			= MK_ERR_CODE(MOD_DXI, MOD_DXI_TRAP, 40),


	//Error code for TRAP handle
	ERR_DXI_CALLBACK_ALEADY_EXITS		= MK_ERR_CODE(MOD_DXI, MOD_DXI_TRAP, 65),
	ERR_DXI_TOO_MANY_CALLBACK			= MK_ERR_CODE(MOD_DXI, MOD_DXI_TRAP, 66),
	ERR_DXI_CALLBACK_NOT_FOUND			= MK_ERR_CODE(MOD_DXI, MOD_DXI_TRAP, 67),
	ERR_DXI_INVAILID_CALLBACK			= MK_ERR_CODE(MOD_DXI, MOD_DXI_TRAP, 68),
};

/* error codes for Security management module	*/
/* minor for SEC module	*/
enum MOD_SEC_MINOR_MODULE_ENUM
{
	MOD_SEC_USER			= 0,		/* for user management*/
};

enum ERR_CODE_SEC_ENUM
{
	/* general errors */
	//Success
	ERR_SEC_OK						= ERR_OK,
	//User existed, cann't add the same user
	ERR_SEC_USER_ALREADY_EXISTED	= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 1),

	ERR_SEC_INVALID_USER_INFO		= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 2),
	ERR_SEC_USER_NOT_EXISTED		= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 3),
	ERR_SEC_PASSWORD_ERROR			= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 4),
	
	//The admin user cann't be deleted
	ERR_SEC_CANNOT_DELETE_ADMIN		= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 5),
	
	//Too many user, cann't add any more
	ERR_SEC_TOO_MANY_USERS			= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 6),
	
	//The admin level cann't be deleted
	ERR_SEC_CANNOT_MODIFY_ADMIN_LEVEL	= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 7),

	ERR_INVALID_USER_LEVEL			= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 8),

	ERR_USR_MUTEX_WAIT_TIMEOUT		= MK_ERR_CODE(MOD_SEC, MOD_SEC_USER, 9),

};

/* error codes for LCD service module	*/
/* minor for LCD module	*/
enum MOD_LCD_MINOR_MODULE_ENUM
{
	MOD_LCD_SERV			= 0,		/* for LCD service*/
};

enum ERR_CODE_LCD_ENUM
{
	/* general errors */
	//Success
	ERR_LCD_OK						= ERR_OK,

	ERR_LCD_NO_MEMORY				= ERR_NO_MEMORY,

	ERR_LCD_LANG_TYPE_NOT_EXIST		= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 1),

	ERR_LCD_OPEN_FONT_FILE_FAILURE	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 2),

	ERR_LCD_READ_FONT_FILE_ERROR	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 3),

	ERR_LCD_FONT_LIB_NOT_EXIST		= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 4),

	ERR_LCD_LIB_NOT_INIT			= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 5),

	ERR_LCD_EXCEED_RIGHT_BORDER		= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 6),

	ERR_LCD_OPEN_LCD_DRIVER_FAILURE	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 7),

	ERR_LCD_DRIVER_NOT_OPEN			= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 8),

	ERR_LCD_OPEN_KEY_DRIVER_FAILURE	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 9),


	ERR_LCD_TIMER_SET_FAILURE		= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 10),

	ERR_LCD_FAILURE					= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 11),

	ERR_LCD_DXI_GET_DATA_FAILURE	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 12),

	ERR_LCD_QUEUE_CREATE_FAILURE	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 13),

	ERR_LCD_ADD_ACTIVE_ALARM_FAILURE	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 14),

	ERR_LCD_ACTIVE_ALARM_NOT_FOUND	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 15),

	ERR_LCD_OPEN_LED_DRIVER_FAILURE	= MK_ERR_CODE(MOD_LCD, MOD_LCD_SERV, 16),

};

	
/* error codes for equipment monitoring module	*/
enum MOD_EQUIPMENT_MONITORING_MODULE_ENUM
{
	MOD_EQP_GENERAL			= 0,
	MOD_EQP_MAIN			= 1,/* for the main of equipment monitoring */
	MOD_EQP_INIT			= 2,/* for the init mod of equipment monitoring */
	MOD_EQP_SAMPLING		= 3,/* data sampling		*/
	MOD_EQP_PROCESSING		= 4,/* equipmeng data processing module		*/
	MOD_EQP_CTRL			= 5,/* equipment ctrl command				*/
};

enum ERR_CODE_EQUIPMENT_MONITORING_ENUM
{
	/* general errors */
	//Success
	ERR_EQP_OK					= ERR_OK,
	ERR_EQP_NO_MEMORY			= ERR_NO_MEMORY,
	ERR_EQP_INVALID_ARGS		= ERR_INVALID_ARGS,//MUST be ERR_INVALID_ARGS, do NOT change!!
	ERR_EQP_TIMEOUT				= ERR_TIMEOUT,
	ERR_EQP_COMM_FAILURE		= MK_ERR_CODE(MOD_EQP, MOD_EQP_CTRL, 1),
	ERR_EQP_COMM_BUSY			= MK_ERR_CODE(MOD_EQP, MOD_EQP_CTRL, 2),
	ERR_EQP_CTRL_SUPPRESSED		= MK_ERR_CODE(MOD_EQP, MOD_EQP_CTRL, 3),//ctrl is suppressed by othe signal.
	ERR_EQP_CTRL_DISABLED		= MK_ERR_CODE(MOD_EQP, MOD_EQP_CTRL, 4),//ctrl is not allowed for hardware swicth.
	ERR_EQP_CTRL_CANCELED		= MK_ERR_CODE(MOD_EQP, MOD_EQP_CTRL, 5),//ctrl is canceled for timeout.
};

/* err code for PLC module */
/* minor modules for xxx	*/
enum MOD_PLC_MINOR_MODULE_ENUM
{
	MOD_PLC_GENERAL			= 0,		/* General						*/	
	MOD_PLC_CTL_CMD			= 1,		/* Read Command Field Error		*/
	MOD_PLC_OPERATE_FUNC	= 2,		/* Operate logic function error */
	
};

/* err code for PLC module */
enum ERR_CODE_PLC_ENUM
{
	ERR_PLC_OK				= ERR_OK,
	ERR_PLC_CFG_NOT_EXIST	= 1,
	ERR_PLC_PERIOD			= 2,		/* Read Cal Period Error		*/
	ERR_PLC_INVALID_SIG_CFG = 3,
	ERR_PLC_FAIL_INIT		= 4,
	ERR_PLC_CAL_LOGIC		= 5,
	ERR_PLC_CMD_FUNC		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 1),
	ERR_PLC_CMD_SIG_I		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 2),
	ERR_PLC_CMD_SIG_II		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 3),
	ERR_PLC_CMD_OUTPUT		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 4),
	ERR_PLC_CMD_PARA_I		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 5),
	ERR_PLC_CMD_PARA_II		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 6),
	ERR_PLC_CMD_DELAY		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 7),
	ERR_PLC_NO_MEMORY		= MK_ERR_CODE(MOD_PLC, MOD_PLC_CTL_CMD, 8),

	ERR_PLC_OPERATE_SET		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 1),
	ERR_PLC_OPERATE_AND		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 2),
	ERR_PLC_OPERATE_OR		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 3),
	ERR_PLC_OPERATE_NOT		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 4),
	ERR_PLC_OPERATE_XOR		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 5),
	ERR_PLC_OPERATE_GT		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 6),
	ERR_PLC_OPERATE_LT		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 7),
	ERR_PLC_OPERATE_DS		= MK_ERR_CODE(MOD_PLC, MOD_PLC_OPERATE_FUNC, 8),

};

/* err code for Data Management module */
/* minor modules for xxx	*/
enum MOD_DAT_MINOR_MODULE_ENUM
{
	MOD_DAT_INIT			= 0,		/* General						*/	
	MOD_DAT_WRIT_REC		= 1,		/* Read Command Field Error		*/
	MOD_DAT_FIND_REC		= 2,		/* Read Command Field Error		*/
	MOD_DAT_FLASH			= 3,		/*Flash operate Error			*/

};

/* err code for Data management module */
enum ERR_CODE_DAT_ENUM
{
	ERR_DAT_OK					= ERR_OK,
	ERR_DAT_INIT_FAILED			= MK_ERR_CODE(MOD_DAT, MOD_DAT_INIT, 8),

	ERR_DAT_CANT_WRITE_FLASH	= MK_ERR_CODE(MOD_DAT, MOD_DAT_FLASH, 1),
	ERR_DAT_CANT_ERASE_FLASH	= MK_ERR_CODE(MOD_DAT, MOD_DAT_FLASH, 2),
};

/* err code for Debug Service module */
/* minor modules for xxx	*/
enum MOD_DBS_MINOR_MODULE_ENUM
{
	MOD_DBS_INIT			= 0,		/* General						*/	
	MOD_DBS_INTER			= 1,		/* Debug service interface		*/
	MOD_DBS_PROG			= 2,		/* Debug service interface		*/
	MOD_DBS_SEND_DATA		= 3,		/* Send data					*/
	MOD_DBS_RECEIV_DATA		= 4,		/* Receive data					*/
	MOD_DBS_CFG				= 5,        /* Read config file				*/

};

/* err code for Data management module */
enum ERR_CODE_DBS_ENUM
{
	ERR_DBS_OK				= ERR_OK,
	ERR_DBS_FAIL			= MK_ERR_CODE(MOD_DBS, MOD_DBS_INIT, 0),
	ERR_INIT_NO_MEMORY		= MK_ERR_CODE(MOD_DBS, MOD_DBS_INIT, 1),
	ERR_INIT_PORT_FAIL		= MK_ERR_CODE(MOD_DBS, MOD_DBS_INIT, 2),

	ERR_DBS_INIT_PRO,
	ERR_DSI_FAIL_INIT_PORT	= MK_ERR_CODE(MOD_DBS, MOD_DBS_INTER, 1),
	ERR_DSP_FAIL_INIT_PORT	= MK_ERR_CODE(MOD_DBS, MOD_DBS_PROG, 1),

	ERR_DBS_CFG_OPEN_FAIL	= MK_ERR_CODE(MOD_DBS, MOD_DBS_CFG, 1),
	ERR_DBS_CFG_READ_FAIL	= MK_ERR_CODE(MOD_DBS, MOD_DBS_CFG, 2),

};
/*err code for Web communicate module*/
enum ERR_CODE_WEB_ENUM
{
	ERR_WEB_OK							= ERR_OK,
	ERR_WEB_NO_MEMORY					= 3,
	ERR_COMM_FALSE_QUERY_TIMES			= 12,
	ERR_WEB_COMM_GET_RESULT_FAIL		= 13,
};

/*err code for Web CGI process*/
enum ERR_CODE_WEB_FILE_MANAGE
{
	ERR_FILE_UNKNOWN_ERROR				= 0,	
	ERR_FILE_OK							= 1,
	ERR_FILE_FAIL_CLOSE_ACU				= 2,
	ERR_FILE_NO_AUTHORITY				= 3,
	ERR_FILE_FAIL_COMM					= 4,
	ERR_FILE_NO_SPACE					= MK_ERR_CODE(MOD_DBS, MOD_DBS_CFG, 1),
};

/* error codes for SNMP service module	*/
/* minor for SNMP module	*/
enum MOD_SNP_MINOR_MODULE_ENUM
{
	MOD_SNP_SERV			= 0,		/* for SNMP service*/
};

enum ERR_CODE_SNP_ENUM
{
	/* general errors */
	//Success
	ERR_SNP_OK						= ERR_OK,

	ERR_SNP_NO_MEMORY				= ERR_NO_MEMORY,

	ERR_SNP_READ_CFG				= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 1),

	ERR_SNP_INIT_HANDLE				= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 2),

	ERR_NMS_MUTEX_TIMEOUT			= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 3),

	ERR_NMS_USER_ALREADY_EXISTED    = MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 4),

	ERR_NMS_TOO_MANY_USERS			= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 5),

	ERR_SNP_USER_NOT_EXISTED		= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 6),

	ERR_MIB_NODE_NOT_EXISTED		= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 7),

	ERR_SNP_DATA_GET_FAILURE		= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 8),

	ERR_SNP_THREAD_NEED_QUIT		= MK_ERR_CODE(MOD_SNP, MOD_SNP_SERV, 9),
};


/* error codes for Running Log module	*/
/* minor for Running Log module	*/
enum MOD_LOG_MINOR_MODULE_ENUM
{
	MOD_LOG_OK			= 0,		/* for SNMP service*/
};

enum ERR_CODE_LOG_ENUM
{
	/* general errors */
	//Success
	ERR_LOG_OK						= ERR_OK,
	ERR_LOG_WRI_EMPTY				= 1,
	ERR_LOG_WRI_WASTE				= 2,
	ERR_LOG_NO_MEMORY				= 3,
	ERR_LOG_CANT_OPEN_FLASH			= 4,
};
/* error codes for others module please come here */


#ifdef __cplusplus
}
#endif

#endif /*__ERR_CODE_H__*/

