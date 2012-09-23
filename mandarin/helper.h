#ifndef HELPER_HEADER_GUARD
#define HELPER_HEADER_GUARD



#ifdef __cplusplus

#include "shortnames.h"
#include <memory>
#include <iostream>
#include <cstring>
#include <map>

#define PAUTO(a,b,pr) ;const decltype((pr).first)& a;const decltype((pr).second)& b;\
	{const auto& tmp=(pr);a=tmp.first;b=tmp.second;}
#define PASSIGN(a,b,pr) {const auto& tmp=(pr);a=tmp.first;b=tmp.second;}
#define TUP(...) make_tuple(__VA_ARGS__)
#define PR(a,b) make_pair((a),(b))
#define findOr(a,b) make_pair((a),(b))
#define T3ASSIGN(a,b,c,tup) ;{const auto& tmp=(tup);a=get<0>(tup);b=get<1>(tup);c=get<2>(tup);}
#define T3AUTO(a,b,c,tup);const auto& a=get<0>(tup);const auto& b=get<1>(tup);const auto& c=get<2>(tup);

using namespace std;
template<class T>
struct CRMaybe //final
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
	bool ok=false;
public:
	linebuf(){buf[0]=0;}
	operator CharT*(){return &buf[0];}
	operator const CharT*()const {return &buf[0];}
	CharT* operator &(){return &buf[0];}
	operator bool(){return ok;}
	linebuf& operator<<(basic_istream<CharT>& ins)
	{
		buf[0]=0;
		ok=(bool)ins.getline(buf,SIZE,(DELIM));
		return *this;		
	}
	
};


template<class K,class V>
inline V operator^(const map<K,V>& m, const pair<K,V>& pr)
{
	auto it = m.find(pr.first);
	return (it == m.end()) ? pr.second : it->second;
}

#endif //__cplusplus

#endif // HELPER_HEADER_GUARD