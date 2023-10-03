#pragma once

#include <txt>
#include <wtxt>

inline txt fishOutFileExt(const txt &fn)
{
	ui64 dot = NFND;
	for(ui64 i = ~fn - 1; i != UI64_MAX; --i)
	{
		if(fn[i] == '.')
		{
			dot = i;
			break;
		}
	}
	
	if(dot == NFND)
	{
		return txt();
	}
	
	ui64 sz = ~fn - dot;
	txt ext = sz;
	mcpy(ext, (const char *)fn + dot, sz);
	txtssz(ext, sz);
	
	return ext;
}

inline txt & fishOutFileExt(const txt &fn, txt &ext)
{
	ui64 dot = NFND;
	for(ui64 i = ~fn - 1; i != UI64_MAX; --i)
	{
		if(fn[i] == '.')
		{
			dot = i;
			break;
		}
	}
	
	if(dot == NFND)
	{
		txtclr(ext);
		return ext;
	}
	
	ui64 sz = ~fn - dot;
	ext = sz;
	mcpy(ext, (const char *)fn + dot, sz);
	txtssz(ext, sz);
	
	return ext;
}

inline wtxt fishOutFileExt(const wtxt &fn)
{
	ui64 dot = NFND;
	for(ui64 i = ~fn - 1; i != UI64_MAX; --i)
	{
		if(fn[i] == '.')
		{
			dot = i;
			break;
		}
	}
	
	if(dot == NFND)
	{
		return wtxt();
	}
	
	ui64 sz = ~fn - dot;
	wtxt ext = sz;
	mcpy(ext, (const wchar_t *)fn + dot, sz * sizeof(wchar_t));
	txtssz(ext, sz);
	
	return ext;
}

inline wtxt & fishOutFileExt(const wtxt &fn, wtxt &ext)
{
	ui64 dot = NFND;
	for(ui64 i = ~fn - 1; i != UI64_MAX; --i)
	{
		if(fn[i] == '.')
		{
			dot = i;
			break;
		}
	}
	
	if(dot == NFND)
	{
		txtclr(ext);
		return ext;
	}
	
	ui64 sz = ~fn - dot;
	ext = sz;
	mcpy(ext, (const wchar_t *)fn + dot, sz * sizeof(wchar_t));
	txtssz(ext, sz);
	
	return ext;
}

inline txt & removeLastDir(txt &dir)
{
	if(~dir == 2) // D: or C: or E: ...
	{
		txtclr(dir);
		return dir;
	}
	else if(dir == empty)
	{
		return dir;
	}
	
	txtd(dir, txtfe(dir, TEND, '\\'), TEND);
	return dir;
}

inline wtxt & removeLastDir(wtxt &dir)
{
	if(~dir == 2) // D: or C: or E: ...
	{
		txtclr(dir);
		return dir;
	}
	else if(dir == empty)
	{
		return dir;
	}
	
	txtd(dir, txtfe(dir, TEND, '\\'), TEND);
	return dir;
}

inline txt & nameFromPath(const txt &path, txt &n)
{
	return txts(n, path, txtfe(path, TEND, '\\')+1, TEND);
}

inline wtxt & nameFromPath(const wtxt &path, wtxt &n)
{
	return txts(n, path, txtfe(path, TEND, '\\')+1, TEND);
}