# JSON Parser / C

## 機能
### josn_parse
**Syntax**: `t_json *josn_parse(const char *json_text);`  
**Discription**: JSON文字列を解析し、t_jsonオブジェクト構造体を生成します。  
**Parameters**:
- `json_text`: 解析対象のJSON文字列
**Return Value**: 正常時は生成された `t_json` へのポインタ。失敗時は `NULL`  
**Example**:  
```c
t_json	*item;

item = josn_parse("{\"key\": [1, 2, 3]}");
if (!item)
	printf("error: %s\n", json_get_error_message(json_get_error_code()));
json_delete(item);
```
**Note**: 戻り値のメモリは不要になったら `json_delete()` で解放してください。解放の責任は呼び出し元にあります。  

### json_delete
**Syntax**: `void json_delete(t_json *item);`  
**Discription**: t_jsonオブジェクトとそれに含まれるすべての要素を再帰的に削除（メモリ解放）します。  
**Parameters**:  
- `item`: 解放する `t_json` オブジェクトへのポインタ
**Return Value**: なし  
**Example**:  
```c
t_json	*item;

item = josn_parse("[1, 2, 3]");
json_delete(item);
```
**Note**: `NULL` を渡した場合は何も行われません。  

### json_generate
**Syntax**: `char *json_generate(const t_json *item);`  
**Discription**: t_jsonオブジェクトを整形済み（インデント・改行あり）のJSON文字列に変換します。  
**Parameters**:  
- `item`: 変換対象の `t_json` オブジェクト  
**Return Value**: 生成されたJSON文字列へのポインタ（失敗時は `NULL`）  
**Example**:  
```c
t_json	*item;
char	*text;

item = josn_parse("{\"key\":[1,2,3]}");
text = json_generate(item);
printf("%s\n", text);
free(text);
json_delete(item);
```
**Note**: 戻り値の文字列バッファは呼び出し元で `free()` などによる解放が必要です。  

### json_generate_unformatted
**Syntax**: `char *json_generate_unformatted(const t_json *item);`  
**Discription**: t_jsonオブジェクトを非整形（改行・空白なしの軽量形式）のJSON文字列に変換します。  
**Parameters**:  
- `item`: 変換対象の `t_json` オブジェクト  
**Return Value**: 生成された圧縮JSON文字列へのポインタ（失敗時は `NULL`）  
**Example**:  
```c
t_json	*item;
char	*text;

item = josn_parse("{\n\t\"key\": [1, 2, 3]\n}");
text = json_generate_unformatted(item);
printf("%s\n", text);
free(text);
json_delete(item);
```
**Note**: 戻り値の文字列バッファは呼び出し元で `free()` などによる解放が必要です。ネットワーク転送等に適しています。  

### json_get_error_code
**Syntax**: `int json_get_error_code(void);`  
**Discription**: 最後に発生したJSON処理エラーのエラーコードを取得します。  
**Parameters**: なし  
**Return Value**: エラーコードを表す整数値（エラーがない場合は `0`）  
**Example**:  
```c
t_json	*item;
int		code;

item = josn_parse("{invalid}");
if (!item)
{
	code = json_get_error_code();
	printf("error code: %d\n", code);
}
```
**Note**: スレッドローカルなエラー状態を返す設計が推奨されます。  

### json_get_error_message
**Syntax**: `char *json_get_error_message(int error_code);`  
**Discription**: エラーコードに対応する人間が読める形式のエラーメッセージ文字列を取得します。  
**Parameters**:   
- `error_code`: `json_get_error_code()` で取得したエラーコード  
**Return Value**: エラー内容を示す文字列へのポインタ  
**Example**:  
```c
t_json	*item;

item = josn_parse("{invalid}");
if (!item)
	printf("error: %s\n", json_get_error_message(json_get_error_code()));
```
**Note**: 返される文字列は静的領域のものとし、呼び出し元で解放しないでください。  

### json_get_error_possision
**Syntax**: `size_t json_get_error_possision(void);` 
**Discription**: JSONパース失敗時、エラーが発生したバイトオフセット（位置）を取得します。  
**Parameters**: なし  
**Return Value**: 0始まりのエラー発生位置。エラーがない場合は `(size_t)-1`  
**Example**:  
```c
t_json	*item;
size_t	pos;

item = josn_parse("{invalid}");
if (!item)
{
	pos = json_get_error_possision();
	printf("error at byte %zu\n", pos);
}
```
**Note**: 先頭でエラーが起きた場合は `0` を返します。  

## 参考
- [Davegamble/cjson](https://github.com/Davegamble/cjson)
