

#include "module.hpp"
#include "color.hpp"

// Need this?
// Utility: convert flags to readable string
// std::string	flagToString(const BlockType &flags) {
// 	std::string out;
// 	if (flags.test(Module::HTTP))     out += "HTTP ";
// 	if (flags.test(Module::SERVER))   out += "SERVER ";
// 	if (flags.test(Module::LOCATION)) out += "LOCATION ";
// 	if (flags.test(Module::CORE))     out += "CORE ";
// 	if (!out.empty()) out.erase(out.size() - 1);
// 	return out;
// }

const Block::SpecMap	Block::MAP = Block::build();

// Block::Spec::Spec(const std::string &name, Module::module_e module):
// 	_name(name), _type(makeBlockFlags(module)) {}

// const BlockType	Block::Spec::makeBlockFlags(Module::module_e module) {
// 	BlockType type;
// 	type.set(Module::CORE);
// 	type.set(module);
// 	return type;
// }

const Block::SpecMap	Block::build(void) {
	std::cout << ">>>>>>>>>>>>>>>>>>>> BUILD MAP <<<<<<<<<<<<<<<< " << ENDL;

	SpecMap	map;
	for (size_t i = 0; SPECS[i]._type != 0; ++i)
		map[SPECS[i]._name] = SPECS[i]._type;
	return (map);
}

BlockType	Block::getType(std::string name) {
	// std::cout << "NAME: " << name << ENDL;
	// std::cout << "ON GET TYPE: " << MAP.find(Name::LOCATION)->first << ENDL;
	// std::cout << "ON GET TYPE: " << MAP.find(Name::SERVER)->first << ENDL;
	// std::cout << "ON GET TYPE: " << MAP.find(Name::HTTP)->first << ENDL;

	SpecConst_it	it = MAP.find(name);
	SpecConst_it	end = MAP.end();
	if (it == end) {
		std::ostringstream oss;
		oss << RED " >>>>>>>>>> Unknown NEW block: " << name << RENDL;
		throw (std::runtime_error(oss.str()));
	}
	return (it->second);
}

// BlockType	lixo0 = Block::SPECS[Module::EMPTY]._type;
// BlockType	lixo1 = BlockType().set(Module::EMPTY);
// BlockType	lixo2 = Block::getType(Name::EMPTY);
// BlockType	lixo3 = Block::MAP.find(Name::HTTP)->second;
