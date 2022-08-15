#pragma once
#include<cstdint>
#include<random>


const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned	int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;


class Chip8
{
public:


	//loading data from ROM to memory
	void LoadROM(const char* filename);

	//constructor
	Chip8();

	void Cycle();

	uint32_t video[VIDEO_HEIGHT * VIDEO_WIDTH]{};
	uint8_t keypad[KEY_COUNT]{};

private:

	uint8_t registers[REGISTER_COUNT]{};
	uint8_t memory[MEMORY_SIZE]{};
	uint16_t index{};
	uint16_t pc;
	uint16_t stack[STACK_LEVELS]{};
	uint8_t sp{};
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint16_t opcode;

	std::default_random_engine randGen;
	std::uniform_int_distribution<int> randByte;

	void Table0();
	void Table8();
	void TableE();
	void TableF();

	//Vx is Register kk is data in bytes

	void OP_NULL();

	// AL:- CLS /clear the Display
	void OP_00E0();

	//AL:- RET /return from a subroutine decrementing Stack pointer and setting pc to new sp
	void OP_00EE();

	//AL:- JP addr /Jump to location nnn he pc will be taken to a new address without adding anything to stack or incrementing stack pointer
	void OP_1nnn();

	//AL:- CALL addr/we call the adrress whic h will be exucated and put the address of pc to stack and increment the sp and again increment the pc by 2
	void OP_2nnn();

	//AL:- SE Vx, byte /skip next intruction if Vx == kk; 
	void OP_3xkk();

	//AL:- SNE Vx, byte / skip next intruction if Vx != kk;
	void OP_4xkk();

	//AL:- SE Vx,Vy / skip tnext intruction if Vx == Vy
	void OP_5xy0();

	//AL:- Ld Vx, byte / set Vx = kk
	void OP_6xkk();

	//AL:- ADD Vx, byte / Set Vx = Vx +kk
	void OP_7xkk();

	//Al:- Ld Vx, Vy / Set Vx = Vy
	void OP_8xy0();

	//AL:- OR Vx, Vy / Set Vx or Vy
	void OP_8xy1();

	//AL:- AND Vx,Vy / set Vx AND Vy
	void OP_8xy2();

	//AL:- XOR Vx, Vy / set Vx XOR Vy
	void OP_8xy3();

	//AL:- ADD Vx, Vy / set  Vx = Vx + Vy, Set vf = carry;
	void OP_8xy4();

	//AL:- SUB Vx, Vy / set Vx = Vx - Vy, set VF = NOT borrow
	void OP_8xy5();

	//Al:- SHR Vx / if last significant bit of VX is 1 the nVf is set 1 otherwise 0, the nVx is divided by 2
	void OP_8xy6();

	//AL:- SUBN Vx, Vy / Vx = Vy - Vx set VF = not borrow
	void OP_8xy7();

	//AL:- SHL Vx{, Vy} / set Vx = Vx SHL 1 if the most significant bit of Vx is 1 then VF is set ot 1 otherwise 0, then Vx is Multiplied by 2
	void OP_8xyE();

	//AL:- SNE Vx, Vy / skip next intstruction if Vx!= Vy
	void OP_9xy0();

	//AL:- LD I, addr
	void OP_Annn();

	//AL:- JP V0, addr
	void OP_Bnnn();

	//AL:- RND Vx, byte
	void OP_Cxkk();

	//AL:- DRW Vx, Vy, nibble
	void OP_Dxyn();

	//AL:- SKP Vx  skip next intruction if key with value of Vx is pressed
	void OP_Ex9E();

	//AL:- SKNP Vx skip next intruction if key with value of Vx is not pressed
	void OP_ExA1();


	//AL:- LD Vx,DT	setVx = delay timer value;
	void OP_Fx07();

	//Al:- LD Vx, K
	void OP_Fx0A();

	//AL:- LD DT, Vx setdelay timer = Vx
	void OP_Fx15();

	//AL:- LD ST, Vx set sound timer = Vx
	void OP_Fx18();

	//Al:- ADD I, Vx Set I = I + Vx
	void OP_Fx1E();

	//AL:- LD F,Vx Set i = location o fsprite for digit Vx
	void OP_Fx29();

	//AL:- LD B, Vx store BCD Representation of Vx in memory location i, i+1, and i+2
	void OP_Fx33();

	//AL:- LD[I], Vx store registers V0 through Vx in memory starting at location I
	void OP_Fx55();

	//AL:- LD Vx, [I] read registers V0 through Vx from memory starting at location I
	void OP_Fx65();


	typedef void(Chip8::* Chip8Func)();

	Chip8Func table[0xF + 1]{ &Chip8::OP_NULL };
	Chip8Func table0[0xE + 1]{ &Chip8::OP_NULL };
	Chip8Func table8[0xE + 1]{ &Chip8::OP_NULL };
	Chip8Func tableE[0xE + 1]{ &Chip8::OP_NULL };
	Chip8Func tableF[0x65 + 1]{ &Chip8::OP_NULL };

};


