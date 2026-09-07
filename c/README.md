# JSON Parser / C

## 機能
- パーサ
- ジェネレータ
- アクセサ

## 備考
- 42 のコーディング規約 norminetteに準拠
- UTF-16による文字列リテラルは現在非対応
- `t_json	*json_parse(const char *json_text)` は対処文字列のサイズを渡せないため、呼び出し側で対象がNULL終端文字列であることを保証してください
- [JSON Test Suit](https://github.com/nst/JSONTestSuite)を通過。(ただしn_multidigit_number_then_00.jsonを除く)

## テスト
- `make test` : `JSONTestSuite/test_parsing` を使ったパーサのaccept/rejectテスト
- `make test-generate` : `test_parsing/y_*.json` を対象に `parse → generate(_unformatted) → 再parse` のラウンドトリップが元の木構造と一致するか検証
- `make test-transform` : `JSONTestSuite/test_transform` を使った挙動確認。このディレクトリには「正解」のaccept/rejectが無いため、クラッシュしないことのみを合否判定に使い、各ファイルのaccept/reject・ラウンドトリップ結果は観察ログとして出力する
- `make test-all` : 上記3つをまとめて実行
- `make debug` の ASan/UBSan ビルドでも上記3スクリプトを実行し、メモリ安全性を確認済み

### test_transform で判明した既知の挙動
- `generate_number` は数値を `%.15g` で出力するため、int64の範囲外にあるような19桁の整数(`number_9223372036854775808.json` 等)はラウンドトリップで最下位桁が変化する(有効15桁までしか保持されない)
- `-0` は `generate` 時に整数分岐に入り符号を保持せず `0` として出力される(IEEE754の `-0.0 == 0.0` により値としては等価)
- 重複キーを持つオブジェクト(`object_same_key_*.json`)や不正なUnicodeコードポイントを含む文字列は、いずれもクラッシュせずラウンドトリップも安定している

## 参考
- [Davegamble/cjson](https://github.com/Davegamble/cjson)
