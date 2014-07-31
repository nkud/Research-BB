#ifndef ___ABEM_FRAMEWORK
#define ___ABEM_FRAMEWORK

// コンフィグ
#include "Config.h"

// エージェント
#include "Agent.h"
#include "AgentManager.h"

// ウイルス
#include "VirusInterface.hpp"
#include "NormalVirus.hpp"
#include "VirusManager.h"

// 土地
#include "Landscape.h"

// ファイルファクトリー
#include "FileFactory.h"
// 期間
#include "Term.h"

// カウンター
#include "VirusCounter.h"
#include "AgentCounter.h"

// 関数群
#include "Function.h"

// ベンチマーク
#ifdef BENCHMARK
#include "Benchmark.h"
#endif

#endif
