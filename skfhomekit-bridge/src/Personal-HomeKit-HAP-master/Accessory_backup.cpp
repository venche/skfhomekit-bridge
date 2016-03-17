/*
 * This accessory.cpp is configurated for light accessory
 */

#include "Accessory.h"

#include "PHKAccessory.h"

//Global Level of light strength
int lightStength = 0;
int fanSpeedVal = 0;

void lightIdentify(bool oldValue, bool newValue) {
    printf("Start Identify Light\n");
}

void changeLightPower(bool oldValue, bool newValue) {
    printf("New Light Power State\n");
}

void changeLightIntensity(int oldValue, int newValue) {
    printf("New Intensity\n");
}

void fanIdentify(bool oldValue, bool newValue) {
    printf("Start Identify Fan\n");
}



 void *updateLightstatusAsync(void *value)
 {
     string valu("10");
     //void updateValueFromDeviceEnd(characteristics *c, int aid, int iid, string value)
     Accessory *a = AccessorySet::getInstance().accessoryAtIndex(1);
     characteristics *c = a->characteristicsAtIndex(10);
     while (1)
     {
     usleep(10000000);//1sec
	 updateValueFromDeviceEnd(c,1,10,valu);

     }
	 return NULL;
 }


AccessorySet *accSet;

void initAccessorySet() {
    currentDeviceType = deviceType_lightBulb;

    printf("Initial Accessory\n");
    accSet = &AccessorySet::getInstance();

    //add Light
    Accessory *lightAcc = new Accessory();
    addInfoServiceToAccessory(lightAcc, "Light-1", "SILVAN", "DIMMER", "4412", &lightIdentify);
    accSet->addAccessory(lightAcc);

    Service *lightService = new Service(serviceType_lightBulb);
    lightAcc->addService(lightService);

    stringCharacteristics *lightServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
    lightServiceName->setValue("Celing-Light");
    lightAcc->addCharacteristics(lightService, lightServiceName);

    boolCharacteristics *powerState = new boolCharacteristics(charType_on, premission_read|premission_write|premission_notify);
    powerState->setValue("true");
    powerState->valueChangeFunctionCall = &changeLightPower;
    lightAcc->addCharacteristics(lightService, powerState);

    intCharacteristics *brightnessState = new intCharacteristics(charType_brightness, premission_read|premission_write|premission_notify, 0, 100, 1, unit_percentage);
    brightnessState->setValue("50");
    brightnessState->valueChangeFunctionCall = &changeLightIntensity;
    lightAcc->addCharacteristics(lightService, brightnessState);

    //Add fan-1
    Accessory *fan = new Accessory();
    addInfoServiceToAccessory(fan, "Fan-1", "SILVAN", "DIMMER", "4412", &fanIdentify);
    accSet->addAccessory(fan);

    Service *fanService = new Service(serviceType_fan);
    fan->addService(fanService);

    stringCharacteristics *fanServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
    fanServiceName->setValue("Celing-Fan");
    fan->addCharacteristics(fanService, fanServiceName);

    boolCharacteristics *fanPower = new boolCharacteristics(charType_on, premission_read|premission_write);
    fanPower->setValue("true");
    fan->addCharacteristics(fanService, fanPower);

    //Add fan-2
    Accessory *fan2 = new Accessory();
    addInfoServiceToAccessory(fan2, "Fan-2", "SILVAN", "DIMMER", "4412", &fanIdentify);
    accSet->addAccessory(fan2);

    Service *fanService2 = new Service(serviceType_fan);
    fan2->addService(fanService2);

    stringCharacteristics *fanServiceName2 = new stringCharacteristics(charType_serviceName, premission_read, 0);
    fanServiceName2->setValue("Fan");
    fan2->addCharacteristics(fanService2, fanServiceName2);

    boolCharacteristics *fanPower2 = new boolCharacteristics(charType_on, premission_read|premission_write);
    fanPower2->setValue("true");
    fan2->addCharacteristics(fanService2, fanPower2);


   //Add sensor
    Accessory *temperatureSensor = new Accessory();
    addInfoServiceToAccessory(temperatureSensor, "temperatureSensor-1", "SILVAN", "DTH11", "1234", &fanIdentify);
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
    addInfoServiceToAccessory(garagedoor, "Garagedoor", "SILVAN", "SILVAN-IOC", "6312", &fanIdentify);
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

    //window covering
	Accessory *windowCurtain = new Accessory();
	addInfoServiceToAccessory(windowCurtain, "windowCurtain", "SILVAN", "SILVANIOC", "6612", &fanIdentify);
	accSet->addAccessory(windowCurtain);

	Service *windowCurtainService = new Service(serviceType_windowCover);
	windowCurtain->addService(windowCurtainService);

	stringCharacteristics *windowCurtainServiceName = new stringCharacteristics(charType_serviceName, premission_read, 0);
	windowCurtainServiceName->setValue("WindowCurtain");
	windowCurtain->addCharacteristics(windowCurtainService, windowCurtainServiceName);
	//mandatory characterstics
	intCharacteristics *windowCurtaincurrentPosition = new intCharacteristics(charType_currentPosition, premission_read|premission_notify, 0, 100, 1, unit_percentage);
	//windowCurtaincurrentPosition->setValue("1");
	//currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
	windowCurtain->addCharacteristics(windowCurtainService, windowCurtaincurrentPosition);

	intCharacteristics *windowCurtaintargetPosition = new intCharacteristics(charType_targetPosition, premission_read|premission_notify|premission_write, 0, 100, 1, unit_percentage);
	windowCurtaintargetPosition->setValue("1");
		//currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
	windowCurtain->addCharacteristics(windowCurtainService,windowCurtaintargetPosition);

	intCharacteristics *windowPositionstate = new intCharacteristics(charType_positionState, premission_read|premission_notify, 0, 1, 1, unit_none);
	//windowCurtaincurrentPosition->setValue("1");
	//currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
    windowCurtain->addCharacteristics(windowCurtainService, windowPositionstate);

    //optional characterstic for door like open,closed
    intCharacteristics *targetwindowState = new intCharacteristics(charType_targetDoorState, premission_read|premission_write|premission_notify, 0, 1, 1, unit_percentage);
    targetwindowState->setValue("1");
    //currentdoorState->valueChangeFunctionCall = &changeLightIntensity;
    windowCurtain->addCharacteristics(windowCurtainService, targetwindowState);


};
