#pragma once
class scrProgram;

class scriptId
{
public:
	virtual ~scriptId() = 0;

	virtual void m_8() = 0;

	virtual void m_10() = 0;

	virtual void m_18() = 0;

	virtual uint32_t* GetIdentifier(uint32_t* outValue) = 0;
};
enum class eThreadState : std::uint32_t
{
	idle,
	running,
	killed,
	unk_3,
	unk_4,
};
class scrThreadContext
{
public:
	std::uint32_t m_thread_id;
	std::uint32_t m_script_hash; // + 4 (program id)
	eThreadState m_state; // + 8
	std::uint32_t m_instruction_pointer; // + 12
	std::uint32_t m_frame_pointer; // 
	std::uint32_t m_stack_pointer; // + 20, aka + 28
	std::uint32_t TimerA; // + 24
	std::uint32_t m_timer_b; // + 28
	std::uint32_t m_timer_c; // + 32, aka + 40
	std::uint32_t m_mUnk1;
	std::uint32_t m_mUnk2;
	std::uint32_t m_2C;
	std::uint32_t m_30;
	std::uint32_t m_34;
	std::uint32_t m_38;
	std::uint32_t m_3C;
	std::uint32_t m_40;
	std::uint32_t m_44;
	std::uint32_t m_48;
	std::uint32_t m_4C;
	std::uint32_t m_stack_size; // should be +88 aka +80; stack size?

	std::uint32_t pad1;
	std::uint32_t pad2;
	std::uint32_t pad3;

	std::uint32_t _set1;

	std::uint32_t pad[68 / 4];
};
class scriptHandler
{
public:
	virtual ~scriptHandler() = 0;
	virtual void _0x08() = 0;
	virtual void _0x10() = 0;
	virtual void _0x18() = 0;
	virtual void _0x20() = 0;
	virtual scriptId *get_id() = 0;
	virtual bool is_networked() = 0;
	virtual void _0x38() = 0;
	virtual void _0x40() = 0;
	virtual bool sync_stuff() = 0;
	virtual void _0x50() = 0;
	virtual void _0x58() = 0;
	virtual void _0x60() = 0;
	virtual void _0x68() = 0;
	virtual void _0x70() = 0;
	virtual void _0x78() = 0;
	virtual void _0x80() = 0;
	virtual void _0x88() = 0;
	virtual void _0x90() = 0;
	virtual void _0x98() = 0;
};
class scrThread
{
public:
	virtual ~scrThread() = default;
	virtual eThreadState reset(std::uint32_t script_hash, void *args, std::uint32_t arg_count) = 0;
	virtual eThreadState run() = 0;
	virtual eThreadState tick() = 0;
	virtual void kill() = 0;
public:
	scrThreadContext m_context; // 0x08
	void *m_stack;              // 0xB0
	char m_padding[0x10];       // 0xB8
	const char *m_exit_message; // 0xC8
	char m_name[0x40];          // 0xD0
	scriptHandler *m_handler;   // 0x110
	char m_padding2[0x28];      // 0x118
	std::uint8_t m_flag1;       // 0x140
	std::uint8_t m_flag2;       // 0x141
	char m_padding3[0x16];      // 0x142
};
struct SHVscrThreadContext
{
	int ThreadId;
	uint32_t ScriptHash;
	eThreadState State;
	int IP;
	int FrameSP;
	int SP;
	float TimerA;
	float TimerB;
	float WaitTimer;
	int _mUnk1;
	int _mUnk2;
	int _f2C;
	int _f30;
	int _f34;
	int _f38;
	int _f3C;
	int _f40;
	int _f44;
	int _f48;
	int _f4C;
	int StackSize;
	int CatchIP;
	int CatchFrame;
	int CatchSP;
	int _set1;
	int FunctionDepth;
	int FunctionReturns[16];
};

static_assert(sizeof(SHVscrThreadContext) == 0xA8, "");

struct SHVscrThread
{
	void *vTable;
	SHVscrThreadContext m_ctx;
	void *m_pStack;
	int pad0;
	int ParameterSize;
	int StaticsSize;
	int pad3;
	const char *m_pszExitMessage;
	char Name[64];
};