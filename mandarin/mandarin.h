#ifndef MANDARIN_HEADER_GUARD
#define MANDARIN_HEADER_GUARD
#include "helper.h"
#include <iostream>
namespace cphonetic
{
namespace msound
{
enum INIT:
	uchar {
		Void = 0,
		B = 1, 	P, M, 	F, 		V,
		D = 7, 	T, N, 	L = 11,
		G = 13, K, NG, 	H,
		J = 19, CH,   	SH = 22, R = 23,
		TZ = 25, TS,    	S = 28,
	};
enum INITGROUP:
	uchar {
		_GRP = 0,
		BGRP, DGRP, GGRP, JGRP, TZGRP,
	};
enum TONE:
	uchar {
		DARK = 0,
		LIGHT = 0b00100000,
		RISING = 0b01000000,
		DEPARTING = 0b01100000,
		ENTERING = 0b10000000,
		NEUTRAL = 0b10100000,
	};

enum MED:
	uchar {
		KAI = 0, I = 0b01000000, U = 0b10000000, IU = 0b11000000,MMAGIC = 255,
	};

enum FIN:
	uchar {
		ZERO = 0,
		A = 1, O, E, EH, Y, EL,
		AI = 11, EI = 13,
		AU = 21, OU = 23,
		AN = 31, EN = 33,
		ANG = 41, ENG = 43,
		AM = 51, EM = 53,
	};

enum RIME:
	uchar {		
		ZILCH = ZERO,
		A_ = A,O_ = O,E_ = E,EH_ = EH,Y_ =  Y,EL_ = EL,AI_ = AI,EI_ = EI,AU_ = AU,OU_ = OU,
		AN_ = AN,EN_ = EN,ANG_ = ANG,ENG_ = ENG,AM_ = AM,EM_ = EM,
		I_ = I, IA = I | A, IE = I | EH, IO = I | O, IAI = I | AI, IAU = I | AU, IOU = I | OU,
		IAN = I | AN, IN = I | EN, IANG = I | ANG, ING = I | ENG, IAM = I | AM, IM = I | EM,
		U_ = U, UA = U | A, UO = U | O, UAI = U | AI, UEI = U | EI, UAN = U | AN, UN = U | EN,
		UANG = U | ANG, ONG = U | ENG, UEH = U | EH,//This is only for pinyin transcription
		IU_ = IU, IUO = IU | O, IUE = IU | EH, IUAN = IU | AN, IUN = IU | EN, IONG = IU | ENG,
	};

	
}
	
class MTransliterator;
class Bopomofo;
class Pinyin;
class MarkedPinyin;
//global transliterator variables
extern const Bopomofo bopomofo;
extern const Pinyin pinyin;
extern const MarkedPinyin mpinyin;


using namespace msound;
class MSyl
{
	
	
public:


	friend class CRMaybe<MSyl>;
	static CRMaybe<MSyl> from( MTransliterator* trans, cchar* pStr );
	MSyl( INIT init, MED med, FIN fin, TONE tone ): MSyl( init | tone, RIME( med | fin ) ) {}



	bool operator==( MSyl rhs )const {return _asUShort == rhs._asUShort;}
	bool operator<( MSyl rhs )const;

	INIT init() const {return INIT( _initTone & IMASK );}
	void init( INIT i ) { _initTone = TMASK & _initTone | i;}
	MED med() const {return MED( _rime & MMASK );}
	void med( MED m ) { _rime = RIME( _rime & FMASK | m );}
	FIN fin() const {return FIN( _rime & FMASK );}
	void fin( FIN f ) { _rime = RIME( _rime & MMASK | f );}
	TONE tone()const {return TONE( _initTone & TMASK );}
	void tone( TONE t ) {_initTone = _initTone & IMASK | t;}
	RIME rime()const {return _rime;}
	void rime( RIME r ) {_rime = r;}
	bool isPalatized() const {return (med() & I) == I;}
	INITGROUP group() const {return INITGROUP( ( (init() + 5 )/ 6 ) );}
	MSyl dup() const {return MSyl( _asUShort );}
	string toStr() const;
	string toStr(const MTransliterator& trans)const;

private:
	MSyl( uchar initTone, RIME rime ): _initTone( initTone ), _rime( rime ) {}

	MSyl( ushort code ): _asUShort( code ) {}
	MSyl() = default;
	static const uchar 	IMASK = 0b00011111,
						TMASK = 0b11100000,
						MMASK = 0b11000000,
						FMASK = 0b00111111;

	//region data members
	union {
		ushort _asUShort;
		struct {
			uchar _initTone;
			RIME _rime;
		};

	};
	//endregion data members
};
inline RIME operator|( MED lhs, FIN rhs ) {return RIME( int( lhs ) | int( rhs ) );}
inline RIME operator|( FIN lhs, MED rhs ) {return rhs | lhs;}
ostream& operator<<( ostream& os, const MSyl& ms );
}
#endif // MANDARIN_HEADER_GUARD
