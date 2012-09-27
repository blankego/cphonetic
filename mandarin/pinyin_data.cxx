#include "pinyin.h"
#include "mandarin.h"
#include <map>
namespace cphonetic
{
using namespace msound;

TokenDict<MSyl> Pinyin::_miDict = {
	
	{"b", {B, KAI, NEUTRAL}}, {"p", {P, KAI, NEUTRAL}},
	{"m", {M, KAI, NEUTRAL}}, {"f", {F, KAI, NEUTRAL}}, {"v", {V, KAI, NEUTRAL}},
	{"d", {D, KAI, NEUTRAL}}, {"t", {T, KAI, NEUTRAL}},
	{"n", {N, KAI, NEUTRAL}}, {"l", {L, KAI, NEUTRAL}},
	{"g", {G, KAI, NEUTRAL}}, {"k", {K, KAI, NEUTRAL}},
	{"ng", {NG, KAI, NEUTRAL}}, {"h", {H, KAI, NEUTRAL}},
	{"zh", {J, KAI, NEUTRAL}}, {"ch", {CH, KAI, NEUTRAL}},
	{"sh", {SH, KAI, NEUTRAL}}, {"r", {R, KAI, NEUTRAL}},
	{"z", {TZ, KAI, NEUTRAL}}, {"c", {TS, KAI, NEUTRAL}}, {"s", {S, KAI, NEUTRAL}},

	{"bi", {B, I, NEUTRAL}}, {"pi", {P, I, NEUTRAL}}, {"mi", {M, I, NEUTRAL}},
	{"fi",{F,I,NEUTRAL}},
	{"di", {D, I, NEUTRAL}}, {"ti", {T, I, NEUTRAL}},
	{"ni", {N, I, NEUTRAL}}, {"li", {L, I, NEUTRAL}},
	{"ji", {G, I, NEUTRAL}}, {"qi", {K, I, NEUTRAL}},
	{"gni", {NG, I, NEUTRAL}}, {"xi", {H, I, NEUTRAL}},
	{"zyi", {TZ, I, NEUTRAL}}, {"cyi", {TS, I, NEUTRAL}}, {"syi", {S, I, NEUTRAL}},
	{"y", {Void, I, NEUTRAL}}, {"yi", {Void, I, NEUTRAL}},
	{"bu", {B, U, NEUTRAL}}, {"pu", {P, U, NEUTRAL}}, {"mu", {M, U, NEUTRAL}}, {"fu", {F, U, NEUTRAL}}, {"vu", {V, U, NEUTRAL}},
	{"du", {D, U, NEUTRAL}}, {"tu", {T, U, NEUTRAL}}, {"nu", {N, U, NEUTRAL}}, {"lu", {L, U, NEUTRAL}},
	{"gu", {G, U, NEUTRAL}}, {"ku", {K, U, NEUTRAL}},
	{"ngu", {NG, U, NEUTRAL}}, {"hu", {H, U, NEUTRAL}},
	{"zhu", {J, U, NEUTRAL}}, {"chu", {CH, U, NEUTRAL}}, {"shu", {SH, U, NEUTRAL}},
	{"ru", {R, U, NEUTRAL}},
	{"zu", {TZ, U, NEUTRAL}}, {"cu", {TS, U, NEUTRAL}}, {"su", {S, U, NEUTRAL}},
	{"w", {Void, U, NEUTRAL}}, {"wu", {Void, U, NEUTRAL}},
	{"nü", {N, IU, NEUTRAL}}, {"lü", {L, IU, NEUTRAL}},
	{"ju", {G, IU, NEUTRAL}}, {"qu", {K, IU, NEUTRAL}},
	{"gnu", {NG, IU, NEUTRAL}}, {"xu", {H, IU, NEUTRAL}},
	{"zü", {TZ, IU, NEUTRAL}}, {"cü", {TS, IU, NEUTRAL}}, {"sü", {S, IU, NEUTRAL}},
	{"yu", {Void, IU, NEUTRAL}},
	


	{"bī", {B, I, DARK}}, {"pī", {P, I, DARK}}, {"mī", {M, I, DARK}},
	{"fī",{F,I,DARK}},
	{"dī", {D, I, DARK}}, {"tī", {T, I, DARK}},
	{"nī", {N, I, DARK}}, {"lī", {L, I, DARK}},
	{"jī", {G, I, DARK}}, {"qī", {K, I, DARK}},
	{"gnī", {NG, I, DARK}}, {"xī", {H, I, DARK}},
	{"zyī", {TZ, I, DARK}}, {"cyī", {TS, I, DARK}}, {"syī", {S, I, DARK}},
	{"yī", {Void, I, DARK}},
	{"bū", {B, U, DARK}}, {"pū", {P, U, DARK}}, {"mū", {M, U, DARK}}, {"fū", {F, U, DARK}}, {"vū", {V, U, DARK}},
	{"dū", {D, U, DARK}}, {"tū", {T, U, DARK}}, {"nū", {N, U, DARK}}, {"lū", {L, U, DARK}},
	{"gū", {G, U, DARK}}, {"kū", {K, U, DARK}},
	{"ngū", {NG, U, DARK}}, {"hū", {H, U, DARK}},
	{"zhū", {J, U, DARK}}, {"chū", {CH, U, DARK}}, {"shū", {SH, U, DARK}},
	{"rū", {R, U, DARK}},
	{"zū", {TZ, U, DARK}}, {"cū", {TS, U, DARK}}, {"sū", {S, U, DARK}},
	{"wū", {Void, U, DARK}},
	{"nǖ", {N, IU, DARK}}, {"lǖ", {L, IU, DARK}},
	{"jū", {G, IU, DARK}}, {"qū", {K, IU, DARK}},
	{"gnū", {NG, IU, DARK}}, {"xū", {H, IU, DARK}},
	{"zǖ", {TZ, IU, DARK}}, {"cǖ", {TS, IU, DARK}}, {"sǖ", {S, IU, DARK}},
	{"yū", {Void, IU, DARK}},

	

	{"bí", {B, I, LIGHT}}, {"pí", {P, I, LIGHT}}, {"mí", {M, I, LIGHT}},
	{"fí",{F,I,LIGHT}},
	{"dí", {D, I, LIGHT}}, {"tí", {T, I, LIGHT}},
	{"ní", {N, I, LIGHT}}, {"lí", {L, I, LIGHT}},
	{"jí", {G, I, LIGHT}}, {"qí", {K, I, LIGHT}},
	{"gní", {NG, I, LIGHT}}, {"xí", {H, I, LIGHT}},
	{"zyí", {TZ, I, LIGHT}}, {"cyí", {TS, I, LIGHT}}, {"syí", {S, I, LIGHT}},
	{"yí", {Void, I, LIGHT}},
	{"bú", {B, U, LIGHT}}, {"pú", {P, U, LIGHT}}, {"mú", {M, U, LIGHT}}, {"fú", {F, U, LIGHT}}, {"vú", {V, U, LIGHT}},
	{"dú", {D, U, LIGHT}}, {"tú", {T, U, LIGHT}}, {"nú", {N, U, LIGHT}}, {"lú", {L, U, LIGHT}},
	{"gú", {G, U, LIGHT}}, {"kú", {K, U, LIGHT}},
	{"ngú", {NG, U, LIGHT}}, {"hú", {H, U, LIGHT}},
	{"zhú", {J, U, LIGHT}}, {"chú", {CH, U, LIGHT}}, {"shú", {SH, U, LIGHT}},
	{"rú", {R, U, LIGHT}},
	{"zú", {TZ, U, LIGHT}}, {"cú", {TS, U, LIGHT}}, {"sú", {S, U, LIGHT}},
	{"wú", {Void, U, LIGHT}},
	{"nǘ", {N, IU, LIGHT}}, {"lǘ", {L, IU, LIGHT}},
	{"jú", {G, IU, LIGHT}}, {"qú", {K, IU, LIGHT}},
	{"gnú", {NG, IU, LIGHT}}, {"xú", {H, IU, LIGHT}},
	{"zǘ", {TZ, IU, LIGHT}}, {"cǘ", {TS, IU, LIGHT}}, {"sǘ", {S, IU, LIGHT}},
	{"yú", {Void, IU, LIGHT}},


	{"bǐ", {B, I, RISING}}, {"pǐ", {P, I, RISING}}, {"mǐ", {M, I, RISING}},
	{"fǐ",{F,I,RISING}},
	{"dǐ", {D, I, RISING}}, {"tǐ", {T, I, RISING}},
	{"nǐ", {N, I, RISING}}, {"lǐ", {L, I, RISING}},
	{"jǐ", {G, I, RISING}}, {"qǐ", {K, I, RISING}},
	{"gnǐ", {NG, I, RISING}}, {"xǐ", {H, I, RISING}},
	{"zyǐ", {TZ, I, RISING}}, {"cyǐ", {TS, I, RISING}}, {"syǐ", {S, I, RISING}},
	{"yǐ", {Void, I, RISING}},
	{"bǔ", {B, U, RISING}}, {"pǔ", {P, U, RISING}}, {"mǔ", {M, U, RISING}}, {"fǔ", {F, U, RISING}}, {"vǔ", {V, U, RISING}},
	{"dǔ", {D, U, RISING}}, {"tǔ", {T, U, RISING}}, {"nǔ", {N, U, RISING}}, {"lǔ", {L, U, RISING}},
	{"gǔ", {G, U, RISING}}, {"kǔ", {K, U, RISING}},
	{"ngǔ", {NG, U, RISING}}, {"hǔ", {H, U, RISING}},
	{"zhǔ", {J, U, RISING}}, {"chǔ", {CH, U, RISING}}, {"shǔ", {SH, U, RISING}},
	{"rǔ", {R, U, RISING}},
	{"zǔ", {TZ, U, RISING}}, {"cǔ", {TS, U, RISING}}, {"sǔ", {S, U, RISING}},
	{"wǔ", {Void, U, RISING}},
	{"nǚ", {N, IU, RISING}}, {"lǚ", {L, IU, RISING}},
	{"jǔ", {G, IU, RISING}}, {"qǔ", {K, IU, RISING}},
	{"gnǔ", {NG, IU, RISING}}, {"xǔ", {H, IU, RISING}},
	{"zǚ", {TZ, IU, RISING}}, {"cǚ", {TS, IU, RISING}}, {"sǚ", {S, IU, RISING}},
	{"yǔ", {Void, IU, RISING}},


	{"bì", {B, I, DEPARTING}}, {"pì", {P, I, DEPARTING}}, {"mì", {M, I, DEPARTING}},
	{"fì",{F,I,DEPARTING}},
	{"dì", {D, I, DEPARTING}}, {"tì", {T, I, DEPARTING}},
	{"nì", {N, I, DEPARTING}}, {"lì", {L, I, DEPARTING}},
	{"jì", {G, I, DEPARTING}}, {"qì", {K, I, DEPARTING}},
	{"gnì", {NG, I, DEPARTING}}, {"xì", {H, I, DEPARTING}},
	{"zyì", {TZ, I, DEPARTING}}, {"cyì", {TS, I, DEPARTING}}, {"syì", {S, I, DEPARTING}},
	{"yì", {Void, I, DEPARTING}},
	{"bù", {B, U, DEPARTING}}, {"pù", {P, U, DEPARTING}}, {"mù", {M, U, DEPARTING}}, {"fù", {F, U, DEPARTING}}, {"vù", {V, U, DEPARTING}},
	{"dù", {D, U, DEPARTING}}, {"tù", {T, U, DEPARTING}}, {"nù", {N, U, DEPARTING}}, {"lù", {L, U, DEPARTING}},
	{"gù", {G, U, DEPARTING}}, {"kù", {K, U, DEPARTING}},
	{"ngù", {NG, U, DEPARTING}}, {"hù", {H, U, DEPARTING}},
	{"zhù", {J, U, DEPARTING}}, {"chù", {CH, U, DEPARTING}}, {"shù", {SH, U, DEPARTING}},
	{"rù", {R, U, DEPARTING}},
	{"zù", {TZ, U, DEPARTING}}, {"cù", {TS, U, DEPARTING}}, {"sù", {S, U, DEPARTING}},
	{"wù", {Void, U, DEPARTING}},
	{"nǜ", {N, IU, DEPARTING}}, {"lǜ", {L, IU, DEPARTING}},
	{"jù", {G, IU, DEPARTING}}, {"qù", {K, IU, DEPARTING}},
	{"gnù", {NG, IU, DEPARTING}}, {"xù", {H, IU, DEPARTING}},
	{"zǜ", {TZ, IU, DEPARTING}}, {"cǜ", {TS, IU, DEPARTING}}, {"sǜ", {S, IU, DEPARTING}},
	{"yù", {Void, IU, DEPARTING}},


};

TokenDict<MSyl> Pinyin::_mfDict( {
	{"a", {A, NEUTRAL}}, {"o", {O, NEUTRAL}}, {"e", {E, NEUTRAL}}, {"ê", {EH, NEUTRAL}}, {"er", {EL, NEUTRAL}},
	{"r", {EL, NEUTRAL}},
	{"ai", {AI, NEUTRAL}}, {"ei", {EI, NEUTRAL}}, {"i", {I,ZERO, NEUTRAL}}, {"ao", {AU, NEUTRAL}}, {"ou", {OU, NEUTRAL}},
	{"u", {U,ZERO, NEUTRAL}},
	{"an", {AN, NEUTRAL}}, {"en", {EN, NEUTRAL}}, {"ang", {ANG, NEUTRAL}}, {"eng", {ENG, NEUTRAL}},
	{"am", {AM, NEUTRAL}}, {"em", {EM, NEUTRAL}}, {"n", {EN, NEUTRAL}}, {"ng", {ENG, NEUTRAL}}, {"m", {EM, NEUTRAL}},
	
	{"ong", {U,ENG, NEUTRAL}},

	{"ā", {A, DARK}}, {"ō", {O, DARK}}, {"ē", {E, DARK}}, {"ê¯", {EH, DARK}}, {"ēr", {EL, DARK}},
	{"āi", {AI, DARK}}, {"ēi", {EI, DARK}}, {"ī", {I,ZERO, DARK}}, {"āo", {AU, DARK}}, {"ōu", {OU, DARK}},
	{"ū", {U,ZERO, DARK}},
	{"ān", {AN, DARK}}, {"ēn", {EN, DARK}}, {"āng", {ANG, DARK}}, {"ēng", {ENG, DARK}}, {"ām", {AM, DARK}},
	{"ēm", {EM, DARK}},
	{"ōng", {U,ENG, DARK}},

	{"á", {A, LIGHT}}, {"ó", {O, LIGHT}}, {"é", {E, LIGHT}}, {"ê´", {EH, LIGHT}}, {"ér", {EL, LIGHT}},
	{"ái", {AI, LIGHT}}, {"éi", {EI, LIGHT}}, {"í", {I,ZERO, LIGHT}}, {"áo", {AU, LIGHT}}, {"óu", {OU, LIGHT}},
	{"ú", {U,ZERO, LIGHT}},
	{"án", {AN, LIGHT}}, {"én", {EN, LIGHT}}, {"áng", {ANG, LIGHT}}, {"éng", {ENG, LIGHT}}, {"ám", {AM, LIGHT}},
	{"ém", {EM, LIGHT}},
	{"óng", {Y, LIGHT}},

	{"ǎ", {A, RISING}}, {"ǒ", {O, RISING}}, {"ě", {E, RISING}}, {"êˇ", {EH, RISING}}, {"ěr", {EL, RISING}},
	{"ǎi", {AI, RISING}}, {"ěi", {EI, RISING}}, {"ǐ", {I,ZERO, RISING}}, {"ǎo", {AU, RISING}}, {"ǒu", {OU, RISING}}, {"ǔ", {U, ZERO, RISING}},
	{"ǎn", {AN, RISING}}, {"ěn", {EN, RISING}}, {"ǎng", {ANG, RISING}}, {"ěng", {ENG, RISING}}, {"ǎm", {AM, RISING}},
	{"ěm", {EM, RISING}},
	{"ǒng", {Y, RISING}},

	{"à", {A, DEPARTING}}, {"ò", {O, DEPARTING}}, {"è", {E, DEPARTING}}, {"ê`", {EH, DEPARTING}}, {"èr", {EL, DEPARTING}},
	{"ài", {AI, DEPARTING}}, {"èi", {EI, DEPARTING}}, {"ì", {I,ZERO, DEPARTING}}, {"ào", {AU, DEPARTING}}, {"òu", {OU, DEPARTING}},
	{"ù", {U,ZERO, DEPARTING}},
	{"àn", {AN, DEPARTING}}, {"èn", {EN, DEPARTING}}, {"àng", {ANG, DEPARTING}}, {"èng", {ENG, DEPARTING}}, {"àm", {AM, DEPARTING}},
	{"èm", {EM, DEPARTING}},
	{"òng", {U, ENG, DEPARTING}},

	{"ah", {A, ENTERING}}, {"oh", {O, ENTERING}}, {"eh", {E, ENTERING}}, {"êh", {EH, ENTERING}},
	{"h", {ZERO, ENTERING}},

} );


vector<cchar*> Pinyin::_ui = {"ī", "í", "ǐ", "ì", "", "i"};
vector<cchar*> Pinyin::_iu = {"ū", "ú", "ǔ", "ù", "", "u"};
map<INIT, cchar*> Pinyin::_miTrans = {
	{Void, ""},
	{B, "b"},
	{P, "p"},
	{M, "m"},
	{F, "f"},
	{V, "v"},
	{D, "d"},
	{T, "t"},
	{N, "n"},
	{L, "l"},
	{G, "g"},
	{K, "k"},
	{NG, "ng"},
	{H, "h"},
	{J, "zh"},
	{CH, "ch"},
	{SH, "sh"},
	{R, "r"},
	{TZ, "z"},
	{TS, "c"},
	{S, "s"},
};
map<INIT, cchar*> Pinyin::_specInit = {
	{G, "j"}, {K, "q"}, {NG, "gn"}, {H, "x"}, {TZ, "zy"}, {TS, "cy"}, {S, "sy"},
};
map<MSyl, cchar*> Pinyin::_m0Trans( {
	{{I_, NEUTRAL}, "yi"}, {{IA, NEUTRAL}, "ya"}, {{IE, NEUTRAL}, "ye"}, {{IO, NEUTRAL}, "yo"},
	{{IAI, NEUTRAL}, "yai"}, {{IAU, NEUTRAL}, "yao"}, {{IOU, NEUTRAL}, "you"},
	{{IAN, NEUTRAL}, "yan"}, {{IN, NEUTRAL}, "yin"}, {{IANG, NEUTRAL}, "yang"}, {{ING, NEUTRAL}, "ying"},
	{{IAM, NEUTRAL}, "yam"}, {{IM, NEUTRAL}, "yim"},
	{{U_, NEUTRAL}, "wu"}, {{UA, NEUTRAL}, "wa"}, {{UO, NEUTRAL}, "wo"},
	{{UAI, NEUTRAL}, "wai"}, {{UEI, NEUTRAL}, "wei"}, {{UAN, NEUTRAL}, "wan"}, {{UN, NEUTRAL}, "wen"}, {{UANG, NEUTRAL}, "wang"}, {{ONG, NEUTRAL}, "weng"},
	{{IU_, NEUTRAL}, "yu"}, {{IUO, NEUTRAL}, "yuo"}, {{IUE, NEUTRAL}, "yue"}, {{IUAN, NEUTRAL}, "yuan"}, {{IUN, NEUTRAL}, "yun"}, {{IONG, NEUTRAL}, "yong"},

	{{I_, DARK}, "yī"}, {{IA, DARK}, "yā"}, {{IE, DARK}, "yē"}, {{IO, DARK}, "yō"},
	{{IAI, DARK}, "yāi"}, {{IAU, DARK}, "yāo"}, {{IOU, DARK}, "yōu"},
	{{IAN, DARK}, "yān"}, {{IN, DARK}, "yīn"}, {{IANG, DARK}, "yāng"}, {{ING, DARK}, "yīng"},
	{{IAM, DARK}, "yām"}, {{IM, DARK}, "yīm"},
	{{U_, DARK}, "wū"}, {{UA, DARK}, "wā"}, {{UO, DARK}, "wō"},
	{{UAI, DARK}, "wāi"}, {{UEI, DARK}, "wēi"}, {{UAN, DARK}, "wān"}, {{UN, DARK}, "wēn"}, {{UANG, DARK}, "wāng"}, {{ONG, DARK}, "wēng"},
	{{IU_, DARK}, "yū"}, {{IUO, DARK}, "yuō"}, {{IUE, DARK}, "yuē"}, {{IUAN, DARK}, "yuān"}, {{IUN, DARK}, "yūn"}, {{IONG, DARK}, "yōng"},

	{{I_, LIGHT}, "yí"}, {{IA, LIGHT}, "yá"}, {{IE, LIGHT}, "yé"}, {{IO, LIGHT}, "yó"},
	{{IAI, LIGHT}, "yái"}, {{IAU, LIGHT}, "yáo"}, {{IOU, LIGHT}, "yóu"},
	{{IAN, LIGHT}, "yán"}, {{IN, LIGHT}, "yín"}, {{IANG, LIGHT}, "yáng"}, {{ING, LIGHT}, "yíng"},
	{{IAM, LIGHT}, "yám"}, {{IM, LIGHT}, "yím"},
	{{U_, LIGHT}, "wú"}, {{UA, LIGHT}, "wá"}, {{UO, LIGHT}, "wó"},
	{{UAI, LIGHT}, "wái"}, {{UEI, LIGHT}, "wéi"}, {{UAN, LIGHT}, "wán"}, {{UN, LIGHT}, "wén"}, {{UANG, LIGHT}, "wáng"}, {{ONG, LIGHT}, "wéng"},
	{{IU_, LIGHT}, "yú"}, {{IUO, LIGHT}, "yuó"}, {{IUE, LIGHT}, "yué"}, {{IUAN, LIGHT}, "yuán"}, {{IUN, LIGHT}, "yún"}, {{IONG, LIGHT}, "yóng"},

	{{I_, RISING}, "yǐ"}, {{IA, RISING}, "yǎ"}, {{IE, RISING}, "yě"}, {{IO, RISING}, "yǒ"},
	{{IAI, RISING}, "yǎi"}, {{IAU, RISING}, "yǎo"}, {{IOU, RISING}, "yǒu"},
	{{IAN, RISING}, "yǎn"}, {{IN, RISING}, "yǐn"}, {{IANG, RISING}, "yǎng"}, {{ING, RISING}, "yǐng"},
	{{IAM, RISING}, "yǎm"}, {{IM, RISING}, "yǐm"},
	{{U_, RISING}, "wǔ"}, {{UA, RISING}, "wǎ"}, {{UO, RISING}, "wǒ"},
	{{UAI, RISING}, "wǎi"}, {{UEI, RISING}, "wěi"}, {{UAN, RISING}, "wǎn"}, {{UN, RISING}, "wěn"}, {{UANG, RISING}, "wǎng"}, {{ONG, RISING}, "wěng"},
	{{IU_, RISING}, "yǔ"}, {{IUO, RISING}, "yuǒ"}, {{IUE, RISING}, "yuě"}, {{IUAN, RISING}, "yuǎn"}, {{IUN, RISING}, "yǔn"}, {{IONG, RISING}, "yǒng"},

	{{I_, DEPARTING}, "yì"}, {{IA, DEPARTING}, "yà"}, {{IE, DEPARTING}, "yè"}, {{IO, DEPARTING}, "yò"},
	{{IAI, DEPARTING}, "yài"}, {{IAU, DEPARTING}, "yào"}, {{IOU, DEPARTING}, "yòu"},
	{{IAN, DEPARTING}, "yàn"}, {{IN, DEPARTING}, "yìn"}, {{IANG, DEPARTING}, "yàng"}, {{ING, DEPARTING}, "yìng"},
	{{IAM, DEPARTING}, "yàm"}, {{IM, DEPARTING}, "yìm"},
	{{U_, DEPARTING}, "wù"}, {{UA, DEPARTING}, "wà"}, {{UO, DEPARTING}, "wò"},
	{{UAI, DEPARTING}, "wài"}, {{UEI, DEPARTING}, "wèi"}, {{UAN, DEPARTING}, "wàn"}, {{UN, DEPARTING}, "wèn"}, {{UANG, DEPARTING}, "wàng"}, {{ONG, DEPARTING}, "wèng"},
	{{IU_, DEPARTING}, "yù"}, {{IUO, DEPARTING}, "yuò"}, {{IUE, DEPARTING}, "yuè"}, {{IUAN, DEPARTING}, "yuàn"}, {{IUN, DEPARTING}, "yùn"}, {{IONG, DEPARTING}, "yòng"},

	{{I_, ENTERING}, "yih"}, {{IA, ENTERING}, "yah"}, {{IE, ENTERING}, "yeh"}, {{IO, ENTERING}, "yoh"},
	{{IAI, ENTERING}, "yaih"}, {{IAU, ENTERING}, "yaoh"}, {{IOU, ENTERING}, "youh"},
	{{U_, ENTERING}, "wuh"}, {{UA, ENTERING}, "wah"}, {{UO, ENTERING}, "woh"},
	{{UAI, ENTERING}, "waih"}, {{UEI, ENTERING}, "weih"},
	{{IU_, ENTERING}, "yuh"}, {{IUO, ENTERING}, "yuoh"}, {{IUE, ENTERING}, "yueh"},
} );

map<MSyl, cchar*> Pinyin::_mfTrans( {
	{{ZILCH , NEUTRAL}, ""},
	{{A_ , NEUTRAL}, "a"}, {{O_ , NEUTRAL}, "o"}, {{E_ , NEUTRAL}, "e"}, {{EH_ , NEUTRAL}, "ê"},
	{{Y_ , NEUTRAL}, "i"}, {{EL_ , NEUTRAL}, "er"},
	{{AI_ , NEUTRAL}, "ai"}, {{EI_ , NEUTRAL}, "ei"}, {{AU_ , NEUTRAL}, "ao"}, {{OU_ , NEUTRAL}, "ou"},
	{{AN_ , NEUTRAL}, "an"}, {{EN_ , NEUTRAL}, "en"}, {{ANG_ , NEUTRAL}, "ang"}, {{ENG_ , NEUTRAL}, "eng"},
	{{AM_ , NEUTRAL}, "am"}, {{EM_ , NEUTRAL}, "em"},
	{{I_ , NEUTRAL}, "i"}, {{IA , NEUTRAL}, "ia"}, {{IE , NEUTRAL}, "ie"}, {{IO , NEUTRAL}, "io"},
	{{IAI , NEUTRAL}, "iai"}, {{IAU , NEUTRAL}, "iao"}, {{IOU , NEUTRAL}, "iu"},
	{{IAN , NEUTRAL}, "ian"}, {{IN , NEUTRAL}, "in"}, {{IANG , NEUTRAL}, "iang"}, {{ING , NEUTRAL}, "ing"},
	{{IAM , NEUTRAL}, "iam"}, {{IM , NEUTRAL}, "im"},
	{{U_ , NEUTRAL}, "u"}, {{UA , NEUTRAL}, "ua"}, {{UO , NEUTRAL}, "uo"},
	{{UAI , NEUTRAL}, "uai"}, {{UEI , NEUTRAL}, "ui"}, {{UAN , NEUTRAL}, "uan"}, {{UN , NEUTRAL}, "un"},
	{{UEH , NEUTRAL}, "ue"},
	{{UANG , NEUTRAL}, "uang"}, {{ONG , NEUTRAL}, "ong"},
	{{IU_ , NEUTRAL}, "ü"}, {{IUO , NEUTRAL}, "üo"}, {{IUE , NEUTRAL}, "üe"},
	{{IUAN , NEUTRAL}, "üan"}, {{IUN , NEUTRAL}, "ün"}, {{IONG , NEUTRAL}, "iong"},

	{{ZILCH , DARK}, ""},
	{{A_ , DARK}, "ā"}, {{O_ , DARK}, "ō"}, {{E_ , DARK}, "ē"}, {{EH_ , DARK}, "êˉ"},
	{{Y_ , DARK}, "ī"}, {{EL_ , DARK}, "ēr"},
	{{AI_ , DARK}, "āi"}, {{EI_ , DARK}, "ēi"}, {{AU_ , DARK}, "āo"}, {{OU_ , DARK}, "ōu"},
	{{AN_ , DARK}, "ān"}, {{EN_ , DARK}, "ēn"}, {{ANG_ , DARK}, "āng"}, {{ENG_ , DARK}, "ēng"},
	{{AM_ , DARK}, "ām"}, {{EM_ , DARK}, "ēm"},
	{{I_ , DARK}, "ī"}, {{IA , DARK}, "iā"}, {{IE , DARK}, "iē"}, {{IO , DARK}, "iō"},
	{{IAI , DARK}, "iāi"}, {{IAU , DARK}, "iāo"}, {{IOU , DARK}, "iū"},
	{{IAN , DARK}, "iān"}, {{IN , DARK}, "īn"}, {{IANG , DARK}, "iāng"}, {{ING , DARK}, "īng"},
	{{IAM , DARK}, "iām"}, {{IM , DARK}, "īm"},
	{{U_ , DARK}, "ū"}, {{UA , DARK}, "uā"}, {{UO , DARK}, "uō"},
	{{UAI , DARK}, "uāi"}, {{UEI , DARK}, "uī"}, {{UAN , DARK}, "uān"}, {{UN , DARK}, "ūn"},
	{{UEH , DARK}, "uē"},
	{{UANG , DARK}, "uāng"}, {{ONG , DARK}, "ōng"},
	{{IU_ , DARK}, "ǖ"}, {{IUO , DARK}, "üō"}, {{IUE , DARK}, "üē"},
	{{IUAN , DARK}, "üān"}, {{IUN , DARK}, "ǖn"}, {{IONG , DARK}, "iōng"},

	{{A_ , LIGHT}, "á"}, {{O_ , LIGHT}, "ó"}, {{E_ , LIGHT}, "é"}, {{EH_ , LIGHT}, "êˊ"},
	{{Y_ , LIGHT}, "í"}, {{EL_ , LIGHT}, "ér"},
	{{AI_ , LIGHT}, "ái"}, {{EI_ , LIGHT}, "éi"}, {{AU_ , LIGHT}, "áo"}, {{OU_ , LIGHT}, "óu"},
	{{AN_ , LIGHT}, "án"}, {{EN_ , LIGHT}, "én"}, {{ANG_ , LIGHT}, "áng"}, {{ENG_ , LIGHT}, "éng"},
	{{AM_ , LIGHT}, "ám"}, {{EM_ , LIGHT}, "ém"},
	{{I_ , LIGHT}, "í"}, {{IA , LIGHT}, "iá"}, {{IE , LIGHT}, "ié"}, {{IO , LIGHT}, "ió"},
	{{IAI , LIGHT}, "iái"}, {{IAU , LIGHT}, "iáo"}, {{IOU , LIGHT}, "iú"},
	{{IAN , LIGHT}, "ián"}, {{IN , LIGHT}, "ín"}, {{IANG , LIGHT}, "iáng"}, {{ING , LIGHT}, "íng"},
	{{IAM , LIGHT}, "iám"}, {{IM , LIGHT}, "ím"},
	{{U_ , LIGHT}, "ú"}, {{UA , LIGHT}, "uá"}, {{UO , LIGHT}, "uó"},
	{{UAI , LIGHT}, "uái"}, {{UEI , LIGHT}, "uí"}, {{UAN , LIGHT}, "uán"}, {{UN , LIGHT}, "ún"},
	{{UEH , LIGHT}, "ué"},
	{{UANG , LIGHT}, "uáng"}, {{ONG , LIGHT}, "óng"},
	{{IU_ , LIGHT}, "ǘ"}, {{IUO , LIGHT}, "üó"}, {{IUE , LIGHT}, "üé"},
	{{IUAN , LIGHT}, "üán"}, {{IUN , LIGHT}, "ǘn"}, {{IONG , LIGHT}, "ióng"},

	{{A_ , RISING}, "ǎ"}, {{O_ , RISING}, "ǒ"}, {{E_ , RISING}, "ě"}, {{EH_ , RISING}, "êˇ"},
	{{Y_ , RISING}, "ǐ"}, {{EL_ , RISING}, "ěr"},
	{{AI_ , RISING}, "ǎi"}, {{EI_ , RISING}, "ěi"}, {{AU_ , RISING}, "ǎo"}, {{OU_ , RISING}, "ǒu"},
	{{AN_ , RISING}, "ǎn"}, {{EN_ , RISING}, "ěn"}, {{ANG_ , RISING}, "ǎng"}, {{ENG_ , RISING}, "ěng"},
	{{AM_ , RISING}, "ǎm"}, {{EM_ , RISING}, "ěm"},
	{{I_ , RISING}, "ǐ"}, {{IA , RISING}, "iǎ"}, {{IE , RISING}, "iě"}, {{IO , RISING}, "iǒ"},
	{{IAI , RISING}, "iǎi"}, {{IAU , RISING}, "iǎo"}, {{IOU , RISING}, "iǔ"},
	{{IAN , RISING}, "iǎn"}, {{IN , RISING}, "ǐn"}, {{IANG , RISING}, "iǎng"}, {{ING , RISING}, "ǐng"},
	{{IAM , RISING}, "iǎm"}, {{IM , RISING}, "ǐm"},
	{{U_ , RISING}, "ǔ"}, {{UA , RISING}, "uǎ"}, {{UO , RISING}, "uǒ"},
	{{UAI , RISING}, "uǎi"}, {{UEI , RISING}, "uǐ"}, {{UAN , RISING}, "uǎn"}, {{UN , RISING}, "ǔn"},
	{{UEH , RISING}, "uě"},
	{{UANG , RISING}, "uǎng"}, {{ONG , RISING}, "ǒng"},
	{{IU_ , RISING}, "ǚ"}, {{IUO , RISING}, "üǒ"}, {{IUE , RISING}, "üě"},
	{{IUAN , RISING}, "üǎn"}, {{IUN , RISING}, "ǚn"}, {{IONG , RISING}, "iǒng"},

	{{A_ , DEPARTING}, "à"}, {{O_ , DEPARTING}, "ò"}, {{E_ , DEPARTING}, "è"}, {{EH_ , DEPARTING}, "êˋ"},
	{{Y_ , DEPARTING}, "ì"}, {{EL_ , DEPARTING}, "èr"},
	{{AI_ , DEPARTING}, "ài"}, {{EI_ , DEPARTING}, "èi"}, {{AU_ , DEPARTING}, "ào"}, {{OU_ , DEPARTING}, "òu"},
	{{AN_ , DEPARTING}, "àn"}, {{EN_ , DEPARTING}, "èn"}, {{ANG_ , DEPARTING}, "àng"}, {{ENG_ , DEPARTING}, "èng"},
	{{AM_ , DEPARTING}, "àm"}, {{EM_ , DEPARTING}, "èm"},
	{{I_ , DEPARTING}, "ì"}, {{IA , DEPARTING}, "ià"}, {{IE , DEPARTING}, "iè"}, {{IO , DEPARTING}, "iò"},
	{{IAI , DEPARTING}, "iài"}, {{IAU , DEPARTING}, "iào"}, {{IOU , DEPARTING}, "iù"},
	{{IAN , DEPARTING}, "iàn"}, {{IN , DEPARTING}, "ìn"}, {{IANG , DEPARTING}, "iàng"}, {{ING , DEPARTING}, "ìng"},
	{{IAM , DEPARTING}, "iàm"}, {{IM , DEPARTING}, "ìm"},
	{{U_ , DEPARTING}, "ù"}, {{UA , DEPARTING}, "uà"}, {{UO , DEPARTING}, "uò"},
	{{UAI , DEPARTING}, "uài"}, {{UEI , DEPARTING}, "uì"}, {{UAN , DEPARTING}, "uàn"}, {{UN , DEPARTING}, "ùn"},
	{{UEH , DEPARTING}, "uè"},
	{{UANG , DEPARTING}, "uàng"}, {{ONG , DEPARTING}, "òng"},
	{{IU_ , DEPARTING}, "ǜ"}, {{IUO , DEPARTING}, "üò"}, {{IUE , DEPARTING}, "üè"},
	{{IUAN , DEPARTING}, "üàn"}, {{IUN , DEPARTING}, "ǜn"}, {{IONG , DEPARTING}, "iòng"},

	{{A_ , ENTERING}, "ah"}, {{O_ , ENTERING}, "oh"}, {{E_ , ENTERING}, "eh"}, {{EH_ , ENTERING}, "êh"},
	{{Y_ , ENTERING}, "ih"},
	{{AI_ , ENTERING}, "aih"}, {{EI_ , ENTERING}, "eih"}, {{AU_ , ENTERING}, "aoh"}, {{OU_ , ENTERING}, "ouh"},
	{{I_ , ENTERING}, "ih"}, {{IA , ENTERING}, "iah"}, {{IE , ENTERING}, "ieh"}, {{IO , ENTERING}, "ioh"},
	{{IAU , ENTERING}, "iaoh"}, {{IOU , ENTERING}, "iuh"},
	{{U_ , ENTERING}, "uh"}, {{UA , ENTERING}, "uah"}, {{UO , ENTERING}, "uoh"},
	{{UAI , ENTERING}, "uaih"}, {{UEI , ENTERING}, "uih"},
	{{UEH , ENTERING}, "ueh"},
	{{IU_ , ENTERING}, "üh"}, {{IUO , ENTERING}, "üoh"}, {{IUE , ENTERING}, "üeh"}

} );
}//end cphonetic
