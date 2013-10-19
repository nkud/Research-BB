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

#include "Global.h"

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
        tag_[i] = 0;                            /* 0で初期化 */
    }
}
