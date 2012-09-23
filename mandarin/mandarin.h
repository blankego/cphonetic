#ifndef MANDARIN_HEADER_GUARD
#define MANDARIN_HEADER_GUARD

#include "shortnames.h"
#ifdef __cplusplus 
extern "C"
#endif 
typedef union {
	ushort code;
	struct {
		uchar initTone;
		uchar rime;
	};
} CpMSyl;


#ifdef __cplusplus//----------------C++ PART----------------------------
#include "msound.h"
#include <string>
#include <ostream>
#include "tokendict.h"
using namespace std;

namespace cphonetic
{
	//forward declarations
	class MTranscriptor;
	class Bopomofo;
	class Pinyin;
	class MarkedPinyin;
	class MSyl;	
	//global transliterator variables
	extern const Bopomofo bopomofo;
	extern const Pinyin pinyin;
	extern const MarkedPinyin mpinyin;	
	//end forward declarations
	
using namespace msound;
class MSyl
{
public:
	
	friend class CRMaybe<MSyl>;
	static CRMaybe<MSyl> from(MTranscriptor* trans, cchar* pStr);
	
	MSyl(INIT init, MED med, FIN fin, TONE tone): MSyl(init | tone, RIME(med | fin)) {}

	bool operator==(MSyl rhs)const {return _data.code == rhs._data.code;}
	bool operator<(MSyl rhs)const;

	INIT init() const {return INIT(_data.initTone & IMASK);}
	void init(INIT i) { _data.initTone = TMASK & _data.initTone | i;}

	MED med() const {return MED(_data.rime & MMASK);}
	void med(MED m) { _data.rime = RIME(_data.rime & FMASK | m);}

	FIN fin() const {return FIN(_data.rime & FMASK);}
	void fin(FIN f) { _data.rime = RIME(_data.rime & MMASK | f);}

	TONE tone()const {return TONE(_data.initTone & TMASK);}
	void tone(TONE t) {_data.initTone = _data.initTone & IMASK | t;}

	RIME rime()const {return RIME(_data.rime);}
	void rime(RIME r) {_data.rime = r;}

	bool isPalatized() const {return (med() & I) == I;}

	INITGROUP group() const {return INITGROUP(((init() + 5) / 6));}

	MSyl dup() const {return MSyl(_data.code);}

	string toStr() const;
	string toStr(const MTranscriptor& trans)const;

private:
	
	MSyl(uchar initTone, RIME rime){_data.initTone = initTone;_data.rime = rime;}
	MSyl(ushort code): _data({code}) {}
	MSyl() = default;
	
	static const uchar 	IMASK = 0b00011111,
						TMASK = 0b11100000,
						MMASK = 0b11000000,
						FMASK = 0b00111111;

	//region data members
	CpMSyl _data;	
	//endregion data members
};
inline RIME operator|(MED lhs, FIN rhs) {return RIME(int(lhs) | int(rhs));}
inline RIME operator|(FIN lhs, MED rhs) {return rhs | lhs;}
ostream& operator<<(ostream& os, const MSyl& ms);

}// end namespace cphonetic
#endif

//----------------C PART----------------------------
#ifdef __cplusplus
namespace cphonetic{
extern "C" {
#endif


#ifdef __cplusplus
}
}
#endif
#endif // MANDARIN_HEADER_GUARD
