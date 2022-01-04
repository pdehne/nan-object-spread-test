#ifndef SAMPLEOBJECT_H
#define SAMPLEOBJECT_H

#include <nan.h>

class SampleObject
: public Nan::ObjectWrap
{
public:
    static NAN_MODULE_INIT(Init);

private:
    static NAN_METHOD(New);
    static NAN_GETTER(Getters);
    static NAN_SETTER(Setters);

    static Nan::Persistent<v8::Function> constructor;

    explicit SampleObject();
    ~SampleObject();

    class SampleObjectNative;
    friend class SampleObjectNative;
    std::unique_ptr<SampleObjectNative> m_native;
};

#endif
