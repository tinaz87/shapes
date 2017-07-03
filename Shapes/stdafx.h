// stdafx.h : file di inclusione per file di inclusione di sistema standard
// o file di inclusione specifici del progetto utilizzati di frequente, ma
// modificati raramente
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Escludere gli elementi utilizzati di rado dalle intestazioni di Windows
// File di intestazione di Windows:
#include <windows.h>






#include <stdlib.h>
//#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Logger\Logger.h"
#include "Config\Configuration.h"


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>  

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif

#endif // DEBUG

using namespace logger;

// TODO: fare riferimento qui alle intestazioni aggiuntive richieste dal programma
