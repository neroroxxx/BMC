/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Contains all the function ids for all editor communication
*/
#ifndef BMC_EDITOR_MIDI_DEF_H
#define BMC_EDITOR_MIDI_DEF_H

// if read/write flag is 0 it's checking the connection status,
// if 1, it's trying to connect
#define BMC_GLOBALF_CONNECT                  0
// ignores read/write flag
#define BMC_GLOBALF_DISCONNECT            	 1
#define BMC_GLOBALF_SETTINGS              	 2
// BMC_GLOBALF_POT_CALIBRATION doesn't use write
#define BMC_GLOBALF_POT_CALIBRATION       	 3
//#define BMC_GLOBALF_STARTUP               	 4
#define BMC_GLOBALF_STORE_ADDRESS         	 5
#define BMC_GLOBALF_BACKUP                	 6
#define BMC_GLOBALF_PARAMETER             	 7
#define BMC_GLOBALF_FORCE_DISCONNECT      	 8
#define BMC_GLOBALF_EDITOR_FETCH_COMPLETE 	 9
#define BMC_GLOBALF_SKETCH_BYTES_DATA     	 10
#define BMC_GLOBALF_TIME                  	 11
#define BMC_GLOBALF_EDITOR_FEEDBACK       	 12
#define BMC_GLOBALF_EDITOR_PERFORM_MODE   	 13
#define BMC_GLOBALF_EDITOR_GET_METRICS    	 14
#define BMC_GLOBALF_EDITOR_MESSENGER      	 15
// for BMC 2.0
#define BMC_EDITOR_FUNCTION_EVENT         	 16
#define BMC_EDITOR_FUNCTION_NAME          	 17
#define BMC_EDITOR_FUNCTION_DEVICE        	 18
#define BMC_EDITOR_FUNCTION_ERASE    	       19
#define BMC_EDITOR_FUNCTION_LINK    	       20
#define BMC_EDITOR_FUNCTION_CONNECTION_ALIVE 21

// get build info, includes things like PINS, number of buttons, leds, etc. Layer Number bytes specify the item being retrieved.
#define BMC_GLOBALF_BUILD_INFO 125
    #define BMC_GLOBALF_BUILD_INFO_FLAGS       0
    #define BMC_GLOBALF_BUILD_INFO_DEVICE_NAME 1

#define BMC_GLOBALF_UTILITY 126
    // UTILITY FUNCTIONS
    #define BMC_UTILF_STATE_BITS                 0
    #define BMC_UTILF_POT                      	 1
    #define BMC_UTILF_ENCODER                  	 2
    #define BMC_UTILF_PRESET                   	 3
    #define BMC_UTILF_CLICK_TRACK              	 4
    #define BMC_UTILF_POT_CALIBRATION          	 5
    #define BMC_UTILF_POT_CALIBRATION_STATUS   	 6
    #define BMC_UTILF_POT_CALIBRATION_ACTIVITY 	 7
    #define BMC_UTILF_POT_CALIBRATION_CANCEL   	 8
    #define BMC_UTILF_DISCONNECTED             	 9
    #define BMC_UTILF_LED_TEST                 	 10
    #define BMC_UTILF_SKETCH_BYTES             	 11
    #define BMC_UTILF_AUX_JACK                 	 12
    #define BMC_UTILF_FAS_STATE                	 13
    #define BMC_UTILF_MAGIC_ENCODER              14


// if read/write flag is 0 it's checking the connection status, if 1, it's trying to connect
#define BMCF_NOTIFY 127
    // codes for notifications
  #define BMC_NOTIFY_CONNECTION                0
  #define BMC_NOTIFY_CONNECTION_STATUS       	 1
  #define BMC_NOTIFY_DISCONNECTED            	 2
  #define BMC_NOTIFY_SUCCESS                 	 3
  #define BMC_NOTIFY_UNAVAILABLE             	 4
  #define BMC_NOTIFY_INVALID_EVENT           	 5
  #define BMC_NOTIFY_INVALID_NAME            	 6
  #define BMC_NOTIFY_INVALID_DEVICE          	 7
  #define BMC_NOTIFY_INVALID_REQUEST         	 8
  #define BMC_NOTIFY_INVALID_CHECKSUM        	 9
  #define BMC_NOTIFY_INVALID_SIZE            	 10
  #define BMC_NOTIFY_INVALID_INDEX           	 11
  #define BMC_NOTIFY_INVALID_LAYER             12
  #define BMC_NOTIFY_INVALID_PRESET          	 13
  #define BMC_NOTIFY_INVALID_POT             	 14
  #define BMC_NOTIFY_INVALID_STORE_ADDRESS   	 15
  #define BMC_NOTIFY_BACKUP_DATA_ACCEPTED    	 16
  #define BMC_NOTIFY_INVALID_SKETCH_BYTE_DATA	 17
  #define BMC_NOTIFY_REQUEST_ACCEPTED        	 18
  #define BMC_NOTIFY_INVALID_LINK           	 19

// LAYER FUNCTIONS
#define BMC_LAYERF_LAYER            0
#define BMC_LAYERF_LAYER_NAME       1
#define BMC_LAYERF_LAYER_COPY_SWAP  2
#define BMC_LAYERF_LAYER_SWAP       3



#endif
