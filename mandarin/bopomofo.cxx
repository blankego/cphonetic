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

namespace cphonetic
{
	// Bopomofo dictionaries
	TokenDict<MSyl::INIT> Bopomofo::_iDict  ({
		{"ㄅ",MSyl::B},{"ㄆ",MSyl::P},{"ㄇ",MSyl::M},{"ㄈ",MSyl::F},{"ㄪ",MSyl::V},
		{"ㄉ",MSyl::D},{"ㄊ",MSyl::T},{"ㄋ",MSyl::N},{"ㄌ",MSyl::L},
		{"ㄍ",MSyl::G},{"ㄎ",MSyl::K},{"ㄫ",MSyl::NG},{"ㄏ",MSyl::H},
		{"ㄐ",MSyl::G},{"ㄑ",MSyl::K},{"ㄬ",MSyl::NG},{"ㄒ",MSyl::H},
		{"ㄓ",MSyl::J},{"ㄔ",MSyl::CH},{"ㄕ",MSyl::SH},{"ㄖ",MSyl::R},
		{"ㄗ",MSyl::TZ},{"ㄘ",MSyl::TS},{"ㄙ",MSyl::S}});
	TokenDict<MSyl::MED> Bopomofo::_mDict ({{"ㄧ",MSyl::I},{"ㄨ",MSyl::U},{"ㄩ",MSyl::IU}});
	TokenDict<MSyl::FIN> Bopomofo::_fDict ({
		{"ㄚ",MSyl::A},{"ㄛ",MSyl::O},{"ㄜ",MSyl::E},{"ㄝ",MSyl::EH},{"ㄭ",MSyl::Y},{"ㄦ",MSyl::EL},
		{"ㄞ",MSyl::AI},{"ㄟ",MSyl::EI},{"ㄠ",MSyl::AU},{"ㄡ",MSyl::OU},
		{"ㄢ",MSyl::AN},{"ㄣ",MSyl::EN},{"ㄤ",MSyl::ANG},{"ㄥ",MSyl::ENG},{"ㆰ",MSyl::AM},{"ㆬ",MSyl::EM}
		
	});
	TokenDict<MSyl::TONE> Bopomofo::_tDict ({
		{"ˉ",MSyl::DARK},{"ˊ",MSyl::LIGHT},{"ˇ",MSyl::RISING},{"ˋ",MSyl::DEPARTING},
		{"·",MSyl::ENTERING},{"˙",MSyl::NEUTRAL},{"",MSyl::DARK},
		
	});
	
	map<MSyl::INIT,cchar*> Bopomofo::_iTrans = {
		{MSyl::Void,""},
		{MSyl::B,"ㄅ"},{MSyl::P,"ㄆ"},{MSyl::M,"ㄇ"},{MSyl::F,"ㄈ"},{MSyl::V,"ㄪ"},
		{MSyl::D,"ㄉ"},{MSyl::T,"ㄊ"},{MSyl::N,"ㄋ"},{MSyl::L,"ㄌ"},
		{MSyl::G,"ㄍ"},{MSyl::K,"ㄎ"},{MSyl::NG,"ㄫ"},{MSyl::H,"ㄏ"},
		{MSyl::J,"ㄓ"},{MSyl::CH,"ㄔ"},{MSyl::SH,"ㄕ"},{MSyl::R,"ㄖ"},
		{MSyl::TZ,"ㄗ"},{MSyl::TS,"ㄘ"},{MSyl::S,"ㄙ"}
		
	};
	
	map<MSyl::MED,cchar*> Bopomofo::_mTrans ={
		{MSyl::KAI,""},{MSyl::I,"ㄧ"},{MSyl::U,"ㄨ"},{MSyl::IU,"ㄩ"}
	};
	
	map<MSyl::FIN,cchar*> Bopomofo::_fTrans = {
		{MSyl::A,"ㄚ"},{MSyl::O,"ㄛ"},{MSyl::E,"ㄜ"},{MSyl::EH,"ㄝ"},{MSyl::Y,""},{MSyl::EL,"ㄦ"},
		{MSyl::AI,"ㄞ"},{MSyl::EI,"ㄟ"},{MSyl::AU,"ㄠ"},{MSyl::OU,"ㄡ"},
		{MSyl::AN,"ㄢ"},{MSyl::EN,"ㄣ"},{MSyl::ANG,"ㄤ"},{MSyl::ENG,"ㄥ"},{MSyl::AM,"ㆰ"},{MSyl::EM,"ㆬ"},
		{MSyl::ZERO,""},
		
	};
	map<MSyl::TONE,cchar*> Bopomofo::_tTrans = {
		{MSyl::DARK,""},{MSyl::LIGHT,"ˊ"},{MSyl::RISING,"ˇ"},{MSyl::DEPARTING,"ˋ"},
		{MSyl::ENTERING,"·"},{MSyl::NEUTRAL,"˙"}
	};
	map<MSyl::INIT,cchar*> Bopomofo::_giGrp = {
		{MSyl::G,"ㄐ"},{MSyl::K,"ㄑ"},{MSyl::NG,"ㄬ"},{MSyl::H,"ㄒ"}
	};
	//end Bopomofo dictionaries
	
	CRMaybe<MSyl> Bopomofo::munchSyl(cchar*& pStr) const
	{
		typedef typename MSyl::INIT INIT;
		typedef typename MSyl::MED MED;
		typedef typename MSyl::FIN FIN;
		typedef typename MSyl::TONE TONE;
		if(!pStr)return nullptr;
		auto init = _iDict.matchStart(pStr);
		auto med = _mDict.matchStart(pStr);
		auto fin = _fDict.matchStart(pStr);
		if(!init.hasValue && !med.hasValue && !fin.hasValue)return nullptr;
		if(med != MSyl::KAI && fin == MSyl::Y)//ㄧㄨㄩ as stand alone rimes
			fin = crmaybe(MSyl::ZERO);
		
		auto tone = _tDict.matchStart(pStr);
		return MSyl(init,med,fin,tone);
	}
	string Bopomofo::transliterate(const MSyl& syl)const
	{
		string bpmf;
		bpmf += (syl.isPalatized() && syl.group() == MSyl::GGRP )? _giGrp[syl.init()] : _iTrans[syl.init()];		
		bpmf += _mTrans[syl.med()];
		bpmf += _fTrans[syl.fin()];
		bpmf += _tTrans[syl.tone()];
		return bpmf;
	}
	
	const Bopomofo* const bopomofo = new Bopomofo;
	
}
