/*
 * =====================================================================================
 *
 *       Filename:  Virus.cpp
 *
 *    Description:  ウイルスのクラス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Global.h"

class Virus                                     /* ウイルスのクラス*/
{
	private:
	public:
		Virus();                                /* コンストラクタ */
		int tag_[TAG_LEN_V];                     /* ウイルスのタグ */
};

Virus :: Virus()
{
	FOR(i, TAG_LEN_V)
	{
		tag_[i] = 0;                             /* 0で初期化 */
	}
}
