#ifndef BOPOMOFO_H
#define BOPOMOFO_H
#include "transliterator.h"
#include "shortnames.h"
#include "msound.h"
#include "tokendict.h"
#include <map>
namespace cphonetic
{

using namespace msound;

class Bopomofo: public MTransliterator
{
	
	static TokenDict<INIT> _iDict;
	static TokenDict<MED> _mDict;
	static TokenDict<FIN> _fDict;
	static TokenDict<TONE> _tDict;
	static map<INIT, cchar*>_iTrans;
	static map<MED, cchar*> _mTrans;
	static map<FIN, cchar*> _fTrans;
	static map<TONE, cchar*> _tTrans;
	static map<INIT, cchar*> _giGrp; //ㄐㄑㄬㄒ group

public:
	virtual MSyl munchSyl(cchar*& pStr) const;

	virtual string transcribe(const MSyl& syl)const;
	
};
	
	
}

#endif //BOPOMOFO_H