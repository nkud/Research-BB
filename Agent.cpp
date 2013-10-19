/*
 * =====================================================================================
 *
 *       Filename:  Agent.cpp
 *
 *    Description:  
 *
 *         Author:  Noaki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

const int TAG_LEN_A = 20;

#define FOR(i, m)	for(int (i)=0; (i)<(m); (i)++)			/* i: 0 ~ (m-1) */

class Agent
{
	private:
	public:
		Agent();
		int tag_[TAG_LEN_A];
};

Agent :: Agent()
{
	FOR(i, TAG_LEN_A)
	{
		tag_[i] = 0;
	}
}
