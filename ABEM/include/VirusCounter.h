/*
 * =====================================================================================
 *
 *       Filename:  VirusCounter.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___VIRUS_COUNTER
#define ___VIRUS_COUNTER

#include "Function.h"

class Virus;

/*
 * =====================================================================================
 *        Class:  Virus
 *  Description:  エージェントのためのカウンター
 *                シングルトン
 * =====================================================================================
 */
class VirusCounter {
  public:

    /*-----------------------------------------------------------------------------
     *  カウンター
     *-----------------------------------------------------------------------------*/
    // 突然変異回数
    int countUpMutation();
    int getCountMutation() const { return count_mutation_; }
    void resetCountMutation() { count_mutation_ = 0; }
    // ウイルスの種類
    bool pushNewVirus( Virus& v );
    int hasDataOfVirus( const Virus& v );
    void resetVirusDataBase();
    int getVirusVariaty() const;
    int getNumVirus( int n ) { return virus_number_data_base_[n]; }
    void resetVirusNumberDataBase() { virus_number_data_base_.clear(); }

    ITERATOR(Virus*) getVirusDataBaseIteratorBegin();
    ITERATOR(Virus*) getVirusDataBaseIteratorEnd();
    VECTOR(Virus *) &getVirusDataBase() { return virus_data_base_; }

    double calcAveValue();

    static VirusCounter& Instance();                                  /* インスタンスを返す */
    void reset();
  private:
    /*-----------------------------------------------------------------------------
     *  パラメータ
     *-----------------------------------------------------------------------------*/
    int count_mutation_;
    VECTOR( Virus * ) virus_data_base_;
    VECTOR( int ) virus_number_data_base_;

    VirusCounter();                                                  /* コンストラクタ */
};

#endif
