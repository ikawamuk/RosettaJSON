# JSON Parser / C

## 機能
- パーサ
- ジェネレータ
- アクセサ

## 備考
- 42 のコーディング規約 norminetteに準拠
- UTF-16による文字列リテラルは現在非対応
- `t_json	*json_parse(const char *json_text)` は対処文字列のサイズを渡せないため、呼び出し側で対象がNULL終端文字列であることを保証してください

## 参考
- [Davegamble/cjson](https://github.com/Davegamble/cjson)
