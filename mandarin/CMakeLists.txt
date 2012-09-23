SET(mandarin_lib_src gworo.cxx 
	marked_pinyin.cxx 
	marked_pinyin_data.cxx
	bopomofo.cxx 
	mandarin.cxx 
	pinyin.cxx 
	pinyin_data.cxx
	)

add_library(mandarin ${mandarin_lib_src})
