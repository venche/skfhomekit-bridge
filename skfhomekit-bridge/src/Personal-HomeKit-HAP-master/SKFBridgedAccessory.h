#include "jsonparser/rapidjson-master/include/rapidjson/document.h"
#include "jsonparser/rapidjson-master/include/rapidjson/writer.h"
#include "jsonparser/rapidjson-master/include/rapidjson/stringbuffer.h"
#include "jsonparser/rapidjson-master/include/rapidjson/pointer.h"
#include "jsonparser/rapidjson-master/include/rapidjson/prettywriter.h"

#include <fstream>
#include <stdlib.h>
#include "Accessory.h"
//#include "PHKAccessory.h"
#include "Configuration.h"
#define Max_fsize 4000000                           //4MB


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

void  addInfoService(Accessory *accessory,char accessoryid );
void getValueFromjson(char *key,json_types*val);
char getsizeofchar(char* key);
void appendFieldandStringify(const char *json,json_types*val,string key,string value);


#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

using namespace rapidjson;
extern Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.

#endif
