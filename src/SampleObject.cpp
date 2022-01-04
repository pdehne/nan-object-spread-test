#include "SampleObject.h"

class SampleObject::SampleObjectNative
{
public:
    SampleObjectNative()
    : m_number(0.0)
    {
    }

    void setString(const std::string& value) {
        m_string = value;
    }

    const std::string& getString() {
        return m_string;
    }

    void setNumber(double value) {
        m_number = value;
    }

    double getNumber() {
        return m_number;
    }

private:
    std::string m_string;
    double m_number;
};

Nan::Persistent<v8::Function> SampleObject::constructor;

NAN_MODULE_INIT(SampleObject::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(SampleObject::New);
    tpl->SetClassName(Nan::New("SampleObject").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New("stringProp").ToLocalChecked(), SampleObject::Getters, SampleObject::Setters);
    Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New("numberProp").ToLocalChecked(), SampleObject::Getters, SampleObject::Setters);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    
    Nan::Set(target, Nan::New("SampleObject").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SampleObject::New)
{
    if (info.IsConstructCall())
    {
        auto obj = new SampleObject();
        obj->Wrap(info.This());

        info.GetReturnValue().Set(info.This());
    }
    else
    {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        info.GetReturnValue().Set(Nan::NewInstance(cons).ToLocalChecked());
    }
}

NAN_GETTER(SampleObject::Getters)
{
    auto self = Nan::ObjectWrap::Unwrap<SampleObject>(info.Holder());
    
    std::string propertyName = *Nan::Utf8String(property);

    if(propertyName == "stringProp")
    {
        std::string nativeValue = self->m_native->getString();
        v8::Local<v8::Value> nanValue = Nan::New(nativeValue).ToLocalChecked();
        info.GetReturnValue().Set(nanValue);
    }
    else if(propertyName == "numberProp")
        info.GetReturnValue().Set(Nan::New(self->m_native->getNumber()));
    else
        info.GetReturnValue().Set(Nan::Undefined());
}

NAN_SETTER(SampleObject::Setters)
{
    auto self = Nan::ObjectWrap::Unwrap<SampleObject>(info.Holder());

    std::string propertyName = *Nan::Utf8String(property);

    if(propertyName == "stringProp")
    {
        v8::Local<v8::String> v8String = Nan::To<v8::String>(value).ToLocalChecked();
        Nan::Utf8String utf8String(v8String);
        std::string nativeString(*utf8String, utf8String.length());
        self->m_native->setString(nativeString);
    }
    else if(propertyName == "numberProp")
    {
        self->m_native->setNumber(Nan::To<double>(value).FromJust());
    }
}

SampleObject::SampleObject()
{
    m_native.reset(new SampleObjectNative());
}

SampleObject::~SampleObject()
{
}
