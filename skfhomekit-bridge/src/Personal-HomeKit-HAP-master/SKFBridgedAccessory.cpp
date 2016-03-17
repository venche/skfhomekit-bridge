#include "SKFBridgedAccessory.h"

//#include "PHKAccessory.h"
Document document;  //handling globally
AccessorySet *accSet1;

void parseSKF_homekit_json() {
	unsigned long fsize;
    FILE *inputFd;
	char *inputFile;

	using namespace rapidjson;
	if ( (inputFd=fopen(SKF_homekit_json, "r+"))  ==NULL) { printf("Not a valid  i/p file\n"); }

	fseek(inputFd, 0, SEEK_END);
	if( (fsize = ftell(inputFd)) > Max_fsize ) { printf("File size is to big to parse:%ld\n",fsize); }
	fseek(inputFd, 0, SEEK_SET);

	if( (inputFile =(char *) malloc(fsize + 1)) == NULL  )  exit (EXIT_FAILURE);
		fread(inputFile, fsize, 1,inputFd);
		fseek(inputFd, 0, SEEK_SET);
	    inputFile[fsize] = 0;

	if (document.Parse(inputFile).HasParseError()) {   //Use normal parsing only for avoiding extra memory foot print
	    printf("json is not parsed correctly!");exit (EXIT_FAILURE);
	   }
	   //printf("SKF_homekit_json\t:%s\n",inputFile);
}

void initAccessorySet_json()
{
  printf("Initializing...\n");
  json_types tmpval;
  char Xpath[512];                           //makesure path shouldnot collapse

  accSet1 = &AccessorySet::getInstance();
  //Accessory *accessory = new Accessory();
  Service *service=NULL;
  char acc='0',ser='0',cha='0',nofelements='0',nofaccessorys,stepsize[6];
  string servicekey="/Accessories";
  strcpy(Xpath,servicekey.c_str());
  nofaccessorys=getsizeofchar(Xpath);                //getting nof accessorys

  for(;acc<nofaccessorys;acc++)  {
	    printf("+start :%c",acc);
        Accessory *accessory = new Accessory();
        addInfoService(accessory,(char)acc);
        accSet1->addAccessory(accessory);

        //add serviceType
        servicekey="/Accessories/";
        servicekey.append(1,(char)acc).append("/InfoService/service_type");
        strcpy(Xpath,servicekey.c_str());
        getValueFromjson(Xpath,&tmpval);
        if(tmpval.tag== tmpval.EMP_INT){
        service = new Service(tmpval.types.i);
        accessory->addService(service);
        }

        servicekey="/Accessories/";
        servicekey.append(1,(char)acc).append("/Services/0/Characteristics");strcpy(Xpath,servicekey.c_str());

        nofelements=getsizeofchar(Xpath);
        char type[10]={0};
        unsigned int charctertype=0;int permissions[3]={0};  //1--read,2--write,3--notify
        unsigned  int min,max,step=0;
        unit unit_display=unit_none;

        for(;cha<nofelements;cha++)
        {
          //add characterstics
          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/type");
          strcpy(Xpath,servicekey.c_str());

          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)  strcpy(type,"int" );
          else if (tmpval.tag== tmpval.EMP_STRING)  strcpy(type,"string" );
          else if (tmpval.tag== tmpval.EMP_BOOL)    strcpy(type,"bool" );
          else if (tmpval.tag== tmpval.EMP_DOUBLE)  strcpy(type,"float" );

          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/charType");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)  charctertype=tmpval.types.i;

          //permissions
          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/permission/0");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)  permissions[0]=tmpval.types.i;

          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/permission/1");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)  permissions[1]=tmpval.types.i;

          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/permission/2");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)  permissions[2]=tmpval.types.i;

          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/minVal");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)  min=tmpval.types.i;
          if(tmpval.tag== tmpval.EMP_DOUBLE)  min=tmpval.types.d;

          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/maxVal");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)  max=tmpval.types.i;
          if(tmpval.tag== tmpval.EMP_DOUBLE)  max=tmpval.types.d;

          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/steps");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_INT)   { step=tmpval.types.i;step=(int) max/step; }
          if(tmpval.tag== tmpval.EMP_DOUBLE)  step=tmpval.types.d;

          servicekey="/Accessories/";
          servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/unit");
          strcpy(Xpath,servicekey.c_str());
          getValueFromjson(Xpath,&tmpval);
          if(tmpval.tag== tmpval.EMP_STRING) {
    	     if(strcmp(tmpval.types.string,"unitPercentage") == 0) unit_display=unit_percentage;
    	     if(strcmp(tmpval.types.string,"unitNone") == 0) unit_display=unit_none;
    	     if(strcmp(tmpval.types.string,"unitCelsius") == 0) unit_display=unit_celsius;
             if(strcmp(tmpval.types.string,"unitArcDegree") == 0) unit_display=unit_arcDegree;
           }

          if(strcmp(type,"string") == 0) {
             stringCharacteristics *charcterstic = new stringCharacteristics(charctertype, permissions[0]|permissions[1]|permissions[2], 0);
             servicekey="/Accessories/";
             servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/initvalue");
             strcpy(Xpath,servicekey.c_str());
             getValueFromjson(Xpath,&tmpval);
             if(tmpval.tag== tmpval.EMP_STRING)  charcterstic->setValue(tmpval.types.string);
             accessory->addCharacteristics(service,charcterstic);

          }

         if(strcmp(type,"int") == 0) {
    	     intCharacteristics *charcterstic = new intCharacteristics(charctertype, permissions[0]|permissions[1]|permissions[2],min,max,step,unit_display);
    	     snprintf(stepsize,6,"%X",step );
    	     //servicekey="/Accessories/";
    	     //servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/initvalue");
    	     strcpy(Xpath,servicekey.c_str());
    	     charcterstic->setValue(stepsize);

             servicekey="/Accessories/";
             servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/Valchangecallback");
             strcpy(Xpath,servicekey.c_str());
             getValueFromjson(Xpath,&tmpval);
             if(tmpval.tag != tmpval.EMP_STRING) { printf("Found null at %s\n",Xpath);exit (EXIT_FAILURE); }

             appendFieldandStringify(tmpval.types.string,&tmpval,"/steps",stepsize) ;
             if(tmpval.tag != tmpval.EMP_STRING) { printf("Found null at %s\n",Xpath);exit (EXIT_FAILURE); }
             charcterstic->jsonobject=tmpval.types.string;
             charcterstic->valueChangeFunctionCall = &handle_typeint_request;
             accessory->addCharacteristics(service,charcterstic);
          }

         if(strcmp(type,"bool") == 0) {
  	         boolCharacteristics *charcterstic = new boolCharacteristics(charctertype, permissions[0]|permissions[1]|permissions[2]);
  	         servicekey="/Accessories/";
  	         servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/initvalue");
  	         strcpy(Xpath,servicekey.c_str());
             getValueFromjson(Xpath,&tmpval);
             if(tmpval.tag != tmpval.EMP_STRING) { printf("Found null at %s\n",Xpath);exit (EXIT_FAILURE); }
             charcterstic->setValue(tmpval.types.string);    //check it

             servicekey="/Accessories/";
             servicekey.append(1,(char)acc).append("/Services/0/Characteristics/").append(1,cha).append("/Valchangecallback");
             strcpy(Xpath,servicekey.c_str());
             getValueFromjson(Xpath,&tmpval);
             if(tmpval.tag != tmpval.EMP_STRING) { printf("Found null at %s\n",Xpath);exit (EXIT_FAILURE); }
             charcterstic->jsonobject=tmpval.types.string;
             charcterstic->valueChangeFunctionCall = &handle_typebool_request;
             accessory->addCharacteristics(service,charcterstic);
          }

        if(strcmp(type,"float") == 0) {
             //floatCharacteristics *charcterstic = new floatCharacteristics(charctertype, permissions[0]|permissions[1]|permissions[2],min, max, step, unit_display);
             //Implement float characterstics for sensors like temperature,thermostat etc
          }
       }
       cha='0';//clearing back to 0

   }
}


void  addInfoService(Accessory *accessory,char accessoryid )
{
	json_types tmpval;

	char key[10][128]={"/InfoService/AccName","/InfoService/manufacture","/InfoService/modelname","/InfoService/serialnumber","/InfoService/Accinfo_callback"};
	char val[10][128];
	char tmpkey[128];

	for(int i=0;strcmp(key[i],"") != 0;i++)
	{
		strcpy(tmpkey,"/Accessories/");strcat(tmpkey,&accessoryid);strcat(tmpkey,key[i]);

		getValueFromjson(tmpkey,&tmpval);
		if(tmpval.tag== tmpval.EMP_STRING){
		  strcpy(val[i],tmpval.types.string );
		  printf("key =%s\t val:%s\n",key[i],val[i]);
		}
		else if(tmpval.tag== tmpval.EMP_INT){
			printf("key =%s\t val:%d\n",key[i],tmpval.types.i);
		}
		else if(tmpval.tag== tmpval.EMP_FLOAT)
		    printf("key =%s\t val:%f\n",key[i],tmpval.types.d);
        //memset(&tmpval,0,sizeof(myvalues)  );
	}
	addInfoServiceToAccessory(accessory,val[0], val[1], val[2], val[3], NULL);
}

void getValueFromjson(char *key,json_types*val)
 {
	        char *Xpath=key;
	        Value *value=NULL;

	        value=Pointer(Xpath).Get(document); //got value now check for types
            if(value == NULL)        { printf("Invalid Xpath in json parse:%s\n",key);exit (EXIT_FAILURE); }

            if( value->IsString() )  {
              strcpy(val->types.string,value->GetString());val->tag=val->EMP_STRING;
             }
            else if(value->IsInt())  {
            	val->types.i=value->GetInt();val->tag=val->EMP_INT;
             }
            else if(value->IsBool()) {
            	val->types.i=value->GetBool();val->tag=val->EMP_BOOL;
             }
            else if(value->IsDouble()) {
            	val->types.d=value->GetBool();val->tag=val->EMP_DOUBLE;
             }
            else if(value->IsNull())   {
                val->types.d=NULL;val->tag=val->EMP_NULL;
             }
            else if(value->IsObject()) {
                StringBuffer buffer1;
                PrettyWriter<StringBuffer> writer(buffer1);
                value->Accept(writer);
                strcpy(val->types.string,buffer1.GetString());val->tag=val->EMP_STRING;
             }
            else
            {	val->tag=val->EMP_NULL;printf("Quired type not found:%s\n",key); }
 }

 char getsizeofchar(char *key)
 {
	        char *Xpath=key;
	        Value *value=NULL;
	        value=Pointer(Xpath).Get(document);
	        if (value->IsArray())
	            return value->Size()+'0';
	        else
	        	return NULL;
 }

 void appendFieldandStringify(const char *json,json_types*val,string key,string value)
  {
	      Document skfjsonobject;
	      char nstr[]="/steps";
    	  if (skfjsonobject.Parse(json).HasParseError())  {  //Use normal parsing only for avoiding extra memory foot print
    		  printf("Request not processed lack of json is not parsed correctly! or error\n");  exit (EXIT_FAILURE);
    	     }

          strcpy(nstr,key.c_str());
          SetValueByPointer(skfjsonobject,nstr,value.c_str());
		  StringBuffer buffer;
		    PrettyWriter<StringBuffer> writer(buffer);
		    skfjsonobject.Accept(writer);
		    strcpy(val->types.string,buffer.GetString());val->tag=val->EMP_STRING;
  }

