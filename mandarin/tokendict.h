#ifndef TOKENDICT_H
#define TOKENDICT_H

#define BOOST_RESULT_OF_USE_DECLTYPE
#include "helper.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <iterator>
using namespace std;

namespace cphonetic
{
template<class TChar>
struct CharAt {
	const TChar ch;
	const int at;
	CharAt( TChar ch, int at ): ch( ch ), at( at ) {}
	template<class S>
	/**
	 * @brief Compare the positioned char with the char at the same position of a string/cstring
	 * @param s The string/cstring to be compared with
	*/
	inline bool operator<( S s ) const {
		TChar cOther = s[at];
		return ch < cOther;
	}
};

/**
 * @brief Compare the char at the position ca.at with the char provided by ca.ch
 * @param s The lefthand side string/cstring
 * @param ca ca.at indicates the index of the lefthand side char of the string s, and the ca.ch is the
 * 		char to be compared with
 */
template <class S,class TChar>
inline bool operator<( S s, CharAt<TChar> ca )
{
	TChar cThis = s[ca.at] ;
	return cThis < ca.ch;
}

template <class TChar>
inline CharAt<TChar> charAt(TChar ch, int pos){return CharAt<TChar>(ch,pos);}

template<class TVal, class TChar = char>
struct TokenDict {
	typedef pair<const TChar*,TVal> _pair;
	typedef vector<_pair > EntVector;
	
	TokenDict( EntVector lst ){
		sort( lst.begin(), lst.end(), []( const _pair& lhs, const _pair& rhs ) {
			return strcmp( ( cchar* )(lhs.first), ( cchar* )(rhs.first) ) < 0;
		} );
		
		for(auto p: lst)
		{
			_keys.push_back(p.first);
			_vals.push_back(p.second);
		}
	};

	CRMaybe<TVal> matchStart( const TChar*& pStr );	
private:
	vector<const TChar*> _keys;
	vector<TVal> _vals;

};

template<class TVal,class TChar>
CRMaybe<TVal> TokenDict<TVal,TChar>::matchStart( const TChar*& pStr )
{
	auto head = _keys.begin();
	auto tail = _keys.end();
	int pos = 0;
	TChar c = *pStr;
	do{
		auto range = equal_range( head, tail, charAt( c, pos ) );
		if( range.first == range.second ) // current char not matched
			break;
		else {
			head = range.first;
			tail = range.second;
		}

	}while((c !='\0')&&(c = *++pStr, ++pos));
	

	if( ( *head )[pos] == '\0' )
		return crmaybe(_vals[head - _keys.begin()]);
	else 
	{
		if( pos > 0 ) // false match: rollback!
			pStr -= pos;
		return nullptr;
	}

}


}//end namespace

#endif //TOKENDICT_H