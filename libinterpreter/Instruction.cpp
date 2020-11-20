/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file Instruction.cpp
 * @author wheatli
 * @date 2018.8.27
 * @record copy from cpp-ethereum
 */
#include "Instruction.h"
#include <map>

namespace bcos
{
namespace eth
{
static const std::map<Instruction, InstructionInfo> c_instructionInfo = {
    //                                                   Args,  Ret,  GasPriceTier
    {Instruction::STOP, {"STOP", 0, 0, Tier::Zero}},
    {Instruction::ADD, {"ADD", 2, 1, Tier::VeryLow}},
    {Instruction::SUB, {"SUB", 2, 1, Tier::VeryLow}},
    {Instruction::MUL, {"MUL", 2, 1, Tier::Low}},
    {Instruction::DIV, {"DIV", 2, 1, Tier::Low}},
    {Instruction::SDIV, {"SDIV", 2, 1, Tier::Low}},
    {Instruction::MOD, {"MOD", 2, 1, Tier::Low}},
    {Instruction::SMOD, {"SMOD", 2, 1, Tier::Low}},
    {Instruction::EXP, {"EXP", 2, 1, Tier::Special}},
    {Instruction::NOT, {"NOT", 1, 1, Tier::VeryLow}},
    {Instruction::LT, {"LT", 2, 1, Tier::VeryLow}},
    {Instruction::GT, {"GT", 2, 1, Tier::VeryLow}},
    {Instruction::SLT, {"SLT", 2, 1, Tier::VeryLow}},
    {Instruction::SGT, {"SGT", 2, 1, Tier::VeryLow}},
    {Instruction::EQ, {"EQ", 2, 1, Tier::VeryLow}},
    {Instruction::ISZERO, {"ISZERO", 1, 1, Tier::VeryLow}},
    {Instruction::AND, {"AND", 2, 1, Tier::VeryLow}},
    {Instruction::OR, {"OR", 2, 1, Tier::VeryLow}},
    {Instruction::XOR, {"XOR", 2, 1, Tier::VeryLow}},
    {Instruction::BYTE, {"BYTE", 2, 1, Tier::VeryLow}},
    {Instruction::SHL, {"SHL", 2, 1, Tier::VeryLow}},
    {Instruction::SHR, {"SHR", 2, 1, Tier::VeryLow}},
    {Instruction::SAR, {"SAR", 2, 1, Tier::VeryLow}},
    {Instruction::ADDMOD, {"ADDMOD", 3, 1, Tier::Mid}},
    {Instruction::MULMOD, {"MULMOD", 3, 1, Tier::Mid}},
    {Instruction::SIGNEXTEND, {"SIGNEXTEND", 2, 1, Tier::Low}},
    {Instruction::SHA3, {"SHA3", 2, 1, Tier::Special}},
    {Instruction::ADDRESS, {"ADDRESS", 0, 1, Tier::Base}},
    {Instruction::BALANCE, {"BALANCE", 1, 1, Tier::Special}},
    {Instruction::ORIGIN, {"ORIGIN", 0, 1, Tier::Base}},
    {Instruction::CALLER, {"CALLER", 0, 1, Tier::Base}},
    {Instruction::CALLVALUE, {"CALLVALUE", 0, 1, Tier::Base}},
    {Instruction::CALLDATALOAD, {"CALLDATALOAD", 1, 1, Tier::VeryLow}},
    {Instruction::CALLDATASIZE, {"CALLDATASIZE", 0, 1, Tier::Base}},
    {Instruction::CALLDATACOPY, {"CALLDATACOPY", 3, 0, Tier::VeryLow}},
    {Instruction::CODESIZE, {"CODESIZE", 0, 1, Tier::Base}},
    {Instruction::CODECOPY, {"CODECOPY", 3, 0, Tier::VeryLow}},
    {Instruction::GASPRICE, {"GASPRICE", 0, 1, Tier::Base}},
    {Instruction::EXTCODESIZE, {"EXTCODESIZE", 1, 1, Tier::Special}},
    {Instruction::EXTCODECOPY, {"EXTCODECOPY", 4, 0, Tier::Special}},
    {Instruction::RETURNDATASIZE, {"RETURNDATASIZE", 0, 1, Tier::Base}},
    {Instruction::RETURNDATACOPY, {"RETURNDATACOPY", 3, 0, Tier::VeryLow}},
    {Instruction::EXTCODEHASH, {"EXTCODEHASH", 1, 1, Tier::Special}},
    {Instruction::BLOCKHASH, {"BLOCKHASH", 1, 1, Tier::Special}},
    {Instruction::COINBASE, {"COINBASE", 0, 1, Tier::Base}},
    {Instruction::TIMESTAMP, {"TIMESTAMP", 0, 1, Tier::Base}},
    {Instruction::NUMBER, {"NUMBER", 0, 1, Tier::Base}},
    {Instruction::DIFFICULTY, {"DIFFICULTY", 0, 1, Tier::Base}},
    {Instruction::GASLIMIT, {"GASLIMIT", 0, 1, Tier::Base}},
    {Instruction::POP, {"POP", 1, 0, Tier::Base}},
    {Instruction::MLOAD, {"MLOAD", 1, 1, Tier::VeryLow}},
    {Instruction::MSTORE, {"MSTORE", 2, 0, Tier::VeryLow}},
    {Instruction::MSTORE8, {"MSTORE8", 2, 0, Tier::VeryLow}},
    {Instruction::SLOAD, {"SLOAD", 1, 1, Tier::Special}},
    {Instruction::SSTORE, {"SSTORE", 2, 0, Tier::Special}},
    {Instruction::JUMP, {"JUMP", 1, 0, Tier::Mid}},
    {Instruction::JUMPI, {"JUMPI", 2, 0, Tier::High}},
    {Instruction::PC, {"PC", 0, 1, Tier::Base}},
    {Instruction::MSIZE, {"MSIZE", 0, 1, Tier::Base}},
    {Instruction::GAS, {"GAS", 0, 1, Tier::Base}},
    {Instruction::JUMPDEST, {"JUMPDEST", 0, 0, Tier::Special}},
    {Instruction::PUSH1, {"PUSH1", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH2, {"PUSH2", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH3, {"PUSH3", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH4, {"PUSH4", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH5, {"PUSH5", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH6, {"PUSH6", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH7, {"PUSH7", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH8, {"PUSH8", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH9, {"PUSH9", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH10, {"PUSH10", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH11, {"PUSH11", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH12, {"PUSH12", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH13, {"PUSH13", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH14, {"PUSH14", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH15, {"PUSH15", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH16, {"PUSH16", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH17, {"PUSH17", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH18, {"PUSH18", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH19, {"PUSH19", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH20, {"PUSH20", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH21, {"PUSH21", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH22, {"PUSH22", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH23, {"PUSH23", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH24, {"PUSH24", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH25, {"PUSH25", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH26, {"PUSH26", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH27, {"PUSH27", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH28, {"PUSH28", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH29, {"PUSH29", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH30, {"PUSH30", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH31, {"PUSH31", 0, 1, Tier::VeryLow}},
    {Instruction::PUSH32, {"PUSH32", 0, 1, Tier::VeryLow}},
    {Instruction::DUP1, {"DUP1", 1, 2, Tier::VeryLow}},
    {Instruction::DUP2, {"DUP2", 2, 3, Tier::VeryLow}},
    {Instruction::DUP3, {"DUP3", 3, 4, Tier::VeryLow}},
    {Instruction::DUP4, {"DUP4", 4, 5, Tier::VeryLow}},
    {Instruction::DUP5, {"DUP5", 5, 6, Tier::VeryLow}},
    {Instruction::DUP6, {"DUP6", 6, 7, Tier::VeryLow}},
    {Instruction::DUP7, {"DUP7", 7, 8, Tier::VeryLow}},
    {Instruction::DUP8, {"DUP8", 8, 9, Tier::VeryLow}},
    {Instruction::DUP9, {"DUP9", 9, 10, Tier::VeryLow}},
    {Instruction::DUP10, {"DUP10", 10, 11, Tier::VeryLow}},
    {Instruction::DUP11, {"DUP11", 11, 12, Tier::VeryLow}},
    {Instruction::DUP12, {"DUP12", 12, 13, Tier::VeryLow}},
    {Instruction::DUP13, {"DUP13", 13, 14, Tier::VeryLow}},
    {Instruction::DUP14, {"DUP14", 14, 15, Tier::VeryLow}},
    {Instruction::DUP15, {"DUP15", 15, 16, Tier::VeryLow}},
    {Instruction::DUP16, {"DUP16", 16, 17, Tier::VeryLow}},
    {Instruction::SWAP1, {"SWAP1", 2, 2, Tier::VeryLow}},
    {Instruction::SWAP2, {"SWAP2", 3, 3, Tier::VeryLow}},
    {Instruction::SWAP3, {"SWAP3", 4, 4, Tier::VeryLow}},
    {Instruction::SWAP4, {"SWAP4", 5, 5, Tier::VeryLow}},
    {Instruction::SWAP5, {"SWAP5", 6, 6, Tier::VeryLow}},
    {Instruction::SWAP6, {"SWAP6", 7, 7, Tier::VeryLow}},
    {Instruction::SWAP7, {"SWAP7", 8, 8, Tier::VeryLow}},
    {Instruction::SWAP8, {"SWAP8", 9, 9, Tier::VeryLow}},
    {Instruction::SWAP9, {"SWAP9", 10, 10, Tier::VeryLow}},
    {Instruction::SWAP10, {"SWAP10", 11, 11, Tier::VeryLow}},
    {Instruction::SWAP11, {"SWAP11", 12, 12, Tier::VeryLow}},
    {Instruction::SWAP12, {"SWAP12", 13, 13, Tier::VeryLow}},
    {Instruction::SWAP13, {"SWAP13", 14, 14, Tier::VeryLow}},
    {Instruction::SWAP14, {"SWAP14", 15, 15, Tier::VeryLow}},
    {Instruction::SWAP15, {"SWAP15", 16, 16, Tier::VeryLow}},
    {Instruction::SWAP16, {"SWAP16", 17, 17, Tier::VeryLow}},
    {Instruction::LOG0, {"LOG0", 2, 0, Tier::Special}},
    {Instruction::LOG1, {"LOG1", 3, 0, Tier::Special}},
    {Instruction::LOG2, {"LOG2", 4, 0, Tier::Special}},
    {Instruction::LOG3, {"LOG3", 5, 0, Tier::Special}},
    {Instruction::LOG4, {"LOG4", 6, 0, Tier::Special}},

    {Instruction::JUMPTO, {"JUMPTO", 1, 0, Tier::VeryLow}},
    {Instruction::JUMPIF, {"JUMPIF", 2, 0, Tier::Low}},
    {Instruction::JUMPV, {"JUMPV", 1, 0, Tier::Mid}},
    {Instruction::JUMPSUB, {"JUMPSUB", 1, 0, Tier::Low}},
    {Instruction::JUMPSUBV, {"JUMPSUBV", 1, 0, Tier::Mid}},
    {Instruction::BEGINSUB, {"BEGINSUB", 0, 0, Tier::Special}},
    {Instruction::BEGINDATA, {"BEGINDATA", 0, 0, Tier::Special}},
    {Instruction::RETURNSUB, {"RETURNSUB", 1, 0, Tier::Mid}},
    {Instruction::PUTLOCAL, {"PUTLOCAL", 1, 0, Tier::VeryLow}},
    {Instruction::GETLOCAL, {"GETLOCAL", 0, 1, Tier::VeryLow}},

    {Instruction::XADD, {"XADD", 0, 0, Tier::Special}},
    {Instruction::XMUL, {"XMUL", 2, 1, Tier::Special}},
    {Instruction::XSUB, {"XSUB", 2, 1, Tier::Special}},
    {Instruction::XDIV, {"XDIV", 2, 1, Tier::Special}},
    {Instruction::XSDIV, {"XSDIV", 2, 1, Tier::Special}},
    {Instruction::XMOD, {"XMOD", 2, 1, Tier::Special}},
    {Instruction::XSMOD, {"XSMOD", 2, 1, Tier::Special}},
    {Instruction::XLT, {"XLT", 2, 1, Tier::Special}},
    {Instruction::XGT, {"XGT", 2, 1, Tier::Special}},
    {Instruction::XSLT, {"XSLT", 2, 1, Tier::Special}},
    {Instruction::XSGT, {"XSGT", 2, 1, Tier::Special}},
    {Instruction::XEQ, {"XEQ", 2, 1, Tier::Special}},
    {Instruction::XISZERO, {"XISZERO", 2, 1, Tier::Special}},
    {Instruction::XAND, {"XAND", 1, 1, Tier::Special}},
    {Instruction::XOOR, {"XOOR", 2, 1, Tier::Special}},
    {Instruction::XXOR, {"XXOR", 2, 1, Tier::Special}},
    {Instruction::XNOT, {"XNOT", 2, 1, Tier::Special}},
    {Instruction::XSHL, {"XSHL", 2, 1, Tier::Special}},
    {Instruction::XSHR, {"XSHR", 2, 1, Tier::Special}},
    {Instruction::XSAR, {"XSAR", 2, 1, Tier::Special}},
    {Instruction::XROL, {"XROL", 2, 1, Tier::Special}},
    {Instruction::XROR, {"XROR", 2, 1, Tier::Special}},
    {Instruction::XPUSH, {"XPUSH", 1, 1, Tier::VeryLow}},
    {Instruction::XMLOAD, {"XMLOAD", 1, 1, Tier::VeryLow}},
    {Instruction::XMSTORE, {"XMSTORE", 2, 0, Tier::VeryLow}},
    {Instruction::XSLOAD, {"XSLOAD", 1, 1, Tier::Special}},
    {Instruction::XSSTORE, {"XSSTORE", 2, 0, Tier::Special}},
    {Instruction::XVTOWIDE, {"XVTOWIDE", 1, 1, Tier::VeryLow}},
    {Instruction::XWIDETOV, {"XWIDETOV", 1, 1, Tier::VeryLow}},
    {Instruction::XPUT, {"XPUT", 3, 1, Tier::Special}},
    {Instruction::XGET, {"XGET", 2, 1, Tier::Special}},
    {Instruction::XSWIZZLE, {"XSWIZZLE", 2, 1, Tier::Special}},
    {Instruction::XSHUFFLE, {"XSHUFFLE", 3, 1, Tier::Special}},
    {Instruction::CREATE, {"CREATE", 3, 1, Tier::Special}},
    {Instruction::CREATE2, {"CREATE2", 4, 1, Tier::Special}},
    {Instruction::CALL, {"CALL", 7, 1, Tier::Special}},
    {Instruction::CALLCODE, {"CALLCODE", 7, 1, Tier::Special}},
    {Instruction::RETURN, {"RETURN", 2, 0, Tier::Zero}},
    {Instruction::STATICCALL, {"STATICCALL", 6, 1, Tier::Special}},
    {Instruction::DELEGATECALL, {"DELEGATECALL", 6, 1, Tier::Special}},
    {Instruction::REVERT, {"REVERT", 2, 0, Tier::Special}},
    {Instruction::INVALID, {"INVALID", 0, 0, Tier::Zero}},
    {Instruction::SUICIDE, {"SUICIDE", 1, 0, Tier::Special}},

    // these are generated by the interpreter - should never be in user code
    {Instruction::PUSHC, {"PUSHC", 0, 1, Tier::VeryLow}},
    {Instruction::JUMPC, {"JUMPC", 1, 0, Tier::Mid}},
    {Instruction::JUMPCI, {"JUMPCI", 2, 0, Tier::High}},
};

InstructionInfo instructionInfo(Instruction _inst)
{
    auto it = c_instructionInfo.find(_inst);
    if (it != c_instructionInfo.end())
        return it->second;
    return InstructionInfo{"", 0, 0, Tier::Invalid};
}


}  // namespace eth
}  // namespace bcos
