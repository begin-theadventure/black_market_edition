#pragma once
#include "pch.h"
#include "SourceInterface.h"

class ConVar
{
public:

	void SetValueString(const char* szString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 12)(this, szString);
	}
	const char* GetString()
	{
		return *(const char**)((size_t)this + 72);
	}
	unsigned int GetInt()
	{
		return *(unsigned int*)((size_t)this + 92);
	}

	const char** GetStringPtr()
	{
		return (const char**)((size_t)this + 72);
	}
	unsigned int* GetIntPtr()
	{
		return (unsigned int*)((size_t)this + 92);
	}
	unsigned int& GetIntRef()
	{
		return *(unsigned int*)((size_t)this + 92);
	}
};

class ConVar2
{
	//unsigned char               unknown[0x60];
	unsigned char               unknown[0x90];
};

class ConVarRef
{
public:
	ConVar* cvar;
	ConVarRef(const char* name);
	~ConVarRef() = default;
	ConVar* operator->()
	{
		return cvar;
	}
};



//-----------------------------------------------------------------------------
// ConVar flags
//-----------------------------------------------------------------------------
// The default, no flags at all
#define FCVAR_NONE				0 

// Command to ConVars and ConCommands
// ConVar Systems
#define FCVAR_UNREGISTERED		(1<<0)	// If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY	(1<<1)	// Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
#define FCVAR_GAMEDLL			(1<<2)	// defined by the game DLL
#define FCVAR_CLIENTDLL			(1<<3)  // defined by the client DLL
#define FCVAR_HIDDEN			(1<<4)	// Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

// ConVar only
#define FCVAR_PROTECTED			(1<<5)  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
#define FCVAR_SPONLY			(1<<6)  // This cvar cannot be changed by clients connected to a multiplayer server.
#define	FCVAR_ARCHIVE			(1<<7)	// set to cause it to be saved to vars.rc
#define	FCVAR_NOTIFY			(1<<8)	// notifies players when changed
#define	FCVAR_USERINFO			(1<<9)	// changes the client's info string
#define FCVAR_CHEAT				(1<<14) // Only useable in singleplayer / debug / multiplayer & sv_cheats

#define FCVAR_PRINTABLEONLY		(1<<10)  // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED			(1<<11)  // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NEVER_AS_STRING	(1<<12)  // never try to print that cvar

// It's a ConVar that's shared between the client and the server.
// At signon, the values of all such ConVars are sent from the server to the client (skipped for local
//  client, of course )
// If a change is requested it must come from the console (i.e., no remote client changes)
// If a value is changed while a server is active, it's replicated to all connected clients
#define FCVAR_REPLICATED		(1<<13)	// server setting enforced on clients, TODO rename to FCAR_SERVER at some time
#define FCVAR_DEMO				(1<<16)  // record this cvar when starting a demo file
#define FCVAR_DONTRECORD		(1<<17)  // don't record these command in demofiles

#define FCVAR_NOT_CONNECTED		(1<<22)	// cvar cannot be changed by a client that is connected to a server

#define FCVAR_ARCHIVE_XBOX		(1<<24) // cvar written to config.cfg on the Xbox

#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)// the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)// If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)	// IVEngineClient::ClientCmd is allowed to execute this command. 
											// Note: IVEngineClient::ClientCmd_Unrestricted can run any client command.

// #define FCVAR_AVAILABLE			(1<<15)
// #define FCVAR_AVAILABLE			(1<<18)
// #define FCVAR_AVAILABLE			(1<<19)
// #define FCVAR_AVAILABLE			(1<<20)
// #define FCVAR_AVAILABLE			(1<<21)
// #define FCVAR_AVAILABLE			(1<<23)
// #define FCVAR_AVAILABLE			(1<<25)
// #define FCVAR_AVAILABLE			(1<<26)
// #define FCVAR_AVAILABLE			(1<<27)
// #define FCVAR_AVAILABLE			(1<<31)
