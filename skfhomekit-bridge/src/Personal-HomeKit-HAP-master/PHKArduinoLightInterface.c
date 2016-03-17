//
//  PHKArduinoLightInterface.c
//  Workbench
//
//  Created by Wai Man Chan on 11/3/14.
//
//

#include "PHKArduinoLightInterface.h"
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

#define SerialPortAddr "/dev/ttyUSB0"

int serialPort = -1;

void setupPort() {
    serialPort = open(SerialPortAddr, O_WRONLY|O_NOCTTY|O_NDELAY);
    printf("Serial Port: %d\n", serialPort);
    if (serialPort >= 0) {
        struct termios options;

        /*
         * Get the current options for the port...
         */

        tcgetattr(serialPort, &options);

        /*
         * Set the baud rates to 19200...
         */

        cfsetispeed(&options, B9600);
        cfsetospeed(&options, B9600);

        /*
         * Enable the receiver and set local mode...
         */

        options.c_cflag |= (CLOCAL | CREAD);

        /*
         * Set the new options for the port...
         */

        tcsetattr(serialPort, TCSANOW, &options);
    }
}

void startIdentify() {
    write(serialPort, "-1", 3);
}

void setLightStrength(int strengthLevel) {
    strengthLevel = strengthLevel < 0? 0: strengthLevel;
    strengthLevel = strengthLevel > 255? 255: strengthLevel;
    char temp[6];
    int len = snprintf(temp, 6, "+%d", strengthLevel);
    write(serialPort, temp, len);
}

void setFanSpeed(int strengthLevel) {}

void setDimmervalue(int strengthLevel,char *devId,char *channel) {

	strengthLevel = strengthLevel <= 0? 0: strengthLevel;
	strengthLevel = strengthLevel >= 13? 13: strengthLevel;

	char temp[6];
	    int len = snprintf(temp, 6, "%X", strengthLevel);
	    // write(serialPort, temp, len);
	    printf("DevId:%s \t Channel:%s \t  val:%s\n",devId,channel,temp);
	    //char dimval[200]="wget -O /dev/null \"http://192.168.2.11/cgi-bin/saya_webAPI.sh?/www/cgi-bin/scripts/atzi_usr_dimmerControl.sh+SD_D401+DM_2L";
	    char dimval[200]="wget -O /dev/null \"http://192.168.2.24/cgi-bin/saya_webAPI.sh?/www/cgi-bin/scripts/atzi_usr_dimmerControl.sh+";
	    strcat(dimval,devId);
	    strcat(dimval,"+");
	    strcat(dimval,channel);
	    strcat(dimval,temp);
	    strcat(dimval,"\"");

	   // wget -O /dev/null "http://192.168.2.42/cgi-bin/saya_webAPI.sh?/www/cgi-bin/scripts/atzi_usr_dimmerControl.sh+SD_D401+DM_2L0"
	 //printf("status change:%s\n",dimval);
	 //system(dimval);




}
















