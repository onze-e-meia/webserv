

#include "module.hpp"
#include "Core.hpp"

Core::Core(const std::string &name): _blockType(Block::getType(name)) {}

Core::Core(const BlockType &block): _blockType(block) {}

Core::~Core() {}
