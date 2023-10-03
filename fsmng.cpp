//
#include <stdp>
#include <ui64a>
#include <math>
#include <fnmanip.h>

//#define HEAP_MULTI_THREAD_MODE

// TODO GROUP FOLDERS TOGETHER
// TODO WHEN CTRL+SHIFT -> PROGLEM! CRTL+SHIFT CAN CHANGE LANGUAGE, CHECK IF IT DOES THEN MB ONLY CTRL WILL ENABLE THE MODE OR SHIFT HOLD ENTER DRAWING MODE DISABLE DRAG AND DROP! JUST DRAGGIN MOUSE WITH LMB PRESS SELECTS FILES LIKE A BRUSH! RMB TO DESELECT ERASE SELECTION
// TODO ADVANCED RENAMING OF MULTIPLE SELECTED FILES OR ALL FILES IN FOLDER/FOLDERS
// TODO SORTING FILEZ SMART NUMERIC\LEXICONUMERIC MB TEST ON WIN SHELL
// TODO SORTING BY EXTENTION (FILE TYPE), BUT WITHOUT SEPARATE TABLE COLUMN!
// TODO TRUNCATED FILE NAME DISPLAY ON LONG HOVER OR OTHER TRIGGER
// TODO FILE PROPERTIES INFO
// TODO https://stackoverflow.com/questions/61314541/how-do-i-list-all-file-names-of-a-zip-archive-in-c-from-scratch
// TODO IS IT WORTH TO DO DIRECTORY ENUMERATION ON OPENINGN FOLDER IN ANOTHER THREAD OR NOT? I THINK NOT!!! FOR SEARCH YES, BUT UI MUST NOT RESPOND DURING LOAD! https://devblogs.microsoft.com/oldnewthing/20131024-00/?p=2843
// TODO USE THIS FOR SUB CONTEXT MENU DISPLAY SystemParametersInfo and use SPI_GETMOUSEHOVERTIME to retrieve the default hover time-out.
// TODO PROGRESS BARS FOR LONG OPERATIONS
// TODO DRAG N DROP FROM SEPARATE PROCESSESS
// TODO FILES IN FOLDER COUNTER DISPLAY + SELECTION COUNT
// TODO INTEGRATE FSS INTO THE FSMNG TO SCAN SYSTEM/DISPLAY % OF SPACE USED, MENUBOX ENTRY 'CALC SIZE' FOR FOLDERS -> N/A SIZE CHANGE TO ACTUAL DIR SIZE
// TODO TABS
// TODO FILE RENAMING
// TODO UNDO ACTIONS
// TODO MOUNTED DRIVES POLLER THREAD IN DRIVES DISPLAY PANE MODE MAKE IT INTO SEPARATE WATCHER THREAD, ONLY ACTIVATE IT WHEN DRIVES DISPLAY ACTIVE!
// TODO MOUNTED DRIVES SHOW PERCENTAGE BAR OF FREE SPACE
// TODO WHEN WATCHED FOLDER CONTENT CHANGED SCROLL AUTOMATICALLY AND SELECT NEW CONTENT
// TODO C:\Users\ScienceDiscoverer\My Documents HIDDEN SYSTEM SYMLINK FILE CRUSH ON OPEN DISPLAY ERROR INSTEAD NO ACEESS
/* LIKELY REASON:
if(ffind == INVALID_HANDLE_VALUE)
{
	p|PE|" --> "|fnd_all|N|N;
	
	txtclr(fnd_all); <<<<<<<<<<<<<<<<<<<< !!!!!!!!!
	return;
}
IF ACCES WAS DENIED, [fnd_all] IS NOT CLEARED AND ALL THE NEXT SCANNING WILL ALWAYS FAIL, AS IT WILL ALSWAYS TRIGGER "FILE NOT EXISTS" ERROR WHICH WILL AGAIN NOT CLEAR [fnd_all] TEXT
AND THE RESULT OF THIS HUGE BUG IS A GIANT STRING OF ENDLESSLY CONCATENATED FILEPATHS!
*/
// TODO WHEN CURRENTLY OPENED DIRECTORY IS DELETED BY EXTERNAL PROGRAM, EVERYTHING BREAKS, NO FILE DISPLAY, ONLY CAN GO BACK TO DRIVES [RELATED TO HIDDEN+SYSTEM+SYMLINK FILES ACCESS BUG] SAME RESULT, PROBABLY RELATED
// TODO !!!!!!!!IMPORTANT!!!!!!!! DISABLE DRIVES DRAG N' DROP AND DELETE/COPY/MOVE !!!
// TODO [PARTIALLY DONE? WITHOUT UpdateWindow() THERE IS NO WHITE FLASHING ON UPDATE EVEN WITH 20 MS INTERVALS] PUT SOME KIND OF LIMIT ON THE FOLDER UPDATE FREQENCY EXAMPLE: LOGGER WRITES TO FILE IN A WATCHED FOLDER 1000 TIMES PER SECOND
// TODO DEVISE A WAY TO TRUNCATE BASE DIRECTORY TEXT FOR VERY LONG PATHS
// TODO MAKE DND CURSOR WITH HIGH DPI SUPPORT 32 48 64 BITS FROM SCRATCH WITHOUT USING STUPID REALWORLD CURSOR EDITOR
// TODO HARDLINK SPECIFIC COMMAND TO FIND AND SHOW LIST OF ALL OTHER LINKS POINTING TO THE SAME FILE GetFileInformationByHandle(f, &bhfi) ---> CHECK ENTIRE DRIVE FOR FILES WITH > 1 bhfi.nNumberOfLinks ---> compare (ui64)bhfi.nFileIndexHigh << 32 | (ui64)bhfi.nFileIndexLow) IF MATCHES, THIS IS LINK TO THE SAME FILE!
// TODO NATIVE ZIP SUPPORT THAT WILL FULLY SUPPORT HARDLINKS PACKING/UNPACKING! According to pkware.cachefly.net/webdocs/casestudies/APPNOTE.TXT, in the UNIX extra field, the variable length data field can contain information about "symbolic or hard links". This suggests that some implementations could support that.
// TODO IMPLEMENT .LNK FILES CREATION WITHOUT USING ANY SHELL INTERFACES! GENERATE .LNK FILE BYTE BY BYTE IF NECESSARY!
// TODO NATIVE MESSAGEBOXES FOR DELETE OPERATION AND ERROR MESSAGES!
// TODO SEARCH IMPLEMENT
// TODO FILTER FOLDER FILE NAMES (LOCAL SEARCH) IMPLEMENT
// TODO IF FOLDER WATCHER DETECT CHANGE AND RELOAD PANE, SAVE CURRENT SELECTION AND SCROLL POSITION, RESTORE!
// TODO EMPTY SPACE + BASE DIR RMB MENU BOX COMMAND OPEN CMD HERE
// TODO FILE UNLOCKER IF FILE IS LOCKED BY SOME UNKNOWN PROCESS FIND PROCESS WITH ABILITY TO KILL
// TODO FILE DUPLICATE FINDER USING QUICK HASHING + HARDLINK DETECTION
// TODO OPTIONAL ICON/IMGTHUMBS DISPLAY NOTE: IMGTHUMBS CAN BE POTENTIALLY SAVED INSIDE THE IMAGE ITSELF, IN EXIF OR OTHER METADATA TAGS!
// TODO ADD MENU BOX ENTRY IF ANY SELECTED FILE OR FOLDER CONTAINS HARDLINK/SYMLINKS OR WHEN SHIFT IS PRESSED + RMB [COPY PRESERVING LINKS] CopyFile() -> If the source file is a symbolic link, the actual file copied is the target of the symbolic link. If the destination file already exists and is a symbolic link, the target of the symbolic link is overwritten by the source file. ALSO DETECT IF SYMLINC IS RELATIVE OR ABSOLUTE. IF ABSOLUTE, REPLACE THE BASE PATH WITH COPY/MOVE TARGET, CREATING NEW ABSOLUTE LINK. IF LINK IS RELATIVE, JUST CREATE THE SAME LINK! Symbolic links can either be absolute or relative links. Absolute links are links that specify each portion of the path name; relative links are determined relative to where relative–link specifiers are in a specified path. Relative links are specified using the following conventions: Dot (. and ..) conventions—for example, "..\" resolves the path relative to the parent directory. Names with no slashes (\\)—for example, "tmp" resolves the path relative to the current directory. Root relative—for example, "\Windows\System32" resolves to "current drive:\Windows\System32" PROBLEM I CANNOT RESTORE ABSOLUTE LINK IF IT PONITS TO ANOTHER DRIVE. WHAT TO DO? COPY TARGET FILE INSTEAD?
// TODO WHEN RETURNING BACK DIR RESTORE PREVIOUS SELECTION AND SCROLL POSITION
// TODO MAKE POSSIBILITY TO CREATE NEW FOLDER BY COPYING NAME OF EXISTING FOLDER + _0 _1 _2 ETC.
// TODO AUTOMATICALLY CANCEL COPY/MOVE OPERATION IF TARGET IS SAME FOLDER
// TODO [OPTIONAL: DO I REALLY NEED THE OVERHEAD?] ADD MOUSE TRACKING TO UNHOVER WHEN MOUSE LEAVES WINDOW
// TODO SOMETIMES BASE DIR NAME IS PAINTED COLORED IN THE HARDLINK COLOR IF FOLDER CONTAINS HARDLINK
// TODO SQUISH VERY STELTHY BUG -> SOME FILES HAVE DIFFERENT BACKGROUND THAN THE DEFAULT 0C0C0C INSTEAD IT HAS 0D0D0D BUT IS NOT SELECTED AND/OR HOVERED MIGHT BE PROBLEM WITH UNICODE EMOTICON IN THE FILE NAME THE SIZE OF FILE ENTRY IS ALSO INCORRECT, SMALLER THEN REST. BUG SCREENSHOT bug\fsmng_0.png
// TODO IMPLEMENT SORTING ORDER LIST EXAMPLI GRATA FIRST SORT BY NAME -> SIZE -> DATE -> FILE TYPE ETC
// TODO COPYFILEEX -> LPPROGRESS_ROUTINE -> RETURN VALUE PROGRESS_STOP Stop the copy operation. It can be restarted at a later time -> CALL COPYFILEEX WITH SAME FNAMES TO RESUME

#pragma comment( lib, "user32" )
#pragma comment( lib, "gdi32" )

#define HW(x) (((unsigned int)x) >> 16)
#define LW(x) (((unsigned int)x) & 0xFFFF)
#define HWSIGN(x) ((int)(short)HW(x))
#define LWSIGN(x) ((int)(short)LW(x))
#define DPIS(x) ((ui64)((double)x * dpi_scale)) // Scale value for DPI

#define HOVERED			0x1
#define SELECTED		0x2
#define DRAGGED_OVER	0x4
#define IS_HARDLINK		0x8

#define FILE_HOVERED		(bools & HOVERED)
#define FILE_SELECTED		(bools & SELECTED)
#define FILE_DRAGGED_OVER	(bools & DRAGGED_OVER)
#define FILE_IS_HARDLINK	(bools & IS_HARDLINK)

#define FSMM_LFOLDER_CHANGED (WM_USER + 42)
#define FSMM_RFOLDER_CHANGED (WM_USER + 43)

struct Pane;

class File
{
public:
	File() = delete;
	File(const wtxt &fn, DWORD atrib, const FILETIME &mt, ui64 sz, ui64 i, Pane *pane);
	File(const wchar_t *fpath, ui64 i, Pane &pane);
	File(const File &o) = delete;
	File(File &&o) = delete;
	
	~File() = default;
	
	File & operator=(const File &o) = default;
	File & operator=(File &&o) = delete;
	File & operator=(const wchar_t *fpath);
	
	const wtxt & Name() const;
	const bool64 IsSelected() const;
	wtxt & FullPathIntoTxt(wtxt &t) const;
	
	void Hover();
	void UnHover();
	void Select(bool64 ctrl);
	void UnSelect();
	void ExecuteCommand(ui64 cmd, wtxt *targ);
	
	void Paint(HDC dc);
	
	void ComputeFullInfo(ui64 max_ns);
	void SetFullInfo(const wtxt &inf);
	void SetIndex(ui64 i);
	void SetHardlinkState();
	void ReleaseMemory();

private:
	void ConstructFromFpath(const wchar_t *fpath);
	void SetState(ui64 state);
	void ResetState(ui64 state);
	
private:
	ui32 attr;
	ui32 bools;
	ui64 mdate;
	ui64 size;
	wtxt name;
	wtxt full_info;
	i32 x;
	i32 y;
	ui64 idx;
	Pane *pn;
};

class Files : public darr
{
public:
	Files()
	{ 
		ts = 128;
		s = 0;
		d = (File *)Alloc(ts * sizeof(File));
		memset(d, 0, ts * sizeof(File)); // All texts invalidated
	}
	Files(const Files &o) = delete;

	~Files()
	{
		for(ui64 i = 0; i < s; ++i)
		{
			d[i].ReleaseMemory();
		}
		DARR_FREE(d);
	}

	File & operator[](ui64 i) { DARR_ASSERT_RANGE(i) return d[i]; }
	const File & operator[](ui64 i) const { DARR_ASSERT_RANGE(i) return d[i]; }

	Files & operator<<(const File &c)
	{
		ui64 ns = s + 1;
		if(ts < ns)
		{
			d = (File *)ReAlloc(d, ns, sizeof(File));
			memset(&d[s], 0, (ts - s) * sizeof(File)); // All new texts invalidated
		}

		d[s] = c;
		s = ns;

		return *this;
	}
	
	inline Files & Clear()
	{
		for(ui64 i = 0; i < s; ++i)
		{
			d[i].ReleaseMemory(); // Texts invalidated in ReleaseMemory()
		}
		
		s = 0;
		return *this;
	}

private:
	File *d;
};

struct Pane
{
	ui64 ch_msg;			// Change message ID for the folder pane
	wtxt bdir;				// Base directory path for the pane
	ui64a sel;				// Indices of all selected files in the folder pane
	ui64 phov_idx;			// Index of the last hovered file
	Files files;			// Files in the folder pane
	ui64 xl, xr, yt, yb;	// Coordinates of the folder pane
	ui64 top_idx;			// Top visible index of a pane's file
	ui64 max_files;			// Maximum amount of files that can fit into pane's height
	ui64 max_txt;			// Maximum text that will fit in current pane's width
	ui64 txtw;				// Width of the file text's line in pixels
	bool64 dnd;				// Draggin' n' Droppin' over the folder pane
	HANDLE watchtower;		// FindFirstChangeNotification handle
	HANDLE watcher;			// Handle to thread that is currently observing the folder pane
};

struct ExtentionExecutor
{
	wtxt ext;
	cwstr executor;
};

ExtentionExecutor execs[] = {
	{ WL(".txt.cpp.h.log.css.js"), WL("C:\\Program Files\\Notepad++\\notepad++.exe") },
	{ WL(".png.jpg.jpeg.gif.bmp.ico"), WL("C:\\Program Files\\IrfanView\\i_view64.exe") },
	{ WL(".mp4.mkv.avi.mov"), WL("C:\\Program Files\\MPC-HC\\mpc-hc64.exe") },
	{ WL(".zip.rar.7z"), WL("C:\\Program Files\\7-Zip\\7zFM.exe") },
	{ WL(".html.htm"), WL("C:\\Program Files\\Mozilla Firefox\\firefox.exe") },
	{ WL(""), WL("") }
};

cwstr no_ext_executor = WL("C:\\Program Files\\Notepad++\\notepad++.exe");

ExtentionExecutor editors[] = {
	{ WL(".txt.cpp.h.log.css.js.html.htm"), WL("C:\\Program Files\\Notepad++\\notepad++.exe") },
	{ WL(".png.jpg.jpeg.gif.bmp.ico"), WL("C:\\Program Files\\GIMP 2\\bin\\gimp-2.10.exe") },
	{ WL(".mp4.mkv.avi.mov"), WL("C:\\Program Files\\Adobe\\Adobe Premiere Pro 2020\\Adobe Premiere Pro.exe") },
	{ WL(""), WL("") }
};

cwstr default_editor = WL("C:\\Program Files\\Notepad++\\notepad++.exe");

#define CMD_OPEN		0
#define CMD_EDIT		1
#define CMD_SYMLINK		2
#define CMD_HARDLINK	3
#define CMD_RENAME		4
#define CMD_DELETE		5

cwstr commands[] = {
	WL("Open"),
	WL("Edit"),
	WL("Symlink"),
	WL("Hardlink"),
	WL("Rename"),
	WL("Delete")
};

// TODO ADD THIS COMMANDS:
// COPY
// COPY NAME
// COPY PATH

#define NO_HOVER UI64_MAX

class MenuBox
{
public:
	MenuBox();
	MenuBox(const MenuBox &o) = delete;
	MenuBox(MenuBox &&o) = delete;
	
	~MenuBox() = default;
	
	MenuBox & operator=(const MenuBox &o) = default; 
	MenuBox & operator=(MenuBox &&o) = delete;
	
	operator bool64();
	
	void Spawn(i64 x, i64 y, const ui64a &cmd_list, Pane *pane);
	void Hover(i64 y);
	void UnHover();
	void Press(i64 y);
	ui64 GetCommand();
	void Exterminate();
	
	Pane * GetPane() const;
	
	bool64 MouseInside(i64 x, i64 y);
	
	void Paint(HDC dc);
	
private:
	void Annihilate();
	
private:
	static const ui64 xpad;
	
private:
	ui64a cmds;	// Commands
	ui64 hi;	// Hover index
	bool64 prs;	// Pressed state
	i64 xl;		// X left
	i64 xr;		// X right
	i64 yt;		// Y top
	i64 yb;		// Y bottom
	Pane *pn;	// Pane where box was spawned
};

const ui64 MenuBox::xpad = 2;

HINSTANCE exec_adress;
ATOM main_class;
HWND main_wnd;

double dpi_scale;
HCURSOR dnd_cur;		// Drag n' Drop cursor
HCURSOR def_cur;
HCURSOR cur_cur;		// Current cursor
HFONT def_font;
HPEN def_pen;
HPEN dnd_pen;			// Drag n' Drop pen
HBRUSH def_back_brush;
HBRUSH sel_back_brush;
HBRUSH scr_back_brush;	// Scroll bar's background brush
HDC main_dc;

RECT work_pix;
UINT mwheel_scroll_ln, mwheel_scroll_ch; // System values for mouse wheel scrolling

ui64 cellw = 8;
ui64 cellh = 16;

ui64 clw, clh; // Client area width/height

i64 dnd_ignore_pix;		// Mouse must move at least this much pixels to initiate Drag n' Drop
i64 dnd_lcx, dnd_lcy;	// Position of last left mouse button click
Pane *dnd_orig_pane;	// Folder pane where Drag n' Drop was initiated (NULL -> no DnD)
Pane *dnd_targ_pane;	// Folder pane where the file/files where dropped
wtxt dnd_target;		// Target where file/files where dropped
File *dnd_targ_file;	// Pointer to file where DnD dropped something


const COLORREF def_back = 0x0C0C0C; // 0x00BBGGRR
const COLORREF hov_back = 0x1C1C1C;
const COLORREF sel_back = 0x4C4C4C;

const COLORREF def_front = 0xCCCCCC;

ui64 fold_pad_x = 4, fold_pad_y = 3; // Folder padding for the frame mesured in cells

Pane lp = { FSMM_LFOLDER_CHANGED, MAX_PATH, ui64a(1024), NFND };
Pane rp = { FSMM_RFOLDER_CHANGED, MAX_PATH, ui64a(1024), NFND };

MenuBox mbox;

// Left/Right panes specific variables  ------------------------------------------------------------------------------

//Files lfiles, rfiles;							// Files in a left/right folder pane
//
//ui64 lfold_xl, lfold_xr, lfold_yt, lfold_yb;	// Coordinates of left folder pane
//ui64 rfold_xl, rfold_xr, rfold_yt, rfold_yb;	// Coordinates of right folder pane
//
//ui64 lf_top_idx, rf_top_idx;					// Left/Right folder top visible index
//
//ui64 fmax_files;								// Maximum amount of files in current folder pane height
//ui64 lfmax_str, rfmax_str;						// Maximum string that will fit in current left/right pane width
//ui64 lfinf_pw, rfinf_pw;						// Width of right/left files' info entries in pixels
//
//ui64 lpast_hov_idx, rpast_hov_idx;				// Index of last hovered file
//
//ui64a lsel = 1024, rsel = 1024;					// Indices of all selected files in left/right folder panes
//
//bool64 dnd_lfold, dnd_rfold;	// Draggin' n' Droppin' over the left/right folder pane
//
//wtxt lb_dir = MAX_PATH, rb_dir = MAX_PATH;		// Base directory path for left/right panes
//
//
//HANDLE left_watchtower, right_watchtower;
//HANDLE left_watcher, right_watcher;

// Left/Right panes specific variables -------------------------------------------------------------------------------

inline bool64 pcoll(POINT pnt, const RECT &rc) // Check if POINT collides with RECT
{
	return pnt.x >= rc.left && pnt.y >= rc.top && pnt.x <= rc.right && pnt.y <= rc.bottom;
}

inline bool64 pcoll(i64 x, i64 y, const RECT &rc) // Check if POINT collides with RECT
{
	return x >= rc.left && y >= rc.top && x <= rc.right && y <= rc.bottom;
}

inline bool64 pcoll(POINT pnt, const Pane &pn)
{
	return pnt.x >= (i64)pn.xl && pnt.y >= (i64)pn.yt && pnt.x <= (i64)pn.xr && pnt.y <= (i64)pn.yb;
}

inline bool64 pcoll(i64 x, i64 y, const Pane &pn)
{
	return x >= (i64)pn.xl && y >= (i64)pn.yt && x <= (i64)pn.xr && y <= (i64)pn.yb;
}

inline bool64 pcoll(i64 x, i64 y, i64 xl, i64 xr, i64 yt, i64 yb)
{
	return x >= xl && y >= yt && x <= xr && y <= yb;
}

inline bool64 pcoll(i64 x, i64 y, ui64 xl, ui64 xr, ui64 yt, ui64 yb)
{
	return x >= (i64)xl && y >= (i64)yt && x <= (i64)xr && y <= (i64)yb;
}

inline void unSelectAll(Pane *pn)
{
	if(~pn->sel == 0)
	{
		return;
	}
	
	for(ui64 i = 0; i < ~pn->sel; ++i)
	{
		pn->files[pn->sel[i]].UnSelect();
	}
	
	pn->sel.Clear();
}

inline wtxt errToWtxt(DWORD err)
{
	wchar_t buff[300];
	
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		err,
		0,
		buff,
		300,
		NULL);
	
	wtxt out = cwstr({ buff, strl(buff) });
	txtd(out, ~out-2, 2); // Remove pesky newline
	return out;
}

wtxt exec_ext = MAX_PATH;

void executeFile(wtxt &fp, const wtxt &bdir, bool64 edit_mode)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));
	
	cwstr exec = { NULL, 0 };
	
	fishOutFileExt(fp, exec_ext);
	
	if(edit_mode)
	{
		t2low(exec_ext);
		ui64 i = 0;
		while(editors[i].ext != empty)
		{
			if(txtf(editors[i].ext, 0, exec_ext) != NFND)
			{
				exec = editors[i].executor;
				break;
			}
			++i;
		}
		
		if(exec.t == NULL)
		{
			exec = default_editor;
		}
	}
	else
	{
		if(exec_ext == empty)
		{
			exec = no_ext_executor;
		}
		else
		{
			t2low(exec_ext);
			
			if(exec_ext == WL(".exe"))
			{
				goto skip_exec_search;
			}
			
			ui64 i = 0;
			while(execs[i].ext != empty)
			{
				if(txtf(execs[i].ext, 0, exec_ext) != NFND)
				{
					exec = execs[i].executor;
					break;
				}
				++i;
			}
		}
	}
	
	if(exec.t != NULL)
	{
		txti(fp, 0, WL(" \""));
		fp += '"';
		txti(fp, 0, exec);
		txti(fp, exec.s, '"');
		txti(fp, 0, '"');
	}
	
skip_exec_search:
	
	// Create Process ============================================================================
	BOOL res = CreateProcess(
		exec.t,				//  [I|O]  Name of the module to be executed, that's it
		fp,					// [IO|O]  Command line to be exectued, searches PATH, adds extention
		NULL,				//  [I|O]  Sec. Attrib. for inhereting new process by child processes
		NULL,				//  [I|O]  Sec. Attrib. for inhereting new thread by child processes
		FALSE,				//    [I]  New proc. inherits each inheritable handle
		0,					//    [I]  Process creation flags
		NULL,				//  [I|O]  Ptr to environment block of new process (inherit if NULL)
		bdir,				//  [I|O]  Full path to current directory for the process
		&si,				//    [I]  Ptr to STARTUPINFO struct, if dwFlags = 0, def. values used
		&pi);				//    [O]  Ptr to PROCESS_INFORMATION struct with new proc identification info
	// ===========================================================================================
	
	if(res)
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		DWORD e = GetLastError();
		MessageBoxW(main_wnd, fp + '\n' + 'E' + i2wt(e) + ' ' + errToWtxt(e), L"ERROR EXECUTING FILE", MB_OK | MB_ICONSTOP);
	}
}

//cwstr file_time_base = WL("00.00.00 00:00");
wtxt file_time_text = WL("00.00.00 00:00");

inline const wtxt & fileTimeToWtxt(ui64 time)
{
	SYSTEMTIME fst;
	FILETIME tloc;
	FileTimeToLocalFileTime((FILETIME *)&time, &tloc);
	FileTimeToSystemTime(&tloc, &fst);
	
	// Unroll dat loop!
	
	file_time_text[1] = (wchar_t)(fst.wYear % 10 | 0x30);
	fst.wYear /= 10;
	file_time_text[0] = (wchar_t)(fst.wYear % 10 | 0x30);
	
	file_time_text[4] = (wchar_t)(fst.wMonth % 10 | 0x30);
	fst.wMonth /= 10;
	file_time_text[3] = (wchar_t)(fst.wMonth % 10 | 0x30);
	
	file_time_text[7] = (wchar_t)(fst.wDay % 10 | 0x30);
	fst.wDay /= 10;
	file_time_text[6] = (wchar_t)(fst.wDay % 10 | 0x30);
	
	file_time_text[10] = (wchar_t)(fst.wHour % 10 | 0x30);
	fst.wHour /= 10;
	file_time_text[9] = (wchar_t)(fst.wHour % 10 | 0x30);
	
	file_time_text[13] = (wchar_t)(fst.wMinute % 10 | 0x30);
	fst.wMinute /= 10;
	file_time_text[12] = (wchar_t)(fst.wMinute % 10 | 0x30);
	
	return file_time_text;
}

wtxt file_size_text = 15;
wtxt size_text = 15;

inline const wtxt & fileSizeToWtxt(ui64 sz)
{
	wchar_t suffix;
	file_size_text = WL("     ");
	
	if(sz < 1'024) // Bytes
	{
		suffix = ' ';
	}
	else if(sz < 1'048'576) // Kilobytes
	{
		suffix = 'K';
		sz /= 1'024;
	}
	else if(sz < 1'073'741'824) // Megabytes
	{
		suffix = 'M';
		sz /= 1'048'576;
	}
	else if(sz < 1'099'511'627'776) // Gigabytes
	{
		suffix = 'G';
		sz /= 1'073'741'824;
	}
	else if(sz < 1'125'899'906'842'624) // Terabytes
	{
		suffix = 'T';
		sz /= 1'099'511'627'776;
	}
	else
	{
		file_size_text = WL("2BIG!");
		return file_size_text;
	}
	
	i2t(sz, size_text);
	size_text += suffix;
	txto(file_size_text, 0, size_text);
	
	return file_size_text;
}

wtxt trunced_fname = MAX_PATH;
wtxt trunced_fext = MAX_PATH;

const wtxt & truncFileName(const wtxt &fn, ui64 fn_max)
{
	if(~fn < fn_max) // Add padding
	{
		trunced_fname = fn;
		for(ui64 i = ~fn; i < fn_max; ++i)
		{
			trunced_fname[i] = ' ';
		}
		trunced_fname[fn_max] = 0;
		txtssz(trunced_fname, fn_max);
		return trunced_fname;
	}
	
	if(~fn == fn_max) // Do nothing
	{
		return fn;
	}
	
	// Star symbol will mean that file name is truncated, example:
	// baka_sete_no_kara.txt
	// baka_set*.txt
	
	fishOutFileExt(fn, trunced_fext);
	if(~trunced_fext >= fn_max) // Extention is too big, trunc it
	{
		trunced_fname = fn;
		txtd(trunced_fname, fn_max-1, TEND);
		trunced_fname += '*';
		return trunced_fname;
	}
	
	ui64 fn_inc = fn_max - ~trunced_fext - 1; // Number of characters still included in the file name
	txts(trunced_fname, fn, 0, fn_inc);
	trunced_fname += '*', trunced_fname += trunced_fext;
	
	return trunced_fname;
}

wtxt sl_dots = MAX_PATH;

inline void absToRelPath(const wtxt &link, wtxt &targ)
{
	ui64 msz = MIN(~link, ~targ);
	ui64 i = 0;
	
	// link D:\T\foo\bar\baz\baka\sete\text.txt
	// targ D:\T\foo\bar\boom\bg\text.txt
	//					  ^
	
	while(i < msz)
	{
		if(link[i] != targ[i])
		{
			break;
		}
		++i;
	}
	
	// link D:\T\foo\bar\baz\baka\sete\text.txt
	// targ D:\T\foo\bar\boom\bg\text.txt
	//					^
	
	ui64 base_ed = txtfe(link, i, '\\');
	
	txtclr(sl_dots);
	for(ui64 j = i; j < ~link; ++j)
	{
		if(link[j] == '\\')
		{
			sl_dots += WL("..\\");
		}
	}
	
	// link D:\T\foo\bar\baz\baka\sete\text.txt
	// targ ..\..\..\boom\bg\text.txt	
	
	txtrp(targ, 0, base_ed, sl_dots);
}

namespace scan_FUNC { // Global Local Variables TM
wtxt star = WL("\\*");
wtxt fnd_all = MAX_PATH;
wtxt full_path = MAX_PATH;
wtxt fn; }
wtxt ffull_inf = 1023;

void scan(Pane *pn, const wtxt &dir)
{	
	using namespace scan_FUNC;
	HANDLE ffind;
	WIN32_FIND_DATAW fdata;
	BY_HANDLE_FILE_INFORMATION bhfi;
	ui64 idx = 0;
	
	fnd_all += dir, fnd_all += star;
	
	// Start files enumeration =================================================================
	ffind = FindFirstFileExW(
		fnd_all,					// [I] LPCSTR Full			dir + path
		FindExInfoBasic,			// [I] FINDEX_INFO_LEVELS	Search accuracy
		&fdata,						// [O] LPVOID				Ouput file data
		FindExSearchNameMatch,		// [I] FINDEX_SEARCH_OPS	Non wildcard filters
		NULL,						// [I] LPVOID				Must be NULL (no support)
		FIND_FIRST_EX_LARGE_FETCH);	// [I] DWORD				Additional search flags
	// =========================================================================================
	
	if(ffind == INVALID_HANDLE_VALUE)
	{
		p|PE|" In FindFirstFileExA!"|N;
		return;
	}

	do
	{
		txtsdt(fn, MAX_PATH, 0, fdata.cFileName); // Always set direct manipulated text back to 0!
		txtszu(fn);
		
		if((~fn == 1 && fn[0] == '.') || (~fn == 2 && fn[0] == '.' && fn[1] == '.'))
		{
			continue;
		}
		
		ui64 fsz = (ui64)fdata.nFileSizeHigh << 32 | (ui64)fdata.nFileSizeLow;
		File f = { fn, fdata.dwFileAttributes, fdata.ftLastWriteTime, fsz, idx++, pn };
		
		// Check if file is a HARDLINK
		full_path = dir;
		full_path += '\\', full_path += fn;
		// Create or open File or Device =================================================================
		HANDLE fh = CreateFile(
		full_path,						//   [I]  Name of the file or device to create/open
		FILE_READ_ATTRIBUTES,			//   [I]  Requested access GENERIC_READ|GENERIC_WRITE|0
		0,								//   [I]  Sharing mode FILE_SHARE_READ|WRITE|DELETE|0
		NULL,							// [I|O]  SECURITY_ATTRIBUTES for file, handle inheritability
		OPEN_EXISTING,					//   [I]  Action to take if file/device exist or not
		FILE_FLAG_OPEN_REPARSE_POINT,	//   [I]  Attributes and flags for file/device
		NULL);							// [I|O]  Handle to template file to copy attributes from
		// ===============================================================================================
		GetFileInformationByHandle(fh, &bhfi);
		CloseHandle(fh);
		if(!(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && bhfi.nNumberOfLinks > 1)
		{
			f.SetHardlinkState();
		}
		
		pn->files << f;
	}
	while(FindNextFileW(ffind, &fdata));
	FindClose(ffind);
	
	ui64 max_fn = pn->max_txt - 23; // __XX.XX.XX XX:XX__XXXXY --> 23 CHARS
	
	if(~pn->files > pn->max_files) // Account for scrollbar
	{
		--max_fn;
	}
	
	ui64 max_fold_fn = 0;
	for(ui64 i = 0; i < ~pn->files; ++i)
	{
		if(~pn->files[i].Name() > max_fold_fn)
		{
			max_fold_fn = ~pn->files[i].Name();
		}
	}
	
	if(max_fold_fn < max_fn)
	{
		max_fn = max_fold_fn;
	}
	
	pn->txtw = (max_fn + 23) * cellw;
	
	for(ui64 i = 0; i < ~pn->files; ++i)
	{
		pn->files[i].ComputeFullInfo(max_fn);
	}
	
	txtclr(fnd_all);
	txtsdt(fn, 0, 0, NULL); // Directly manipulated text set back to 0 before it goes out of scope
}

inline void invalidatePane(Pane *pn)
{
	RECT rc = { (LONG)pn->xl, (LONG)pn->yt, (LONG)pn->xr, (LONG)pn->yb };
	InvalidateRect(main_wnd, &rc, TRUE);
}

inline void invalidateWindowSide(Pane *pn)
{
	RECT rc = { 0, 0, 0, (LONG)clh };
	
	if(pn->ch_msg == FSMM_LFOLDER_CHANGED)
	{
		rc.right = (LONG)clw/2;
	}
	else
	{
		rc.left = (LONG)clw/2;
		rc.right = (LONG)clw;
	}
	
	InvalidateRect(main_wnd, &rc, TRUE);
}

inline void invalidateBaseDir(Pane *pn)
{
	RECT rc = { (LONG)(pn->xl + cellw), (LONG)(pn->yt - cellh), (LONG)pn->xr, (LONG)pn->yt };
	InvalidateRect(main_wnd, &rc, TRUE);
}

void reInitPane(Pane *pn, const wtxt &new_bdir)
{
	pn->top_idx = 0;
	pn->phov_idx = NFND;
	pn->sel.Clear();
	pn->bdir = new_bdir;
	
	pn->files.Clear();
	scan(pn, new_bdir);
	
	RECT rc = { (LONG)pn->xl, (LONG)pn->yt, (LONG)pn->xr, (LONG)pn->yb };
	InvalidateRect(main_wnd, &rc, TRUE);
	invalidateBaseDir(pn);
	//UpdateWindow(main_wnd);
}

FILETIME null_time;

void listDrives(Pane *pn)
{
	pn->top_idx = 0;
	pn->phov_idx = 0;
	pn->sel.Clear();
	pn->files.Clear();
	
	DWORD drives = GetLogicalDrives();
	wchar_t disk_name[3] = { 'A', ':', 0 };
	ui64 idx = 0;
	for(ui64 i = 1; i <= 0x2000000; i <<= 1) // 26 letters, 26 bits
	{
		if(drives & i)
		{
			ULARGE_INTEGER tot, free;
			GetDiskFreeSpaceEx(disk_name, NULL, &tot, &free);
			
			File f = { cwstr({ disk_name, 2 }), FILE_ATTRIBUTE_DIRECTORY, null_time, tot.QuadPart, idx++, pn };
			
			ffull_inf = WL("DISK ");
			ffull_inf += disk_name[0], ffull_inf += WL("  ");
			ffull_inf += fileSizeToWtxt(tot.QuadPart), ffull_inf += WL("  ");
			ffull_inf += fileSizeToWtxt(free.QuadPart);
			f.SetFullInfo(ffull_inf);
			
			pn->files << f;
		}
		++disk_name[0];
	}
	
	pn->txtw = 20 * cellw; // DISK X__XXXXY__XXXXY
	
	RECT rc = { (LONG)pn->xl, (LONG)pn->yt, (LONG)pn->xr, (LONG)pn->yb };
	InvalidateRect(main_wnd, &rc, TRUE);
	invalidateBaseDir(pn);
	//UpdateWindow(main_wnd);
}

THREAD directoryWatcher(void *param)
{
	while(1)
	{
		WaitForSingleObject(((Pane *)param)->watchtower, INFINITE);
		PostMessage(main_wnd, (UINT)((Pane *)param)->ch_msg, 0, 0);
		FindNextChangeNotification(((Pane *)param)->watchtower);
	}
	
	return 0;
}

wtxt to_observe_txt = MAX_PATH;

void observeDirectory(Pane *pn)
{
	if(pn->watcher != NULL)
	{
		FindCloseChangeNotification(pn->watchtower);
		TerminateThread(pn->watcher, 0);
	}
	
	const wchar_t *to_observe;
	if(~pn->bdir == 2) // Handle root drives directories i.e. D:
	{
		to_observe_txt = pn->bdir;
		to_observe_txt += '\\';
		to_observe = to_observe_txt;
	}
	else
	{
		to_observe = pn->bdir;
	}
	
	pn->watchtower = FindFirstChangeNotification(
	to_observe,
	FALSE,
	FILE_NOTIFY_CHANGE_FILE_NAME	|
	FILE_NOTIFY_CHANGE_DIR_NAME		|
	FILE_NOTIFY_CHANGE_ATTRIBUTES	|
	FILE_NOTIFY_CHANGE_SIZE			|
	FILE_NOTIFY_CHANGE_LAST_WRITE);
	
	pn->watcher = CreateThread(NULL, 0, directoryWatcher, pn, 0, NULL);
}

void butcherWatcher(Pane *pn)
{
	if(pn->watcher != NULL)
	{
		FindCloseChangeNotification(pn->watchtower);
		TerminateThread(pn->watcher, 0);
		pn->watchtower = NULL;
		pn->watcher = NULL;
	}
}

inline File::File(const wtxt &fn, DWORD atrib, const FILETIME &mt, ui64 sz, ui64 i, Pane *pane)
{
	name = fn;
	attr = atrib;
	mdate = *((ui64 *)&mt);
	size = sz;
	bools = 0;
	idx = i;
	pn = pane;
}

inline File::File(const wchar_t *fpath, ui64 i, Pane &pane)
{
	ConstructFromFpath(fpath);
	bools = 0;
	idx = i;
	pn = &pane;
}

inline File & File::operator=(const wchar_t *fpath)
{
	ConstructFromFpath(fpath);
}

inline const wtxt & File::Name() const
{
	return name;
}

inline const bool64 File::IsSelected() const
{
	return FILE_SELECTED;
}

inline wtxt & File::FullPathIntoTxt(wtxt &t) const
{
	t = pn->bdir;
	t += '\\', t += name;
	return t;
}

inline void File::Hover() // TODO *FIXED* POSSIBLY? !!!NO!!! DIDNT FIXED! STILL HAPPENS ON HOVER SOMETIMES NOT ON SCROL ELLIMINATING TOO MUCH UPDATEWINDOW SOLVED IT? TO FIX BLACK CHAOS CORRUPTION LIMIT AMOUNT OF RECT INVALIDATION ON FAST MOUSE MOVEMENT! NOTE: CORRUPTION CAN BEGIN AT RANDOM MOMENT EVEN WITHOUT RAPID HOVERING!
{
	if(pn->phov_idx != NFND)
	{
		pn->files[pn->phov_idx].UnHover();
	}
	//if(rp.phov_idx != NFND)
	//{
	//	rp.files[rp.phov_idx].UnHover();
	//}
	pn->phov_idx = idx;
	SetState(HOVERED);
	
	if(dnd_orig_pane != NULL)
	{
		SetState(DRAGGED_OVER);
	}
}

inline void File::UnHover()
{
	ResetState(HOVERED);
	
	if(dnd_orig_pane != NULL)
	{
		ResetState(DRAGGED_OVER);
	}
}

inline void File::Select(bool64 ctrl)
{
	if(!ctrl)
	{
		unSelectAll(pn);
	}
	else
	{
		if(FILE_SELECTED)
		{
			pn->sel.DelVal(idx);
			UnSelect();
			return;
		}
	}
	
	pn->sel << idx;
	SetState(SELECTED);
}

inline void File::UnSelect()
{
	ResetState(SELECTED);
}

wtxt targ_file = MAX_PATH;
wtxt link_file = MAX_PATH;

inline void File::ExecuteCommand(ui64 cmd, wtxt *targ)
{
	switch(cmd)
	{
	case CMD_OPEN:
		if(pn->bdir == empty) // File name contains drive
		{
			targ_file = name;
		}
		else
		{
			FullPathIntoTxt(targ_file);
		}
		
		if(attr & FILE_ATTRIBUTE_DIRECTORY)
		{
			reInitPane(pn, targ_file);
			observeDirectory(pn);
		}
		else
		{
			executeFile(targ_file, pn->bdir, false); // TODO ADD TARG AS OPTIONAL PARAMETER TO EXECUTEFILE
		}
		break;
	case CMD_EDIT:
		if(pn->bdir == empty)
		{
			return;
		}
		if(attr & FILE_ATTRIBUTE_DIRECTORY)
		{
			return;
		}
		
		FullPathIntoTxt(targ_file);
		executeFile(targ_file, pn->bdir, true);
		break;
	case CMD_SYMLINK:
	{
		if(targ == NULL)
		{
			FullPathIntoTxt(link_file);
			txti(link_file, txtfe(link_file, TEND, '\\')+1, WL("SYMLINK_"));
			targ_file = name;
		}
		else
		{
			link_file = *targ;
			link_file += '\\', link_file += name;
			FullPathIntoTxt(targ_file);
			
			if(link_file[0] == targ_file[0]) // Same drive, make relative symlink instead of absolute
			{
				absToRelPath(link_file, targ_file);
			}
		}
		
		BOOL res;
		if(attr & FILE_ATTRIBUTE_DIRECTORY)
		{
			res = CreateSymbolicLink(link_file, targ_file, SYMBOLIC_LINK_FLAG_DIRECTORY);
		}
		else
		{
			res = CreateSymbolicLink(link_file, targ_file, 0);
		}
		
		if(!res)
		{
			DWORD e = GetLastError();
			MessageBoxW(main_wnd, targ_file + '\n' + 'E' + i2wt(e) + ' ' + errToWtxt(e),
				L"ERROR CREATING SYMLINK", MB_OK | MB_ICONSTOP);
		}
	}	break;
	case CMD_HARDLINK:
	{
		FullPathIntoTxt(targ_file);
		if(targ == NULL)
		{
			link_file = targ_file;
			txti(link_file, txtfe(link_file, TEND, '\\')+1, WL("HARDLINK_"));
		}
		else
		{
			link_file = *targ;
			link_file += '\\', link_file += name;
		}
		
		BOOL res = CreateHardLink(link_file, targ_file, NULL);
		// The maximum number of hard links that can be created with this function is 1023 per file
		// If more than 1023 links are created for a file, an error results
		// The specific design of the NTFS MFT data structure and the space allocated for pointers within each
		// MFT record are the technical reasons behind this limitation
		
		if(!res)
		{
			DWORD e = GetLastError();
			MessageBoxW(main_wnd, targ_file + '\n' + 'E' + i2wt(e) + ' ' + errToWtxt(e),
				L"ERROR CREATING HARDLINK", MB_OK | MB_ICONSTOP);
		}
		else
		{
			SetState(IS_HARDLINK);
		}
	}	break;
	case CMD_RENAME: // TODO
		break;
	case CMD_DELETE: // TODO IF HARDLINK IS DELETED, RELOAD OPPOSITE PANE VIA POSTMSG TOO TO UPDATE HARLINK HIGHLIGHT
		break;
	default:
		break;
	}
}

inline void File::Paint(HDC dc)
{
	x = (i32)(pn->xl + cellw);
	y = (i32)(((idx - pn->top_idx) * cellh) + pn->yt + cellh);
	
	i32 chn = (i32)MIN(~full_info, pn->max_txt); // Number of characters to paint
	
	COLORREF tc = def_front;
	
	if(attr & FILE_ATTRIBUTE_HIDDEN)
	{
		// tc = (tc & 0xFF0000)/2 | (tc & 0xFF00)/2 | (tc & 0xFF)/2; For independent channel scaling
		tc /= 3;
	}
	if(attr & FILE_ATTRIBUTE_SYSTEM)
	{
		tc = tc & 0xFFFF00;
	}
	if(attr & FILE_ATTRIBUTE_REPARSE_POINT)
	{
		tc = tc & 0xFF00FF;
	}
	if(FILE_IS_HARDLINK)
	{
		tc = tc & 0x00FF00;
	}
	
	if(attr & FILE_ATTRIBUTE_DIRECTORY)
	{
		i32 yl = y + (i32)cellh/2;
		MoveToEx(dc, (i32)pn->xl, yl, NULL);
		LineTo(dc, x, yl);
	}
	
	SetTextColor(dc, tc);
	
	if(FILE_SELECTED)
	{
		if(attr & FILE_ATTRIBUTE_HIDDEN)
		{
			tc *= 3;
			SetTextColor(dc, tc);
		}
		
		SetBkColor(dc, sel_back);
		TextOutW(dc, x, y, full_info, chn);
		SetBkColor(dc, def_back);
		
		if(FILE_DRAGGED_OVER)
		{
			SelectObject(dc, GetStockObject(NULL_BRUSH));
			Rectangle(dc, x, y, (i32)(x + ~full_info * cellw), y + (i32)cellh);
		}
		return;
	}
	else if(FILE_HOVERED)
	{
		SetBkColor(dc, hov_back);
		TextOutW(dc, x, y, full_info, chn);
		SetBkColor(dc, def_back);
		
		if(FILE_DRAGGED_OVER)
		{
			SelectObject(dc, GetStockObject(NULL_BRUSH));
			Rectangle(dc, x, y, (i32)(x + ~full_info * cellw), y + (i32)cellh);
		}
		return;
	}
	
	TextOutW(dc, x, y, full_info, chn);
}

inline void File::ComputeFullInfo(ui64 max_ns)
{
	ffull_inf = truncFileName(name, max_ns);
	ffull_inf += WL("  ");
	ffull_inf += fileTimeToWtxt(mdate);
	ffull_inf += WL("  ");
	if(attr & FILE_ATTRIBUTE_DIRECTORY)
	{
		ffull_inf += WL("-    ");
	}
	else
	{
		ffull_inf += fileSizeToWtxt(size);
	}
	
	full_info = ffull_inf;
}

inline void File::SetFullInfo(const wtxt &inf)
{
	full_info = inf;
}

inline void File::SetIndex(ui64 i)
{
	idx = i;
}

inline void File::SetHardlinkState()
{
	SetState(IS_HARDLINK);
}

inline void File::ReleaseMemory()
{
	txtinv(name);
	txtinv(full_info);
}

inline void File::ConstructFromFpath(const wchar_t *fpath)
{
	WIN32_FILE_ATTRIBUTE_DATA fa;
	BOOL res = GetFileAttributesExW(fpath, GetFileExInfoStandard, &fa);
	//DWORD    dwFileAttributes;
	//FILETIME ftCreationTime;
	//FILETIME ftLastAccessTime;
	//FILETIME ftLastWriteTime;
	//DWORD    nFileSizeHigh;
	//DWORD    nFileSizeLow;
	
	if(!res) // When the GetFileAttributesEx function is called on a directory that is a mounted folder
	{ // it returns the attributes of the directory, not those of the root directory
		attr = 0; // in the volume that the mounted folder associates with the directory
		mdate = 0;
		size = 0;
		name = WL("GetFileAttributesExW FAILED");
		return;
	}
	
	attr = fa.dwFileAttributes;
	mdate = *((ui64 *)&fa.ftLastWriteTime);
	size = (ui64)fa.nFileSizeHigh << 32 | (ui64)fa.nFileSizeLow;
	name = { fpath, strl(fpath) };
	txtd(name, 0, txtfe(name, TEND, '\\') + 1);
	
	//SYSTEMTIME fst;
	//FileTimeToLocalTime(&fa.ftLastWriteTime, &fst);
	//finfp|SPDN(PADR)|SPN(24)|name|S(4);
	//finfp|SPC('0')|SPN(2)|fst.wYear % 100|'.'|SPN(2)|fst.wMonth|'.'|SPN(2)|fst.wDay|S|SPN(2)|fst.wHour|':'|SPN(2)|fst.wMinute|DP;
	//finfp|S(4)|size; // TODO IGNORE SIZE FOR FOLDERS!!! ITS JUNK VALUES
	//full_info = *finfp;
	//finfp|CL;
}

inline void File::SetState(ui64 state)
{
	if(bools & state)
	{
		return;
	}
	
	bools |= state;
	
	RECT rc;
	rc.left = (LONG)pn->xl;
	rc.right = (LONG)pn->xr;
	rc.top = y;
	rc.bottom = y + (LONG)cellh;
	InvalidateRect(main_wnd, &rc, FALSE);
}

inline void File::ResetState(ui64 state)
{
	if(!(bools & state))
	{
		return;
	}
	
	bools ^= state; // Toggle the bit
	
	RECT rc;
	rc.left = (LONG)pn->xl;
	rc.right = (LONG)pn->xr;
	rc.top = y;
	rc.bottom = y + (LONG)cellh;
	InvalidateRect(main_wnd, &rc, FALSE);
}

inline MenuBox::MenuBox()
{
	hi = NO_HOVER;
}

inline MenuBox::operator bool64()
{
	return ~cmds != 0;
}

inline void MenuBox::Spawn(i64 x, i64 y, const ui64a &cmd_list, Pane *pane)
{
	Exterminate(); // Oh my, making an exterminatus on youself!
	
	cmds = cmd_list;
	pn = pane;
	
	ui64 max_cmd = 0; // Maximum command width in characters
	for(ui64 i = 0; i < ~cmds; ++i)
	{
		if(max_cmd < commands[cmds[i]].s)
		{
			max_cmd = commands[cmds[i]].s;
		}
	}
	
	ui64 boxw = max_cmd * cellw + xpad * cellw * 2;
	ui64 boxh = ~cmds * cellh;
	
	xl = x, xr = x + (i64)boxw, yt = y, yb = y + (i64)boxh;
	
	if(xr > (i64)clw)
	{
		xl = x - (i64)boxw;
		xr = x;
	}
	if(yb > (i64)clh)
	{
		yt = y - (i64)boxh;
		yb = y;
	}
	
	RECT rc = { (LONG)xl, (LONG)yt, (LONG)xr, (LONG)yb };
	InvalidateRect(main_wnd, &rc, TRUE);
}

inline void MenuBox::Hover(i64 y)
{
	ui64 new_hi = (y - yt)/cellh;
	if(new_hi == hi)
	{
		return;
	}
	
	hi = new_hi;
	RECT rc = { (LONG)xl, (LONG)yt, (LONG)xr, (LONG)yb };
	InvalidateRect(main_wnd, &rc, TRUE);
}

inline void MenuBox::UnHover()
{
	if(hi == NO_HOVER)
	{
		return;
	}
	
	hi = NO_HOVER;
	prs = false;
	RECT rc = { (LONG)xl, (LONG)yt, (LONG)xr, (LONG)yb };
	InvalidateRect(main_wnd, &rc, TRUE);
}

inline void MenuBox::Press(i64 y)
{
	ui64 new_hi = (y - yt)/cellh;
	if(prs && new_hi == hi)
	{
		return;
	}
	
	prs = true;
	hi = new_hi;
	RECT rc = { (LONG)xl, (LONG)yt, (LONG)xr, (LONG)yb };
	InvalidateRect(main_wnd, &rc, TRUE);
}

inline ui64 MenuBox::GetCommand()
{
	ui64 cmd = cmds[hi];
	Annihilate();
	return cmd;
}

inline void MenuBox::Exterminate()
{
	Annihilate();
}

inline Pane * MenuBox::GetPane() const
{
	return pn;
}

inline bool64 MenuBox::MouseInside(i64 x, i64 y)
{
	return pcoll(x, y, xl, xr, yt, yb);
}

inline void MenuBox::Paint(HDC dc)
{
	if(~cmds == 0)
	{
		return;
	}
	
	SetTextColor(dc, def_front);
	SelectObject(dc, def_back_brush);
	Rectangle(dc, (i32)xl, (i32)yt, (i32)xr, (i32)yb);
	
	SetBkMode(dc, TRANSPARENT);
	for(ui64 i = 0; i < ~cmds; ++i)
	{
		i32 y_pos = (i32)(yt + i * cellh);
		if(i == hi)
		{
			if(prs)
			{
				SelectObject(dc, sel_back_brush);
			}
			else
			{
				SelectObject(dc, GetStockObject(NULL_BRUSH));
			}
			Rectangle(dc, (i32)xl, y_pos, (i32)xr, y_pos + (i32)cellh);
			TextOutW(dc, (i32)(xl + xpad * cellw), y_pos, commands[cmds[i]].t, (i32)commands[cmds[i]].s);
			continue;
		}
		
		TextOutW(dc, (i32)(xl + xpad * cellw), y_pos, commands[cmds[i]].t, (i32)commands[cmds[i]].s);
	}
	SetBkMode(dc, OPAQUE);
}

inline void MenuBox::Annihilate()
{
	cmds.Clear();
	pn = NULL;
	prs = false;
	hi = NO_HOVER;
	RECT rc = { (LONG)xl, (LONG)yt, (LONG)xr, (LONG)yb };
	InvalidateRect(main_wnd, &rc, TRUE);
}

inline ui64 fileIdx(Pane *pn, i32 x, i32 y)
{
	i64 fbx = (i64)(pn->xl + cellw);
	i64 fby = (i64)(pn->yt + cellh);
	if(x < fbx || x > fbx + (i64)pn->txtw || y < fby)
	{
		return NFND;
	}
	
	ui64 hidx = (y - fby)/cellh + pn->top_idx;
	
	if(hidx >= ~pn->files)
	{
		return NFND;
	}
	
	return hidx;
}

inline void initiateDragAndDrop(WPARAM wpar, i32 x, i32 y, Pane *pn)
{
	if(dnd_orig_pane == NULL && (wpar & MK_LBUTTON || wpar & MK_RBUTTON))
	{
		if(abs(dnd_lcx - x) > dnd_ignore_pix || abs(dnd_lcy - y) > dnd_ignore_pix) // Initiate Drag n' Drop
		{
			cur_cur = dnd_cur;
			dnd_orig_pane = pn;
		}
	}
}

inline void begDragOverPane(Pane *pn)
{
	if(dnd_orig_pane != NULL && !pn->dnd)
	{
		pn->dnd = true;
		invalidateWindowSide(pn);
	}
}

inline void endDragOverPane(Pane *pn)
{
	if(dnd_orig_pane != NULL && pn->dnd)
	{
		pn->dnd = false;
		invalidateWindowSide(pn);
	}
}

inline void disableDragAndDrop()
{
	cur_cur = def_cur;
	SetCursor(cur_cur);
}

inline void finishDragAndDrop()
{
	dnd_orig_pane = NULL;
}

inline void abortDragAndDrop()
{
	cur_cur = def_cur;
	SetCursor(cur_cur);
	dnd_orig_pane = NULL;
}

LRESULT wmSizeHandler(HWND wnd, LPARAM lpar)
{
	clw = LW(lpar);
	clh = HW(lpar);

	lp.xl = fold_pad_x * cellw;
	ui64 foldw = (clw - lp.xl * 3)/2;
	
	lp.xr = lp.xl + foldw;
	lp.yt = fold_pad_y * cellh;
	lp.yb = clh - lp.yt;
	
	rp.xl = lp.xr + lp.xl;
	rp.xr = rp.xl + foldw;
	rp.yt = lp.yt, rp.yb = lp.yb;
	
	ui64 new_mfiles = (rp.yb - rp.yt)/cellh - 2; // -2 for skipped top/bottom line
	if(new_mfiles > rp.max_files)
	{
		if(lp.top_idx > 0)
		{
			--lp.top_idx;
		}
		
		if(rp.top_idx > 0)
		{
			--rp.top_idx;
		}
	}
	
	rp.max_files = new_mfiles, lp.max_files = new_mfiles;
	lp.max_txt = foldw/cellw - 2;
	rp.max_txt = lp.max_txt; // For now, folder panes always have exactly the same width, no need to recalc
	
	InvalidateRect(wnd, NULL, FALSE);
	
	return 0;
}

LRESULT wmMouseWheelHandler(HWND wnd, WPARAM wpar, LPARAM lpar) // TODO? COMBINE SCROLLING LOGIC IN ONE FUNCTION! ? WHY?! <-- ONE FUNCTION IS RIGHT HERE
{
	POINT mp = { LWSIGN(lpar), HWSIGN(lpar) };
	ScreenToClient(wnd, &mp);
	
	if(mbox)
	{
		return 0;
	}
	
	Pane *pn;
	if(pcoll(mp, lp)) // Left folder pane scrolled
	{
		pn = &lp;
	}
	else if(pcoll(mp, rp)) // Right folder pane scrolled
	{
		pn = &rp;
	}
	else
	{
		return 0;
	}
	
	i32 scrl_ln = (i32)((i16)HW(wpar)/WHEEL_DELTA * (i32)mwheel_scroll_ln); // Lines to scroll
	
	if(~pn->files < pn->max_files)
	{
		return 0;
	}
	
	ui64 new_idx = pn->top_idx - scrl_ln; // SCRL BACK: a - (-b) = a + b | FORW: a - b
	
	if(new_idx & 0x8000000000000000) // Check for overflow, means top of scroll range reached
	{
		if(pn->top_idx != 0 && pn->phov_idx != NFND)
		{
			pn->files[pn->phov_idx - (scrl_ln - (UI64_MAX - new_idx + 1))].Hover(); // Preserves hover
		}
		
		pn->top_idx = 0;
	}
	else // Scrolling down (BACK)
	{
		i64 idx_delta = (i64)(new_idx + pn->max_files) - (i64)~pn->files; 
		if(idx_delta > 0) // Reached bottom of scroll range
		{
			ui64 max_idx = ~pn->files - pn->max_files;
			if(pn->top_idx != max_idx && pn->phov_idx != NFND)
			{
				pn->files[pn->phov_idx - (scrl_ln + idx_delta)].Hover();
			}
			
			pn->top_idx = max_idx;
		}
		else
		{
			pn->top_idx = new_idx;
			
			if(pn->phov_idx != NFND)
			{
				pn->files[pn->phov_idx - scrl_ln].Hover();
			}
		}
	}
	
	invalidatePane(pn);
	
	return 0;
}

LRESULT wmMouseMoveHandler(/*HWND wnd,*/ WPARAM wpar, LPARAM lpar)
{
	SetCursor(cur_cur); // Is this not too much overhead? Not shure...
	
	i32 x = LWSIGN(lpar), y = HWSIGN(lpar);
	
	if(mbox)
	{
		if(mbox.MouseInside(x, y))
		{
			if(wpar & MK_LBUTTON || wpar & MK_RBUTTON)
			{
				mbox.Press(y);
			}
			else
			{
				mbox.Hover(y);
			}
		}
		else
		{
			mbox.UnHover();
		}
		return 0;
	}
	
	Pane *pn;
	if(pcoll(x, y, lp)) // Left folder pane hovered
	{
		pn = &lp;
	}
	else if(pcoll(x, y, rp)) // Right folder pane hovered
	{
		pn = &rp;
	}
	else
	{
		if(lp.phov_idx != NFND)
		{
			lp.files[lp.phov_idx].UnHover();
		}
		if(rp.phov_idx != NFND)
		{
			rp.files[rp.phov_idx].UnHover();
		}
		lp.phov_idx = NFND;
		rp.phov_idx = NFND;
		
		endDragOverPane(&lp);
		endDragOverPane(&rp);
		return 0;
	}
	
	ui64 fi = fileIdx(pn, x, y);
	if(fi != NFND)
	{
		initiateDragAndDrop(wpar, x, y, pn);
		
		pn->files[fi].Hover();
		
		endDragOverPane(pn);
	}
	else
	{
		if(pn->phov_idx != NFND)
		{
			pn->files[pn->phov_idx].UnHover();
		}
		pn->phov_idx = NFND;
		
		begDragOverPane(pn);
	}
	
	return 0;
}

LRESULT wmLbuttonDownHandler(WPARAM wpar, LPARAM lpar)
{
	i32 x = LWSIGN(lpar), y = HWSIGN(lpar);
	
	if(mbox)
	{
		if(mbox.MouseInside(x, y))
		{
			mbox.Press(y);
			return 0;
		}
		
		mbox.Exterminate();
	}
	
	dnd_lcx = x, dnd_lcy = y;
	
	Pane *pn;
	if(pcoll(x, y, lp)) // Left folder pane clicked
	{
		pn = &lp;
	}
	else if(pcoll(x, y, rp)) // Right folder pane clicked
	{
		pn = &rp;
	}
	else
	{
		return 0;
	}
	
	ui64 fi = fileIdx(pn, x, y);
	if(fi != NFND)
	{
		if(!(wpar & MK_CONTROL) && !pn->files[fi].IsSelected())
		{
			pn->files[fi].Select(false);
		}
	}
	else
	{
		unSelectAll(pn);
		abortDragAndDrop();
	}
	
	return 0;
}

bool64 dclick_trigg; // Double click was triggered

LRESULT wmLbuttonUpHandler(WPARAM wpar, LPARAM lpar)
{
	if(dclick_trigg) // Double click mouse up protection
	{
		dclick_trigg = false;
		return 0;
	}
	
	i32 x = LWSIGN(lpar), y = HWSIGN(lpar);
	
	if(mbox)
	{
		if(!mbox.MouseInside(x, y))
		{
			mbox.Exterminate();
			finishDragAndDrop();
			return 0;
		}
		
		Pane *pn;
		wtxt *cmd_targ;
		if(dnd_orig_pane != NULL) // File was RMB dropped
		{
			pn = dnd_orig_pane;
			cmd_targ = &dnd_target;
			
			if(dnd_targ_file != NULL)
			{
				dnd_targ_file->UnHover();
			}
			else
			{
				endDragOverPane(dnd_targ_pane);
			}
			
			finishDragAndDrop();
		}
		else
		{
			cmd_targ = NULL;
			pn = mbox.GetPane();
		}
		
		ui64 cmd = mbox.GetCommand();
		for(ui64 i = 0; i < ~pn->sel; ++i)
		{
			pn->files[pn->sel[i]].ExecuteCommand(cmd, cmd_targ);
		}
		return 0;
	}
	
	Pane *pn;
	if(pcoll(x, y, lp)) // Left folder pane unclicked
	{
		pn = &lp;
	}
	else if(pcoll(x, y, rp)) // Right folder pane unclicked
	{
		pn = &rp;
	}
	else
	{
		unSelectAll(&lp);
		unSelectAll(&rp);
		abortDragAndDrop();
		return 0;
	}
	
	ui64 fi = fileIdx(pn, x, y);
	if(fi != NFND)
	{
		//if(pn->files[fi].IsSelected())
		//{
			pn->files[fi].Select(wpar & MK_CONTROL);
		//}
	}
	else
	{
		unSelectAll(pn);
		abortDragAndDrop();
	}
	
	return 0;
}

LRESULT wmLbuttonDblClkHandler(LPARAM lpar)
{
	dclick_trigg = true;
	i32 x = LWSIGN(lpar), y = HWSIGN(lpar);
	
	if(mbox)
	{
		return 0;
	}
	
	Pane *pn;
	if(pcoll(x, y, lp)) // Left folder pane double clicked
	{
		pn = &lp;
	}
	else if(pcoll(x, y, rp)) // Right folder pane double clicked
	{
		pn = &rp;
	}
	else
	{
		unSelectAll(&lp);
		unSelectAll(&rp);
		return 0;
	}
	
	ui64 fi = fileIdx(pn, x, y);
	if(fi != NFND)
	{
		pn->files[fi].ExecuteCommand(CMD_OPEN, NULL);
	}
	
	return 0;
}

LRESULT wmRbuttonDownHandler(/*WPARAM wpar, */LPARAM lpar)
{
	i32 x = LWSIGN(lpar), y = HWSIGN(lpar);
	
	if(mbox)
	{
		if(mbox.MouseInside(x, y))
		{
			mbox.Press(y);
			return 0;
		}
		
		mbox.Exterminate();
	}
	
	if(pcoll(x, y, lp.xl, lp.xr, lp.yt - cellh, lp.yt)) // Left base directory clicked
	{
		removeLastDir(lp.bdir);
		if(lp.bdir == empty) // All mounted drives display mode
		{
			listDrives(&lp);
			butcherWatcher(&lp);
		}
		else
		{
			reInitPane(&lp, lp.bdir);
			observeDirectory(&lp);
		}
		
		return 0;
	}
	if(pcoll(x, y, rp.xl, rp.xr, rp.yt - cellh, rp.yt)) // Right base directory clicked
	{
		removeLastDir(rp.bdir);
		if(rp.bdir == empty) // All mounted drives display mode
		{
			listDrives(&rp);
			butcherWatcher(&rp);
		}
		else
		{
			reInitPane(&rp, rp.bdir);
			observeDirectory(&rp);
		}
		
		return 0;
	}
	
	Pane *pn;
	if(pcoll(x, y, lp)) // Left folder pane unclicked
	{
		pn = &lp;
	}
	else if(pcoll(x, y, rp)) // Right folder pane unclicked
	{
		pn = &rp;
	}
	else
	{
		return 0;
	}
	
	ui64 fi = fileIdx(pn, x, y);
	if(fi != NFND && !pn->files[fi].IsSelected())
	{
		pn->files[fi].Select(false);
	}
	
	return 0;
}

LRESULT wmRbuttonUpHandler(/*WPARAM wpar, */LPARAM lpar)
{
	i32 x = LWSIGN(lpar), y = HWSIGN(lpar);
	
	if(mbox)
	{
		if(!mbox.MouseInside(x, y))
		{
			mbox.Exterminate();
			return 0;
		}
		// TODO RMB UP IN MENU BOX MUST TRIGGER COMMANDS TOO!
		return 0;
	}
	
	if(pcoll(x, y, lp.xl, lp.xr, lp.yt - cellh, lp.yt)) // Left base directory clicked
	{
		return 0;
	}
	if(pcoll(x, y, rp.xl, rp.xr, rp.yt - cellh, rp.yt)) // Right base directory clicked
	{
		return 0;
	}
	
	Pane *pn;
	if(pcoll(x, y, lp)) // Left folder pane unclicked
	{
		pn = &lp;
	}
	else if(pcoll(x, y, rp)) // Right folder pane unclicked
	{
		pn = &rp;
	}
	else
	{
		unSelectAll(&lp);
		unSelectAll(&rp);
		return 0;
	}
	
	ui64 fi = fileIdx(pn, x, y);
	if(fi != NFND)
	{
		if(dnd_orig_pane != NULL)
		{
			pn->files[fi].FullPathIntoTxt(dnd_target);
			dnd_targ_file = &pn->files[fi]; // TODO SPAWN DRAG N' DROP SPECIFIC MENU HERE AND RETURN
			dnd_targ_pane = pn;
			disableDragAndDrop();
		}
		
		ui64a tmp_cmd; tmp_cmd << 0, tmp_cmd << 1, tmp_cmd << 2, tmp_cmd << 3, tmp_cmd << 4, tmp_cmd << 5;////////////////////////TMPSOLUTION
		mbox.Spawn(x, y, tmp_cmd, pn);
	}
	else
	{
		if(dnd_orig_pane != NULL)
		{
			dnd_target = pn->bdir;
			dnd_targ_file = NULL;
			dnd_targ_pane = pn;
			disableDragAndDrop();
			
			ui64a tmp_cmd; tmp_cmd << 0, tmp_cmd << 1, tmp_cmd << 2, tmp_cmd << 3, tmp_cmd << 4, tmp_cmd << 5;////////////////////////TMPSOLUTION
			mbox.Spawn(x, y, tmp_cmd, pn);
			return 0;
		}
		
		unSelectAll(pn);
	}
	
	return 0;
}

void paintScrlBar(Pane *pn)
{
	if(~pn->files <= pn->max_files)
	{
		return;
	}
	
	i32 sbx = (i32)(pn->xr - cellw);
	MoveToEx(main_dc, sbx, (i32)pn->yt, NULL);
	LineTo(main_dc, sbx, (i32)pn->yb);
	
	float fit_q = (float)pn->max_files/(float)~pn->files; // Quotient of files that fit in the currenttly sized window
	ui64 max_pix = pn->yb - pn->yt;
	ui64 barsz = (ui64)((float)max_pix * fit_q); // Size of a scroll bar
	
	if(barsz < cellw)
	{
		barsz = cellw;
	}
	
	ui64 max_sb_pix = max_pix - barsz; // Maximum scrollable scrollbar pixel
	float max_scrl_idx = (float)(~pn->files - pn->max_files); // Maximum index representable by scrollbar position
	float idx_q = (float)pn->top_idx/max_scrl_idx; // Main scroll index quotient
	i32 sby = (i32)((float)max_sb_pix * idx_q) + (i32)pn->yt;
	
	SelectObject(main_dc, scr_back_brush);
	Rectangle(main_dc, sbx, sby, (i32)pn->xr, sby + (i32)barsz);
}

LRESULT wndProc(HWND wnd, UINT msg, WPARAM wpar, LPARAM lpar)
{
	PAINTSTRUCT ps;
	
	switch(msg)
	{
	case WM_PAINT:
	{
		main_dc = BeginPaint(wnd, &ps); // BEGIN PAINT ------------------------------
		
		SelectObject(main_dc, def_font);
		
		if(ps.rcPaint.right == 0 && ps.rcPaint.bottom == 0)
		{
			EndPaint(wnd, &ps);
			return 0;
		}
		
		SetBkColor(main_dc, def_back);
		SetTextColor(main_dc, def_front);
		SelectObject(main_dc, def_pen);
		
		if(ps.rcPaint.left <= (LONG)lp.xr)
		{
			TextOutW(main_dc, (i32)(lp.xl + cellw), (i32)(lp.yt - cellh), lp.bdir, (i32)~lp.bdir);
			
			ui64 max_idx = lp.top_idx + lp.max_files;
			for(ui64 i = lp.top_idx; i < ~lp.files && i < max_idx; ++i) 
			{
				lp.files[i].Paint(main_dc);
			}

			paintScrlBar(&lp);
		}
		
		if(ps.rcPaint.right >= (LONG)rp.xl)
		{
			TextOutW(main_dc, (i32)(rp.xl + cellw), (i32)(rp.yt - cellh), rp.bdir, (i32)~rp.bdir);
			
			ui64 max_idx = rp.top_idx + rp.max_files;
			for(ui64 i = rp.top_idx; i < ~rp.files && i < max_idx; ++i) 
			{
				rp.files[i].Paint(main_dc);
			}

			paintScrlBar(&rp);
		}
		
		SelectObject(main_dc, GetStockObject(NULL_BRUSH));
		
		if(lp.dnd)
		{
			SelectObject(main_dc, dnd_pen);
			Rectangle(main_dc, (i32)lp.xl, (i32)lp.yt, (i32)lp.xr+1, (i32)lp.yb+1);
			SelectObject(main_dc, def_pen);
		}
		else
		{
			Rectangle(main_dc, (i32)lp.xl, (i32)lp.yt, (i32)lp.xr, (i32)lp.yb);
		}
		
		if(rp.dnd)
		{
			SelectObject(main_dc, dnd_pen);
			Rectangle(main_dc, (i32)rp.xl, (i32)rp.yt, (i32)rp.xr+1, (i32)rp.yb+1);
			SelectObject(main_dc, def_pen);
		}
		else
		{
			Rectangle(main_dc, (i32)rp.xl, (i32)rp.yt, (i32)rp.xr, (i32)rp.yb);
		}
		
		mbox.Paint(main_dc);
		
		EndPaint(wnd, &ps); // END PAINT --------------------------------------------
	}	return 0;
	case WM_SIZE:
		return wmSizeHandler(wnd, lpar);
	case WM_MOUSEWHEEL:
		return wmMouseWheelHandler(wnd, wpar, lpar);
	case WM_MOUSEMOVE:
		return wmMouseMoveHandler(/*wnd,*/ wpar, lpar);
	case WM_LBUTTONDOWN:
		return wmLbuttonDownHandler(wpar, lpar);
	case WM_LBUTTONUP:
		return wmLbuttonUpHandler(wpar, lpar);
	case WM_LBUTTONDBLCLK:
		return wmLbuttonDblClkHandler(lpar);
	case WM_RBUTTONDOWN:
		return wmRbuttonDownHandler(/*wpar, */lpar);
	case WM_RBUTTONUP:
		return wmRbuttonUpHandler(/*wpar, */lpar);
	case WM_RBUTTONDBLCLK:
		return wmRbuttonDownHandler(/*wpar, */lpar);
	case FSMM_LFOLDER_CHANGED:
		reInitPane(&lp, lp.bdir);
		return 0;
	case FSMM_RFOLDER_CHANGED:
		reInitPane(&rp, rp.bdir);
		return 0;
	case WM_CLOSE:
		DestroyWindow(wnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(wnd, msg, wpar, lpar);
	}
}

void initGui()
{
	exec_adress = GetModuleHandle(NULL);

	// Create Fake Window to get active monitor's DPI
	HWND hwnd = CreateWindowEx(0, L"Button", 0, 0,
		0, 0, 0, 0, 0, 0, exec_adress, 0);
	dpi_scale = (float)GetDpiForWindow(hwnd) / 96.0f;
	DestroyWindow(hwnd);
	
	cellw = DPIS(cellw);
	cellh = DPIS(cellh);
	
	dnd_ignore_pix = (i64)cellw/2;
	
	// Create Font =============================================================================
	def_font = CreateFontA(
		(i32)cellh,				// [I] Height, in logical units
		0,						// [I] Average width, in logical units [0 -> closest match]
		0,						// [I] Angle, between the esc. vect. & the x-ax. of device
		0,						// [I] Angle, between char's base and the x-ax. of device
		0,						// [I] Weight of font in the range 0 - 1000 [0 -> default]
		FALSE,					// [I] Specifies an italic font if set to TRUE
		FALSE,					// [I] Specifies an underlined font if set to TRUE
		FALSE,					// [I] A strikeout font if set to TRUE
		DEFAULT_CHARSET,		// [I] The character set
		OUT_DEFAULT_PRECIS,		// [I] Output precision match h, w, orient., esc., pitch, type
		CLIP_DEFAULT_PRECIS,	// [I] Clipping precision how to clip chars part. outside clip.
		CLEARTYPE_QUALITY,		// [I] Output quality how carefully GDI match to physical font
		DEFAULT_PITCH,			// [I] Pitch and family of the font [chars/25.4mm of text]
		"Consolas");			// [I] Typeface name of the font
	// =========================================================================================
	
	SystemParametersInfoA(SPI_GETWHEELSCROLLCHARS, 0, &mwheel_scroll_ch, 0);
	SystemParametersInfoA(SPI_GETWHEELSCROLLLINES, 0, &mwheel_scroll_ln, 0);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &work_pix, 0);
	
	HICON ico = LoadIcon(exec_adress, L"MAINICON");
	dnd_cur = (HCURSOR)LoadImage(exec_adress, L"DND_CURSOR", IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
	def_cur = LoadCursor(NULL, IDC_ARROW);
	cur_cur = def_cur;
	def_back_brush = CreateSolidBrush(def_back);
	sel_back_brush = CreateSolidBrush(sel_back);
	scr_back_brush = CreateSolidBrush(def_front);
	def_pen = CreatePen(PS_SOLID, 1, def_front);
	dnd_pen = CreatePen(PS_SOLID, 2, def_front);
	
	// Register Window Class Atom ==============================================================
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);					// Structure size in bytes
	wc.style = CS_DBLCLKS;/*CS_VREDRAW CS_HREDRAW*/	// Class style, any combination
	wc.lpfnWndProc = wndProc;						// Window callback function
	wc.cbClsExtra = 0;								// Extra Class Memory (max 40B)
	wc.cbWndExtra = 0;								// Extra Window Memory (max 40B)
	wc.hInstance = exec_adress;						// Handle to module's instance
	wc.hIcon = ico;									// Def. icon for all windows
	wc.hCursor = NULL;								// DC. If NULL app must set cur every time
	wc.hbrBackground = def_back_brush;				// Def. brush for WM_ERASEBKGND
	wc.lpszMenuName = NULL;							// Def. menu name for all w.
	wc.lpszClassName = L"superSimpleWindow";		// Name of the Class (Atom)
	wc.hIconSm = 0;									// Def. small icon for all w.

	main_class = RegisterClassEx(&wc);
	// =========================================================================================
}

HWND spawnMainWnd()
{
	DWORD style_ex = WS_EX_COMPOSITED | WS_EX_ACCEPTFILES;
	DWORD style = WS_OVERLAPPEDWINDOW | WS_MAXIMIZE;
	
	//i32 x = work_pix.left;
	//i32 y = work_pix.top;
	//i32 w = work_pix.right - work_pix.left;
	//i32 h = work_pix.bottom - work_pix.top;//////////////////////////////////////////////////////
	i32 x = 600;
	i32 y = 400;
	i32 w = 200 * (i32)cellw;
	i32 h = 60 * (i32)cellh;//////////////////////////////////////////////////////
	
	// Create Window ===========================================================================
	main_wnd = CreateWindowEx(
		style_ex,				//   [I] Extended window style
		(LPCWSTR)main_class,	// [I|O] Class Atom / Class Atom String
		L"fsmng",				// [I|O] Window name String (Title)
		style,					//   [I] Window style (WS_OVERLAPPED = 0x0)
		x, y, w, h,				//   [I] PosX, PoxY, Width, Height
		NULL,					// [I|O] Handle to this window's parent
		NULL,					// [I|O] Handle to menu / Child-window ID
		exec_adress,			// [I|O] Handle to instance of the module
		NULL);					// [I|O] CREATESTRUCT ptr. for lParam of WM_CREATE
	// =========================================================================================

	UpdateWindow(main_wnd);
	//ShowWindow(main_wnd, SW_MAXIMIZE);///////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	
	
	////////////////////////////////////////////////////// NEED OR NO NEED?
	HWND fgwnd = GetForegroundWindow();
	
	AllowSetForegroundWindow(ASFW_ANY);
	DWORD cur_thread = GetCurrentThreadId();
	DWORD fg_pid = 0;
	DWORD fg_thread = GetWindowThreadProcessId(fgwnd, &fg_pid);
	
	AttachThreadInput(cur_thread, fg_thread, TRUE);
	SetFocus(main_wnd);
	SetForegroundWindow(main_wnd);
	SetWindowPos(main_wnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	AttachThreadInput(cur_thread, fg_thread, FALSE);
	
	
	
	
	
	
	
	
	
	ShowWindow(main_wnd, SW_NORMAL);///////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	
	return main_wnd;
}

ui64 getFirstDrive(ui64 st_idx, wtxt &out)
{
	DWORD drives = GetLogicalDrives();
	out = WL("A:");
	out[0] += (wchar_t)st_idx;
	for(ui64 i = 1ULL << st_idx; i <= 0x2000000; i <<= 1) // 26 letters, 26 bits
	{
		if(drives & i)
		{
			return st_idx;
		}
		++out[0], ++st_idx;
	}
	
	return NFND;
}

ui32 wmain(/*ui64 argc, wchar_t **argv*/)
{
	ui64 drive_idx = 2; // Start with drive C:
	drive_idx = getFirstDrive(drive_idx, lp.bdir);
	drive_idx = getFirstDrive(++drive_idx, rp.bdir);
	
	if(drive_idx == NFND) // Only drive C: is present
	{
		rp.bdir = lp.bdir;
	}
	
	scan(&lp, lp.bdir);
	scan(&rp, rp.bdir);
	
	observeDirectory(&lp);
	observeDirectory(&rp);
	
	initGui();
	spawnMainWnd();
	
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		DispatchMessage(&msg);
	}
	
	return 0;
}