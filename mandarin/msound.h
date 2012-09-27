#ifndef MSOUND_H
#define MSOUND_H
#include "shortnames.h"

namespace cphonetic
{
namespace msound
{
	

enum INIT:
uchar
{
    Void = 0,
    B = 1, 	P, M, 	F, 		V,
    D = 7, 	T, N, 	L = 11,
    G = 13, K, NG, 	H,
    J = 19, CH,   	SH = 22, R = 23,
    TZ = 25, TS,    	S = 28,
};
enum INITGROUP:
uchar
{
    _GRP = 0,
    BGRP, DGRP, GGRP, JGRP, TZGRP,
};
enum TONE:
uchar
{
    DARK = 0,
    LIGHT = 0b00100000,
    RISING = 0b01000000,
    DEPARTING = 0b01100000,
    ENTERING = 0b10000000,
    NEUTRAL = 0b10100000,
};

enum MED:
uchar
{
    KAI = 0, I = 0b01000000, U = 0b10000000, IU = 0b11000000, MMAGIC = 255,
};

enum FIN:
uchar
{
    ZERO = 0,
    A = 1, O, E, EH, Y, EL,
    AI = 11, EI = 13,
    AU = 21, OU = 23,
    AN = 31, EN = 33,
    ANG = 41, ENG = 43,
    AM = 51, EM = 53,
};

enum RIME:
uchar
{
    ZILCH = ZERO,
    A_ = A, O_ = O, E_ = E, EH_ = EH, Y_ =  Y, EL_ = EL, AI_ = AI, EI_ = EI, AU_ = AU, OU_ = OU,
    AN_ = AN, EN_ = EN, ANG_ = ANG, ENG_ = ENG, AM_ = AM, EM_ = EM,
    I_ = I, IA = I | A, IE = I | EH, IO = I | O, IAI = I | AI, IAU = I | AU, IOU = I | OU,
    IAN = I | AN, IN = I | EN, IANG = I | ANG, ING = I | ENG, IAM = I | AM, IM = I | EM,
    U_ = U, UA = U | A, UO = U | O, UAI = U | AI, UEI = U | EI, UAN = U | AN, UN = U | EN,
    UANG = U | ANG, ONG = U | ENG, UEH = U | EH,//This is only for pinyin transcription
    IU_ = IU, IUO = IU | O, IUE = IU | EH, IUAN = IU | AN, IUN = IU | EN, IONG = IU | ENG,
};


}//end msound
}//end cphonetic

#endif //MSOUND_H
