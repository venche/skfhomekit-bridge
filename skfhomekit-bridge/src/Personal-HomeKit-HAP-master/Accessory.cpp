/*
 * This accessory.cpp is configurated for light accessory
 */
#include "Accessory.h"
//#include "PHKAccessory.h"
//#include "SKFBridgedAccessory.h"


typedef struct json_types
{
 enum { EMP_INT, EMP_FLOAT,EMP_STRING,EMP_DOUBLE,EMP_NULL,EMP_BOOL,EMP_RETURN } tag;
 union types
 {
    int i;
    double d;
    long l;
    char string[1024];
 }types;
};

void getValueFromjson(char *key,json_types*val);

void handle_typebool_request(bool oldValue, bool newValue,string skf_api_object) {
	using namespace rapidjson;
	string Xpath="/script",cgiapi="",id="",channel="",servicekey;
	char xpath[512];
	json_types tmpval;
	//skfapicall="wget -O /dev/null \"http://192.168.2.24/cgi-bin/saya_webAPI.sh?/www/cgi-bin/scripts/";
	string skfapicall;
    printf("jsonstr:%s\n",skf_api_object.c_str());
	Document skfjsonobject;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
	if (skfjsonobject.Parse(skf_api_object.c_str()).HasParseError())    //Use normal parsing only for avoiding extra memory foot print
	    printf("Request not processed lack of json is not parsed correctly! or error");

	Value *value=NULL;

    Xpath="/script";
      	value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
       	if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
       	if( value->IsString() )
       		skfapicall.append(value->GetString());skfapicall.append(" ");    //ApI

    Xpath="/id";
        value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
        if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
        if( value->IsString() )
        skfapicall.append(value->GetString());skfapicall.append(" ");

	Xpath="/type";
	 //strcpy(xpath,Xpath.c_str());
	 //getValueFromjson(xpath,&tmpval);
	 value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
	 if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
	 if( value->IsString() != 1 )   { printf("undefined type to process %s\n",Xpath.c_str());return; }


	if(strcmp( value->GetString(),"switching") == 0  ) {
		//Xpath="/command/tg";
		Xpath="/command/on";
		if(newValue == false) Xpath="/command/off";
		    printf("xpath:%s\n",Xpath.c_str());
			value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
			if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
			if( value->IsString() )   skfapicall.append(value->GetString());
	  }
      //add handlers for other devices if needed
	printf("skfAPIcall:%s\n",skfapicall.c_str());
	system(skfapicall.c_str());

	//printf("New Intensity :skfjsonobject:%s\n",skf_api_object.c_str());setDimmervalue(newValue,"SD_D502","DM_1L");
}

void handle_typeint_request(int oldValue, int newValue,string skf_api_object) {
	int powerState = newValue == 0 ? 0:newValue;
	using namespace rapidjson;

	char xpath[512];
	json_types tmpval;
	string Xpath="/script";
	char level[6];
	string cgiapi="",id="",channel="";
	//string skfapicall="wget -O /dev/null \"http://192.168.2.24/cgi-bin/saya_webAPI.sh?/www/cgi-bin/scripts/";
	string skfapicall;
	Document skfjsonobject;  // Default template parameter uses UTF8 and MemoryPoolAllocator.

	if (skfjsonobject.Parse(skf_api_object.c_str()).HasParseError())    //Use normal parsing only for avoiding extra memory foot print
	    printf("Request not processed lack of json is not parsed correctly! or error");


	printf("jsonstr:%s\n",skf_api_object.c_str());
	Value *value=NULL;

    value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
    if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
    if( value->IsString() )
    	skfapicall.append(value->GetString());skfapicall.append(" ");
        //skfapicall.append(value->GetString());skfapicall.append("+");

    Xpath="/id";
    value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
    if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
    if( value->IsString() )
        skfapicall.append(value->GetString());skfapicall.append(" ");
    //skfapicall.append(value->GetString());skfapicall.append("+");

    Xpath="/channel";
    value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
    if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
    if( value->IsString() )
    	 channel=value->GetString();

	Xpath="/type";
	 value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
	 if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
	 if( value->IsString() != 1 )   { printf("undefined type to process %s\n",Xpath.c_str());return; }

    printf("int+1\n");
    if(strcmp( value->GetString(),"dimming") == 0  ) {

    	  int lev;
    	  Xpath="/steps";
    	   value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
    	   if(value == NULL) { printf("Invalid Xpath in json parse\n"); }

    	   if( value->IsString() )
    		   lev=atoi (value->GetString());
        	   lev= newValue/lev;

        	   if(lev > 13) return;
               snprintf(level, 6, "%d",lev );
               printf("level=%s\n",level);

               Xpath="/command/level";Xpath.append(level);
               //printf("newval:%s\n",Xpath.c_str);
               value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
               if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
               if( value->IsString() )   skfapicall.append(value->GetString());


    	  /*printf("intchar old:%d,new:%d",oldValue,newValue);
    	  Xpath="/command/down";
    	  if( newValue >  oldValue ) Xpath="/command/up";
    	  value=Pointer(Xpath.c_str()).Get(skfjsonobject); //got value now check for types
    	  if(value == NULL) { printf("Invalid Xpath in json parse\n"); }
    	  if( value->IsString() )   skfapicall.append(value->GetString());*/

      }
           //hardcoding should romove shout suppot dimmer,srm,curtain,ir
    	   //skfapicall.append("DM_");skfapicall.append(channel);skfapicall.append("L").append(level);
    	   system(skfapicall.c_str());
    	   printf("skfapicall %s\n",skfapicall.c_str());

}



 void *updateLightstatusAsync(void *value)
 {
     string valu("1");

     string valu1("100");
     int x=1;
     //void updateValueFromDeviceEnd(characteristics *c, int aid, int iid, string value)
     Accessory *a = AccessorySet::getInstance().accessoryAtIndex(1);


     characteristics *c = a->characteristicsAtIndex(9);         //light1 brightness
     characteristics *c1 = a->characteristicsAtIndex(10);         //light1 brightness
     while (1)
     {
     usleep(10000000);//20sec

     if(x == 1) {  valu="1";valu1="90.5";x=0; }
	 else
		{ valu="0";x=1;valu1="0"; }

     updateValueFromDeviceEnd(c1,1,10,valu1);
     updateValueFromDeviceEnd(c,1,9,valu);


     }
 }

void initAccessorySet() {
    currentDeviceType = deviceType_lightBulb;
    AccessorySet *accSet;

    printf("Initial Accessory\n");
    accSet = &AccessorySet::getInstance();

    //add Light
    Accessory *lightAcc = new Accessory();
    addInfoServiceToAccessory(lightAcc, "Light-1", "SILVAN", "DIMMER", "4412", NULL);
    //addInfoServiceToAccessory(lightAcc, "Light-1", "SILVAN", "DIMMER", "4412", &AcessoryIdentify);
    accSet->addAccessory(lightAcc);

    Service *lightService = new Service(serviceType_lightBulb);
    lightAcc->addService(lightService);

    stringCharacteristics *lightServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
    lightServiceName->setValue("Celing-Light");
    lightAcc->addCharacteristics(lightService, lightServiceName);

     printf("char+1\n");
   /* boolCharacteristics *powerState = new boolCharacteristics(charType_on, premission_read|premission_write|premission_notify);
    printf("char+2\n");
    powerState->setValue("true");
    printf("char+3\n");
    powerState->jsonobject="jsonstring as strinfied";
    powerState->valueChangeFunctionCall = &changeDimmer_1_Power;
    lightAcc->addCharacteristics(lightService, powerState);

    printf("int+1\n");
    intCharacteristics *brightnessState = new intCharacteristics(charType_brightness, premission_read|premission_write|premission_notify, 0, 100, 8, unit_percentage);
    brightnessState->setValue("50");
    brightnessState->jsonobject="jsonstring as strinfied";
    //brightnessState->valueChangeFunctionCall = &changeDimmer_1_Intensity;
    lightAcc->addCharacteristics(lightService, brightnessState);*/


    /*//add Light-2
    Accessory *lightAcc_2 = new Accessory();
    addInfoServiceToAccessory(lightAcc_2, "Light-2", "SILVAN", "DIMMER", "4412", &AcessoryIdentify);
    accSet->addAccessory(lightAcc_2);

    Service *lightService_2 = new Service(serviceType_lightBulb);
    lightAcc_2->addService(lightService_2);

    stringCharacteristics *lightServiceName_2 = new stringCharacteristics(charType_serviceName, premission_read, 0);
    lightServiceName_2->setValue("Celing-Light");
    lightAcc_2->addCharacteristics(lightService_2, lightServiceName_2);

    boolCharacteristics *powerState_2 = new boolCharacteristics(charType_on, premission_read|premission_write|premission_notify);
    powerState_2->setValue("true");
    powerState_2->valueChangeFunctionCall = &changeDimmer_3_Power;
    lightAcc_2->addCharacteristics(lightService_2, powerState_2);

    intCharacteristics *brightnessState_2 = new intCharacteristics(charType_brightness, premission_read|premission_write|premission_notify, 0, 100, 1, unit_percentage);
    brightnessState_2->setValue("50");
    brightnessState_2->valueChangeFunctionCall = &changeDimmer_3_Intensity;
    lightAcc_2->addCharacteristics(lightService_2, brightnessState_2);



    //Add fan-1
    Accessory *fan = new Accessory();
    addInfoServiceToAccessory(fan, "Fan-1", "SILVAN", "DIMMER", "4412", &AcessoryIdentify);
    accSet->addAccessory(fan);

    Service *fanService = new Service(serviceType_fan);
    fan->addService(fanService);

    stringCharacteristics *fanServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
    fanServiceName->setValue("Celing-Fan");
    fan->addCharacteristics(fanService, fanServiceName);

    boolCharacteristics *fanPower = new boolCharacteristics(charType_on, premission_read|premission_write);
    fanPower->setValue("true");
    fanPower->valueChangeFunctionCall = &changeDimmer_2_Power;
    fan->addCharacteristics(fanService, fanPower);

    floatCharacteristics *fanspeed = new floatCharacteristics(charType_rotationSpeed, premission_read|premission_write|premission_notify, 0, 100, 1, unit_percentage);
    //fanspeed->setValue("50");
    fanspeed->valueChangeFunctionCall = &changeDimmer_2_Intensity;
    fan->addCharacteristics(fanService, fanspeed);



    //window covering
	Accessory *windowCurtain = new Accessory();
	addInfoServiceToAccessory(windowCurtain, "windowCurtain", "SILVAN", "SILVANIOC", "6612", &AcessoryIdentify);
	accSet->addAccessory(windowCurtain);

	Service *windowCurtainService = new Service(serviceType_windowCover);
	windowCurtain->addService(windowCurtainService);

	stringCharacteristics *windowCurtainServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
	windowCurtainServiceName->setValue("WindowCurtain");
	windowCurtain->addCharacteristics(windowCurtainService, windowCurtainServiceName);

	//mandatory characterstics
	intCharacteristics *windowCurtaincurrentPosition = new intCharacteristics(charType_currentPosition, premission_read|premission_notify, 0, 100, 1, unit_percentage);
	//currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
	windowCurtain->addCharacteristics(windowCurtainService, windowCurtaincurrentPosition);

	intCharacteristics *windowCurtaintargetPosition = new intCharacteristics(charType_targetPosition, premission_read|premission_notify|premission_write, 0, 100, 1, unit_percentage);
	//windowCurtaintargetPosition->setValue("1");
	windowCurtaintargetPosition->valueChangeFunctionCall = &changeCurtain_1_State;
	windowCurtain->addCharacteristics(windowCurtainService,windowCurtaintargetPosition);

	intCharacteristics *windowPositionstate = new intCharacteristics(charType_positionState, premission_read|premission_notify, 0, 1, 1, unit_none);
	//currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
    windowCurtain->addCharacteristics(windowCurtainService, windowPositionstate);


    //optional characterstic for door like open,closed
    /*intCharacteristics *targetwindowState = new intCharacteristics(charType_targetDoorState, premission_read|premission_write|premission_notify, 0, 1, 1, unit_percentage);
    targetwindowState->setValue("1");
    //currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
    windowCurtain->addCharacteristics(windowCurtainService, targetwindowState);*/


/*   //Add sensor
    Accessory *temperatureSensor = new Accessory();
    addInfoServiceToAccessory(temperatureSensor, "temperatureSensor-1", "SILVAN", "DTH11", "1234", &AcessoryIdentify);
    accSet->addAccessory(temperatureSensor);

    Service *temperatureSensorService = new Service(serviceType_temperatureSensor);
    temperatureSensor->addService(temperatureSensorService);

    stringCharacteristics *temperatureSensorServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
    temperatureSensorServiceName->setValue("TemperatureSensor");
    temperatureSensor->addCharacteristics(temperatureSensorService, temperatureSensorServiceName);
    //Required characterstuic
    floatCharacteristics *temperatureSensorstatus = new floatCharacteristics(charType_currentTemperature, premission_read|premission_notify, 0, 100, 0.1, unit_celsius);
    temperatureSensorstatus->setValue("true");
    // brightnessState->valueChangeFunctionCall = &changeLightIntensity;
    temperatureSensor->addCharacteristics(temperatureSensorService, temperatureSensorstatus);

    //garage Door
    Accessory *garagedoor = new Accessory();
    addInfoServiceToAccessory(garagedoor, "Garagedoor", "SILVAN", "SILVAN-IOC", "6312", &AcessoryIdentify);
    accSet->addAccessory(garagedoor);

    Service *garagedoorService = new Service(serviceType_garageDoorOpener);
    garagedoor->addService(garagedoorService);

    stringCharacteristics *garagedoorServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
    garagedoorServiceName->setValue("Garagedoor");
    garagedoor->addCharacteristics(garagedoorService, garagedoorServiceName);

    //mandatory characterstics
    intCharacteristics *currentdoorState = new intCharacteristics(charType_currentDoorState, premission_read|premission_notify, 0, 4, 1, unit_percentage);
    //currentdoorState->setValue("1");
    //currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
    garagedoor->addCharacteristics(garagedoorService, currentdoorState);

    intCharacteristics *targetdoorState = new intCharacteristics(charType_targetDoorState, premission_read|premission_write|premission_notify, 0, 1, 1, unit_percentage);
    targetdoorState->setValue("1");
    //currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
    garagedoor->addCharacteristics(garagedoorService, targetdoorState);

    boolCharacteristics *obstructionDetect = new boolCharacteristics(charType_obstruction, premission_read|premission_notify);
    //obstructionDetect->setValue("true");
    garagedoor->addCharacteristics(garagedoorService,obstructionDetect);

*/



};

