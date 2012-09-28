//
// Generated file, do not edit! Created by opp_msgc 4.2 from node/SourceRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "SourceRoutingPacket_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(SourceRoutingPacket);

SourceRoutingPacket::SourceRoutingPacket(const char *name, int kind) : cPacket(name,kind)
{
    this->srcAddr_var = 0;
    destAddr_arraysize = 0;
    this->destAddr_var = 0;
    this->hopCount_var = 0;
    recordRoute_arraysize = 0;
    this->recordRoute_var = 0;
}

SourceRoutingPacket::SourceRoutingPacket(const SourceRoutingPacket& other) : cPacket(other)
{
    destAddr_arraysize = 0;
    this->destAddr_var = 0;
    recordRoute_arraysize = 0;
    this->recordRoute_var = 0;
    copy(other);
}

SourceRoutingPacket::~SourceRoutingPacket()
{
    delete [] destAddr_var;
    delete [] recordRoute_var;
}

SourceRoutingPacket& SourceRoutingPacket::operator=(const SourceRoutingPacket& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void SourceRoutingPacket::copy(const SourceRoutingPacket& other)
{
    this->srcAddr_var = other.srcAddr_var;
    delete [] this->destAddr_var;
    this->destAddr_var = (other.destAddr_arraysize==0) ? NULL : new int[other.destAddr_arraysize];
    destAddr_arraysize = other.destAddr_arraysize;
    for (unsigned int i=0; i<destAddr_arraysize; i++)
        this->destAddr_var[i] = other.destAddr_var[i];
    this->hopCount_var = other.hopCount_var;
    delete [] this->recordRoute_var;
    this->recordRoute_var = (other.recordRoute_arraysize==0) ? NULL : new int[other.recordRoute_arraysize];
    recordRoute_arraysize = other.recordRoute_arraysize;
    for (unsigned int i=0; i<recordRoute_arraysize; i++)
        this->recordRoute_var[i] = other.recordRoute_var[i];
}

void SourceRoutingPacket::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->srcAddr_var);
    b->pack(destAddr_arraysize);
    doPacking(b,this->destAddr_var,destAddr_arraysize);
    doPacking(b,this->hopCount_var);
    b->pack(recordRoute_arraysize);
    doPacking(b,this->recordRoute_var,recordRoute_arraysize);
}

void SourceRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->srcAddr_var);
    delete [] this->destAddr_var;
    b->unpack(destAddr_arraysize);
    if (destAddr_arraysize==0) {
        this->destAddr_var = 0;
    } else {
        this->destAddr_var = new int[destAddr_arraysize];
        doUnpacking(b,this->destAddr_var,destAddr_arraysize);
    }
    doUnpacking(b,this->hopCount_var);
    delete [] this->recordRoute_var;
    b->unpack(recordRoute_arraysize);
    if (recordRoute_arraysize==0) {
        this->recordRoute_var = 0;
    } else {
        this->recordRoute_var = new int[recordRoute_arraysize];
        doUnpacking(b,this->recordRoute_var,recordRoute_arraysize);
    }
}

int SourceRoutingPacket::getSrcAddr() const
{
    return srcAddr_var;
}

void SourceRoutingPacket::setSrcAddr(int srcAddr)
{
    this->srcAddr_var = srcAddr;
}

void SourceRoutingPacket::setDestAddrArraySize(unsigned int size)
{
    int *destAddr_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = destAddr_arraysize < size ? destAddr_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        destAddr_var2[i] = this->destAddr_var[i];
    for (unsigned int i=sz; i<size; i++)
        destAddr_var2[i] = 0;
    destAddr_arraysize = size;
    delete [] this->destAddr_var;
    this->destAddr_var = destAddr_var2;
}

unsigned int SourceRoutingPacket::getDestAddrArraySize() const
{
    return destAddr_arraysize;
}

int SourceRoutingPacket::getDestAddr(unsigned int k) const
{
    if (k>=destAddr_arraysize) throw cRuntimeError("Array of size %d indexed by %d", destAddr_arraysize, k);
    return destAddr_var[k];
}

void SourceRoutingPacket::setDestAddr(unsigned int k, int destAddr)
{
    if (k>=destAddr_arraysize) throw cRuntimeError("Array of size %d indexed by %d", destAddr_arraysize, k);
    this->destAddr_var[k] = destAddr;
}

int SourceRoutingPacket::getHopCount() const
{
    return hopCount_var;
}

void SourceRoutingPacket::setHopCount(int hopCount)
{
    this->hopCount_var = hopCount;
}

void SourceRoutingPacket::setRecordRouteArraySize(unsigned int size)
{
    int *recordRoute_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = recordRoute_arraysize < size ? recordRoute_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        recordRoute_var2[i] = this->recordRoute_var[i];
    for (unsigned int i=sz; i<size; i++)
        recordRoute_var2[i] = 0;
    recordRoute_arraysize = size;
    delete [] this->recordRoute_var;
    this->recordRoute_var = recordRoute_var2;
}

unsigned int SourceRoutingPacket::getRecordRouteArraySize() const
{
    return recordRoute_arraysize;
}

int SourceRoutingPacket::getRecordRoute(unsigned int k) const
{
    if (k>=recordRoute_arraysize) throw cRuntimeError("Array of size %d indexed by %d", recordRoute_arraysize, k);
    return recordRoute_var[k];
}

void SourceRoutingPacket::setRecordRoute(unsigned int k, int recordRoute)
{
    if (k>=recordRoute_arraysize) throw cRuntimeError("Array of size %d indexed by %d", recordRoute_arraysize, k);
    this->recordRoute_var[k] = recordRoute;
}

class SourceRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    SourceRoutingPacketDescriptor();
    virtual ~SourceRoutingPacketDescriptor();

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

Register_ClassDescriptor(SourceRoutingPacketDescriptor);

SourceRoutingPacketDescriptor::SourceRoutingPacketDescriptor() : cClassDescriptor("SourceRoutingPacket", "cPacket")
{
}

SourceRoutingPacketDescriptor::~SourceRoutingPacketDescriptor()
{
}

bool SourceRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SourceRoutingPacket *>(obj)!=NULL;
}

const char *SourceRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SourceRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int SourceRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *SourceRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "hopCount",
        "recordRoute",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int SourceRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "recordRoute")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SourceRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *SourceRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SourceRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SourceRoutingPacket *pp = (SourceRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return pp->getDestAddrArraySize();
        case 3: return pp->getRecordRouteArraySize();
        default: return 0;
    }
}

std::string SourceRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SourceRoutingPacket *pp = (SourceRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrcAddr());
        case 1: return long2string(pp->getDestAddr(i));
        case 2: return long2string(pp->getHopCount());
        case 3: return long2string(pp->getRecordRoute(i));
        default: return "";
    }
}

bool SourceRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SourceRoutingPacket *pp = (SourceRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcAddr(string2long(value)); return true;
        case 1: pp->setDestAddr(i,string2long(value)); return true;
        case 2: pp->setHopCount(string2long(value)); return true;
        case 3: pp->setRecordRoute(i,string2long(value)); return true;
        default: return false;
    }
}

const char *SourceRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *SourceRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SourceRoutingPacket *pp = (SourceRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


