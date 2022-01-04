#include <nan.h>
#include "SampleObject.h"

NAN_MODULE_INIT(Init)
{
    SampleObject::Init(target);
}

NAN_MODULE_WORKER_ENABLED(nanobjectspreadtest, Init)
