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

const int TAG_LEN_V = 3;                        /* ウイルスのタグの長さ */

class Virus                                     /* ウイルスのクラス*/
{
	private:
	public:
		Virus();                                /* コンストラクタ */
		int tag_[TAG_LEN_V];                     /* ウイルスのタグ */
};

Virus :: Virus()
{
	for(int i=0; i<TAG_LEN_V; i++)
	{
		tag_[i] = 0;                             /* 0で初期化 */
	}
}
