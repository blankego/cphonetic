#ifndef HELPER_HEADER_GUARD
#define HELPER_HEADER_GUARD
#include <memory>
#include <iostream>
#include <cstring>
#include <map>
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef const char cchar;
typedef const unsigned char cuchar;
typedef const int cint;
typedef const uint cuint;
typedef const double cdouble;
typedef const float cfloat;

#define PAUTO(a,b,pr) ;const decltype((pr).first)& a;const decltype((pr).second)& b;\
	{const auto& tmp=(pr);a=tmp.first;b=tmp.second;}
#define PASSIGN(a,b,pr) {const auto& tmp=(pr);a=tmp.first;b=tmp.second;}
#define TUP(...) make_tuple(__VA_ARGS__)
#define PR(a,b) make_pair((a),(b))
#define findOr(a,b) make_pair((a),(b))
#define T3ASSIGN(a,b,c,tup) ;{const auto& tmp=(tup);a=get<0>(tup);b=get<1>(tup);c=get<2>(tup);}
#define T3AUTO(a,b,c,tup);const auto& a = get<0>
using namespace std;
template<class T>
struct CRMaybe final
{
	const bool hasValue;
	const T  value;
	
	
	CRMaybe(const T& val):value(val),hasValue(true){}
	CRMaybe():value(T()),hasValue(false){}
	CRMaybe(nullptr_t np):value(T()),hasValue(np){}	
	operator bool()const{return hasValue;}
	operator const T&()const{return value;}
	
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
template<int SIZE,class CharT=char,CharT DELIM = '\n'>
class linebuf
{
	CharT buf[SIZE];
public:
	linebuf(){buf[0]=0;}
	operator CharT*(){return &buf[0];}
	operator const CharT*()const {return &buf[0];}
	CharT* operator &(){return &buf[0];}
	operator bool(){return buf[0] != 0;}
	linebuf& operator<<(basic_istream<CharT>& ins)
	{
		buf[0]=0;ins.getline(buf,ins.widen(DELIM));return *this;		
	}
	
};


template<class K,class V>
inline V operator^(const map<K,V>& m, const pair<K,V>& pr)
{
	auto it = m.find(pr.first);
	return (it == m.end()) ? pr.second : it->second;
}

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