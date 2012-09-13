#ifndef BOPOMOFO_H
#define BOPOMOFO_H
#include "transliterators.h"

namespace cphonetic
{
class Bopomofo: public MTransliterator
{
	static TokenDict<MSyl::INIT> _iDict;
	static TokenDict<MSyl::MED> _mDict;
	static TokenDict<MSyl::FIN> _fDict;
	static TokenDict<MSyl::TONE> _tDict;
	static map<MSyl::INIT, cchar*>_iTrans;
	static map<MSyl::MED, cchar*> _mTrans;
	static map<MSyl::FIN, cchar*> _fTrans;
	static map<MSyl::TONE, cchar*> _tTrans;
	static map<MSyl::INIT, cchar*> _giGrp; //ㄐㄑㄬㄒ group

public:
	virtual CRMaybe<MSyl> munchSyl( cchar*& pStr ) const;

	virtual string transliterate ( const MSyl& syl )const;
	
};
	
	
}

#endif //BOPOMOFO_H