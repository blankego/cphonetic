#include "pinyin.h"
#include "mandarin.h"
#include "transcriptor.h"

namespace cphonetic
{
	using namespace msound;

	TokenDict<pair<INIT,MED> > Pinyin::_imDict = {
		{"b",{B,KAI}},{"p",{P,KAI}},
		{"m",{M,KAI}},{"f",{F,KAI}},{"v",{V,KAI}},
		{"d",{D,KAI}},{"t",{T,KAI}},
		{"n",{N,KAI}},{"l",{L,KAI}},
		{"g",{G,KAI}},{"k",{K,KAI}},
		{"ng",{NG,KAI}},{"h",{H,KAI}},
		{"zh",{J,KAI}},{"ch",{CH,KAI}},
		{"sh",{SH,KAI}},{"r",{R,KAI}},
		{"z",{TZ,KAI}},{"c",{TS,KAI}},{"s",{S,KAI}},
		{"bi",{B,I}},{"pi",{P,I}},{"mi",{M,I}},{"fi",{F,I}},
		{"di",{D,I}},{"ti",{T,I}},
		{"ni",{N,I}},{"li",{L,I}},
		{"ji",{G,I}},{"qi",{K,I}},
		{"gni",{NG,I}},{"xi",{H,I}},
		{"zyi",{TZ,I}},{"cyi",{TS,I}},{"syi",{S,I}},
		{"y",{Void,I}},{"yi",{Void,I}},
		{"bu",{B,U}},{"pu",{P,U}},{"mu",{M,U}},{"fu",{F,U}},{"vu",{V,U}},
		{"du",{D,U}},{"tu",{T,U}},{"nu",{N,U}},{"lu",{L,U}},
		{"gu",{G,U}},{"ku",{K,U}},
		{"ngu",{NG,U}},{"hu",{H,U}},
		{"zhu",{J,U}},{"chu",{CH,U}},{"shu",{SH,U}},
		{"ru",{R,U}},
		{"zu",{TZ,U}},{"cu",{TS,U}},{"su",{S,U}},
		{"w",{Void,U}},{"wu",{Void,U}},
		{"nü",{N,IU}},{"lü",{L,IU}},
		{"ju",{G,IU}},{"qu",{K,IU}},
		{"gnu",{NG,IU}},{"xu",{H,IU}},
		{"zü",{TZ,IU}},{"cü",{TS,IU}},{"sü",{S,IU}},
		{"yu",{Void,IU}},
		//use special combination to substitute zhi...
		{"zhi",{J,MMAGIC}},{"chi",{CH,MMAGIC}},
		{"shi",{SH,MMAGIC}},{"ri",{R,MMAGIC}},
		{"zi",{TZ,MMAGIC}},{"ci",{TS,MMAGIC}},{"si",{S,MMAGIC}},
		
	};
	
	TokenDict<FIN> Pinyin::_fDict ({
		{"a",A},{"o",O},{"e",E},{"ê",EH},{"er",EL},{"r",EL},
		{"ai",AI},{"ei",EI},{"i",EI},{"ao",AU},{"ou",OU},{"u",OU},
		{"an",AN},{"en",EN},{"ang",ANG},{"eng",ENG},{"am",AM},
		{"em",EM},{"n",EN},{"ng",ENG},{"m",EM},
		//magic value
		{"ong",Y}
		
	});
	TokenDict<TONE> Pinyin::_tDict ({
		{"ˉ",DARK},{"ˊ",LIGHT},{"ˇ",RISING},{"ˋ",DEPARTING},
		{"·",ENTERING},{"˙",NEUTRAL},{"",NEUTRAL},
		{"1",DARK},{"2",LIGHT},{"3",RISING},{"4",DEPARTING},
		{"0",ENTERING},{"5",NEUTRAL},
		
	});
	
	map<pair<INIT,MED>,cchar*> Pinyin::_imTrans = {
		{{B,KAI},"b"},{{P,KAI},"p"},{{M,KAI},"m"},
		{{F,KAI},"f"},{{V,KAI},"v"},
		{{D,KAI},"d"},{{T,KAI},"t"},{{N,KAI},"n"},{{L,KAI},"l"},
		{{G,KAI},"g"},{{K,KAI},"k"},
		{{NG,KAI},"ng"},{{H,KAI},"h"},
		{{J,KAI},"zh"},{{CH,KAI},"ch"},
		{{SH,KAI},"sh"},{{R,KAI},"r"},
		{{TZ,KAI},"z"},{{TS,KAI},"c"},{{S,KAI},"s"},
		{{Void,KAI},""},
		{{B,I},"bi"},{{P,I},"pi"},{{M,I},"mi"},{{F,I},"fi"},
		{{D,I},"di"},{{T,I},"ti"},{{N,I},"ni"},{{L,I},"li"},
		{{G,I},"ji"},{{K,I},"qi"},
		{{NG,I},"gni"},{{H,I},"xi"},
		{{TZ,I},"zyi"},{{TS,I},"cyi"},{{S,I},"syi"},
		{{Void,I},"y"},
		{{B,U},"bu"},{{P,U},"pu"},
		{{M,U},"mu"},{{F,U},"fu"},{{V,U},"vu"},
		{{D,U},"du"},{{T,U},"tu"},
		{{N,U},"nu"},{{L,U},"lu"},
		{{G,U},"gu"},{{K,U},"ku"},
		{{NG,U},"ngu"},{{H,U},"hu"},
		{{J,U},"zhu"},{{CH,U},"chu"},
		{{SH,U},"shu"},{{R,U},"ru"},
		{{TZ,U},"zu"},{{TS,U},"cu"},{{S,U},"su"},
		{{Void,U},"w"},
		{{N,IU},"nü"},{{L,IU},"lü"},
		{{G,IU},"ju"},{{K,IU},"qu"},
		{{NG,IU},"gnu"},{{H,IU},"xu"},
		{{TZ,IU},"zü"},{{TS,IU},"cü"},{{S,IU},"sü"},
		{{Void,IU},"yu"},
		
	};	
	
	
	map<FIN,cchar*> Pinyin::_fTrans = {
		{A,"a"},{O,"o"},{E,"e"},{EH,"e"},{Y,""},{EL,"er"},
		{AI,"ai"},{EI,"ei"},{AU,"ao"},{OU,"ou"},
		{AN,"an"},{EN,"en"},{ANG,"ang"},{ENG,"eng"},{AM,"am"},{EM,"em"},
		{ZERO,""},
		
	};
	map<TONE,cchar*> Pinyin::_tTrans = {
		{DARK,"1"},{LIGHT,"2"},{RISING,"3"},{DEPARTING,"4"},
		{ENTERING,"0"},{NEUTRAL,"5"}
	};
	
	//end Pinyin dictionaries
}//end namespace
