/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 22:08:43 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/29 23:28:57 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

# include <stdbool.h>

typedef enum e_json_type
{
	Error,
	Null,
	Boolean,
	Number,
	String,
	Array,
	Object
}	t_json_type;

typedef struct s_json
{
	t_json_type		type;
	union u_json_data
	{
		void	*null_data;
		bool	bool_data;
		int		int_data;
		double	double_data;
		char	*string_data;
		struct s_json_array
		{
			struct s_json	*prev;
			struct s_json	*next;
			struct s_json	*element;
		}	array_data;
		struct s_json_object
		{
			struct s_json	*prev;
			struct s_json	*next;
			char			*key;
			struct s_json	*value;
		}	object_data;
	};
}	t_json;

/**
 * @brief JSON文字列を解析し、t_jsonオブジェクト構造体を生成します。
 * @param json_text 解析対象のJSON文字列
 * @return 正常時は生成された t_json へのポインタ。失敗時は NULL
 * @note 戻り値のメモリは不要になったら json_delete() で解放してください。解法の責任は呼び出し元にあります
 */
t_json	*josn_parse(const char *json_text);

/**
 * @brief t_jsonオブジェクトとそれに含まれるすべての要素を再帰的に削除（メモリ解放）します。
 * @param item 解放する t_json オブジェクトへのポインタ
 * @return なし
 * @note NULLを渡した場合は何も行われません。
 */
void	json_delete(t_json *item);

/**
 * @brief t_jsonオブジェクトを整形済み（インデント・改行あり）のJSON文字列に変換します。
 * @param item 変換対象の t_json オブジェクト
 * @return 生成されたJSON文字列へのポインタ（失敗時は NULL）
 * @note 戻り値の文字列バッファは呼び出し元で free() などによる解放が必要です。
 */
char	*json_generate(const t_json *item);

/**
 * @brief t_jsonオブジェクトを非整形（改行・空白なしの軽量形式）のJSON文字列に変換します。
 * @param item 変換対象の t_json オブジェクト
 * @return 生成された圧縮JSON文字列へのポインタ（失敗時は NULL）
 * @note 戻り値の文字列バッファは呼び出し元で free() などによる解放が必要です。ネットワーク転送等に適しています。
 */
char	*json_generate_unformatted(const t_json *item);

/**
 * @brief 最後に発生したJSON処理エラーのエラーコードを取得します。
 * @param _ なし
 * @return エラーコードを表す整数値（エラーがない場合は 0 ）
 * @note スレッドローカルなエラー状態を返す設計が推奨されます。
 */
int		json_get_error_code(void);

/**
 * @brief エラーコードに対応する人間が読める形式のエラーメッセージ文字列を取得します。
 * @param error_code json_get_error_code() で取得したエラーコード
 * @return エラー内容を示す文字列へのポインタ
 * @note 返される文字列は静的領域のものとし、呼び出し元で解放しないでください。
 */
char	*json_get_error_message(int error_code);

/**
 * @brief SONパース失敗時、エラーが発生したバイトオフセット（位置）を取得します。
 * @param _ なし
 * @return 0始まりのエラー発生位置。エラーがない場合は (size_t)-1
 * @note 先頭でエラーが起きた場合は 0 を返します。
 */
size_t	json_get_error_possision(void);

#endif
