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
		return memcmp( &ch, &cOther, sizeof( TChar ) ) < 0; // /*(ushort)*/ch < /*(ushort)*/cOther;//default signed char is nasty
	}
};

/**
 * @brief Compare the char at the position ca.at with the char provided by ca.ch
 * @param s The lefthand side string/cstring
 * @param ca ca.at indicates the index of the lefthand side char of the string s, and the ca.ch is the
 * 		char to be compared with
 */
template <class S, class TChar>
inline bool operator<( S s, CharAt<TChar> ca )
{
	TChar cThis = s[ca.at] ;
	return ( uint )cThis < ( uint )ca.ch;
}

template <class TChar>
inline CharAt<TChar> charAt( TChar ch, int pos ) {return CharAt<TChar>( ch, pos );}

template<class TVal, class TChar = char>
struct TokenDict {
	typedef pair<const TChar*, TVal> _pair;
	typedef initializer_list<_pair > EntLst;

	TokenDict( EntLst lst ); 
	const vector<const TChar*>& keys() const {return _keys;}
	const vector<TVal>& values() const {return _vals;}
	CRMaybe<TVal> matchStart( const TChar*& pStr );
private:
	vector<const TChar*> _keys;
	vector<size_t> _sizes;
	vector<TVal> _vals;
	bool _caseSensitive;//TODO:

};

template<class TVal, class TChar>
TokenDict<TVal,TChar>::TokenDict(EntLst lst){
	typedef tuple<const TChar*, size_t, TVal> tup3;
	vector<tup3 > tlst( lst.size() );
	transform( lst.begin(), lst.end(), tlst.begin(), []( const _pair & pr ) {
		return make_tuple( pr.first, strlen( ( cchar* )pr.first ), pr.second );
	} );

	sort( tlst.begin(), tlst.end(), []( const tup3 & lhs, const tup3 & rhs ) {
		auto lkey = get<0>( lhs ), rkey = get<0>( rhs );
		auto llen = get<1>( lhs ), rlen = get<1>( rhs );
		bool lt = llen < rlen;
		int res = memcmp( lkey, rkey, lt ? llen : rlen );
		return ( res == 0 ) ? lt : ( res < 0 );
	} );

	for( const tup3& t: tlst ) {
		_keys.push_back( get<0>( t ) );
		_sizes.push_back( get<1>( t ) );
		_vals.push_back( get<2>( t ) );
	}

}

template<class TVal, class TChar>
CRMaybe<TVal> TokenDict<TVal, TChar>::matchStart( const TChar*& pStr )
{
	
	auto head = _keys.begin();
	auto tail = _keys.end(), candidate = tail;
	size_t pos = 0, rollbackPos = 0;
	TChar c = pStr[0];

	do {
		auto range = equal_range( head, tail, charAt( c, pos ) );
	
		if( range.first == range.second ){ // current char not matched
			pos = rollbackPos;
			break;
		}else {
			head = range.first;
			tail = range.second;
			if(tail - head == 1){//check the only left candidate
				size_t restLen = _sizes[head - _keys.begin()] - pos;
				if(restLen == 0 || memcmp(pStr + pos, (*head + pos), restLen) == 0){
					candidate = head;
					pos += restLen;
				}
				else{
					pos = rollbackPos;
				}
				break;
			}else if( ( *head )[pos + 1] == '\0' ) { //range match & check if the first el qualified as a candidate
				rollbackPos = pos + 1;
				candidate = head;
			}
		}

	} while( c = pStr[++pos] );

	pStr += pos;
	if(candidate != _keys.end()){
		return crmaybe( _vals[candidate - _keys.begin()] );
	}else if((*head)[pos]=='\0'){//empty key matches any thing!
		return crmaybe(_vals[head - _keys.begin()]);			
	}else {		
		return nullptr;
	}

}


}//end namespace

#endif //TOKENDICT_H
