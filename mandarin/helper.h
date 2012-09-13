#ifndef HELPER_HEADER_GUARD
#define HELPER_HEADER_GUARD
#include <memory>
#include <iostream>
#include <cstring>
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef const char cchar;
typedef const unsigned char cuchar;
typedef const int cint;
typedef const uint cuint;
typedef const double cdouble;
typedef const float cfloat;

using namespace std;
template<class T>
struct CRMaybe final
{
	const bool hasValue;
	const T  value;
	
	
	CRMaybe(const T& val):value(val),hasValue(true){}
	CRMaybe():value(T()),hasValue(false){}
	CRMaybe(nullptr_t np):value(T()),hasValue(np){}	
	operator bool(){return hasValue;}
	operator const T(){return value;}
	
	CRMaybe& operator=(const CRMaybe& other)
	{
		if(this != &other)
		{
			this->~CRMaybe();
			new(this)CRMaybe(other);
		}
		return *this;
	}
};

template <class T>
CRMaybe<T> crmaybe(const T& val){return CRMaybe<T>(val);}

// struct StrSlice	
// {
// 	cchar*const head;
// 	const size_t length;
// 	StrSlice(cchar* hd,size_t len):head(hd),length(len){}
// 	StrSlice(cchar* hd):StrSlice(hd,strlen(hd)){}
// 	StrSlice(string s,cchar* hd):head(hd),length(s.size()){}
// 	StrSlice(string s):StrSlice(s,&s[0]){}
// 	bool operator<(const StrSlice rhs) const 
// 	{return length < rhs.length || strncmp(head,rhs.head,length)<0;}
// };
// 
// ostream& operator<<(ostream& os, StrSlice ss)
// {
// 	for(int i = 0;i != ss.length;++i)os<<ss.head[i];
// 	return os;
// }
#endif // HELPER_HEADER_GUARD