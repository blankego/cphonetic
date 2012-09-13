#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mandarin_test
#include <boost/test/unit_test.hpp>
#include "mandarin.h"
#include "helper.h"
#include "tokendict.h"
#include "bopomofo.h"
#include <iostream>
#include <fstream>
#include <array>
using namespace cphonetic;
using namespace std;
BOOST_AUTO_TEST_CASE(maybe)
{
	int i = 42; 
	auto mb = crmaybe(i);
	BOOST_CHECK(mb.hasValue);
	BOOST_CHECK_EQUAL(42,mb.value);
	
	BOOST_CHECK(250==crmaybe(250));
	
	CRMaybe<int> mb1 = nullptr;
	bool b = mb1;
	BOOST_CHECK_EQUAL(false,b);
	
	
	const double& d = crmaybe(42.0);
	BOOST_CHECK_EQUAL(42,d);
}

BOOST_AUTO_TEST_CASE( msyl )
{
	MSyl juang4( MSyl::J, MSyl::U, MSyl::ANG, MSyl::DEPARTING );
	int size = sizeof( juang4 );
	auto init = juang4.init();
	auto med = juang4.med();
	auto fin = juang4.fin();
	auto tone = juang4.tone();
	auto rime = MSyl::RIME(med | fin);
	
	BOOST_CHECK_EQUAL( 2, size );
	BOOST_CHECK_EQUAL( MSyl::J, init );
	BOOST_CHECK_EQUAL( MSyl::U, med );
	BOOST_CHECK_EQUAL( MSyl::ANG, fin );
	BOOST_CHECK_EQUAL( MSyl::DEPARTING, tone );
	BOOST_CHECK_EQUAL( juang4.rime(),rime);
	
	MSyl j2 (MSyl::J,MSyl::U,MSyl::ANG,MSyl::DEPARTING);
	BOOST_CHECK(juang4==j2);
	j2.tone(MSyl::RISING);
	BOOST_CHECK(j2 < juang4);
	BOOST_CHECK_EQUAL(MSyl::RISING, j2.tone());
	j2.init(MSyl::G);
	BOOST_CHECK_EQUAL(MSyl::G, j2.init());
	j2.med(MSyl::KAI);
	BOOST_CHECK_EQUAL(MSyl::KAI , j2.med());
	j2.fin(MSyl::ENG);
	BOOST_CHECK_EQUAL(MSyl::ENG,j2.fin());
	j2.med(MSyl::U);
	BOOST_CHECK_EQUAL((MSyl::U|MSyl::ENG),j2.rime());
};

BOOST_AUTO_TEST_CASE( tokendict )
{
	TokenDict<cchar*> td ({
		{"b","b"},{"p","p"},{"m","m"},{"f","f"},{"v","v"},
		{"d","d"},{"t","t"},{"n","n"},{"l","l"},
		{"g","g"},{"k","k"},{"ng","ng"},{"h","h"},
		{"j","g"},{"q","k"},{"gn","gn"},{"x","h"},
		{"zh","j"},{"ch","ch"},{"sh","sh"},{"r","r"},
		{"z","tz"},{"c","ts"},{"s","s"},
		
	});
	TokenDict<cchar*> d2 ({{"","empty"},{"●","symbol"}});
	
	
	cchar* s = "gang";
	cchar* p = s;	
	BOOST_CHECK_EQUAL("empty",d2.matchStart(p).value);	
 	BOOST_CHECK_EQUAL(s,p);
	
 	BOOST_CHECK_EQUAL("g",td.matchStart(p).value);
	p = "b";
	BOOST_CHECK_EQUAL("b",td.matchStart(p).value);
	s= "012";
	p=s;
	BOOST_CHECK_EQUAL(false,td.matchStart(p).hasValue);
	BOOST_CHECK_EQUAL(s,p);
	s = "gnzc";
	p=s;
	
	BOOST_CHECK_EQUAL("gn",td.matchStart(p).value);	
	BOOST_CHECK_EQUAL("tz",td.matchStart(p).value);
	
	BOOST_CHECK_EQUAL("ts",td.matchStart(p).value);
	BOOST_CHECK(td.matchStart(p).hasValue == false);
	
}

BOOST_AUTO_TEST_CASE(bopomofo_test)
{
	cchar* s = "ㄓㄨㄤˋa", *p = s,*s0 = "ㄓㄨㄤˋ";
	
	auto syl =  Bopomofo().munchSyl(p);
	syl.value.toStr();
	BOOST_CHECK_EQUAL("a",p);
// 	cout << typeid(syl.value).name() <<endl;
	BOOST_CHECK_EQUAL(s0,syl.value.toStr());
	BOOST_CHECK_EQUAL(MSyl::JGRP,syl.value.group());
	cchar* s1 = "ㄐㄩㄢˇ";
	p = s1;
	auto syl1 = bopomofo->munchSyl(p);
	BOOST_CHECK_EQUAL(MSyl::GGRP,syl1.value.group());
	BOOST_CHECK(syl1.value.isPalatized());
	char line[50];
	vector<string>syls;
	fstream f("all_syllables.txt",ios_base::in);
	
	while(f.getline(line,50,'\n'))syls.push_back(string(line));
	//int i = 1;
	for(const string& s : syls)
	{
		//cout << i++ <<endl;
		cchar* p = &s[0];
		auto thesyl = bopomofo->munchSyl(p);
		if(!thesyl)cout << "wtf"<<","<<s<<endl;
		BOOST_CHECK_EQUAL(s,thesyl.value.toStr());
	}
	
	
}