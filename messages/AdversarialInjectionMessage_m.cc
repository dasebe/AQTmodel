//
// Generated file, do not edit! Created by opp_msgc 4.5 from messages/AdversarialInjectionMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "AdversarialInjectionMessage_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(AdversarialInjectionMessage);

AdversarialInjectionMessage::AdversarialInjectionMessage(const char *name, int kind) : ::cPacket(name,kind)
{
    path_arraysize = 0;
    this->path_var = 0;
}

AdversarialInjectionMessage::AdversarialInjectionMessage(const AdversarialInjectionMessage& other) : ::cPacket(other)
{
    path_arraysize = 0;
    this->path_var = 0;
    copy(other);
}

AdversarialInjectionMessage::~AdversarialInjectionMessage()
{
    delete [] path_var;
}

AdversarialInjectionMessage& AdversarialInjectionMessage::operator=(const AdversarialInjectionMessage& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AdversarialInjectionMessage::copy(const AdversarialInjectionMessage& other)
{
    delete [] this->path_var;
    this->path_var = (other.path_arraysize==0) ? NULL : new int[other.path_arraysize];
    path_arraysize = other.path_arraysize;
    for (unsigned int i=0; i<path_arraysize; i++)
        this->path_var[i] = other.path_var[i];
}

void AdversarialInjectionMessage::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    b->pack(path_arraysize);
    doPacking(b,this->path_var,path_arraysize);
}

void AdversarialInjectionMessage::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    delete [] this->path_var;
    b->unpack(path_arraysize);
    if (path_arraysize==0) {
        this->path_var = 0;
    } else {
        this->path_var = new int[path_arraysize];
        doUnpacking(b,this->path_var,path_arraysize);
    }
}

void AdversarialInjectionMessage::setPathArraySize(unsigned int size)
{
    int *path_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = path_arraysize < size ? path_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        path_var2[i] = this->path_var[i];
    for (unsigned int i=sz; i<size; i++)
        path_var2[i] = 0;
    path_arraysize = size;
    delete [] this->path_var;
    this->path_var = path_var2;
}

unsigned int AdversarialInjectionMessage::getPathArraySize() const
{
    return path_arraysize;
}

int AdversarialInjectionMessage::getPath(unsigned int k) const
{
    if (k>=path_arraysize) throw cRuntimeError("Array of size %d indexed by %d", path_arraysize, k);
    return path_var[k];
}

void AdversarialInjectionMessage::setPath(unsigned int k, int path)
{
    if (k>=path_arraysize) throw cRuntimeError("Array of size %d indexed by %d", path_arraysize, k);
    this->path_var[k] = path;
}

class AdversarialInjectionMessageDescriptor : public cClassDescriptor
{
  public:
    AdversarialInjectionMessageDescriptor();
    virtual ~AdversarialInjectionMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(AdversarialInjectionMessageDescriptor);

AdversarialInjectionMessageDescriptor::AdversarialInjectionMessageDescriptor() : cClassDescriptor("AdversarialInjectionMessage", "cPacket")
{
}

AdversarialInjectionMessageDescriptor::~AdversarialInjectionMessageDescriptor()
{
}

bool AdversarialInjectionMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AdversarialInjectionMessage *>(obj)!=NULL;
}

const char *AdversarialInjectionMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AdversarialInjectionMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int AdversarialInjectionMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *AdversarialInjectionMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "path",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int AdversarialInjectionMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "path")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AdversarialInjectionMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *AdversarialInjectionMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int AdversarialInjectionMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AdversarialInjectionMessage *pp = (AdversarialInjectionMessage *)object; (void)pp;
    switch (field) {
        case 0: return pp->getPathArraySize();
        default: return 0;
    }
}

std::string AdversarialInjectionMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AdversarialInjectionMessage *pp = (AdversarialInjectionMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPath(i));
        default: return "";
    }
}

bool AdversarialInjectionMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AdversarialInjectionMessage *pp = (AdversarialInjectionMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setPath(i,string2long(value)); return true;
        default: return false;
    }
}

const char *AdversarialInjectionMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *AdversarialInjectionMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AdversarialInjectionMessage *pp = (AdversarialInjectionMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


