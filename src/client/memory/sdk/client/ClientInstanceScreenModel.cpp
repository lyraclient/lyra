#include "./ClientInstanceScreenModel.hpp"
#include "../../patcher.hpp"

void ClientInstanceScreenModel::executeCommand_hk(const std::string& command_line) {
	selaura::call_fn<&ClientInstanceScreenModel::executeCommand_hk>(this, command_line);
}
