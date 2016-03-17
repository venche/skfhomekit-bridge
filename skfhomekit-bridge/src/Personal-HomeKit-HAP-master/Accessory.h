#pragma once
//
#include "jsonparser/rapidjson-master/include/rapidjson/document.h"
#include "jsonparser/rapidjson-master/include/rapidjson/writer.h"
#include "jsonparser/rapidjson-master/include/rapidjson/stringbuffer.h"
#include "jsonparser/rapidjson-master/include/rapidjson/pointer.h"
#include "jsonparser/rapidjson-master/include/rapidjson/prettywriter.h"
#include <sstream>
#include "PHKAccessory.h"
#include <string.h>
#include <stdio.h>

//  Workbench
//
//  Created by Wai Man Chan on 9/27/14.
//
//

void initAccessorySet();
void *updateLightstatusAsync(void *value);
//void lightIdentify(bool oldValue, bool newValue);

void parseSKF_homekit_json();
void initAccessorySet_json();

void changeDimmer_1_Intensity(int oldValue, int newValue,string skf_api_object);

void changeDimmer_1_Power(bool oldValue, bool newValue,string skf_api_object);
void changeDimmer_2_Power(float oldValue, float newValue,string skf_api_object);
void handle_typebool_request(bool oldValue, bool newValue,string skf_api_object);
void handle_typeint_request(int oldValue, int newValue,string skf_api_object);






