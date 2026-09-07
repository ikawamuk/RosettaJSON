# JSON Parser / C

## 機能
- パーサ
- ジェネレータ
- アクセサ

## 備考
- 42 のコーディング規約 norminetteに準拠
- `t_json	*json_parse(const char *json_text)` は対処文字列のサイズを渡せないため、呼び出し側で対象がNULL終端文字列であることを保証してください
- [JSON Test Suit](https://github.com/nst/JSONTestSuite)を通過。(ただしn_multidigit_number_then_00.jsonを除く)

## 参考
- [Davegamble/cjson](https://github.com/Davegamble/cjson)
