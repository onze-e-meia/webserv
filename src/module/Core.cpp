




#include "Core.hpp"

#define CORE_NAME_HANDLER(name) { #name, &Core::name##_Handler }

typedef	std::map<std::string, Core::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator				DirectiveConst_it;

static const NameHandler<Core::HandlerPointer>	CORE_HANDLER[] = {
	{ "root", &Core::root_Handler },
	CORE_NAME_HANDLER(root),
	CORE_NAME_HANDLER(index),
	CORE_NAME_HANDLER(autoIndex),
	CORE_NAME_HANDLER(error_page),
	CORE_NAME_HANDLER(client_max_body_size),
	CORE_NAME_HANDLER(allow_methods),
	{ "", NULL },
};

static const DirectiveMap	buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; CORE_HANDLER[i]._handler != NULL; ++i)
		map[CORE_HANDLER[i]._name] = CORE_HANDLER[i]._handler;
	return (map);
}

static const DirectiveMap	CORE_MAP = buildMap();

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Core::Core(const Block::type_e &block): _blockType(block) {}

/* Destructor */
Core::~Core(void) {}

/* Member Functions */
Core::HandlerPointer	Core::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = CORE_MAP.find(name);
	DirectiveConst_it	end = CORE_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

/* Handlers */
void	Core::root_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Core::index_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Core::autoIndex_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Core::error_page_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Core::client_max_body_size_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Core::allow_methods_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}
