#pragma once
#define Synthesize(ValueType,ValueName,FuncName) \
protected: ValueType ValueName;\
public: inline ValueType get##FuncName(void) const{return ValueName;}\
public: inline void set##FuncName(ValueType value){ValueName = value;}

#define SynthesizePublic(ValueType,ValueName,FuncName) \
public: ValueType ValueName;\
public: inline ValueType get##FuncName(void) const{return ValueName;}\
public: inline void set##FuncName(ValueType value){ValueName = value;}