/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "bopomofo.h"
#include "mandarin.h"
#include "tokendict.h"
namespace cphonetic
{
using namespace msound;
// Bopomofo dictionaries
TokenDict<INIT> Bopomofo::_iDict( {
	{"ㄅ", B}, {"ㄆ", P}, {"ㄇ", M}, {"ㄈ", F}, {"ㄪ", V},
	{"ㄉ", D}, {"ㄊ", T}, {"ㄋ", N}, {"ㄌ", L},
	{"ㄍ", G}, {"ㄎ", K}, {"ㄫ", NG}, {"ㄏ", H},
	{"ㄐ", G}, {"ㄑ", K}, {"ㄬ", NG}, {"ㄒ", H},
	{"ㄓ", J}, {"ㄔ", CH}, {"ㄕ", SH}, {"ㄖ", R},
	{"ㄗ", TZ}, {"ㄘ", TS}, {"ㄙ", S}
});
TokenDict<MED> Bopomofo::_mDict( {{"ㄧ", I}, {"ㄨ", U}, {"ㄩ", IU}});
TokenDict<FIN> Bopomofo::_fDict( {
	{"ㄚ", A}, {"ㄛ", O}, {"ㄜ", E}, {"ㄝ", EH}, {"ㄭ", Y}, {"ㄦ", EL},
	{"ㄞ", AI}, {"ㄟ", EI}, {"ㄠ", AU}, {"ㄡ", OU},
	{"ㄢ", AN}, {"ㄣ", EN}, {"ㄤ", ANG}, {"ㄥ", ENG}, {"ㆰ", AM}, {"ㆬ", EM}

});
TokenDict<TONE> Bopomofo::_tDict( {
	{"ˉ", DARK}, {"ˊ", LIGHT}, {"ˇ", RISING}, {"ˋ", DEPARTING},
	{"·", ENTERING}, {"˙", NEUTRAL}, {"", DARK},

});

map<INIT, cchar*> Bopomofo::_iTrans = {
	{Void, ""},
	{B, "ㄅ"}, {P, "ㄆ"}, {M, "ㄇ"}, {F, "ㄈ"}, {V, "ㄪ"},
	{D, "ㄉ"}, {T, "ㄊ"}, {N, "ㄋ"}, {L, "ㄌ"},
	{G, "ㄍ"}, {K, "ㄎ"}, {NG, "ㄫ"}, {H, "ㄏ"},
	{J, "ㄓ"}, {CH, "ㄔ"}, {SH, "ㄕ"}, {R, "ㄖ"},
	{TZ, "ㄗ"}, {TS, "ㄘ"}, {S, "ㄙ"}

};

map<MED, cchar*> Bopomofo::_mTrans = {
	{KAI, ""}, {I, "ㄧ"}, {U, "ㄨ"}, {IU, "ㄩ"}
};

map<FIN, cchar*> Bopomofo::_fTrans = {
	{A, "ㄚ"}, {O, "ㄛ"}, {E, "ㄜ"}, {EH, "ㄝ"}, {Y, ""}, {EL, "ㄦ"},
	{AI, "ㄞ"}, {EI, "ㄟ"}, {AU, "ㄠ"}, {OU, "ㄡ"},
	{AN, "ㄢ"}, {EN, "ㄣ"}, {ANG, "ㄤ"}, {ENG, "ㄥ"}, {AM, "ㆰ"}, {EM, "ㆬ"},
	{ZERO, ""},

};
map<TONE, cchar*> Bopomofo::_tTrans = {
	{DARK, ""}, {LIGHT, "ˊ"}, {RISING, "ˇ"}, {DEPARTING, "ˋ"},
	{ENTERING, "·"}, {NEUTRAL, "˙"}
};
map<INIT, cchar*> Bopomofo::_giGrp = {
	{G, "ㄐ"}, {K, "ㄑ"}, {NG, "ㄬ"}, {H, "ㄒ"}
};
//end Bopomofo dictionaries

CRMaybe<MSyl> Bopomofo::munchSyl(cchar*& pStr) const
{

	if(!pStr)return nullptr;

	auto init = _iDict.matchStart(pStr);
	auto med = _mDict.matchStart(pStr);
	auto fin = _fDict.matchStart(pStr);

	if(!init.hasValue && !med.hasValue && !fin.hasValue)return nullptr;

	if(med != KAI && fin == Y)//ㄧㄨㄩ as stand alone rimes
		fin = crmaybe(ZERO);

	auto tone = _tDict.matchStart(pStr);
	return MSyl(init, med, fin, tone);
}
string Bopomofo::transcribe(const MSyl& syl)const
{
	string bpmf;
	bpmf += (syl.isPalatized() && syl.group() == GGRP) ? _giGrp[syl.init()] : _iTrans[syl.init()];
	bpmf += _mTrans[syl.med()];
	bpmf += _fTrans[syl.fin()];
	bpmf += _tTrans[syl.tone()];
	return bpmf;
}

const Bopomofo bopomofo;

}
