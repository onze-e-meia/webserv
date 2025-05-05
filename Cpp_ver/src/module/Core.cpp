




#include "Core.hpp"

#define CORE_NAME_HANDLER(name) { #name, &Core::name##_Handler }

static const NameHandler	CORE_HANDLER[] = {
	CORE_NAME_HANDLER(root),
	CORE_NAME_HANDLER(index),
	CORE_NAME_HANDLER(autoIndex),
	CORE_NAME_HANDLER(error_page),
	CORE_NAME_HANDLER(client_max_body_size),
	CORE_NAME_HANDLER(allow_methods),
	{ "", NULL },
};

static const DirectiveMap	CORE_MAP = Core::buildMap();

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Core::Core(const Block::type_e &block): _blockType(block) {}

/* Destructor */
Core::~Core(void) {}

/* Member Functions */
const DirectiveMap	Core::buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; CORE_HANDLER[i]._handler != NULL; ++i)
		map[CORE_HANDLER[i]._name] = CORE_HANDLER[i]._handler;
	return (map);
}

const handler_t	Core::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = CORE_MAP.find(name);
	DirectiveConst_it	end = CORE_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

/* Handlers */
void	Core::root_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Core::index_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Core::autoIndex_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Core::error_page_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Core::client_max_body_size_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Core::allow_methods_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}
