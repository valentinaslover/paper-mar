#include "romfont.h"
#include "memory.h"
#include <dolphin/os.h>

//.sbss
static romFontWork work;

//.sdata
static romFontWork* wp = &work;

//.rodata string, .sdata table
const char* msg_jp[10] = {
	/*"プログレッシブモードで表示しますか？"*/
	"\x83\x76\x83\x8D\x83\x4F\x83\x8C\x83\x62\x83\x56\x83\x75\x83\x82\x81\x5B\x83\x68\x82\xC5\x95\x5C\x8E\xA6\x82\xB5\x82\xDC\x82\xB7\x82\xA9\x81\x48",
	/*"は　い　　　　　　いいえ"*/
	"\x82\xCD\x81\x40\x82\xA2\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x82\xA2\x82\xA2\x82\xA6",
	/*"【　　　　】"*/
	"\x81\x79\x81\x40\x81\x40\x81\x40\x81\x40\x81\x7A",
	/*"画面表示モードはプログレッシブモードにセットされました。"*/
	"\x89\xE6\x96\xCA\x95\x5C\x8E\xA6\x83\x82\x81\x5B\x83\x68\x82\xCD\x83\x76\x83\x8D\x83\x4F\x83\x8C\x83\x62\x83\x56\x83\x75\x83\x82\x81\x5B\x83\x68\x82\xC9\x83\x5A\x83\x62\x83\x67\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\x81\x42",
	/*"画面表示モードはインターレースモードにセットされました。"*/
	"\x89\xE6\x96\xCA\x95\x5C\x8E\xA6\x83\x82\x81\x5B\x83\x68\x82\xCD\x83\x43\x83\x93\x83\x5E\x81\x5B\x83\x8C\x81\x5B\x83\x58\x83\x82\x81\x5B\x83\x68\x82\xC9\x83\x5A\x83\x62\x83\x67\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\x81\x42",
	/*"ディスクカバーが開いています。\n\nゲームを続ける場合は、\nディスクカバーを閉めてください。"*/
	"\x83\x66\x83\x42\x83\x58\x83\x4E\x83\x4A\x83\x6F\x81\x5B\x82\xAA\x8A\x4A\x82\xA2\x82\xC4\x82\xA2\x82\xDC\x82\xB7\x81\x42\x0A\x0A\x83\x51\x81\x5B\x83\x80\x82\xF0\x91\xB1\x82\xAF\x82\xE9\x8F\xEA\x8D\x87\x82\xCD\x81\x41\x0A\x83\x66\x83\x42\x83\x58\x83\x4E\x83\x4A\x83\x6F\x81\x5B\x82\xF0\x95\xC2\x82\xDF\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42",
	/*"ペーパーマリオＲＰＧの\nディスクをセットしてください。"*/
	"\x83\x79\x81\x5B\x83\x70\x81\x5B\x83\x7D\x83\x8A\x83\x49\x82\x71\x82\x6F\x82\x66\x82\xCC\x0A\x83\x66\x83\x42\x83\x58\x83\x4E\x82\xF0\x83\x5A\x83\x62\x83\x67\x82\xB5\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42",
	/*"ディスクを読めませんでした。\n\nくわしくは、本体の取扱説明書を\nお読みください。"*/
	"\x83\x66\x83\x42\x83\x58\x83\x4E\x82\xF0\x93\xC7\x82\xDF\x82\xDC\x82\xB9\x82\xF1\x82\xC5\x82\xB5\x82\xBD\x81\x42\x0A\x0A\x82\xAD\x82\xED\x82\xB5\x82\xAD\x82\xCD\x81\x41\x96\x7B\x91\xCC\x82\xCC\x8E\xE6\x88\xB5\x90\xE0\x96\xBE\x8F\x91\x82\xF0\x0A\x82\xA8\x93\xC7\x82\xDD\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42",
	/*"エラーが発生しました。\n\n本体のパワーボタンを押して電源をOFFにし、\n本体の取扱説明書の指示に従ってください。"*/
	"\x83\x47\x83\x89\x81\x5B\x82\xAA\x94\xAD\x90\xB6\x82\xB5\x82\xDC\x82\xB5\x82\xBD\x81\x42\x0A\x0A\x96\x7B\x91\xCC\x82\xCC\x83\x70\x83\x8F\x81\x5B\x83\x7B\x83\x5E\x83\x93\x82\xF0\x89\x9F\x82\xB5\x82\xC4\x93\x64\x8C\xB9\x82\xF0\x4F\x46\x46\x82\xC9\x82\xB5\x81\x41\x0A\x96\x7B\x91\xCC\x82\xCC\x8E\xE6\x88\xB5\x90\xE0\x96\xBE\x8F\x91\x82\xCC\x8E\x77\x8E\xA6\x82\xC9\x8F\x5D\x82\xC1\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42",
	NULL
};

const char* msg_en[9] = {
	"Would you like to display in progressive scan mode?",
	"Yes              N o",
	"[    ]",
	"Progressive scan mode has been turned on.",
	"Progressive scan mode has been turned off.",
	"The Disc Cover is open.\nIf you want to continue the game,\nplease close the Disc Cover.",
	"Please insert\nthe \"Paper Mario 2\" Game Disc.",
	"The Game Disc could not be read.\nPlease read the\nNintendo GameCube Instruction Booklet\nfor more information.",
	NULL
};

static const char** msg_tbl[2] = { msg_jp, msg_en };

//local prototypes
void romFontMake(void);

const char* romFontGetMessage(s32 msg) {
	return msg_tbl[0][msg]; //has eng but always returns JP
}

void romFontInit(void) {
	wp->field_0x0 = 0;
	wp->field_0x4 = 0;
	if (OSGetFontEncode() == OS_FONT_ENCODE_SJIS) {
		wp->mLanguage = 0;
	}
	else {
		wp->mLanguage = 1;
	}
	romFontMake();
}

void romFontMake(void) {

}





void romFontPrintGX(f32 x, f32 y, f32 scale, GXColor color, const char* msg) {

}


s32 romFontGetWidth(const char* message) {
	return 0;
}