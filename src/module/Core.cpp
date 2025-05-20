




#include "Core.hpp"

// #define CORE_NAME_HANDLER(name, nb) { #name, &Core::name##_Handler, nb }

#define CORE_NAME(structName, name, nb) \
	const NameHandler<Core::HandlerPointer> structName(#name, &Core::name##_Handler, nb)

typedef	std::map<std::string, Core::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator				DirectiveConst_it;

CORE_NAME(ROOT, root, 1);
CORE_NAME(INDEX, index, 1);
CORE_NAME(AUTO_INDEX, autoindex, 1);
CORE_NAME(ERRO_PAGE, error_page, 99);
CORE_NAME(MAX_BODY, client_max_body_size, 1);
CORE_NAME(METHODS, allow_methods, 9);
const NameHandler<Core::HandlerPointer> EMPTY("empty", NULL, 0);

static const NameHandler<Core::HandlerPointer>	CORE_HANDLER[] = {
	ROOT, INDEX, AUTO_INDEX, ERRO_PAGE, MAX_BODY, METHODS
};

// static const NameHandler<Core::HandlerPointer>	CORE_HANDLER[] = {
// 	CORE_NAME_HANDLER(root, 1),
// 	CORE_NAME_HANDLER(index, 1),
// 	CORE_NAME_HANDLER(autoindex, 1),
// 	CORE_NAME_HANDLER(error_page, 99),
// 	CORE_NAME_HANDLER(client_max_body_size, 1),
// 	CORE_NAME_HANDLER(allow_methods, 9),
// 	{ "", NULL },
// };

static const DirectiveMap	buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; CORE_HANDLER[i]._handler != NULL; ++i)
		map[CORE_HANDLER[i]._name] = CORE_HANDLER[i]._handler;
	return (map);
}

static const DirectiveMap	CORE_MAP = buildMap();

// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */
bool	Core::validArgs(std::size_t nbArgs, std::size_t maxArgs) {
	return ((nbArgs > 0 && nbArgs <= maxArgs)? true : false );
}


// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Core::Core(const Block::Module &block): _blockType(block) {}

/* Destructor */
Core::~Core(void) {}

/* Member Functions */


/* Handlers */
Core::HandlerPointer	Core::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = CORE_MAP.find(name);
	DirectiveConst_it	end = CORE_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

void	Core::root_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	if (!validArgs(args.size(), ROOT._maxArgs))
		

	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Core::index_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Core::autoindex_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
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
