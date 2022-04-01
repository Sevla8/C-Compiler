#include "IRx86.h"

using namespace std;

string REGCALL[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};

void IRInstrx86::gen_asm(ostream &o)
{
    cfg->get_table().setCurrentBlock(num_block);
    string tmp("%ebx");
    string opstring;
    int i;
    switch (op)
    {
    case Operation::ldconst:
        o << "movl $" << params[1] << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        break;
    case Operation::copy:
        o << "movl " << cfg->IR_reg_to_asm(params[1]) << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        break;
    case Operation::sub:
        if (params[1] == params[0])
        {
            o << "subl " << cfg->IR_reg_to_asm(params[2]) << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        else
        {
            o << "movl " << cfg->IR_reg_to_asm(params[1]) << ", " << tmp << "\n";
            o << "subl " << cfg->IR_reg_to_asm(params[2]) << ", " << tmp << "\n";
            o << "movl " << tmp << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        break;
    case Operation::lsl:
    case Operation::lsr:
        if (op == Operation::lsl) opstring = "sall";
        else if (op == Operation::lsr) opstring = "sarl";
        o << "movl " << cfg->IR_reg_to_asm(params[2]) << ", " << "%ecx" << "\n";
        if (params[1] != params[0])
        {
            o << "movl " << cfg->IR_reg_to_asm(params[1]) << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        o << opstring << " %cl, " << cfg->IR_reg_to_asm(params[0]) << "\n";
        break;
    case Operation::div:
        o << "movl " << cfg->IR_reg_to_asm(params[2]) << ", " << tmp << "\n";
        o << "movl " << cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
        o << "cltd\n";
        o << "idivl " << tmp << "\n";
        o << "movl %eax, " << cfg->IR_reg_to_asm(params[0]) << "\n";
        break;
    case Operation::mod:
        o << "movl " << cfg->IR_reg_to_asm(params[2]) << ", " << tmp << "\n";
        o << "movl " << cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
        o << "cltd\n";
        o << "idivl " << tmp << "\n";
        o << "movl %edx, " << cfg->IR_reg_to_asm(params[0]) << "\n";
        break;
    case Operation::lnot:
    case Operation::neg:
        if (op == Operation::neg) opstring = "negl";
        else if (op == Operation::lnot) opstring = "notl";
        if (params[1] == params[0])
        {
            o << opstring << " " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        else
        {
            o << "movl " << cfg->IR_reg_to_asm(params[1]) << ", " << tmp << "\n";
            o << opstring << " " << tmp << "\n";
            o << "movl " << tmp << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        break;
    case Operation::land:
    case Operation::lor:
    case Operation::lxor:
    case Operation::add:
    case Operation::mul:
        if (op == Operation::land) opstring = "andl";
        else if (op == Operation::lor) opstring = "orl";
        else if (op == Operation::lxor) opstring = "xorl";
        else if (op == Operation::add) opstring = "addl";
        else if (op == Operation::mul) opstring = "imull";
        if (params[1] == params[0])
        {
            o << opstring << " " << cfg->IR_reg_to_asm(params[2]) << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        else if (params[2] == params[0])
        {
            o << opstring << " " << cfg->IR_reg_to_asm(params[1]) << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        else
        {
            o << "movl " << cfg->IR_reg_to_asm(params[1]) << ", " << tmp << "\n";
            o << opstring << " " << cfg->IR_reg_to_asm(params[2]) << ", " << tmp << "\n";
            o << "movl " << tmp << ", " << cfg->IR_reg_to_asm(params[0]) << "\n";
        }
        break;
    case Operation::cnot:
        o << "cmpl $0, " << cfg->IR_reg_to_asm(params[1]) << "\n";
        o << "sete %bl\n";
        o << "movzbl %bl, " << cfg->IR_reg_to_asm(params[0]) << "\n";
        break;
    case Operation::cmp_eq:
    case Operation::cmp_ne:
    case Operation::cmp_lt:
    case Operation::cmp_le:
    case Operation::cmp_gt:
    case Operation::cmp_ge:
        if (op == Operation::cmp_eq) opstring = "sete";
        else if (op == Operation::cmp_ne) opstring = "setne";
        else if (op == Operation::cmp_lt) opstring = "setl";
        else if (op == Operation::cmp_le) opstring = "setle";
        else if (op == Operation::cmp_gt) opstring = "setg";
        else if (op == Operation::cmp_ge) opstring = "setge";
        o << "cmpl " << cfg->IR_reg_to_asm(params[2]) << ", " << cfg->IR_reg_to_asm(params[1]) << "\n";
        o << opstring << " %bl\n";
        o << "movzbl %bl, " << cfg->IR_reg_to_asm(params[0]) << "\n";
        break;
    case Operation::cmp_z:
        o<<"cmpl $0, "<<cfg->IR_reg_to_asm(params[0])<<"\n";
        break;
    case Operation::rmem:
        break;
    case Operation::wmem:
        break;
    case Operation::call:
        for (i=1; i<params.size(); ++i) {
            o<<"movl "<<cfg->IR_reg_to_asm(params[i])<<", "<<REGCALL[i-1]<<"\n";
        }
        o<<"call "<<params[0]<<"\n";
        break;
    case Operation::ret:
        cfg->jump_to_epilogue(o);

        break;
    default:
        break;
    }
}

void CFGx86::jump_to_epilogue(ostream &o){
    o<<"jmp "<<name<<".epilogue \n";
}

void CFGx86::create_jumps(BasicBlock* exit_true,BasicBlock* exit_false,ostream &o){
    if(exit_true!=nullptr && exit_false!=nullptr && (exit_true->label)==(exit_false->label)){
        o<<"jmp "<<exit_true->label<<'\n';
    }else{
        if(exit_true!=nullptr){
            o<<"jne "<<exit_true->label<<'\n';
        }
        if(exit_false!=nullptr){
            o<<"je "<<exit_false->label<<'\n';
        }
    }
    
}
SymbolTable& CFGx86::get_table(){
    return symbols;
}

void CFGx86::add_IRInstr_to_current(IRInstr::Operation op, vector<string> &params)
{
    IRInstr *instr = new IRInstrx86(this, current_bb, op, params,symbols.getCurrentBlock());
    current_bb->add_IRInstr(instr);
}

// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
void CFGx86::gen_asm(ostream &o)
{
    gen_asm_prologue(o);
    vector<BasicBlock *>::iterator it;
    for (it = bbs.begin(); it != bbs.end(); it++)
    {
        (*it)->gen_asm(o);
    }
    gen_asm_epilogue(o);
}

string CFGx86::IR_reg_to_asm(string reg)
{
    if (reg == "!reg")
    {
        return string("%eax");
    }
    else if (symbols.exists(reg)!=-1)
    {
        std::pair<std::string,int> id=make_pair(reg,symbols.exists(reg));
        return string("-") + to_string(symbols.get(id).getOffset()) + string("(%rbp)");
    }
    else
    {
        return string("-") + reg + string("(%rbp)");
    }
}

void CFGx86::gen_asm_prologue(ostream &o)
{
    int i;
    o << ".globl	"<<name<<"\n"
         " "<<name<<": \n"
         " 	pushq  %rbp\n"
         " 	movq   %rsp, %rbp\n";
    symbols.setCurrentBlock(1);
    for (i=0; i<params.size(); ++i) {
        o<<"movl "<<REGCALL[i]<<", "<<IR_reg_to_asm(params[i])<<"\n";
    }
    int offset = get_table().getMaxStackSize();
    if (offset%32!=0) {
        offset += 32 - offset%32;
    }
    o<<"subq $"<<offset<<", %rsp\n";
}

void CFGx86::gen_asm_epilogue(ostream &o)
{
    o << name <<".epilogue:\n"
         " 	leave\n"
         " 	ret\n";
}

CFG* CFGx86Factory::create() {
    CFG* cfg = new CFGx86;
    return cfg;
}